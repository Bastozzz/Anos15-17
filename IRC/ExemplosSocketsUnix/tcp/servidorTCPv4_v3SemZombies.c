/*======================= Servidor interactivo TCP ============================
Este servidor destina-se mostrar mensagens recebidas via TCP, no porto
definido pela constante SERV_TCP_PORT.
Trata-se de um servidor que envia confirmacao (o comprimento, em bytes, da
mensagem recebida).

_ConcorrenteSemZombies --> atende varios clientes em "simultaneo" e resolve o
problema dos processos "zombies".
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
#include <errno.h>

#include <signal.h>

#define SERV_TCP_PORT  6122

#define BUFFERSIZE     4096

void Abort(char *msg);
void AtendeCliente(int sockfd);
int WriteN(int sockfd,char * buffer,int nbytes);
int ReadLine(int sockfd,char * buffer,int nbytes);

void EnterraZombie();

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

	/*====================== CUIDA DOS FILHOS "ZOMBIES"  ====================*/
	signal(SIGCHLD,EnterraZombie);

	/*================ PASSA A ATENDER CLIENTES INTERACTIVAMENTE =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len))==-1){

			if(errno == EINTR)
				continue;

			fprintf(stderr,"<SER>Impossibilidade de aceitar cliente...\n");

		}else{

			switch(fork()){/*Passa para backgroud*/

				case -1:fprintf(stderr,"<SER>Impossibilidade de atender...");
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
	static unsigned int cont=0;
	int nbytes;
		
	/*==================== PROCESSA PEDIDO ==========================*/
	switch((nbytes=ReadLine(sockfd,buffer,BUFFERSIZE))){

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

			    if(WriteN(sockfd,buffer,nbytes)!=nbytes)
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
	fprintf(stderr,"\n<SER>Erro fatal: <%s>\n",msg);
	perror("Erro do sistema");
	exit(EXIT_FAILURE);
}

/*______________________________ WriteN _______________________________________
Escreve n bytes no socket em causa. Devolve o numero de bytes escritos ou
-1 caso ocorra um erro ou 0 caso a ligacao seja encerrada.
______________________________________________________________________________*/

int WriteN(int sockfd,char * buffer,int nbytes){

	int nleft,nwritten;

	nleft=nbytes;

	while(nleft>0){

		nwritten=write(sockfd,buffer,nleft);

		if(nwritten<=0)
			return(nwritten); /*Erro (-1) ou End Of File (0) */

		nleft-=nwritten;
		buffer+=nwritten;

	}

	return(nwritten);
}

/*______________________________ ReadLine _______________________________________
Le uma linha de texto no socket em causa.

Regressa quando encontra o caractere '\n', quando o buffer fica cheio,
quando a ligacao TCP e' encerrada ou quando quando ocorre um erro.

Devolve o numero de bytes lidos ou -1 caso ocorra um erro.
______________________________________________________________________________*/

int ReadLine(int sockfd,char * buffer,int nbytes){

	int nleft,nread;

	int i;
	char c;

	i = 0;

	while(i < nbytes-1){ /* -1 para deixar espaço ao '\0'*/
		
		nread = read(sockfd, &c, sizeof(c));

		if(nread < 0)
			return nread; /*Erro*/

		if(nread == 0)
			break; /*End Of File*/

		if(c == '\r')
			continue; /*Ignora o '\r' numa sequencia "\r\n"*/
		
		if(c == '\n')
			break; /*Final da linha*/

		buffer[i++] = c;
	}
	
	buffer[i] = '\0';
	
	return(i);
}

/*_____________________________ EnterraZombie _________________________________
Faz o wait para eliminar os processos zombie.
_______________________________________________________________________________
*/
void EnterraZombie(){
	static status;

	wait(&status);
}
