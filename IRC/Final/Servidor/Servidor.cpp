#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERV_UDP_PORT 6001

#define BUFFERSIZE 4096
#define IP_SIZE 20

void Abort(char *msg);

/*________________________________ main ________________________________________
*/

int main(int argc, char *argv[]) {
	SOCKET sockfd;
	int iResult, nbytes;
	int length_addr;
	struct sockaddr_in serv_addr, cli_addr1, cli_addr2;
	char buffer[BUFFERSIZE];
	WSADATA wsaData;

	/*=============== INICIA OS WINSOCKS ==============*/

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*============ CRIA O SOCKET PARA RECEPCAO/ENVIO DE DATAGRAMAS UDP ============*/

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		Abort((char*)"Impossibilidade de abrir socket");


	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_UDP_PORT);

	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort((char*)"Impossibilidade de registar-se para escuta");

	while (1) {
		fprintf(stderr, "\n<SER1> Esperando primeiro datagram...");

		length_addr = sizeof(cli_addr1);
		nbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr1, &length_addr);

		if (nbytes == SOCKET_ERROR)
			printf("\n<SER1>Erro na rececao de datagrams");

		fprintf(stderr, "\n<SER1> Esperando segundo datagram...");

		length_addr = sizeof(cli_addr2);
		nbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr2, &length_addr);

		if (nbytes == SOCKET_ERROR)
			printf("\n<SER1>Erro na rececao de datagrams");

		nbytes = sendto(sockfd, (char*)&cli_addr2, sizeof(cli_addr2), 0, (struct sockaddr*)&cli_addr1, sizeof(cli_addr1));

		if (nbytes == SOCKET_ERROR)
			printf("\n<SER1>Erro no envio de datagrams");
	}
}

void Abort(char *msg) {
	fprintf(stderr, "<SERV>Erro fatal: <%s> (%d)\n", msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}