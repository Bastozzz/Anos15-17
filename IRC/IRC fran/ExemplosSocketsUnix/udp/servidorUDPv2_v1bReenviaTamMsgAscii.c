/*============================== Servidor basico UDP ==========================
  Este servidor UDP destina-se a mostrar os conteudos dos datagramas recebidos,
  bem como as respectivas origens.
  O porto de escuta encontra-se definido pela constante SERV_UDP_PORT.
  Assume-se que as mensagens recebida sao cadeias de caracteres (ou seja, 
  "strings").

  Mostra a origem da mensagem (IP + porto cliente).

  Reenvia uma mensagem com o tamanho da mensagem recebida.

===============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERV_UDP_PORT 6000

#define BUFFERSIZE 4096
#define IP_SIZE 20
#define MAX_RESPOSTA 10

void Abort(char *msg);

/*________________________________ main ________________________________________
*/

int main( int argc , char *argv[] )
{
	int sockfd , nbytes;
	unsigned int length_addr, source_port;
	char source_ip[IP_SIZE];
	struct sockaddr_in serv_addr , cli_addr;
	char buffer[BUFFERSIZE], resposta[MAX_RESPOSTA];

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

		length_addr = sizeof(cli_addr);
		nbytes=recvfrom(sockfd , buffer , sizeof(buffer) , 0 , (struct sockaddr *)&cli_addr , &length_addr);

		if(nbytes<0) 
			Abort("Erro na recepcao de datagrams");

		buffer[nbytes] = '\0'; /*Termina a cadeia de caracteres recebidos com '\0'*/

		source_port = ntohs( cli_addr.sin_port); /*Network TO Host Short*/
		strcpy( source_ip , (char *)inet_ntoa( cli_addr.sin_addr ) ); /*Network TO Ascii*/

		printf( "\n<SER1>Mensagem recebida {%s} de {IP: %s; porto: %d}\n" , buffer, source_ip , source_port );

		sprintf(resposta, "%d", strlen(buffer));
                
		nbytes = sendto(sockfd , resposta , strlen(resposta) , 0 , (struct sockaddr *)&cli_addr,sizeof(cli_addr));
		if (nbytes <0){
			printf("\n<SER1>Error ao reenviar a mensagem ao cliente\n");
		}
		
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

