#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")


#define SERV_HOST_ADDR "10.65.137.141"
#define SERV_UDP_PORT  6001

#define BUFFERSIZE     4096

int main(int argc, char * argv[]);

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main(int argc, char *argv[]) {

	SOCKET sockfd;
	int iResult, nbytes;
	int ip_idx, port_idx, msg_idx;
	int tam;
	struct sockaddr_in serv_addr, cli_addr, recv_addr;
	WSADATA wsaData;

	/*========================= TESTA A SINTAXE =========================*/

	if (argc != 7) {
		fprintf(stderr, "Sintaxe: %s -ip ip_destino -port porto_destino -msg frase_a_enviar\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-ip")) {
			ip_idx = i + 1;
		}
		if (!strcmp(argv[i], "-port")) {
			port_idx = i + 1;
		}
		if (!strcmp(argv[i], "-msg")) {
			msg_idx = i + 1;
		}
	}

	/*=============== INICIA OS WINSOCKS ==============*/

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*=============== CRIA SOCKET PARA ENVIO/RECEPCAO DE DATAGRAMAS ==============*/

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd == INVALID_SOCKET)
		Abort((char*)"Impossibilidade de criar socket");

	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[ip_idx]);
	serv_addr.sin_port = htons(atoi(argv[port_idx]));

	tam = sizeof(cli_addr);
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) != SOCKET_ERROR) {
		printf("<CLI1>Porto local automatico: %d\n", ntohs(cli_addr.sin_port));
	}

	nbytes = sendto(sockfd, argv[msg_idx], strlen(argv[msg_idx]), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if (nbytes == SOCKET_ERROR)
		Abort((char*)"<CLI1> Erro no envio de datagrams");

	tam = sizeof(serv_addr);

	printf("\nAguardando resposta");

	nbytes = recvfrom(sockfd, (char*)&recv_addr, sizeof(recv_addr), 0, (struct sockaddr*)&serv_addr, &tam);

	if (nbytes == SOCKET_ERROR)
		Abort((char*)"Erro enquanto aguardava resposta");

	if (strcmp(argv[ip_idx], (char*)inet_ntoa(serv_addr.sin_addr)) == 0 && atoi(argv[port_idx]) == ntohs(serv_addr.sin_port)) {
		nbytes = sendto(sockfd, (char*)&cli_addr, sizeof(cli_addr), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

		if (nbytes == SOCKET_ERROR)
			Abort((char*)"Erro a enviar resposta ao par");

		printf("\n1: Resposta enviada para {%s}:{%d}", (char *)inet_ntoa(recv_addr.sin_addr), ntohs(recv_addr.sin_port));
	}
	else {
		printf("\n2: O meu par esta em {%s}:{%d}", (char *)inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
	}


}

void Abort(char *msg) {
	fprintf(stderr, "<CLI1>Erro fatal: <%s> (%d)\n", msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}