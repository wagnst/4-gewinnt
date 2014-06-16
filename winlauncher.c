#include <stdlib.h>

int main(int argc, char *argv[])
{
	system("TITLE ConnectFour"); //Titel in Fensterleiste
	system("CHCP 65001 > nul"); //UTF8 Codepage
	system("COLOR 0A"); //Grüne Schrift auf schwarzem Grund
	system("mode con:cols=75 lines=35"); //Fenstergröße
	system("CLS"); //Konsole leeren

	/*
	//Startprozedur
	char append[16] = "4-gewinnt FANCY";
	int i = 0;
	int last = 0;
	while(argv[0][i]!=0){
		if (argv[0][i]=='\\' || argv[0][i]=='/') last = i;
		i++;
	}
	char* caller = malloc(sizeof(char)*(last+16));
	if (caller==NULL) return 777;
	strncat(caller,argv[0],last);
	strncat(caller+last,append,16);
	printf("!%s!",caller+1);
	system("pause"); //Konsole leeren
	return system(caller+1);
	*/

	return system("4-gewinnt FANCY"); //eigentliches Programm starten
}
