/*________________________________ResolucaoIncompletaTeste02-P1-1011.C___________________________________
   IRC - 2010/11
   Turma P1 : Resolução do teste sobre TCP (incompleta)
===============================================================================*/

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
#define SERV_TCP_PORT  6122
#endif
#define BUFFERSIZE     4096

#define IP_DEST "Endereco IP de destino: "
#define PORTO_DEST "Porto de destino: "

void Abort(char *msg);
void AtendeCliente(int s1);
void EnterraZombie();
int Troca(int s1, int s2);
int ReadLine(int sockfd,char* buffer,int maxlen);

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;
	struct sockaddr_in cli_addr,serv_addr;

	switch(fork()){/*Passa para backgroud*/
		case -1:Abort("<SERV> Impossibilidade de passar para backgroud");
		case  0:break;   /*filho*/
		default:exit(EXIT_SUCCESS); /* pai*/
	}

	/*====================== CUIDA DOS FILHOS "ZOMBIES"  ====================*/
	signal(SIGCHLD,EnterraZombie);

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		Abort("<SERV> Impossibilidade de abrir socket");

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(SERV_TCP_PORT);  /*Escuta no porto Well-Known*/


	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0){
		close(sockfd);
		Abort("<SERV> Impossibilidade de registar-se para escuta");
	}

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(listen(sockfd,5)==-1){
		close(sockfd);		
		Abort("<SERV> Impossibilidade de escutar pedidos");
	}

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len)) ==-1)
			fprintf(stderr,"<SERV> Impossibilidade de aceitar o cliente %s:%d!\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		else{
			fprintf(stderr,"<SERV> O cliente %s:%d foi aceite.\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
			/*Passa para background*/
			switch(fork()){
				case -1:fprintf(stderr, "<SERV> Impossibilidade de atender o cliente %s:%d!\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
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
	exit(EXIT_FAILURE);
}

/*___________________________ AtendeCliente ____________________________________*/

void AtendeCliente(int s1)
{
	int nbytes, s2;
	struct sockaddr_in remotoAddr;
	fd_set fdread;
	char buffer[BUFFERSIZE];

	bzero((char *)&remotoAddr, sizeof(remotoAddr));
	remotoAddr.sin_family=AF_INET;

	//Solicita IP ao cliente
	if(write(s1, IP_DEST, strlen(IP_DEST))<=0){
		close(s1);
		return;
	}

	//Recebe IP em ascii no formaro "dotted-decimal"
	if((nbytes=ReadLine(s1, buffer, sizeof(buffer)))<=0){
		/*TODO*/
	}

	buffer[nbytes]='\0';

	//Preenche campo s_addr de remotoAddr
	remotoAddr.sin_addr.s_addr = /*TODO*/(buffer); //String -> formato de rede

	//solicita porto ao cliente
	if(write(/*TODO*/)<=0){
		close(s1);
		return;
	}

	//Recebe porto em ascii
	if((nbytes=/*TODO*/))<=0){
		/*TODO*/
	}

	buffer[nbytes]='\0';

	//Preenche campo sin_port de remotoAddr
	remotoAddr.sin_port = /*TODO*/(/*TODO*/(buffer)); //String -> inteiro -> short no formato da rede

	//Cria o segundo socket
	if((s2=socket(PF_INET, SOCK_STREAM, 0))<0){
		close (s1); //Fecha apenas s1 porque s2 ainda nao foi criado
		Abort("Impossibilidade de criar segundo socket");
	}

	//Estabelece ligacao com o destino solicitado e definido atraves de remotoAddr
	if(connect(/*TODO*/)<0){
		/*TODO*/ //Fecha s1 e s2
		Abort("Impossibilidade de estabelecer ligacao remota");
	}
		
	//Troca bytes entre s1 e s2
	while(1){
	
		FD_ZERO(&fdread);
		FD_SET(s1, &fdread);
		/*TODO*/ //Acrescenta s2 a fdread

		switch(select(32, &fdread, NULL, NULL, NULL)){

			case -1: //erro
				/*TODO*/ //Fecha os sockets
				Abort("Erro no Select");
				break;

			case 0: //Timeout: nunca ocorre porque o ultimo argumento e' NULL
				break;

			default://Troca
				if(/*TODO*/(s1, /*TODO*/)){
					if(Troca(s1, s2)/*TODO*/){
						/*TODO*/ //Fecha os sockets
						return;
					}
				}

				if(/*TODO*/(s2, /*TODO*/)){
					if(Troca(s2, s1)/*TODO*/){
						/*TODO*/ //Fecha os sockets
						return;
					}
				}
		}
	}	
}

/*___________________________ EnterraZombie __________________________________*/
void EnterraZombie()
{
	int status;

	wait(&status);
}

/*___________________________ Troca __________________________________*/
int Troca(int s1, int s2)
{
	char c;
	int nbytes;

	if((nbytes=read(s1, &c, sizeof(c)))>0)
		nbytes=write(s2, &c, sizeof(c));

	return nbytes;
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

	for(n=0 ; n<maxlen-1 ; n++){

		if((rc=read(sockfd,&c,1))==1){

			if(c=='\r')
				continue;

			if(c=='\n')
				break;

			*buffer++=c;

		}else if (rc==0){

			if(n==0)
				return(0); /*EOF*/
			else 
				break; /*EOF, mas ja leu alguns dados*/

		}else{ 

			return(-1); /*Erro*/

		}
	}

	*buffer=0;
	return(n);
}
