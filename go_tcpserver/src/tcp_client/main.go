package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"net"
	"os"
	"os/signal"
	"syscall"
	"time"
)

const letters = "abcdefghijklmopqrts"

func main() {

	count := 0
	rand.Seed(time.Now().Unix())
	conn, _ := net.Dial("tcp", "127.0.0.1:9000")

	signal_chan := make(chan os.Signal, 1)
	signal.Notify(signal_chan, os.Interrupt, syscall.SIGTERM)

	//reader := bufio.NewReader(os.Stdin)
	//reader.ReadString('\n')
	go func() {
		chanReader := bufio.NewReader(conn)
		for {
			text := make([]byte, 256)
			for idx := range text {
				text[idx] = letters[rand.Int63()%int64(len(letters))]
			}
			textString := string(text[:256])
			fmt.Fprintf(conn, textString+"\n")
			chanReader.ReadString('\n')
			//fmt.Print("response: " + message)
			count++
		}
	}()

	fmt.Println(<-signal_chan)
	conn.Close()
	fmt.Println(os.Getpid(), " did ", count)
}
