package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"tserver"
)

func main() {
	s := tserver.NewServer("127.0.0.1:9000")

	signal_channel := make(chan os.Signal, 1)
	signal.Notify(signal_channel, os.Interrupt, syscall.SIGTERM)

	go s.Listen()

	fmt.Println(<-signal_channel)
	s.Stop()
}
