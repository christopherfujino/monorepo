package main

import (
	"bytes"
	"fmt"
	"io"
	"net/http"
	"os"
	"runtime/debug"

	"golang.org/x/net/html"
)

func write(w io.Writer, contents string) {
	_, err := w.Write([]byte(contents + "\n"))
	if err != nil {
		panic(err)
	}
}

func fetchPage(url string) (*bytes.Buffer, error) {
	res, err := http.Get(url)
	fmt.Println("")
	if err != nil {
		return nil, err
	}

	if res.StatusCode < 200 || res.StatusCode >= 300 {
		return nil, fmt.Errorf("Bad response code: %d", res.StatusCode)
	}

	roots := parse(res.Body)
	err = res.Body.Close()
	if err != nil {
		return nil, err
	}
	buffer := bytes.NewBuffer([]byte{})
	write(buffer, fmt.Sprintf(`
<!DOCTYPE html>
<html lang="en">
	<head>
		<link rel="stylesheet" href="style.css" />
		<title>%s</title>
	</head>`, roots.Title))
	html.Render(buffer, roots.Body)
	write(buffer, `
</html>`)

	return buffer, nil
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		var handleError = func(code int, err error) {
			var msg = err.Error()
			http.Error(w, msg, code)
			fmt.Fprintf(os.Stderr, "%s\n", msg)
			debug.PrintStack()
		}
		var requestPath = r.URL.Path
		switch requestPath {
		case "/":
			fallthrough
		case "/index.html":
			queries := r.URL.Query()
			url := queries.Get("q")
			if url == "" {
				handleError(404, fmt.Errorf("no query in: %s\n", r.URL))
				return
			}

			buffer, err := fetchPage(url)
			if err != nil {
				handleError(404, err)
				return
			}

			_, err = w.Write(buffer.Bytes())
			if err != nil {
				handleError(500, err)
				return
			}
		case "/style.css":
			w.Header().Set("Content-Type", "text/css")
			css, err := os.Open("style.css")
			if err != nil {
				handleError(500, err)
				return
			}
			_, err = io.Copy(w, css)
			if err != nil {
				handleError(500, err)
				return
			}
			err = css.Close()
			if err != nil {
				handleError(500, err)
				return
			}
		default:
			http.Error(w, fmt.Sprintf("404: Page not found: %s", requestPath), 404)
			fmt.Fprintf(os.Stderr, "404 %s\n", r.URL.String())
		}
	})

	const addr = "0.0.0.0:8080"
	fmt.Printf("Listening to connections at %s\n", addr)
	http.ListenAndServe(addr, nil)
}
