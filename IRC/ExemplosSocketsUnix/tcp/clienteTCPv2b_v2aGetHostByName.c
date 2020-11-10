/*=========================== Cliente basico TCP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cujo socket e' fornecido através
da linha de comando. Tambem e' aguarda confirmacao (trata-se do comprimento da mensagem).

O protocolo usado e' o TCP.

GetHostByName ---> Tambem aceita nomes alem de endereços IP no formato "dotted decimal".

Em relacao ao exemplo clienteTCPv1b.c, optou-se por uma abordagem mais
rigorosa em termos dos acessos para leitura e escrita no socket TCP.
Para o efeito, sao usadas as funcoes auxiliares WriteN e ReadLine.
==============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netdb.h>

#define BUFFERSIZE     4096

void Abort(char *msg);
int WriteN(int sockfd,char * buffer,int nbytes);
int ReadLine(int sockfd,char * buffer,int nbytes);

/*________________________________ main ________________________________________
*/

int main(int argc,char *argv[]){

	int sockfd,msg_len,nbytes;
	struct sockaddr_in serv_addr;
	char buffer[BUFFERSIZE];

	struct hostent *info;

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

	/*================= SE NECESSARIO, RESOLVE O NOME ====================*/
	if(serv_addr.sin_addr.s_addr == INADDR_NONE){
		info = gethostbyname(argv[2]);

		if(info == NULL)
			Abort("Servidor desconhecido");

		memcpy(&(serv_addr.sin_addr.s_addr), info->h_addr, info->h_length);

		printf("Endereco IP de %s: %s\n", argv[2], inet_ntoa(serv_addr.sin_addr));
	}

	/*========================== ESTABELECE LIGACAO ======================*/
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		Abort("Impossibilidade de estabelecer ligacao");

	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/
	msg_len=strlen(argv[1]);

	if(WriteN(sockfd,argv[1],msg_len)!=msg_len)
		Abort("Impossibilidade de transmitir mensagem...");

	if(WriteN(sockfd,"\n",1)!=1) /*termina mensagem com '\n'*/
		Abort("Impossibilidade de transmitir mensagem...");
	
	/*========================== ESPERA CONFIRMACAO =======================*/

	nbytes=ReadLine(sockfd,buffer,sizeof(buffer));

	if(nbytes<0) 
		Abort("Impossibilidade de receber confirmacao");

	printf("<CLI1>Confirmacao recebida {%s}.\n",buffer);
	fflush(stdout);

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

	int nread;

	int i;
	char c;

	i = 0;

	while(i < (nbytes-1)){ /* -1 para deixar espaco ao '\0' */

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
