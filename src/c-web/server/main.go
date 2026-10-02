package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
)

// TODO cache
func renderPage(w http.ResponseWriter) {
	w.Header().Set("Content-Type", "text/html")
	bytes, err := os.ReadFile("./index.html")
	if err != nil {
		panic(err)
	}
	_, err = w.Write(bytes)
	if err == io.EOF {
		return
	} else if err != nil {
		w.WriteHeader(500)
		return
	}
}

func main() {
	const addr = "127.0.0.1:8080"
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if r.URL.Path != "/" {
			w.WriteHeader(404)
			return
		}
		fmt.Fprintf(os.Stderr, "Received request to %s from %s\n", r.URL.Path, r.RemoteAddr)
		renderPage(w)
	})

	fmt.Printf("Listening at %s\n", addr)
	err := http.ListenAndServe(addr, nil)
	if err != nil {
		panic(err)
	}
}
