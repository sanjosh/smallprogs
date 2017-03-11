package main

import (
	"bufio"
	"fmt"
	"net"
)

func main() {
	fmt.Println("starting server")

	ln, _ := net.Listen("tcp", ":9000")

	conn, _ := ln.Accept()

	count := 0

	for {
		message, err := bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			break
		}
		fmt.Print("message:", string(message))
		count++
		_, err = conn.Write([]byte("got \n"))
		if err != nil {
			break
		}
	}
	fmt.Println("wrote msgs=", count)
}
