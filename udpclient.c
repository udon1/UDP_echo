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

int main (int argc, char *argv[]) {
	/*変数宣言*/
	struct echo_msg em;
	socklen_t tolen;//fromlen, tolen;
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
	// skt.sin_addr.s_addr = htonl(ipaddr.s_addr); // 動かない
	skt.sin_addr.s_addr = ipaddr.s_addr;
    // skt.sin_addr.s_addr = inet_addr(argv[1]); // 動く

	//printf("port: %hu\n", port);
	//printf("ipaddr: %u\n", ipaddr);
	//printf("htonl(ipaddr.s_addr): %u\n", htonl(ipaddr.s_addr));
	//printf("ipaddr.s_addr: %u\n", ipaddr.s_addr);
	tolen = sizeof(skt);

	//printf("tolen: %u\n", tolen);
	//printf("sizeof(tolen): %lu\n", sizeof(tolen));
	/*送信*/
	while(em.seq < 10) {
		//printf("ループ突入\n");
		printf("input: ");
		fgets(em.msg, sizeof(em.msg), stdin);
		//printf("fgetした\n");
		printf("seq: %d, msg: %s", em.seq, em.msg);
		//printf("em.msg: %s", em.msg);
		if((sendto(soc, &em, sizeof(em), 0, 
						(struct sockaddr *)&skt, tolen)) == -1) {
			perror("sendto");
			return (-1);
		}
		//printf("sendtoした\n");
	/*受信*/
		if((recvfrom(soc, &em, sizeof(em), 0,
						(struct sockaddr *)&skt, &tolen)) == -1) {
			perror("recvfrom");
			return (-1);
		} //else {
			//printf("recvした");
		//}
		printf("seq: %d, msg: %s\n", em.seq, em.msg);
        if (strcmp(em.msg, "FIN\n") == 0) {
            break;
        }
		// if (seq >= 10) {
		// 	break;
		// }
	}
	/*ソケットクローズ*/
	close(soc);
	/*プロセスの終了*/
	exit(0);
}
