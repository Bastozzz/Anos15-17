/*________________________________PROXY.C___________________________________*/
/*======================= Servidor concorrente Proxy =========================
Este servidor destina-se a servir de proxy para acesso a um servidor POP3.
O porto de escuta bem como o IP/nome do servidor POP3 sao passados na linha
de comando.
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#define POP_PORT	110 //Porto well-known dos servidores de mail pop3
#define TIMEOUT		3   //segundos
#define BUFFERSIZE	4096

void Abort(char *msg);
void AtendeCliente(int sockfd, struct sockaddr_in *);
int ReadLine(int sockfd,char *buffer,int maxlen);
int WriteN(int sockfd,char * buffer,int nbytes);
void EnterraZombie();

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	int sockfd,newsockfd,nbytes;
	unsigned cliaddr_len;
	struct sockaddr_in cli_addr, serv_addr, pop_addr;
	struct hostent *info;

	if(argc!=3){
		fprintf(stderr, "Usage: %s <porto de escuta> <servidor POP3>\n",argv[0]); 
		exit(EXIT_SUCCESS);
	}

	switch(fork()){/*Passa para backgroud*/
		case -1:Abort("Impossibilidade de passar para backgroud");
		case  0:break;   /*filho*/
		default:exit(EXIT_SUCCESS); /* pai*/
	}

	/*===== PREENCHE A ESTRURA DE ENDERECO ARA O SERVIDOR POP3 ============*/
	bzero((char *)&pop_addr, sizeof(pop_addr));
	pop_addr.sin_family = AF_INET;
	pop_addr.sin_port = htons(POP_PORT);
	pop_addr.sin_addr.s_addr = inet_addr(argv[2]);

	//Resolve o nome caso seja necessario ...
	if(pop_addr.sin_addr.s_addr==INADDR_NONE)
		if((info = gethostbyname(argv[2])) == NULL)
			Abort("Host desconhecido");
		else
			memcpy(&(pop_addr.sin_addr.s_addr), info->h_addr, info->h_length);

	/*====================== CUIDA DOS FILHOS "ZOMBIES"  ====================*/
	signal(SIGCHLD,EnterraZombie);

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		Abort("Impossibilidade de abrir socket");

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(atoi(argv[1]));  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
		Abort("Impossibilidade de registar-se para escuta");

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(listen(sockfd,5)==-1) Abort("Impossibilidade de escutar pedidos");

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&cliaddr_len))==-1){

			if(errno==EINTR)
				continue;

			fprintf(stderr,"<SERV>Impossibilidade de aceitar cliente...\n");

		}else{
			switch(fork()){/*Passa para backgroud*/
				case -1:fprintf(stderr,"Impossibilidade de atender...");
					close(newsockfd);
					break;
				case  0:close(sockfd); /*filho*/
					AtendeCliente(newsockfd, &pop_addr);
					exit(EXIT_SUCCESS);
				default:close(newsockfd); /* pai*/
			}
		}
	}
}

/*___________________________ AtendeCliente ____________________________________
Atende cliente.
______________________________________________________________________________*/

void AtendeCliente(int sockfd, struct sockaddr_in *pop_addr){
	static char buffer[BUFFERSIZE];
	int nbytes;
	int sockfd2; // Socket para comunicar como o servidor POP3
	fd_set fdread, fdtemp;
	struct timeval timeout = {TIMEOUT, 0};	

	if((sockfd2=socket(PF_INET, SOCK_STREAM,0))==-1){
		fprintf(stderr,"Erro na criacao do socket para comunicar com o servidor POP3...\n");
		perror("Erro de sistema");
		close (sockfd);
		return;
	}

	if(connect(sockfd2, (struct sockaddr *)pop_addr, sizeof(*pop_addr))==-1){
		fprintf(stderr,"Erro na ligacao ao servidor POP3...\n");
		perror("Erro de sistema");
		close (sockfd); close (sockfd2);
		return;
	}

	FD_ZERO(&fdread);
	FD_SET(sockfd, &fdread);
	FD_SET(sockfd2, &fdread);

	while(1){
		/*==================== PROCESSA PEDIDO ==========================*/

		fdtemp=fdread;
		timeout.tv_sec=TIMEOUT;
		timeout.tv_usec=0;

		switch(select(32, &fdtemp, NULL, NULL, NULL)){ // Sem timeout
		//switch(select(32, &fdtemp, NULL, NULL, &timeout)){
			case -1:
				if(errno==EINTR)
					break;

				fprintf(stderr,"Erro na rotina select ...\n");
				perror("Erro de sistema");
				close (sockfd); close (sockfd2);
				return;

			case  0:printf(".");
				break;

			default:
				if(FD_ISSET(sockfd, &fdtemp)){
					if(exchange(sockfd, sockfd2)<=0){
						close (sockfd); close (sockfd2);
						return;
					}
				}

				if(FD_ISSET(sockfd2, &fdtemp)){
					if(exchange(sockfd2, sockfd)<=0){
						close (sockfd); close (sockfd2);
						return;
					}
				}

				break;
		} //switch
	} //while
}

/*_____________________________ exchange _______________________________________
Recebe um caractere do primeiro socket e escreve-o no segundo

Devolve:
	-1 : se houve erro
	 0 : EOF
	>=0: se leu algum byte
______________________________________________________________________________*/
int exchange(int s1, int s2)
{
	int result;
	char c;

	if((result=read(s1, &c, sizeof(char)))==sizeof(char))
		result=write(s2, &c, sizeof(char));

	if(result==0)
		fprintf(stderr, "Connection closed by foreign host\n");

	if(result<0){
		fprintf(stderr, "Erro no acesso para I/O a um dos sockets\n");
		perror("Erro de sistema");
	}

	return(result);
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

/*_____________________________ EnterraZombie _________________________________
Faz o wait para eliminar os processos zombie.
_______________________________________________________________________________
*/
void EnterraZombie(){
	static status;

	wait(&status);
}

