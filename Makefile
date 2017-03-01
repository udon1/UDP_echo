all: udpserver udpclient

udpserver: udpserver.c
	gcc -o udpserver udpserver.c

udpclient: udpclient.c
	gcc -o udpclient udpclient.c
