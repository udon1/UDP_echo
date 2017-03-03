#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sysexits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// network
#include <arpa/inet.h>

#define BUF 512

struct echo_msg {
	unsigned short seq;
	unsigned short reserve;
	char msg[32];
};

// int
// get_info(char *hostnum, char *portnum, struct
// 		sockaddr_storage *saddr, socklen_t *saddr_len)
// {
// 	struct addrinfo hints, *res0;
// 	int errcode;
// 
// 	/*hintsをゼロクリア*/
// 
// 	(void) memset(&hints, 0, sizeof(hints));
// 	hints.ai_family = AF_INET4;
// 	hints.ai_socktype = SOCK_DGRAM;
// 	//hints.ai_flags = AI_PASSIVE;
// 	/*アドレス情報の決定*/
// 	if((errcode = getaddrinfo(hostnum, portnum, &hints,
// 					&res0)) != 0) {
// 		perror("getaddrinfo");
// 		return (-1);
// 	}
// 	(void) memcpy(saddr, res0->ai_addr, res0->ai_addrlen);
// 	*saddr_len = res0->ai_addrlen;
// 	freeaddrinfo(res0);
// 	return 0;
// }

// void send_recv(int soc, char* hostnun, char* portnum)
// {
// 	struct echo_msg em;
// 	// struct timeval timeout;
// 	struct sockaddr_storage from, to;
// 	int end, width;
// 	ssize_t len;
// 	socklen_t fromlen, tolen;
// 	int seq;
// 	char rbuf[BUF];
// 	char sbuf[BUF];
// 	struct sockaddr_in myskt;
// 	struct sockaddr_in skt;
// 
// 	for(seq = 0;;) {
// 		printf("input: ");
// 		scanf("%s", em.msg);
// 		if((sendto(s, sbuf, datalen, 0, 
// 						(struct sockaddr *)&skt, sizeof skt)) == -1) {
// 			perror("sendto");
// 			return (-1);
// 		}
// 		if((recvfrom(s, rbuf, sizeof rbuf, 0,
// 						(struct sockaddr *)&skt, sizeof skt)) == -1) {
// 			perror("recvfrom");
// 			return (-1);
// 		}
// 		//if (seq >= 10) {
// 		//break;
// 		//}
// 		Close();
// 		exit();
// 		/*標準入力待ち*/
// 		/*送信先情報の取得*/
// 		//sendto(acc, ..)
// 		//recvfrom(acc, ..)
// 	}
// }

int main (int argc, char *argv[]) {
	/*変数宣言*/
	struct echo_msg em;
	// struct timeval timeout;
	//struct sockaddr_storage from;//, to;
	//int end, width;
	//ssize_t len;
	socklen_t tolen;//fromlen, tolen;
	//int seq;
	//char rbuf[BUF];
	//char sbuf[BUF];
	//struct sockaddr_in myskt;
	struct sockaddr_in skt;
	int soc;
	in_port_t port;
	struct in_addr ipaddr;

	if (argc != 3) {
		fprintf(stderr, "Usage: ./udpclient [localhost] [port]\n");
		exit(1);
	}
	
	inet_aton(argv[1], &ipaddr);	
	port = atoi(argv[2]);
	em.seq = 0;

	/*ソケット生成*/
	if((soc = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return (EX_UNAVAILABLE);
	}
	
	memset(&skt, 0, sizeof(skt));
	skt.sin_family = PF_INET;
	skt.sin_port = htons(port);
	skt.sin_addr.s_addr = htonl(ipaddr.s_addr);

	printf("port: %hu\n", port);
	printf("ipaddr: %u\n", ipaddr);
	printf("htonl(ipaddr.s_addr): %u\n", htonl(ipaddr.s_addr));
	printf("ipaddr.s_addr: %u\n", ipaddr.s_addr);
	tolen = sizeof(skt);

	printf("tolen: %u\n", tolen);
	printf("sizeof(tolen): %lu\n", sizeof(tolen));
	/*送信*/
	while(em.seq < 10) {
		printf("ループ突入\n");
		printf("input: ");
		fgets(em.msg, sizeof(em.msg), stdin);
		printf("fgetした\n");
		printf("seq: %d, msg: %s", em.seq, em.msg);
		printf("em.msg: %s", em.msg);
		if((sendto(soc, &em, sizeof(em), 0, 
						(struct sockaddr *)&skt, tolen)) == -1) {
			perror("sendto");
			return (-1);
		}
		printf("sendtoした\n");
	/*受信*/
		if((recvfrom(soc, &em, sizeof(em), 0,
						(struct sockaddr *)&skt, &tolen)) == -1) {
			perror("recvfrom");
			return (-1);
		} else {
			printf("recvした");
		}
		printf("seq: %d, msg: %s\n", em.seq, em.msg);
		// if (seq >= 10) {
		// 	break;
		// }
	}
	/*ソケットクローズ*/
	close(soc);
	/*プロセスの終了*/
	exit(0);
}
