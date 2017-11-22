package main

import (
	"bufio"
	"fmt"
	"io"
	"math/rand"
	"net"
	"os"
	"strings"
	"time"
)

// NOTE:
//   please add a '\n' at the end of a request.

func main() {
	rand.Seed(0)

	serveTcp()
}

func serveTcp() {
	listener, err := net.Listen("tcp", ":8000")
	if err != nil {
		panic(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Failed to accept a connection. ", err)
			continue
		}
		go handle(conn)
	}
}

func handle(conn net.Conn) {
	defer conn.Close()

	request, err := bufio.NewReader(conn).ReadString('\n')
	if err != nil && err != io.EOF {
		handleError("Failed to read a request.", err)
	}
	request = strings.TrimSpace(request)

	// Set the amount of computational work and the I/O latency of this task
	var amount int
	var latencyMs int
	switch request {
	case "cpubound":
		amount = randInt(19000000, 20000000)
		latencyMs = randInt(0, 1)
	case "balanced":
		amount = randInt(1900000, 2000000)
		latencyMs = randInt(10, 12)
	case "iobound":
		amount = randInt(190, 200)
		latencyMs = randInt(60, 80)
	default:
		handleError("Invalid Request!", nil)
		return
	}

	// Make fake latency
	time.Sleep(time.Duration(latencyMs) * time.Millisecond)

	fmt.Fprintln(conn, amount)
}

func handleError(msg string, err error) {
	fmt.Println(msg, err)
	os.Exit(1)
}

func randInt(min int, max int) int {
	return min + rand.Intn(max-min) + 1
}
