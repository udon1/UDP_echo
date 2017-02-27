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


int
get_info(char *hostnum, char *portnum, struct
		sockaddr_storage *saddr, socklen_t *saddr_len)
{
	struct addrinfo hints, *res0;
	int errcode;

	/*hintsをゼロクリア*/

	(void) memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET4;
	hints.ai_socktype = SOCK_DGRAM;
	//hints.ai_flags = AI_PASSIVE;
	/*アドレス情報の決定*/
	if((errcode = getaddrinfo(hostnum, portnum, &hints,
					&res0)) != 0) {
		perror("getaddrinfo");
		return (-1);
	}
	(void) memcpy(saddr, res0->ai_addr, res0->ai_addrlen);
	*saddr_len = res0->ai_addrlen;
	freeaddrinfo(res0);
	return 0;
}

	void
send_recv(int soc, char* hostnun, char* portnum)
{
	struct echo_msg em;
	struct timeval timeout;
	struct sockaddr_storage from, to;
	int end, width;
	ssize_t len;
	socklen_t fromlen, tolen;
	int seq;
	char rbuf[BUF];
	char sbuf[BUF];
	struct sockaddr_in myskt;
	struct sockaddr_in skt;

	for(seq = 0;;) {
		printf("input: ");
		scanf("%s", em.msg);
		if((sendto(s, sbuf, datalen, 0, 
						(struct sockaddr *)&skt, sizeof skt)) == -1) {
			perror("sendto");
			return (-1);
		}
		if((recvfrom(s, rbuf, sizeof rbuf, 0,
						(struct sockaddr *)&skt, sizeof skt)) == -1) {
			perror("recvfrom");
			return (-1);
		}
		if (seq >= 10) {
			break;
		}
		Close();
		exit();
		/*標準入力待ち*/
		/*送信先情報の取得*/
		//sendto(acc, ..)
		//recvfrom(acc, ..)
	}
}






int main () {
	if((soc = socket(PF_INET4, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return (EX_UNANAILABLE);
	}

}













