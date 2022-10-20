#include "declaration.h"



#ifdef PSPFW3XX
#endif


//PSP_MODULE_INFO("Mario Toy", 0x1006, 1, 0);// ???
PSP_MODULE_INFO("Sonic", 0x1006, 0, 1);
//PSP_MODULE_INFO("Mario Toy", 0x1000, 0, 1);
PSP_MAIN_THREAD_ATTR(0);
//PSP_HEAP_SIZE_MAX(); 
//PSP_HEAP_SIZE_KB(18*1024);
//PSP_MAIN_THREAD_STACK_SIZE_KB(4*1024);

/*
PSP_MODULE_INFO(PBPNAME_STR, 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();
*/


void BouclePrincipal();

/*
	Thread en mode kernel: il ne faut rien faire l� dedans parce que c'est dangereux (on a acc�s � la flash et tout!)
	Afin d'�viter les ennuis, on va cr�er un thread en mode user et le jeu va s'ex�cuter depuis l�. Ainsi on �vite tout
	risque!
*/
int main(int argc, char* argv[])
{
	
	#ifdef PSP
	//Initialise l'audio OSLib
	//oslInitAudioME(OSL_FMT_MP3);
	//BouclePrincipal();
	//R�cup�re le chemin, car le thread en mode user n'a aucun chemin par d�faut, donc on ne trouvera aucun fichier.
	sceIoGetThreadCwd(sceKernelGetThreadId(), startPath, sizeof(startPath));

    //Cr�ation du thread en mode user, sans oublier qu'on a besoin de la VFPU.
    SceUID thid = sceKernelCreateThread("User Mode Thread", (int (*)(SceSize, void*))BouclePrincipal,
            0x12,		//Priorit� par d�faut
            256 * 1024, //Taille de la pile (ici 256 ko est la valeur par d�faut)
            PSP_THREAD_ATTR_USER | THREAD_ATTR_VFPU, NULL);

    //D�marrage du thread user (le jeu, quoi)
    sceKernelStartThread(thid, 0, 0);
	//Attend jusqu'� ce qu'il ait termin� (c�d ind�finiment)
    sceKernelWaitThreadEnd(thid, NULL);
	//sceIoChdir( "ms0:/PSP/GAME150/Mario_pjeff");  //set the current dir, so we can use relative path 
	#else
	BouclePrincipal();
	#endif

	return 0;
}

/*
int main(int argc, char* argv[])
{

	BouclePrincipal();
	return 0;
}
*/

