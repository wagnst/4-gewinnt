#include <stdio.h>
#include <stdlib.h>

/* To-Do:
Spielfunktion (-----) {
	Spielernamen eingeben
	Spielschleife bis Funktion Spielende? {
		Rufe Funktion EingebenBisGültig
		Rufe Funktion Animation
		Rufe Funktion EingabeVerarbeiten
	}
	Ergebnismeldung
	Rufe Funktion Zeige HallOfShame
}
*/

char name1[20];
char name2[20];
char winner[20];
char looser[20];

void gamefunction(){

	_Bool end = 0;

    //Get names of the players
	fprintf(stdout, "Please enter a name for Player 1: \n");
	fscanf(stdin, "%s", &name1);
	fprintf(stdout, "Please enter a name for Player 2: \n");
	fscanf(stdin, "%s", &name2);

    //Loop till the game is done
    while(end==0){
		//ZeichneFeld();
		//animation(); -> animation();-> Bewege Pfeil, Abwurf
		//Rufe Funktion EingabeVerarbeiten -> EingabeVerarbeiten(); -> drop chip, nächster Spieler ist an der Reihe
		//Rufe Funktion EingebenBisGültig (returns end=1 und Loop ist vorbei? Oder wie gedacht?) -> EingebenBisGültig();
		//Setze Variablen winner und looser
    }

    system("CLS");
    printf("Congratulations! %s you made the game and defeated %s. \nClick to enter the famous 'Hall of Shame'...", winner, looser);
    //hallOfShame();
}
