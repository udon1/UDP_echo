#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sysexits.h>

#define BUF 512


struct echo_msg {
	unsigned int seq;
	unsigned int reserve;
	char msg[32];
};

//int udp_server_socket(in_port_t myport) {
//	struct addrinfo hints, *res0;
//	int soc, opt, errcode;
//	socklen_t opt_len;
//	struct sockaddr_in myskt;

/*アドレス情報の*hintsをゼロクリア*/
// 		(void) memset(&hints, 0, sizeof(hints));
// 	hints.ai_family = AF_INIT4;
// 	hints.ai_socktype = SOCK_DGRAM;
// 	hints.ai_flags = AI_PASSIVE;
// 	/*アドレス情報の決定*/
// 
// 	if((errcode = getaddrinfo(NULL, port_num, &hints,
// 					&res0)) != 0){
// 		perror("getaddrinfo");
// 		return (-1);
// 	}
/*ソケットの生成*/
//	if((soc = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
//		perror("socket");
// freeaddrinfo(res0);
//		return (-1);
//	}

//	bzero(&myskt, sizeof(myskt));
//	myskt.sin_family = PF_INET;
//	myskt.sin_port = htons(myport);
//	myskt.sin_addr.s_addr = htonl(INADDR_ANY);
//	opt_len = sizeof(myskt);

/*bind*/
//	if(bind(soc, (struct sockaddr *)&myskt, opt_len) == -1) {
//		perror("bind");
// (void) close(soc);
// freeadrinfo(res0);
//		return (-1);
//}
// freeaddrinfo(res0);
//	return soc;
//}

//void send_recv(in_port_t myport)
//{
//struct sockaddr_storage from;
//ssize_t len;
//	socklen_t fromlen;
//	int s;
//char rbuf[BUF];
//char sbuf[BUF];
//struct sockaddr_in myskt;
//	struct sockaddr_in skt;
//	struct echo_msg msg;

// ソケット作成し，バインド
//	s = udp_server_socket(myport);

//	fromlen = sizeof(skt);

//	for(;;) {
/*仕様に合うように実装*/
//		if ((recvfrom(s, &msg, sizeof(msg), 0, 
//						(struct sockaddr *)&skt, &fromlen)) == -1) {
//			perror("recvfrom");
//			exit(-1);
//		}
//
//		printf("seq: %d, msg: %s\n", msg.seq, msg.msg);
//		msg.seq++;
//
//		if ((sendto(s, &msg, sizeof(msg), 0, 
//				(struct sockaddr *)&skt, fromlen)) == -1) {
//			perror("sendto");
//			exit(-1);
//		}

//recvfrom(acc, ..);
//sendto(acc, ..);
//	}
//}

int main (int argc, char *argv[]) {
	in_port_t myport;
	//struct addrinfo hints, *res0;
	int soc;//, opt, errcode;
	socklen_t opt_len;
	struct sockaddr_in myskt;
	socklen_t fromlen;
	//int s;
	struct sockaddr_in skt;
	struct echo_msg msg;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./udpserver [port]\n");		
		exit(1);
	}
	myport = inet_addr(argv[1]);
	//send_recv(myport);
	if((soc = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		// freeaddrinfo(res0);
		return (-1);
	}

	memset(&myskt, 0, sizeof(myskt));
	myskt.sin_family = PF_INET;
	myskt.sin_port = htons(myport);
	myskt.sin_addr.s_addr = htonl(INADDR_ANY);
	opt_len = sizeof(myskt);

	/*bind*/
	if(bind(soc, (struct sockaddr *)&myskt, opt_len) == -1) {
		perror("bind");
		// (void) close(soc);
		// freeadrinfo(res0);
		return (-1);
	}
	// freeaddrinfo(res0);
//	s = udp_server_socket(myport);

	fromlen = sizeof(skt);

	for(;;) {
		/*仕様に合うように実装*/
		if ((recvfrom(soc, &msg, sizeof(msg), 0, 
						(struct sockaddr *)&skt, &fromlen)) == -1) {
			perror("recvfrom");
			exit(-1);
		}

		printf("seq: %d, msg: %s\n", msg.seq, msg.msg);
		msg.seq++;

		if ((sendto(soc, &msg, sizeof(msg), 0, 
						(struct sockaddr *)&skt, fromlen)) == -1) {
			perror("sendto");
			exit(-1);
		}
	}
	return 0;
}
