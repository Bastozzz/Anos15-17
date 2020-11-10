/*============== Servidor concorrente TCP com IOMUX ===============
- Este servidor destina-se a visualizar no terminal mensagens recebidas.
- Nao corre, por omissao, em background.
- Retorna o PID do processo servidor que atende o pedido.
- Em simultaneo com a espera de pedidos de ligacao, este servidor
tambem processa comandos introduzidos no teclado (inclui o STDIN_FILENO 
no fdread passado `a rotina select). Termina quando e' digitado o comando 
"exit".
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
#include <signal.h>
#include <string.h>
#include <errno.h>

/*esta constante simbolica deve defenir-se na Makefile */
#ifndef SERV_TCP_PORT
#define SERV_TCP_PORT  6122
#endif
#define BUFFERSIZE     4096

void Abort(char *msg);
void AtendeCliente(int sockfd);
int ReadLine(int sockfd,char *buffer,int maxlen);
int WriteN(int sockfd,char * buffer,int nbytes);
void enterraZombie();


/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;
	struct sockaddr_in cli_addr,serv_addr;
	fd_set fd_read;
	int n;
	char comando[100];

	signal(SIGCHLD, enterraZombie);

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

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){

		FD_ZERO(&fd_read);
		FD_SET(STDIN_FILENO, &fd_read);
		FD_SET(sockfd, &fd_read);

		fflush(stdin);
		
		n=select(32, &fd_read, NULL, NULL, NULL);

		if(n<0)
			if( errno!=EINTR){
				close(sockfd);
				Abort("Erro no select");
			}else
				continue; 
			

		if(FD_ISSET(STDIN_FILENO, &fd_read)){
			gets(comando);
			if(strcmp(comando, "exit")==0){
				close(sockfd);
				printf("Adeus...\n");
				exit(0);
			}
		}

	   	if(FD_ISSET(sockfd, &fd_read))
			if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len))
						  ==-1)
				fprintf(stderr,"<SERV>Impossibilidade de aceitar cliente...\n");
			else{
				switch(fork()){/*Passa para backgroud*/
					case -1:fprintf(stderr,"Impossibilidade de atender...");
						close(newsockfd);
						break;
					case  0:close(sockfd); /*filho*/
						AtendeCliente(newsockfd);
						exit(EXIT_SUCCESS);
					default:close(newsockfd); /* pai*/
				}
			}
	}
}


/*___________________________ AtendeCliente ____________________________________
Atende cliente.
______________________________________________________________________________*/

void AtendeCliente(int sockfd){
	static char buffer[BUFFERSIZE];
	static unsigned int cont=0U;
	int nbytes;
	pid_t pid=getpid();
		

	while(1){
		/*==================== PROCESSA PEDIDO ==========================*/
		cont++;

		switch((nbytes=ReadLine(sockfd,buffer,BUFFERSIZE))){
			case -1:fprintf(stderr,"Erro na recepcao de dados...\n");
					return;
			case  0:fprintf(stderr,"Cliente nao enviou dados...\n");
					return;
			default:printf("\n<%d>Mensagem recebida: %s\n",pid,buffer);
					if(!strncmp(buffer,"exit",4)){
						printf("<%d>Vou desligar...\n",pid);
						close(sockfd);
						return;
					}
					/*============ ENVIA CONFIRMACAO =============*/
					sprintf(buffer,"<%d>",pid);
					nbytes=strlen(buffer);
				    if(WriteN(sockfd,buffer,nbytes)!=nbytes)
						fprintf(stderr,"Impossibilidade de Confirmar.\n");

		}
	}
}

/*_____________________________ ReadLine _______________________________________
Le uma linha (ate encontrar o caracter '\n') de um socket.
Devolve:
	-1 : se houve erro
	 0 : EOF
	!= : se leu alguns bytes
______________________________________________________________________________*/

int ReadLine(int sockfd,char* buffer,int maxlen){
	int n,rc;
	char c;

	for(n=0;n<maxlen-1;n++){
		if((rc=read(sockfd,&c,1))==1){
			*buffer++=c;
			if(c=='\n') break;
		}else if (rc==0) {
			if(n==0) return(0); /*EOF*/
			else break; /*EOF mas ja leu alguns dados*/
		} else return(-1); /*Erro*/
	}
	*buffer=0;
	return(n);
}

/*______________________________ WriteN _______________________________________
Escreve n bytes no socket em causa. Devolve o numero de bytes escritos.
______________________________________________________________________________*/
int WriteN(int sockfd,char * buffer,int nbytes){

	int nleft,nwritten;

	nleft=nbytes;
	while(nleft>0){
		if((nwritten=write(sockfd,buffer,nleft))<=0) return(nwritten);
		nleft-=nwritten;
		buffer+=nwritten;
	}
	return(nbytes-nleft);
}



/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro no SO e abando com 
"exit status" a 1
_______________________________________________________________________________
*/
void Abort(char *msg){
	fprintf(stderr,"\a<SER1>Erro fatal: <%s>\n",msg);
	perror("Erro do sistema");
	exit(EXIT_FAILURE);
}

void enterraZombie()
{
	static int status;
	wait(&status);

}
