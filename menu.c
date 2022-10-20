#include "declaration.h"

#include "carte/menu/fond.h"


OSL_FONT *maFonte, *maFonte2, *maFonte3;
int ChoixMenu ;
int valide;
int PossX ;
OSL_IMAGE *CarrerMenu , *HautMenu, *GaucheMenu;
OSL_IMAGE *image01, *image02, *image03, *image04,*image05, *titre_haut;
OSL_MAP *CarrerMap;

OSL_IMAGE *MenuStartImg;

int PossitionBarreY;


void Touche_menu();
void MenuSonicStart();


void MenuStart()
{
	MenuStartImg = oslLoadImageFile("menu/start.png", OSL_IN_RAM, OSL_PF_5551);

	while (!osl_quit)
	{
		oslStartDrawing();
		oslReadKeys();

		oslDrawImage(MenuStartImg);
		
 
		if (osl_keys->pressed.start){
		DevsFX_MasqueRectangle(NOIR);
		break;
		}

		DevsSynchronisation();

	}

}


void InitMenu()
{
	
	CarrerMenu = oslLoadImageFile("menu/carrer.png", OSL_IN_RAM, OSL_PF_5551);
	HautMenu = oslLoadImageFile("menu/haut.png", OSL_IN_RAM, OSL_PF_8888 );
	GaucheMenu = oslLoadImageFile("menu/gauche.png", OSL_IN_RAM, OSL_PF_8888 );
	image01 = oslLoadImageFile("menu/01.png", OSL_IN_RAM, OSL_PF_5551);
	titre_haut = oslLoadImageFile("menu/titre.png", OSL_IN_RAM, OSL_PF_5551);

	maFonte2 = oslLoadFontFile("font/ArialBlack.oft"); //chargement de ma police perso
	maFonte3 = oslLoadFontFile("font/Adobe.oft"); //chargement de ma police perso
	maFonte = oslLoadFontFile("font/ArialBlack18.oft"); //chargement de ma police perso

	CarrerMap = oslCreateMap(
	CarrerMenu,       
	(void *)fond_map,      
	16,16,        
	30,17,        
	OSL_MF_U16);  

	image02 = oslLoadImageFile("menu/perso/image2.png", OSL_IN_RAM, OSL_PF_5551);
	image03 = oslLoadImageFile("menu/perso/image3.png", OSL_IN_RAM, OSL_PF_5551);
	image04 = oslLoadImageFile("menu/perso/image6.png", OSL_IN_RAM, OSL_PF_5551);
	image05 = oslLoadImageFile("menu/perso/image5.png", OSL_IN_RAM, OSL_PF_5551);



}


void MenuSonic()
{

	titre_haut->x = -30;
	titre_haut->y = 30;

	PossitionBarreY= 38;
	ChoixMenu = 1;
	valide = 0;
	PossX = 0;

	oslSetFont(maFonte);

	GaucheMenu->x = -GaucheMenu->stretchX ;
	GaucheMenu->y = 272 - GaucheMenu->stretchY;

	image01->x = 480 - image01->stretchX - 30;
	image01->y = 272 - image01->stretchY - 30;
	 

	while (!osl_quit)
	{
		oslStartDrawing();
		Touche_menu();

		oslDrawMapSimple(CarrerMap);
		CarrerMap->scrollX += 1;

		if (GaucheMenu->x <= -GaucheMenu->stretchX+300){PossX += 6;GaucheMenu->x += 6;}

		oslDrawImage(GaucheMenu);
		oslDrawImage(HautMenu);

		DevsAffichageTexte(480 - 200, HautMenu->stretchY - 25,VERT,"MENU PRINCIPAL", 0);

		
		oslSetScreenClipping(-300 + 40+ PossX - 3, 110, 480, 272);

		if (ChoixMenu == 1)
		DevsAffichageTexte(-300 + 40+ PossX, 120,JAUNE,"NOUVEAU JEUX", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 120,BLEU,"NOUVEAU JEUX", 0);

		if (ChoixMenu == 2)
		DevsAffichageTexte(-300 +40+ PossX, 150,JAUNE,"OPTIONS", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 150,BLEU,"OPTIONS", 0);

		if (ChoixMenu == 3)
		DevsAffichageTexte(-300 +40+ PossX, 180,JAUNE,"PASSWORD", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 180,BLEU,"PASSWORD", 0);

		if (ChoixMenu == 4)
		DevsAffichageTexte(-300 +40+ PossX, 210,JAUNE,"QUITTER", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 210,BLEU,"QUITTER", 0);
		oslResetScreenClipping();

		if (valide == 1)
		{
			if (GaucheMenu->x < 480)
			{
				PossX += 6;
				GaucheMenu->x += 6;
				image01->x += 6;
			}

			if (GaucheMenu->x > 480)
			{
				switch (ChoixMenu)
				{
					case 1:
						MenuSonicStart();
						GaucheMenu->x = -GaucheMenu->stretchX ;
						GaucheMenu->y = 272 - GaucheMenu->stretchY;

						image01->x = 480 - image01->stretchX - 30;
						image01->y = 272 - image01->stretchY - 30;

						PossitionBarreY= 38;
						ChoixMenu = 1;
						valide = 0;
						PossX = 0;
						break;
					case 2:
						//valide = 1;
						break;
					case 3:
						//valide = 1;
						break;
					case 4:
						break;
				}
				
			}

		}


		oslDrawImage(image01);
		oslDrawImage(titre_haut);


		if (PossitionBarreY > 0 && valide == 0)PossitionBarreY --;
		else if (valide == 1)PossitionBarreY ++;
		//bleu
		oslSetScreenClipping(0 , 243+ PossitionBarreY , 480 , 272 + PossitionBarreY);
		DevsMyDrawLine(0 , 244+ PossitionBarreY , 480 , 244+ PossitionBarreY , RGBA(23, 7, 103, 255));
		DevsMyDrawLine(0 , 265 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(23, 7, 103, 255));
		DevsMyDrawFillRect(0 , 245 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(0, 0, 255, 255));
		DevsAffichageTexte(470-(DevsLongeurString("SONIC PAR PJEFF")), 246+ PossitionBarreY,BLANC,"SONIC PAR PJEFF", 0);
		oslResetScreenClipping();
		//fin bleu


	/*	oslSetBkColor(RGBA(0, 0, 0, 0));
		oslSetTextColor(RGBA(0, 0, 0, 255));
		oslPrintf_xy(40, 120,"NOUVEAU JEUX");
		oslPrintf_xy(40, 150,"OPTIONS");
		oslPrintf_xy(40, 180,"PASSWORD");
		oslPrintf_xy(40, 210,"QUITTER");
	*/


//		oslPrintf_xy(0, 80, "X: %i", (int)(GaucheMenu->x +GaucheMenu->stretchX));


		DevsSynchronisation();
	}

}



void Touche_menu()
{
 oslReadKeys();
 
 if (osl_keys->pressed.start){
		screenshot();
	}

 if (osl_keys->pressed.up){

	 ChoixMenu --;
	 if (ChoixMenu == 0)ChoixMenu = 4;

	}

 if (osl_keys->pressed.down){

	 ChoixMenu ++;
	 if (ChoixMenu == 5)ChoixMenu = 1;

	}

 if (osl_keys->pressed.cross){

	 
	 				switch (ChoixMenu)
				{
					case 1:
						valide = 1;
						break;
					case 2:
						//valide = 1;
						break;
					case 3:
						//valide = 1;
						break;
					case 4:
							oslEndGfx();
							oslQuit();
						break;
				}

	}


}



/////////////////////////////////////////////////////////
void ResetImagePerso()
{
	image01->x = 480;
	image02->x = 480;
	image03->x = 480;
	image04->x = 480;
	image05->x = 480;
	PossitionBarreY= 38;
}

void Touche_menuPersonnage()
{
 oslReadKeys();

  if (osl_keys->pressed.start){
		screenshot();
	}

 if (osl_keys->pressed.up){

	 ChoixMenu --;
	 if (ChoixMenu == 0)ChoixMenu = 5;
	 ResetImagePerso();

	}

 if (osl_keys->pressed.down){

	 ChoixMenu ++;
	 if (ChoixMenu == 6)ChoixMenu = 1;
	 ResetImagePerso();

	}

 if (osl_keys->pressed.cross){

	 valide = 1;

	}


}


void MenuSonicStart()
{

	titre_haut->x = -30;
	titre_haut->y = 30;

	GaucheMenu->x = -GaucheMenu->stretchX ;
	GaucheMenu->y = 272 - GaucheMenu->stretchY;

	PossX = 0;
	valide = 0;
	ChoixMenu = 1;
	PossitionBarreY= 38;


	image02->x = 480;
	image02->y = 272 - image02->stretchY - 30;

	image03->x = 480;
	image03->y = 272 - image03->stretchY - 30;

	image04->x = 480;
	image04->y = 272 - image04->stretchY - 30;

	image05->x = 480;
	image05->y = 272 - image05->stretchY - 30;

	image01->x = 480;
	image01->y = 272 - image01->stretchY - 30;

	int retour = 0;

	while (!osl_quit)
	{
		oslStartDrawing();
		Touche_menuPersonnage();

		oslDrawMapSimple(CarrerMap);
		CarrerMap->scrollX += 1;

		if (retour)break;

		if (GaucheMenu->x <= -GaucheMenu->stretchX+300){PossX += 6;GaucheMenu->x += 6;}

		if (ChoixMenu == 1)
			if (image02->x >= 480 - image02->stretchX - 30)image02->x -= 6;
		if (ChoixMenu == 2)
			if (image03->x >= 480 - image03->stretchX - 30)image03->x -= 6;
		if (ChoixMenu == 3)
			if (image04->x >= 480 - image04->stretchX - 30)image04->x -= 6;
		if (ChoixMenu == 4)
			if (image05->x >= 480 - image05->stretchX - 30)image05->x -= 6;
		if (ChoixMenu == 5)
			if (image01->x >= 480 - image01->stretchX - 30)image01->x -= 6;

		oslDrawImage(GaucheMenu);
		oslDrawImage(HautMenu);

		DevsAffichageTexte(480 - 200, HautMenu->stretchY - 25,VERT,"PERSONNAGES", 0);

		
		oslSetScreenClipping(-300 + 40+ PossX - 3, 110, 480, 272);

		if (ChoixMenu == 1)
		DevsAffichageTexte(-300 + 40+ PossX, 110,JAUNE,"SONIC", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 110,BLEU,"SONIC", 0);

		if (ChoixMenu == 2)
		DevsAffichageTexte(-300 +40+ PossX, 130,JAUNE,"TAILS", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 130,BLEU,"TAILS", 0);

		if (ChoixMenu == 3)
		DevsAffichageTexte(-300 +40+ PossX, 150,JAUNE,"KNUCKLES", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 150,BLEU,"KNUCKLES", 0);

		if (ChoixMenu == 4)
		DevsAffichageTexte(-300 +40+ PossX, 170,JAUNE,"CREAM", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 170,BLEU,"CREAM", 0);

	
		if (ChoixMenu == 5)
		DevsAffichageTexte(-300 +40+ PossX, 220,JAUNE,"RETOUR", 0);
		else
		DevsAffichageTexte(-300 +40+ PossX, 220,BLEU,"RETOUR", 0);
		//DevsAffichageTexte(-300 +40+ PossX, 200,BLEU,"COMMENCER", 0);
		oslResetScreenClipping();

		if (valide == 1)
		{
			if (GaucheMenu->x < 480)
			{
				PossX += 6;
				GaucheMenu->x += 6;
			}

			if (GaucheMenu->x > 480)
			{

				switch (ChoixMenu)
				{
					case 1:
						//MenuSonicStart();
						Level1Sonic();
						break;
					case 2:
						//valide = 1;
						Level1Sonic();
						break;
					case 3:
						//valide = 1;
						Level1Sonic();
						break;
					case 4:
						//valide = 1;
						Level1Sonic();
						break;
					case 5:
						retour = 1;
						break;
				}
				
			}

		}


		if (PossitionBarreY > 0 && valide == 0)PossitionBarreY --;
		else if (valide == 1)PossitionBarreY ++;
	
		switch (ChoixMenu)
				{
					case 1:
						oslDrawImage(image02);
						//bleu
						oslSetScreenClipping(0 , 243+ PossitionBarreY , 480 , 272 + PossitionBarreY);
						DevsMyDrawLine(0 , 244+ PossitionBarreY , 480 , 244+ PossitionBarreY , RGBA(23, 7, 103, 255));
						DevsMyDrawLine(0 , 265 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(23, 7, 103, 255));
						DevsMyDrawFillRect(0 , 245 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(0, 0, 255, 255));
						DevsAffichageTexte(470-(DevsLongeurString("SONIC THE HEDGEHOG")), 246+ PossitionBarreY,BLANC,"SONIC THE HEDGEHOG", 0);
						oslResetScreenClipping();
						//fin bleu
						break;
					case 2:
						oslDrawImage(image03);
						//orange
						oslSetScreenClipping(0 , 243 + PossitionBarreY , 480 , 272+ PossitionBarreY);
						DevsMyDrawLine(0 , 244+ PossitionBarreY , 480 , 244+ PossitionBarreY , RGBA(166, 103, 21, 255));
						DevsMyDrawLine(0 , 265 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(166, 103, 21, 255));
						DevsMyDrawFillRect(0 , 245 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(193, 156, 6, 255));
						DevsAffichageTexte(470-(DevsLongeurString("MILES 'tails' PROWER")), 246+ PossitionBarreY,BLANC,"MILES 'tails' PROWER", 0);
						oslResetScreenClipping();
						//fin orange
						break;
					case 3:
						oslDrawImage(image04);
						//rouge
						oslSetScreenClipping(0 , 243+ PossitionBarreY , 480 , 272+ PossitionBarreY);
						DevsMyDrawLine(0 , 244+ PossitionBarreY , 480 , 244+ PossitionBarreY , RGBA(163, 13, 13, 255));
						DevsMyDrawLine(0 , 265+ PossitionBarreY , 480 , 265+ PossitionBarreY, RGBA(163, 13, 13, 255));
						DevsMyDrawFillRect(0 , 245+ PossitionBarreY , 480 , 265+ PossitionBarreY, RGBA(255, 0, 0, 255));
						DevsAffichageTexte(470-(DevsLongeurString("KNUCKLES THE ECHIDNA")), 246+ PossitionBarreY,BLANC,"KNUCKLES THE ECHIDNA", 0);
						oslResetScreenClipping();
						//fin rouge
						break;
					case 4:
						oslDrawImage(image05);				
						//créme
						oslSetScreenClipping(0 , 243 + PossitionBarreY, 480 , 272+ PossitionBarreY);
						DevsMyDrawLine(0 , 244 + PossitionBarreY, 480 , 244+ PossitionBarreY , RGBA(193, 156, 6, 255));
						DevsMyDrawLine(0 , 265 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(193, 156, 6, 255));
						DevsMyDrawFillRect(0 , 245 + PossitionBarreY, 480 , 265+ PossitionBarreY, RGBA(239, 212, 102, 255));
						DevsAffichageTexte(470-(DevsLongeurString("CREAM THE RABBIT")), 246 + PossitionBarreY,BLANC,"CREAM THE RABBIT", 0);
						oslResetScreenClipping();
						//fin creme
						break;
					case 5:
						oslDrawImage(image01);
				}





		
		oslDrawImage(titre_haut);

		DevsSynchronisation();
	}


}