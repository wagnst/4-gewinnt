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
    printf("Please, enter a name for player 1: "); //Get name of player 1
    scanf("%s", &name1);
    printf("Please, enter a name for player 2: "); //Get name of player 2
    scanf("%s", &name2);

    //Loop till the game is done
    while(end==0){
		//Rufe Funktion Animation -> animation();-> Bewege Pfeil, Abwurf
		//Rufe Funktion EingabeVerarbeiten -> EingabeVerarbeiten(); -> drop chip, nächster Spieler ist an der Reihe
		//Rufe Funktion EingebenBisGültig (returns end=1 und Loop ist vorbei? Oder wie gedacht?) -> EingebenBisGültig();
		//Setze Variablen winner und looser
    }

    system("CLS");
    printf("Congratulations! %s you made the game and defeated %s. \nClick to enter the famous 'Hall of Shame'...", winner, looser);
    //hallOfShame();
}
