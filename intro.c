#include "declaration.h"



void titre();

void intro()
{
	int i;
	OSL_IMAGE *Logo[44];
	char *fileName;
	char buffer[4096];
	buffer[0] = '\0';

	for (i= 1; i <44; i++)
	{
	fileName = buffer;
	sprintf(fileName, "menu/intro/%i.png", i);
	Logo[i] = oslLoadImageFile(fileName, OSL_IN_RAM, OSL_PF_5551);
	Logo[i]->y = (272/2) - (Logo[i]->stretchY/2);
	}

	int compteur = 1;
	int unsurdeux = 0;
	while (!osl_quit)
	{
		oslStartDrawing();

		oslDrawImage(blanc);

		if (compteur <44)
		{
		oslDrawImage(Logo[compteur]);

		unsurdeux ++;
		if (unsurdeux == 6){compteur++;unsurdeux = 0;}
		}else
		{
			oslDrawImage(Logo[43]);
			compteur++;
			if (compteur >= 200){
				oslDrawFillRect(0,0,480,272,RGBA(255,255,255,((compteur-200)*2)-254));
			}
			if (((compteur-200)*2) == 254) break;

		
		}

		DevsSynchronisation();

	}
	//lance la 2eme partie le titre
	titre();

}


void titre()
{
	int compteur = 0;
	OSL_IMAGE *Titre;

	Titre = oslLoadImageFile("menu/titre.png", OSL_IN_RAM, OSL_PF_5551);
	Titre->y = (272/2) -(Titre->stretchY/2);
	Titre->x = (480/2) -(Titre->stretchX/2);

	while (!osl_quit)
	{
		oslStartDrawing();


		oslDrawImage(blanc);
		oslDrawImage(Titre);

		compteur++;

		if (compteur < (254/2)){

			oslDrawFillRect(0,0,480,272,RGBA(255,255,255,(254 -(compteur *2))));
		}
		
		if (compteur == 400)
		{
			oslDrawImage(blanc);
			DevsSynchronisation();
			break;
		}


		DevsSynchronisation();


	}

}