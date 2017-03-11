package tserver

import (
	_ "bufio"
	"log"
	"net"
	"sync"
	"time"
)

type Server struct {
	clients   []*ClientCtx
	address   string
	exit_chan chan bool
	waitGroup *sync.WaitGroup
}

func (s *Server) Listen() {
	defer s.waitGroup.Done()

	laddr, err := net.ResolveTCPAddr("tcp", s.address)
	if err != nil {
		log.Fatal(err)
	}
	listener, err := net.ListenTCP("tcp", laddr)
	if err != nil {
		log.Fatal("error starting server at ", s.address)
	}
	defer listener.Close()
	log.Println("Listening on ", listener.Addr())

	for {
		select {
		case <-s.exit_chan:
			log.Println("stopping listener ", listener.Addr())
			return
		default:
		}
		listener.SetDeadline(time.Now().Add(1e9))
		conn, err := listener.AcceptTCP()
		if err != nil {
			opErr, ok := err.(*net.OpError)
			if ok && opErr.Timeout() {
				continue
			}
			log.Print("accept failed with ", err)
		} else {
			log.Print("got connection from ", conn.RemoteAddr())
			client := NewClientCtx(conn, s)
			// add new client to clients array
			s.clients = append(s.clients, client)
			s.waitGroup.Add(1)
			go client.Listen()
		}
	}
}

// called when client connection is closed
func (s *Server) OnClientClose(c *ClientCtx, err error) {
	// delete client from list of clients
	isFound := false
	for idx := range s.clients {
		if s.clients[idx] == c {
			// swap elem with last
			s.clients[len(s.clients)-1], s.clients[idx] = s.clients[idx],
				s.clients[len(s.clients)-1]
			// truncate slice
			s.clients = s.clients[:len(s.clients)-1]
			isFound = true
			log.Println("deleted client from registry")
			break
		}
	}
	if isFound != true {
		log.Println("failed to find client in registered list")
	}
}

func (s *Server) Stop() {
	close(s.exit_chan)
	s.waitGroup.Wait()
}

// Return new instance of server
func NewServer(address string) *Server {
	server := &Server{
		address:   address,
		exit_chan: make(chan bool),
		waitGroup: &sync.WaitGroup{},
		clients:   make([]*ClientCtx, 0, 10),
	}
	server.waitGroup.Add(1)
	return server
}
