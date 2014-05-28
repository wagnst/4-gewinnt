#pragma once

/**
* Method to us as a programmer:-)
* @return no return because of void
*/
void showCredits() {
	startBuffer(70);
	output("[ CREDITS ]:\n\n Niko Berkmann | @n2code\n   -> mail@n2code.de\n Steffen Wagner | @wagnst\   -> mail@wagnst.de\n Marvin Klose | @marvinklose\n   -> marvinklose@gmx.net\n Michael Wieneke | @momoxd\n   -> mail@momoxd.de\n Inga Miadowicz | @IngaMiad\n   -> inga.miadowicz@gmx.de\n\n");
	output("Press any key to return to main menu.\n");
	flushBuffer();
	getch();
}
