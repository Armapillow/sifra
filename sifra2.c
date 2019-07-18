#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_REC	5

struct termios nova, stara;

char* ucitajSifru();
void inicijalizuj(void);
void resetuj(void);

int main()
{
	printf("Unesi sifru: ");
	inicijalizuj();
	char* sifra = ucitajSifru();
	resetuj();

	printf("\n%s\n",sifra);

	free(sifra);
	return 0;
}
char* ucitajSifru()
{
	int c, poz = 0;
	int vel = MAX_REC;

	char* niska = malloc(vel * sizeof(char));
	if(!niska){
		fprintf(stderr,"Alokacija nije uspela\n");
		exit(EXIT_FAILURE);
	}

	while(1){
		c = getchar();
		if(c == '\n'){
			niska[poz] = '\0';
			return niska;
		}
		else
			niska[poz] = c;
		poz++;
		if(poz >= MAX_REC){
			vel += MAX_REC;
			niska = realloc(niska, vel * sizeof(char));
			if(!niska){
				fprintf(stderr,"Alokacija nije uspela\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
void resetuj(void)
{
	tcsetattr(0, TCSANOW, &stara);
}
void inicijalizuj(void)
{
	tcgetattr(0, &stara);

	nova = stara;

	nova.c_lflag &= ~ECHO;

	tcsetattr(0, TCSANOW, &nova);
}
