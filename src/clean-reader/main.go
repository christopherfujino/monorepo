package main

import (
	"bytes"
	"fmt"
	"io"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func write(w io.Writer, contents string) {
	_, err := w.Write([]byte(contents + "\n"))
	if err != nil {
		panic(err)
	}
}

func main() {
	args := os.Args[1:]
	if len(args) != 1 {
		panic("Usage")
	}
	url := args[0]
	fmt.Printf("GET %s", url)
	res, err := http.Get(url)
	fmt.Println("")
	if err != nil {
		panic(err)
	}

	if res.StatusCode < 200 || res.StatusCode >= 300 {
		panic(fmt.Sprintf("Bad response code: %d", res.StatusCode))
	}

	roots := parse(res.Body)
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

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		switch r.URL.String() {
		case "/":
			fallthrough
		case "/index.html":
			_, err := w.Write(buffer.Bytes())
			if err != nil {
				panic(err)
			}
		case "/style.css":
			w.Header().Set("Content-Type", "text/css")
			css, err := os.Open("style.css")
			if err != nil {
				panic(err)
			}
			_, err = io.Copy(w, css)
			if err != nil {
				panic(err)
			}
			err = css.Close()
			if err != nil {
				panic(err)
			}
		default:
			http.Error(w, "Flooboo", 404)
			fmt.Fprintf(os.Stderr, "404 %s\n", r.URL.String())
		}
	})

	const addr = "0.0.0.0:8080"
	fmt.Printf("Listening to connections at %s\n", addr)
	http.ListenAndServe(addr, nil)
}
