/*=========================== Cliente basico TCP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cujo socket e' fornecido através
da linha de comando. Tambem e' aguarda confirmacao (trata-se do comprimento da mensagem).

O protocolo usado e' o TCP.
==============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE     4096

void Abort(char *msg);

/*________________________________ main ________________________________________
*/

int main(int argc,char *argv[]){

	int sockfd,msg_len,nbytes;
	struct sockaddr_in serv_addr;
	char buffer[BUFFERSIZE];

	if(argc!=4){ /*Testa sintaxe*/
		fprintf(stderr,"Sintaxe: %s \"frase_a_enviar\" ip_destino porto_destino\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=============== ABRE SOCKET PARA CONTACTAR O SERVIDOR ==============*/
	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		Abort("Impossibilidade de abrir socket");

	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/
	bzero((char*)&serv_addr,sizeof(serv_addr));	/*a zero todos os bytes*/
	serv_addr.sin_family=AF_INET;				/*Address Family - Internet*/
	serv_addr.sin_addr.s_addr=inet_addr(argv[2]);   
	serv_addr.sin_port=htons(atoi(argv[3]));          

	/*========================== ESTABELECE LIGACAO ======================*/
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		Abort("Impossibilidade de estabelecer ligacao");

	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/
	msg_len=strlen(argv[1]);

	if(write(sockfd,argv[1],msg_len) != msg_len)
		Abort("Impossibilidade de transmitir mensagem...");

	if(write(sockfd,"\n",1)!=1) /*termina mensagem com '\n'*/
		Abort("Impossibilidade de transmitir mensagem...");
	
	/*========================== ESPERA CONFIRMACAO =======================*/
	nbytes=read(sockfd,buffer,sizeof(buffer));

	if(nbytes<0) 
		Abort("Impossibilidade de receber confirmacao");

	buffer[nbytes] = '\0';

	printf("<CLI1>Confirmacao recebida {%s}.\n",buffer);

	/*=========================== FECHA SOCKET ============================*/
	close(sockfd);

	exit(EXIT_SUCCESS);
}


/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro no SO e abando com 
"exit status" a 1
_______________________________________________________________________________
*/
void Abort(char *msg){
	fprintf(stderr,"\a<CLI1>Erro fatal: <%s>\n",msg);
	perror("Erro do sistema");
	exit(EXIT_FAILURE);
}

