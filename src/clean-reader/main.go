package main

import (
	"bytes"
	"fmt"
	"io"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func write(w io.Writer, first string, cb func(), second string) {
	_, err := w.Write([]byte(first + "\n"))
	if err != nil {
		panic(err)
	}

	cb()

	_, err = w.Write([]byte(second + "\n"))
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
	fmt.Printf("Getting %s...", url)
	res, err := http.Get(url)
	fmt.Println("")
	if err != nil {
		panic(err)
	}

	if res.StatusCode < 200 || res.StatusCode >= 300 {
		panic(fmt.Sprintf("Bad response code: %d", res.StatusCode))
	}

	root := parse(res.Body)
	buffer := bytes.NewBuffer([]byte{})
	write(buffer, `<html>
	<head>
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/sakura.css/css/sakura.css" type="text/css">
	</head>
	<body>`, func() {
		html.Render(buffer, root)
	}, `
	</body>
</html>`)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		_, err := w.Write(buffer.Bytes())
		if err != nil {
			panic(err)
		}
	})

	const addr = "0.0.0.0:8080"
	fmt.Printf("Listening to connections at %s\n", addr)
	http.ListenAndServe(addr, nil)
}
