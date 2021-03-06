/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja locacao e' dada
pelas seguintes constantes: SERV_HOST_ADDR (endereco IP) e SERV_UDP_PORT (porto)

Mostra o porto local que foi automaticamente atribuido pelo sistema operativo.

Aguarda pela resposta (cadeia de carateres).

O protocolo usado e' o UDP.
==============================================================================*/

#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")


#define SERV_HOST_ADDR "10.65.137.141"
#define SERV_UDP_PORT  6001

#define BUFFERSIZE     4096
#define TIMEOUT 5000

int main(int argc, char * argv[]);

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main(int argc, char *argv[])
{

	SOCKET sockfd;
	int iResult, msg_len, nbytes;
	int ip_idx, port_idx, msg_idx;
	int resposta;
	int tam;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFERSIZE];
	DWORD timeout;
	WSADATA wsaData;
	
	timeout = TIMEOUT;

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

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)); 


	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	memset((char*)&serv_addr, 0, sizeof(serv_addr)); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = inet_addr(argv[ip_idx]); /*IP no formato "dotted decimal" => 32 bits*/
	serv_addr.sin_port = htons(atoi(argv[port_idx])); /*Host TO Netowork Short*/

	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[msg_idx]);

	if (sendto(sockfd, argv[msg_idx], msg_len, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort((char*)"SO nao conseguiu aceitar o datagram");


	tam = sizeof(cli_addr);
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) != SOCKET_ERROR) {
		printf("<CLI1>Porto local automatico: %d\n", ntohs(cli_addr.sin_port));
	}

	/*====================== AGUARDA RESPOSTA ==========================*/
	
	nbytes = recvfrom(sockfd, (char*)&resposta, sizeof(resposta), 0, NULL, NULL);

	if (nbytes == SOCKET_ERROR)
		Abort((char*)"Erro enquanto aguarda pela resposta");

	buffer[nbytes] = '\0';
	printf("<CLI1>Mensagem recebida: %d\n", resposta);

	/*========================= FECHA O SOCKET ===========================*/

	closesocket(sockfd);

	printf("\n");
	exit(EXIT_SUCCESS);
}


/*________________________________ Abort________________________________________
Mostra uma mensagem de erro e o código associado ao ultimo erro com Winsocks.
Termina a aplicacao com "exit status" a 1 (constante EXIT_FAILURE)
________________________________________________________________________________*/

void Abort(char *msg)
{
	fprintf(stderr, "<CLI1>Erro fatal: <%s> (%d)\n", msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}