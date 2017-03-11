package tserver

import (
	"bufio"
	"log"
	"net"
	"time"
)

type ClientCtx struct {
	conn   net.Conn
	server *Server
}

func (c *ClientCtx) Listen() {
	var err error
	defer c.server.waitGroup.Done()
	defer c.server.OnClientClose(c, err)
	defer c.conn.Close()

	reader := bufio.NewReader(c.conn)

	for {
		select {
		case <-c.server.exit_chan:
			log.Println("disconnecting ", c.conn.RemoteAddr())
			return
		default:
		}
		c.conn.SetDeadline(time.Now().Add(1e9))
		_, err = reader.ReadString('\n')
		if err != nil {
			opErr, ok := err.(*net.OpError)
			if ok && opErr.Timeout() {
				continue
			}
			log.Println(err)
			return
		} else {
			_, err = c.conn.Write([]byte("got \n"))
			if err != nil {
				log.Println(err)
				return
			}
		}
	}
}

func (c *ClientCtx) Close() error {
	return c.conn.Close()
}

func NewClientCtx(conn net.Conn, s *Server) *ClientCtx {
	client := &ClientCtx{
		conn:   conn,
		server: s,
	}
	return client
}
