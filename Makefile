all: TCPEchoClient TCPEchoServer

TCPEchoClient: TCPEchoClient.c DieWithError.c
	gcc -Wall -o TCPEchoClient TCPEchoClient.c DieWithError.c

TCPEchoServer: TCPEchoServer.c HandleTCPClient.c DieWithError.c
	gcc -Wall -o TCPEchoServer TCPEchoServer.c HandleTCPClient.c DieWithError.c

.PHONY: clean
clean:
	rm -f TCPEchoClient TCPEchoServer a.out
