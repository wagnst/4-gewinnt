#include <stdlib.h>

int main()
{
	system("TITLE ConnectFour"); //Titel in Fensterleiste
	system("CHCP 65001 > nul"); //UTF8 Codepage
	system("COLOR 0A"); //Grüne Schrift auf schwarzem Grund
	system("mode con:cols=80 lines=40"); //Fenstergröße
	system("CLS"); //Konsole leeren
	return system("4-gewinnt FANCY"); //eigentliches Programm starten
}
