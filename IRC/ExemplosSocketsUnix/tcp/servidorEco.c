/*________________________________eco.c___________________________________*/
/*======================= Servidor concorrente TCP  ==================
Este servidor destina-se a reenviar os caracter aos clientes.
Termina quando detecta a sequência EXIT.
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

#ifndef SERV_TCP_PORT
#define SERV_TCP_PORT  5001
#endif
#define BUFFERSIZE   100

#define EXIT "exit"

void Abort(char *msg);
void AtendeCliente(int sockfd);
void IniciaBuffHistorico(char *buff);
void InsereNovoCharBuffHistorico(char *buff, char c);
void EnterraZombie();


/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;
	struct sockaddr_in cli_addr,serv_addr;

	switch(fork()){/*Passa para backgroud*/
		case -1:Abort("<echo> Impossibilidade de passar para backgroud");
		case  0:break;   /*filho*/
		default:exit(EXIT_SUCCESS); /* pai*/
	}

	/*====================== CUIDA DOS FILHOS "ZOMBIES"  ====================*/
	signal(SIGCHLD,EnterraZombie);

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		Abort("<echo> Impossibilidade de abrir socket");

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(SERV_TCP_PORT);  /*Escuta no porto Well-Known*/


	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0){
		close(sockfd);
		Abort("<echo> Impossibilidade de registar-se para escuta");
	}


	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(listen(sockfd,5)==-1){
		close(sockfd);		
		Abort("<echo> Impossibilidade de escutar pedidos");
	}

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len)) ==-1)
			fprintf(stderr,"<echo> Impossibilidade de aceitar o cliente %s:%d!\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		else{
			fprintf(stderr,"<echo> O cliente %s:%d foi aceite.\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
			/*Passa para background*/
			switch(fork()){
				case -1:fprintf(stderr, "<echo> Impossibilidade de atender o cliente %s:%d!\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
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

/*___________________________ Abort ____________________________________*/

void Abort(char *msg)
{
	perror(msg);
	printf("\n");
	exit(EXIT_FAILURE);
}

/*___________________________ AtendeCliente ____________________________________*/

void AtendeCliente(int sockfd)
{
	int nbytes, tam=sizeof(char);
	char c, buff[BUFFERSIZE];

	IniciaBuffHistorico(buff);

	while(1){
		if((nbytes = read(sockfd, &c, tam))>0){

			InsereNovoCharBuffHistorico(buff, c);
			if(strcmp(buff, EXIT)==0){
				fprintf(stderr, "<echo> Sequencia \"%s\" recebida -> ligacao encerrada.\n", EXIT);
				close(sockfd);
				return;		
			}

			nbytes= write(sockfd, &c, tam);
		}

		if(nbytes < 0){
			close(sockfd);
			Abort("<echo> Erro na recepcao/envio de dados");
		}else if(nbytes==0){
			fprintf(stderr, "<echo> Ligacao encerrada.\n");
			close(sockfd);
			return;
		}

	} //while
}


/*_________________ IniciaBuffHistorico ________________________________*/
void IniciaBuffHistorico(char *buff)
{
	int i=0;

	for(i=0; i<strlen(EXIT); i++)
		buff[i]='*';

	buff[i]='\0';
}



/*______________ InsereNovoCharBuffHistorico_____________________________*/
void InsereNovoCharBuffHistorico(char *buff, char c)
{
	int i;

	for(i=0; i<strlen(EXIT)-1; i++){
		buff[i]=buff[i+1];
	}

	buff[i]=c;	
}

/*___________________________ EnterraZombie __________________________________*/

void EnterraZombie()
{
	int status;

	wait(&status);
}
