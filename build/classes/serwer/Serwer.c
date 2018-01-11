#include <sys/socket.h> //socket
#include <stdio.h> //printf
#include <netinet/in.h> //sockaddr i htons

int port=2222,
	deskryptorSerwera,
	deskryptorKlienta,
	n=0;

struct sockaddr_in gniazdoSerwera,
	gniazdoKlienta;
socklen_t klient;

char* wiadomoscPowitalna="Witaj, kliencie.";
char buforPowitania[255],
	buforWiadomosci[255];

int main(){
	printf("Uruchamianie serwera...\n");

	printf("Tworzenie deskryptora...\n");
	deskryptorSerwera=socket(AF_INET,SOCK_STREAM,0);
	if(deskryptorSerwera<0){
		perror("Błąd przy otwieraniu gniazda!\n");
		return(1);	
	}
	
	printf("Tworzenie gniazda...\n");
	gniazdoSerwera.sin_family=AF_INET;
	gniazdoSerwera.sin_addr.s_addr=INADDR_ANY;
	gniazdoSerwera.sin_port=htons(port);
	if(bind(deskryptorSerwera,(struct sockaddr*)&gniazdoSerwera,sizeof(gniazdoSerwera))<0){
		perror("Błąd przy bindowaniu gniazda!\n");
		return(1);
	}
	
	printf("Akceptowanie gniazda...\n");
	klient=(socklen_t)sizeof(gniazdoKlienta);
	listen(deskryptorSerwera,5);
	deskryptorKlienta=accept(deskryptorSerwera,(struct sockaddr*)&gniazdoKlienta,&klient);
	if(deskryptorKlienta<0){
		perror("Błąd przy akceptowaniu gniazda!\n");
		return(1);
	}

	printf("Sukces!\n");	
	while(strcmp(wiadomoscPowitalna,buforPowitania)!=0){
		bzero(buforWiadomosci,255);
		bzero(buforPowitania,255);
		n=read(deskryptorKlienta,buforWiadomosci,255);
		if(n<0){
			perror("Błąd przy odebraniu wiadomości powitalnej!\n");
			return(1);
		}
	}
	
	close(deskryptorSerwera);	
	return 0;
}
