/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja localizacao e' igualmente
passada na linha de comando.

Aguarda pela resposta (cadeia de carateres) e verifica a origem.

O protocolo usado e' o UDP.
==============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUFFERSIZE     4096

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main( int argc , char *argv[] )
{

	int sockfd,msg_len, nbytes;
	unsigned int tam;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFERSIZE];


	/*========================= TESTA A SINTAXE =========================*/

	if(argc != 4){
		fprintf(stderr,"Sintaxe: %s frase_a_enviar ip_destino porto_destino\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=============== CRIA SOCKET PARA ENVIO/RECEPCAO DE DATAGRAMAS ==============*/

	sockfd = socket( PF_INET , SOCK_DGRAM , 0 );
	if(sockfd < 0)
		Abort("Impossibilidade de criar socket");


	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	bzero( (char*)&serv_addr , sizeof(serv_addr) ); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/

	serv_addr.sin_addr.s_addr = inet_addr(argv[2]); /*IP no formato "dotted decimal" => 32 bits*/
	serv_addr.sin_port = htons(atoi(argv[3])); /*Host TO Netowork Short*/


	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[1]);
	
	if(sendto( sockfd , argv[1] , msg_len , 0 , (struct sockaddr*)&serv_addr , sizeof(serv_addr) ) != msg_len)
		Abort("SO nao conseguiu aceitar o datagram");

	/* Descobre qual o porto que o SO atribuiu ao cliente */
	tam = sizeof(cli_addr);	
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) >= 0)
		printf("O porto atribuido pelo SO e: %d\n", ntohs(cli_addr.sin_port));

	printf("<CLI1>Mensagem enviada ... a entrega nao e' confirmada.\n"); 


	/*====================== AGUARDA RESPOSTA ==========================*/

	tam = sizeof(serv_addr);
	nbytes = recvfrom(sockfd, buffer, sizeof(buffer),0,(struct sockaddr *)&serv_addr, &tam);

	if(nbytes<0)
		Abort("Erro enquanto aguarda pela resposta");

	buffer[nbytes] = '\0';
	printf("<CLI1>Mensagem recebida: %s\n", buffer); 

	if (strcmp(inet_ntoa(serv_addr.sin_addr), argv[2]) == 0 && ntohs(serv_addr.sin_port) == atoi(argv[3])){
		printf("<CLI1>A mensagem veio do servidor.\n");
	}else{
		printf("<CLI1>A mensagem nao veio do servidor!\n");
	}
	
	/*========================= FECHA O SOCKET ===========================*/

	close(sockfd);

	printf("\n");
	exit(EXIT_SUCCESS);
}


/*________________________________ Abort________________________________________
  Mostra a mensagem de erro associada ao ultimo erro no sistema operativo 
  e termina a aplicacao com "exit status" a 1 (constante EXIT_FAILURE)
________________________________________________________________________________*/

void Abort(char *msg)
{

	fprintf(stderr,"<CLI1>Erro fatal: <%s>\n",msg);
	perror("Erro do sistema");
	exit(EXIT_FAILURE);

}
