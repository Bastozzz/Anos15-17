/*________________________________servidorTCPBase.c___________________________________*/
/*======================= Servidor interactivo TCP ============================
Este servidor destina-se mostrar mensagens recebidas via TCP, no porto
definido pela constante SERV_TCP_PORT.
Trata-se de um servidor que envia confirmacao (o comprimento, em bytes, da
mensagem recebida).
===============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_TCP_PORT  6122

#define BUFFERSIZE     4096

void Abort(char *msg);
void AtendeCliente(int sockfd);

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;	
	struct sockaddr_in cli_addr,serv_addr;

	switch(fork()){/*Passa para backgroud*/
		case -1:Abort("Impossibilidade de passar para backgroud");
		case  0:break;   /*filho*/
		default:exit(EXIT_SUCCESS); /* pai*/
	}

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		Abort("Impossibilidade de abrir socket");

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(SERV_TCP_PORT);  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
		Abort("Impossibilidade de registar-se para escuta");

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(listen(sockfd,5)==-1) Abort("Impossibilidade de escutar pedidos");

	/*================ PASSA A ATENDER CLIENTES INTERACTIVAMENTE =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len))==-1)
			fprintf(stderr,"<SERV>Impossibilidade de aceitar cliente...\n");
		else{
			AtendeCliente(newsockfd);
			close(newsockfd);
		}
	}
}


/*___________________________ AtendeCliente ____________________________________
Atende cliente. 
______________________________________________________________________________*/

void AtendeCliente(int sockfd){
	static char buffer[BUFFERSIZE];
	static unsigned int cont=0;
	int nbytes;
		
	/*==================== PROCESSA PEDIDO ==========================*/
	switch((nbytes=read(sockfd,buffer,BUFFERSIZE))){

		case -1:fprintf(stderr,"\n<SER>Erro na recepcao de dados...\n");
				return;

		case  0:fprintf(stderr,"\n<SER>O cliente nao enviou dados...\n");
				return;

		default:buffer[nbytes]='\0';
				printf("\n<SER>Mensagem n. %d recebida {%s}\n", ++cont, buffer);				
				/*============ ENVIA CONFIRMACAO =============*/
				printf("<SER>Confirma recepcao de mensagem.\n");
				sprintf(buffer,"%d",nbytes);
				nbytes=strlen(buffer);

			    if(write(sockfd,buffer,nbytes)!=nbytes)
					fprintf(stderr,"<SER>Impossibilidade de Confirmar.\n");
				else 
					printf("<SER>Mensagem confirmada.\n");
	}
	
}

/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro no SO e abando com 
"exit status" a 1
_______________________________________________________________________________
*/
void Abort(char *msg){
	fprintf(stderr,"\a<SER>Erro fatal: <%s>\n",msg);
	perror("Erro do sistema");
	exit(EXIT_FAILURE);
}

