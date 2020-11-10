/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja locacao e' dada
pelas seguintes constantes: SERV_HOST_ADDR (endereco IP) e SERV_UDP_PORT (porto)

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


#define SERV_HOST_ADDR "127.0.0.1"
#define SERV_UDP_PORT  6000

#define BUFFERSIZE     4096

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main( int argc , char *argv[] )
{

	int sockfd,msg_len;
	struct sockaddr_in serv_addr;
	char buffer[BUFFERSIZE];


	/*========================= TESTA A SINTAXE =========================*/

	if(argc != 2){
		fprintf(stderr,"Sintaxe: %s frase_a_enviar\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=============== CRIA SOCKET PARA ENVIO/RECEPCAO DE DATAGRAMAS ==============*/

	sockfd = socket( PF_INET , SOCK_DGRAM , 0 );
	if(sockfd < 0)
		Abort("Impossibilidade de criar socket");


	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	bzero( (char*)&serv_addr , sizeof(serv_addr) ); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/

	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); /*IP no formato "dotted decimal" => 32 bits*/
	serv_addr.sin_port = htons(SERV_UDP_PORT); /*Host TO Netowork Short*/


	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[1]);

	if(sendto( sockfd , argv[1] , msg_len , 0 , (struct sockaddr*)&serv_addr , sizeof(serv_addr) ) != msg_len)
		Abort("SO nao conseguiu aceitar o datagram");


	printf("<CLI1>Mensagem enviada ... a entrega nao e' confirmada.\n"); 


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
