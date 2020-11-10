/*============================== Servidor basico UDP ==========================
  Este servidor UDP destina-se a mostrar os conteudos dos datagramas recebidos.
  O porto de escuta encontra-se definido pela constante SERV_UDP_PORT.
  Assume-se que as mensagens recebida sao cadeias de caracteres (ou seja, 
  "strings").
===============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define SERV_UDP_PORT 6000

#define BUFFERSIZE     4096

void Abort(char *msg);

/*________________________________ main ________________________________________
*/

int main( int argc , char *argv[] )
{
	int sockfd , nbytes;
	struct sockaddr_in serv_addr;
	char buffer[BUFFERSIZE];

	/*======================= PASSA PARA BACKGROUND ==========================*/

	switch( fork() ){
		case -1: Abort("Impossibilidade de passar para backgroud");
		case  0: break; /* O filho continua em background */
		default: exit(EXIT_SUCCESS); /* O pai termina */
	}

	/*============ CRIA O SOCKET PARA RECEPCAO/ENVIO DE DATAGRAMAS UDP ============*/

	if((sockfd = socket( PF_INET , SOCK_DGRAM , 0))<0)
		Abort("Impossibilidade de abrir socket");

	/*=============== ASSOCIA O SOCKET AO  ENDERECO DE ESCUTA ===============*/

	/*Define que pretende receber datagramas vindos de qualquer interface de 
	rede, no porto pretendido*/

	bzero( (char*)&serv_addr , sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /*Host TO Network Long*/
	serv_addr.sin_port = htons(SERV_UDP_PORT);  /*Host TO Network Short*/

	/*Associa o socket ao porto pretendido*/

	if(bind( sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) <0)
		Abort("Impossibilidade de registar-se para escuta");


	/*================ PASSA A ATENDER CLIENTES INTERACTIVAMENTE =============*/

	while(1){

		fprintf(stderr,"<SER1>Esperando datagram...\n");

		nbytes=recvfrom(sockfd , buffer , sizeof(buffer) , 0 , NULL , NULL);

		if(nbytes<0) 
			Abort("Erro na recepcao de datagrams");

		buffer[nbytes]='\0'; /*Termina a cadeia de caracteres recebidos com '\0'*/

		printf("\n<SER1>Mensagem recebida {%s}\n",buffer);
		
	}
	
}

/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro no SO e termina com 
"exit status" a 1 (EXIT_FAILURE)
_______________________________________________________________________________*/

void Abort(char *msg)
{
	fprintf(stderr,"\a<SER1>Erro fatal: <%s>\n",msg);
	perror("");
	exit(EXIT_FAILURE);
}

