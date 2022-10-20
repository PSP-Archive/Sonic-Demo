/*****************************************************\
 Sonic
 Autor : Foury Jean-francois
 V.0.1 - Version Beta

\*****************************************************/
//defines

#include "devslib.h"

#include "fmod/fmod.h"

#ifdef PSP
#include <psputils.h>
#endif

#define min(x, y)		(((x) < (y)) ? (x) : (y))
#define max(x, y)		(((x) > (y)) ? (x) : (y))


static char startPath[1024];

extern OSL_IMAGE *blanc;
extern OSL_FONT *maFonte, *maFonte2, *maFonte3;


extern void BouclePrincipal();

extern void intro();
extern void MenuSonic();
extern void InitMenu();
extern void MenuStart();

extern void Level1Sonic();

extern void screenshot();