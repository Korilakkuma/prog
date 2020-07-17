package main

import (
	"encoding/json"
	"io"
	"net/http"
)

func uploadHandler(w http.ResponseWriter, r *http.Request) {
	reader, err := r.MultipartReader()

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	h := w.Header()

	h.Set("Access-Control-Allow-Origin", "*")
	h.Set("Content-Type", "application/json")

	for {
		part, err := reader.NextPart()

		if err == io.EOF {
			break
		}

		if part.FileName() == "" {
			continue
		}

		res, err := json.Marshal(part)

		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}

		w.Write(res)
	}
}

func main() {
	http.HandleFunc("/upload", uploadHandler)
	http.ListenAndServe(":8080", nil)
}
