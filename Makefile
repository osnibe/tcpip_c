all: TCPEchoClient TCPEchoServer

TCPEchoClient: TCPEchoClinet.c DieWithError.c
	gcc -Wall -o TCPEchoClinet TCPEchoClinet.c DieWithError.c

TCPEchoServer: TCPEchoServer.c HandleTCPClient.c DieWithError.c
	gcc -Wall -o TCPEchoServer TCPEchoServer.c HandleTCPClient.c DieWithError.c

.PHONY: clean
clean:
	rm -f TCPEchoClinet TCPEchoServer a.out
