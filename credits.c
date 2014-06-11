#pragma once

/**
* Method to us as a programmer:-)
* @return no return because of void
*/
void showCredits() {
	startBuffer(66);
	output("[ CREDITS ]:\n\n Niko Berkmann | @n2code\n   -> n2code@users.noreply.github.com\n Steffen Wagner | @wagnst\n   -> mail@wagnst.de\n Marvin Klose | @marvinklose\n   -> marvinklose@gmx.net\n Michael Wieneke | @momoxd\n   -> mail@momoxd.de\n Inga Miadowicz | @IngaMiad\n   -> inga.miadowicz@gmx.de\n\n");
	output("Press any key to return to main menu.\n");
	flushBuffer();
	getch();
}
