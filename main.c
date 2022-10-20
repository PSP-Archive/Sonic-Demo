#include "declaration.h"


PSP_MODULE_INFO("Sonic", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

extern void BouclePrincipal();

int main(int argc, char* argv[])
{

	BouclePrincipal();
	return 0;
}




/*
	Thread en mode kernel: il ne faut rien faire là dedans parce que c'est dangereux (on a accès à la flash et tout!)
	Afin d'éviter les ennuis, on va créer un thread en mode user et le jeu va s'exécuter depuis là. Ainsi on évite tout
	risque!
*/
/*
int main(int argc, char* argv[])
{
	
	#ifdef PSP
	//Initialise l'audio OSLib
	//oslInitAudioME(OSL_FMT_MP3);
	//BouclePrincipal();
	//Récupère le chemin, car le thread en mode user n'a aucun chemin par défaut, donc on ne trouvera aucun fichier.
	sceIoGetThreadCwd(sceKernelGetThreadId(), startPath, sizeof(startPath));

    //Création du thread en mode user, sans oublier qu'on a besoin de la VFPU.
    SceUID thid = sceKernelCreateThread("User Mode Thread", (int (*)(SceSize, void*))BouclePrincipal,
            0x12,		//Priorité par défaut
            256 * 1024, //Taille de la pile (ici 256 ko est la valeur par défaut)
            PSP_THREAD_ATTR_USER | THREAD_ATTR_VFPU, NULL);
	//thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);

    //Démarrage du thread user (le jeu, quoi)
    sceKernelStartThread(thid, 0, 0);
	//Attend jusqu'à ce qu'il ait terminé (càd indéfiniment)
    sceKernelWaitThreadEnd(thid, NULL);
	//sceIoChdir( "ms0:/PSP/GAME150/Mario_pjeff");  //set the current dir, so we can use relative path 
	//Initialisation de OSLib
	sceIoChdir(startPath);
	#else
	BouclePrincipal();
	#endif



	return 0;
}
*/