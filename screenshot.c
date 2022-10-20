/*****************************************************\
 Sonic
 Autor : Foury Jean-francois
 V.0.1 - Version Beta

\*****************************************************/

#include "declaration.h"

char            checkname[256];
static int      lastNumber = -1;

/*
====================
FileExists

Verifie si Le fichier existe
====================
*/
int FileExists(const char *file)
{
	FILE           *f;

	f = fopen(file, "rb");
	if(f)
	{
		fclose(f);
		return 1;
	}
	return 0;
}


/*
====================
ScreenshotFilename

Change le nom du fichier selon si on et dans les 10ene ou les 100ene ...
====================
*/
static void ScreenshotFilename(int lastNumber, char *fileName, const char *ext)
{
	int   a, b, c, d;

	a = lastNumber / 1000;
	lastNumber -= a * 1000;
	b = lastNumber / 100;
	lastNumber -= b * 100;
	c = lastNumber / 10;
	lastNumber -= c * 10;
	d = lastNumber;

	sprintf(fileName, "../../../PICTURE/sonic%i%i%i%i%s", a, b, c, d, ext);

}

/*
====================
screenshot

Prise des screenshot pendant le jeux
====================
*/
void screenshot()
{
	#ifdef PSP
		sprintf(checkname, "%s", "sonic");// a changer selong la categorie de jeux c'est la raison du sprintf

		if(lastNumber == -1)
		{
			lastNumber = 0;
		}

		ScreenshotFilename(lastNumber, checkname, ".png");
		while (FileExists(checkname))
		{
			lastNumber++;
			ScreenshotFilename(lastNumber, checkname, ".png");
		}
		oslWriteImageFile(OSL_SECONDARY_BUFFER, checkname, 0);
		lastNumber++;


		#endif

}