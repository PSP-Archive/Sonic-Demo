

#include "declaration.h"


#ifdef PSP
#include <psputils.h>
#define min(x, y)		(((x) < (y)) ? (x) : (y))
#endif


OSL_IMAGE *blanc;


void BouclePrincipal()
{


#ifdef PSP
	scePowerSetClockFrequency(333, 333, 166); // etre sur d'utiliser la psp a plein regime lol
#endif
	//Initialisation
	oslInit(0);						
	oslInitGfx(OSL_PF_8888, 1);		
	oslInitConsole();			
	oslInitAudio();	

	osl_bilinearFilterEnabled = 1;
	oslSetBilinearFilter(1);


	#ifdef PSP
	#else
		FSOUND_Init(44100, 32, 0);	
	#endif
	
	

	//Quit directly if a file could not be found
	oslSetQuitOnLoadFailure(1);

	blanc = oslCreateImage(480, 272, OSL_IN_RAM, OSL_PF_5551);
	oslClearImage(blanc, RGB(255,255,255));	

	oslStartDrawing();
	oslDrawImage(blanc);

	oslEndFrame();
	oslSyncFrame();

	intro();
	MenuStart();
	InitMenu();
	MenuSonic();
	Level1Sonic();


recommence:



	while (!osl_quit)
	{
		//osl_skip indicates that frameskipping should be applied. Don't render anything when osl_skip is true!
		if (!osl_skip)		{
			oslStartDrawing();


		goto recommence;


			oslEndDrawing();
		}


		oslEndFrame();
		oslSyncFrame();
	}

	#ifdef PSP
	#else
		FSOUND_Close();	
	#endif

	oslEndGfx();
	oslQuit();

}