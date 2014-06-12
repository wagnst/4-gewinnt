#pragma once

/**
* Show program credits
*/
void showCredits() {
	animateBox(25,8,66,17);
	startBuffer(66);
	setLineAlign(0);
	output("____ ____ ____ ___  _ ___ ____ \n|    |__/ |___ |  \\ |  |  [__  \n|___ |  \\ |___ |__/ |  |  ___] \n\n");
	setLineAlign(-1);
	output("  Niko Berkmann | @n2code\n    n2code@users.noreply.github.com\n");
	setLineAlign(+1);
	output("Steffen Wagner | @wagnst  \nmail@wagnst.de    \n");
	setLineAlign(-1);
	output("  Marvin Klose | @marvinklose\n    marvinklose@gmx.net\n");
	setLineAlign(+1);
	output("Michael Wieneke | @momoxd  \nmail@momoxd.de    \n");
	setLineAlign(-1);
	output("  Inga Miadowicz | @IngaMiad\n    inga.miadowicz@gmx.de\n");
	setLineAlign(0);
	output("\nPress any key to return to main menu.\n");
	flushBuffer();
	getch();
	animateBox(66,17,25,8);
}
