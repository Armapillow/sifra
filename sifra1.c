#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>

#define MAX_REC	5

/* STDIN_FILENO = 0
 * STDOUT_FILENO = 1 */

static struct termios stara, nova;

void inicijalizuj(void); 
void resetuj(void);    
char* ucitajSifru();

int main()
{
	printf("Unesite sifru: ");
	inicijalizuj();
	char* sifra = ucitajSifru();
	resetuj();

	printf("\n%s\n",sifra);

	free(sifra);
	return 0;
}
char* ucitajSifru()
{
	int i = 0, vel = MAX_REC;
	char c;

	char* niska = malloc(MAX_REC * sizeof(char));

	while((c = getchar()) != '\n'){
		if(i + 1 == MAX_REC){
			vel += MAX_REC;
			niska = realloc(niska, vel);
		}
		niska[i++] = c;
	}
	niska[i] = '\0';

	return niska;
}
void resetuj()
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
