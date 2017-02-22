// sample web server
package main

import (
    "crypto/md5"
    "fmt"
    "html/template"
    "io"
    "time"
    "log"
    "net/http"
    "strconv"
)

func helloHandler(w http.ResponseWriter, req *http.Request) {
    io.WriteString(w, "hello, world!\n")
}

func whoHandler(w http.ResponseWriter, req *http.Request) {
    cookie, _ := req.Cookie("username")
    if cookie != nil {
        fmt.Println(cookie, " is logged in")
    } else {
        fmt.Println("no one logged in")
    }
}

func loginHandler(w http.ResponseWriter, req *http.Request) {
    fmt.Println("method:", req.Method)
    if req.Method == "GET" {
        // set hidden field to check duplicate submission
        // take hash(current_time)
        crutime := time.Now().Unix()
        h := md5.New()
        io.WriteString(h, strconv.FormatInt(crutime, 10))
        hidden_token := fmt.Sprintf("%x", h.Sum(nil))
        // post the form
        t, _ := template.ParseFiles("login.gtpl")
        t.Execute(w, hidden_token)
    } else if req.Method == "POST" {
        // interpret the input fields
        req.ParseForm()

        // check hidden token
        hidden_token := req.Form.Get("token")
        if hidden_token != "" {
           fmt.Println("hidden token: ", hidden_token)
        } else {
        }

        username := template.HTMLEscapeString(req.Form.Get("username"))
        password := template.HTMLEscapeString(req.Form.Get("password"))
        gender := template.HTMLEscapeString(req.Form.Get("gender"))

        fmt.Println("username:", username)
        fmt.Println("password:", password)
        fmt.Println("gender:", gender)

        // set cookie
        expiration := time.Now().Add(60 * time.Second)
        new_cookie := http.Cookie{Name: "username", Value: username, Expires: expiration}
        http.SetCookie(w, &new_cookie)
    } else {
    }
}

func main() {
    http.HandleFunc("/hello", helloHandler)
    http.HandleFunc("/login", loginHandler)
    http.HandleFunc("/who", whoHandler)
    err := http.ListenAndServe(":12343", nil)
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
