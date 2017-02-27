#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF 512


struct echo_msg {
	unsigned int seq;
	unsigned int reserve;
	char msg[32];
};

int udp_server_socket(void) {
	struct addrinfo hints, *res0;
	int soc, opt, errcode;
	socklen_t opt_len

		/*アドレス情報の*hintsをゼロクリア*/
		(void) memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INIT4;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	/*アドレス情報の決定*/

	if((errcode = getaddrinfo(NULL, port_num, &hints,
					&res0)) != 0){
		perror("getaddrinfo");
		return (-1);
	}
	/*ソケットの生成*/
	if((soc = socket(res0->ai_family, res0->ai_socktype,
					res0->ai_protocol)) == -1) {
		perror("socket");
		freeaddrinfo(res0);
		return (-1);
	}
	/*bind*/
	if(bind(soc, res0->ai_addr, res0->ai_addrlen) == -1) {
		perror("bind");
		(void) close(soc);
		freeadrinfo(res0);
		return (-1);
	}
	freeaddrinfo(res0);
	return soc;
}

void send_recv(int acc)
{
	struct sockaddr_storage from;
	ssize_t len;
	socklen_t fromlen;
	int s;
	char rbuf[BUF];
	char sbuf[BUF];
	struct sockaddr_in myskt;
	struct sockaddr_in skt;

	s = udp_server_socket;

	for(;;) {
		/*仕様に合うように実装*/
		if ((recvfrom(s, rbuf, sizeof rbuf, 0, 
						(struct sockaddr *)&skt, &sktlen)) == -1) {
			perror("recvfrom");
			return (-1);
		}
		if ((sendto(s, sbuf, datalen, 0, 
				(struct sockaddr *)&skt,sizeof skt)) == -1) {
			perror("sendto");
			return (-1);
		}

		//recvfrom(acc, ..);
		//sendto(acc, ..);
	}
}




int main () {
	send_recv(acc);
}






















