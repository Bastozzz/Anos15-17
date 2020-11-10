/*======================= Servidor concorrente TCP ============================
- Este servidor destina-se a mostrar mensagens recebidas via TCP, no porto
definido pela constante SERV_TCP_PORT.
- Trata-se de um servidor que envia confirmacao (o comprimento, em bytes, da
mensagem recebida). 
- O servidor e' concorrente: tem capacidade para atender varios clientes em 
simultaneo.
- O atendimento de um cliente termina quando este envia a mensagem definida
pela constante SAI, quando a ligacao e' quebrada ou quando esta e' encerrada.
- O servidor pode ser testado com clientes Telnet (comando telnet, 
aplicacao putty, etc.).
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
#include <signal.h>

#define SERV_TCP_PORT	6122

#define BUFFERSIZE	4096
#define SAI		"fim!"
#define MSG_BOAS_VINDAS	"\r\nDigite \"fim!\" para terminar.\r\n"

void Abort(char *msg);
void AtendeCliente(int sockfd);
int WriteN(int sockfd,char * buffer,int nbytes);
int ReadLine(int sockfd,char * buffer,int nbytes);
void enterraZombie();


void enterraZombie()
{
	int status;
	int pid;

	pid = wait(&status);

	if(pid != getpid())
		printf("\nO filho com pid %d terminou!\n\n", pid);
}

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;	
	struct sockaddr_in cli_addr,serv_addr;

	signal(SIGCHLD, enterraZombie);

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
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len))						  ==-1)
			fprintf(stderr,"<SERV>Impossibilidade de aceitar cliente...\n");
		else{
			switch(fork()){
				case -1:
					printf("Impossibilidade de lancar filho.\n");
					break;

				case 0:
					close(sockfd);
					AtendeCliente(newsockfd);
					close(newsockfd);
					exit(0);
				default:
					break;
					
			}
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


	struct sockaddr_in peerAddr;
	unsigned int tam = sizeof(peerAddr);
	if(getpeername(sockfd, (struct sockaddr *)&peerAddr, &tam)>=0){
		printf("\r\nVou atender o cliente {%s:%d}.\r\n", (char *)inet_ntoa(peerAddr.sin_addr), ntohs(peerAddr.sin_port));
		fflush(stdout);
	}

	write(sockfd, MSG_BOAS_VINDAS, strlen(MSG_BOAS_VINDAS));
		
	/*==================== PROCESSA PEDIDOS ==========================*/
	while(1){
		switch((nbytes=ReadLine(sockfd,buffer,BUFFERSIZE))){

			case -1:
				fprintf(stderr,"\n<SER>Erro na recepcao de dados...\n");
				return;

			case  0:
				fprintf(stderr,"\n<SER>O cliente nao enviou dados...\n");
				return;
	
			default:
				buffer[nbytes]='\0';
				printf("\n<SER>Mensagem n. %d recebida {%s}\n", ++cont, buffer);				
				
				if(strcmp(buffer, SAI) == 0)
					return;

				/*============ ENVIA CONFIRMACAO =============*/
				printf("<SER>Confirma recepcao de mensagem.\n");
				sprintf(buffer,"%d caracteres\r\n",nbytes);
				nbytes=strlen(buffer);

				if(WriteN(sockfd,buffer,nbytes)!=nbytes)
					fprintf(stderr,"<SER>Impossibilidade de Confirmar.\n");
				else 
					printf("<SER>Mensagem confirmada.\n");
		}//switch	
	}//while
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
