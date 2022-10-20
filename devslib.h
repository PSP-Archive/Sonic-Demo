/*****************************************************\
 Devslib et une librairie fait par le site de
 DEVSGEN.COM
 V.0.1 - Version Beta

\*****************************************************/


#include <oslib/oslib.h>
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "lua/luaconf.h"
#include "chipmunk/chipmunk.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  !FALSE
#endif

#define boolean int

#define pointer void *

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MIN3(a,b,c) MIN(MIN(a,b),MIN(b,c))
#define MAX3(a,b,c) MAX(MAX(a,b),MAX(b,c))

#define ABS(a)   ((a >= 0)?(a):-(a))


/************************************************************************************************/
/*                                                                                              */
/*                                     ANNIMATION                                               */
/*                                                                                              */
/************************************************************************************************/

/////dans cette premiere partie pour les annimation certaine chose seront plus claire et nettoyer la prochaine fois

//  pour les test de collition pour les pnj
typedef struct {
 
 int Gauche;
 int Droite;
 int Haut;
 int Bas;

} COLLISION;



typedef struct	{
	int position; //possition du player HAUT BAS GAUCHE DROITE SAUTE CE BAISSE
	int anim_marche;  // pour l'animation indique la possition actuel de l'annimation
	int temp_anim_marche; // pour l'animation
	int piece_gagner;  // pour le compteur de Mario
	int animation; //Nombre d'annimation pour l'object
	int anim_X;  // Largeur X de la taille du sprite pour l'annimation)
	int Vitesse; // Vitesse de l'annimation
	int BonusTime; // temps pour l'affichage d'un bonus
	int gauhe, droit ,haut, bas, Hauteur, sens;
	bool flipv, fliph, Active;

} ANIMATION;


// Infos sur Les Objects   (piece, Player, Ennemie)
typedef struct	OBJETS{
	//sprite du player
	OSL_IMAGE *sprite ;
	OSL_IMAGE *Photo_Dialogue ;
	float vx, vy;  // pour l'acceleration et les saut  
	float sauve_x, sauve_y;  // pour l'acceleration et les saut 
	float sauve_scrool_x, sauve_scrool_y;  // pour l'acceleration et les saut 
	bool auSol;  // En train de sauter ???
	int Vie;     //Nombre de vie
	bool mort;   // Mort ou vivant
	int piece_gagner;  // pour le compteur de Mario
	int bonus_gagner;  // pour le compteur de Mario
	int Next_bonus;  // pour le compteur de Mario
	int level;  // nivea courant
	int Next_level;  // prochaine niveau
	ANIMATION Animation;
	int type;	// Voir les T_defines pour le type d'objet
	int type2;	// Verifie si c'est un volant, un rampent , un sautant ....
	int npcCount; 
	int PieceCount; 
	int Collision;
	COLLISION Test_Collision;
	COLLISION PNJ_Collision;
	int Orientation; //Orientation pour les pnj
	int tempo_Orientation; //temporisation pour l'Orientation pour les pnj
	int timer;
	int Etat_perso ;//etat du personnage ( en introductio, en dialogue premiere etape ...)
	int intro;
	int ramasser;
	char *nom;
	void (*AI)(struct OBJETS* npc);//pointeur ver une intelligence artificiel adapter
	void (*Update)(struct OBJETS* npc);//pointeur ver une mise a jour de l'objet ou du personnage adapter a lui meme
	void (*F_Collision)(struct OBJETS* npc);//pointeur ver un systeme de collision adapter

} OBJETS;


extern OBJETS *DevsCreerSprite(OSL_IMAGE *Image,int PossitionDepard,int animation ,int anim_X,int Hauteur,int Vitesse );
extern void DevsAnimation_sprite(OBJETS* Obj);
extern void DevsSetAnimationFrameMax(OBJETS* Obj,int animation);
extern void DevsSetAnimationFramePause(OBJETS* Obj,int Poss,int animation);
extern void DevsChangePossition(OBJETS* Obj, int Poss);
extern void DevsSetFliphOn(OBJETS* Obj);
extern void DevsSetFliphOff(OBJETS* Obj);
extern void DevsDrawImageAnime(OBJETS* Obj);
extern void DevsAnimationPlay(OBJETS* Obj);
extern void DevsAnimationStop(OBJETS* Obj);
extern void DevsResetPossition(OBJETS* Obj);
extern void DevsSetAnimation(OBJETS* Obj,int animation ,int anim_X,int Hauteur,int Vitesse );
extern void DevsDeleteAnnimation(OBJETS* Obj);



/************************************************************************************************/
/*                                                                                              */
/*                                     TEXTE				                                    */
/*                                                                                              */
/************************************************************************************************/

//En mode numérique
//  pour les test de collition pour les pnj
typedef struct {
 int Largeur;
 int Hauteur;
 double FontTaille;
 OSL_IMAGE *Image;

} FONTDevs;

//couleur de texte toute faite
#define JAUNE RGBA(255, 255, 0, 255)
#define ROUGE RGBA(255, 0, 0, 255)
#define VERT RGBA(0, 255, 0, 255)
#define BLEU RGBA(0, 0, 255, 255)
#define NOIR RGBA(0, 0, 0, 255)
#define BLANC RGBA(255, 255, 255, 255)

extern void DevsAffichageTexte(int x, int y,OSL_COLOR couleur,char *texte, int alphaBack);
extern FONTDevs *DevsSetDessineLettre(OSL_IMAGE *Image,int Largeur, int Hauteur, double FontTaille);
//lettre possible : abcdefghijklmnopqrstuvx0123456,;:?.()
extern void DevsDessineLettre(FONTDevs* font,int x, int y, char *Texte);
extern void DevsDessineChiffre(FONTDevs* font,int x, int y,int nombre);
extern void DevsAffichageTexte(int x, int y,OSL_COLOR couleur,char *texte, int alphaBack);
extern int DevsLongeurString(const char *str);
extern unsigned int DevsNb_Chiffres(unsigned int n);
extern void Devs_strcpy(char *dst, char *src, u32 maxlen);
extern void Devs_strcat(char *dst, char *src, u32 maxlen);
extern int Devs_atoi (char *str);
extern void DevsTexteWave( int x, int y, const char *texte);
extern void DevsTexteHautBas( int x, int y, const char *texte);
extern char *DevsStringLimite(char *str, int longeur);
extern char* DevsStr_replace (const char* txt, const char* Avant, const char* Apres);
extern void DevsTexteColorer(int PossX, int PossY,char *Texte);
extern char *DevsFileExtension (char *Depard);
extern void DevsSuppExtension (char *Depard, char *Sortie);
extern char *DevsSuppPath (char *pathname);
extern void DevsDeleteFont(FONTDevs* font);


/************************************************************************************************/
/*                                                                                              */
/*                                    LOG					                                    */
/*                                                                                              */
/************************************************************************************************/

extern void DevsAjouter_Fichier_LOG(char * Fichier,char * Texte);
extern bool DevsTest_Presence_Fichier(char * Fichier);


/************************************************************************************************/
/*                                                                                              */
/*                                     COLLISION			                                    */
/*                                                                                              */
/************************************************************************************************/

extern int Devscolision(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY );
extern int Devscolision_rayon(OSL_IMAGE *img1,float img1posX, float img1posY, OSL_IMAGE *img2, float img2posX, float img2posY , float Rayon);
extern int Devscolision_Sens(OBJETS* sprite1,OBJETS* sprite2,int Gauche,int Droite,int Haut,int Bas );
extern int DevscolisionObj(OBJETS* sprite1,OBJETS* sprite2 );
extern int DevscolisionCercle(int x1 , int y1 , int r1 ,int x2 , int y2 , int r2 , int offset);
extern int DevscolisionSpriteCercle(OSL_IMAGE *a , int x1 , int y1 , OSL_IMAGE *b , int x2 , int y2 , int offset);
extern int DevscolisionCercleObj(OBJETS* sprite1,OBJETS* sprite2, int offset);

/************************************************************************************************/
/*                                                                                              */
/*                                     MAP					                                    */
/*                                                                                              */
/************************************************************************************************/

extern short DevsGetTile(OSL_MAP *m,int col, int row);


/************************************************************************************************/
/*                                                                                              */
/*                                     FENETRE				                                    */
/*                                                                                              */
/************************************************************************************************/
//a venir !!!!!!!!!!!!!!!!!!!!!!!

typedef struct WINDOW		{
	char *titre;
	char *texte;
	char *button1;
	char *button2;
	int buttons; //type de fenetre ?
	int ouverte; //ouverte ou non
	int startX;
	int startY;
	OSL_COLOR Ctitre1;
	OSL_COLOR Ctitre2;
	OSL_COLOR colorFond1;
	OSL_COLOR colorFond2;

} WINDOW;

extern void DevsInitWindows();
extern void DevsAffichierWindowBox3(int tailleX, int tailleY, int PossX, int PossY);
extern void DevsDrawWindowBox3(int x0, int y0, int x1, int y1);
extern void DevsDrawBouttonBox(int x0, int y0, int x1, int y1, int active,char *Texte);
extern void DevsAffichierWindowBox2(int tailleX, int tailleY, int PossX, int PossY,char *titre);
extern void DevsDrawWindowBox2(int x0, int y0, int x1, int y1, int TitreX);
extern void DevsMySetTextColor(OSL_COLOR color);
extern int DevsAffichierWindowBox(WINDOW *w);
extern void DevsDrawWindowBox(int x0, int y0, int x1, int y1);


/************************************************************************************************/
/*                                                                                              */
/*                                     EFFET FX				                                    */
/*                                                                                              */
/************************************************************************************************/
typedef struct {
 int Largeur;
 int Hauteur;
 int tile;
 int type;
 int vitesse;
 int tempo;
 OSL_IMAGE *Image;
 int moin,plus;
 int largeur,hauteur;
 int active;// pour les masques si 1 alor le masque et lancer

 
 unsigned int tempsAB;
 unsigned int tempsBA;
 unsigned int compteur;
 int from;
 int to;
 int nbLoops;
 int currentLoop;
 bool aToB;

 unsigned int duree;
 unsigned int dureemini;
 bool direction;

 unsigned short ZoomX;
 unsigned short unZoomX;
 unsigned short ZoomY;
 unsigned short unZoomY;
 bool growing;

} FXDevs;


extern void DevsReinitialiseFX(FXDevs *FX);
extern FXDevs *DevsChargeEffetCube(char *Fichier,int Largeur,int Hauteur,int type, int vitesse, int tile);
extern void DevsLogoDrawTiles(FXDevs *FX);
extern void DevsActiveCubeFX(FXDevs *FX);
extern FXDevs *DevsFxmasque(char *Fichier);
extern void DevsFX_masque_update(FXDevs *fx);
extern void DevsFX_masque_dessine(FXDevs *fx);
extern void DevsFX_active(FXDevs *fx,int plus, int moin);
extern void DevsDeleteFX(FXDevs *FX);
extern void DevsFX_FadeIn();
extern void DevsFX_MasqueRectangle(OSL_COLOR color);
extern void DevsFX_masque_cube(int tailleX,int TailleY ,OSL_COLOR color);


/************************************************************************************************/
/*                                                                                              */
/*                                     SCREENSHOT			                                    */
/*                                                                                              */
/************************************************************************************************/
//Prise des screenshot pendant le jeux et sauvegarde dans le dossier picture dans la racine de la carte memoire
extern void Devsscreenshot();



/************************************************************************************************/
/*                                                                                              */
/*                                     PARTICULE			                                    */
/*                                                                                              */
/************************************************************************************************/



#define cGfxParticleSet		4
#define MaxParticules	600
#define cGfxParticleState	4


typedef struct PARTICLE
{
	int	x[ cGfxParticleSet ];//poss x
	int	y[ cGfxParticleSet ];//poss y
	int	dx[ cGfxParticleSet ];//distance x
	int	dy[ cGfxParticleSet ];//distance y
	int sx[ cGfxParticleSet ];//direction y
	int sy[ cGfxParticleSet ];//direction y
	int	status;


} PARTICLE;

typedef struct PARTICULE
{

PARTICLE	particle[ MaxParticules ];
OSL_IMAGE		*Images[ cGfxParticleState ];

int vie;//	50
int Vitesse;//	30 //30
int Vitesse_Mini;//	10
int Graviter;//	4

} PARTICULE;

extern PARTICULE *DevsInitParticule(char *Fichier);
extern void DevsgfxUpdateParticles(PARTICULE *Part);
extern void DevsgfxInitParticles(PARTICULE *Part,int duree,int vitesse,int Graviter,int vitessemini);
extern void DevsgfxNewParticle(PARTICULE *Part, int x, int y );
extern void DevsgfxRenderParticles(PARTICULE *Part);
extern void DevsDeleteParticule(PARTICULE *Part);
extern void DevsgfxMoveXParticle( PARTICULE *Part,int x);
extern void DevsgfxMoveYParticle( PARTICULE *Part,int y );




/************************************************************************************************/
/*                                                                                              */
/*                                     INIPARSER			                                    */
/*                                                                                              */
/************************************************************************************************/


typedef struct _dictionary_ {
	int				n ;		/** Number of entries in dictionary */
	int				size ;	/** Storage size */
	char 		**	val ;	/** List of string values */
	char 		**  key ;	/** List of string keys */
	unsigned	 *	hash ;	/** List of hash values for keys */
} dictionary ;

extern unsigned dictionary_hash(char * key);
extern dictionary * dictionary_new(int size);
extern void dictionary_del(dictionary * vd);
extern char * dictionary_get(dictionary * d, char * key, char * def);
extern int dictionary_set(dictionary * vd, char * key, char * val);
extern void dictionary_unset(dictionary * d, char * key);
extern void dictionary_dump(dictionary * d, FILE * out);


#define iniparser_getstr(d, k)  iniparser_getstring(d, k, NULL)
#define iniparser_setstr        iniparser_set

extern int iniparser_getnsec(dictionary * d);
extern char * iniparser_getsecname(dictionary * d, int n);
extern void iniparser_dump_ini(dictionary * d, FILE * f);
extern void iniparser_dump(dictionary * d, FILE * f);
extern char * iniparser_getstring(dictionary * d, const char * key, char * def);
extern int iniparser_getint(dictionary * d, const char * key, int notfound);
extern double iniparser_getdouble(dictionary * d, char * key, double notfound);
extern int iniparser_getboolean(dictionary * d, const char * key, int notfound);
extern int iniparser_set(dictionary * ini, char * entry, char * val);
extern void iniparser_unset(dictionary * ini, char * entry);
extern int iniparser_find_entry(dictionary * ini, char * entry) ;
extern dictionary * iniparser_load(const char * ininame);
extern void iniparser_freedict(dictionary * d);


/************************************************************************************************/
/*                                                                                              */
/*                                     MENUROND				                                    */
/*                                                                                              */
/************************************************************************************************/


typedef struct {
 
	int AlphaMenu; //alpha celon l'eloignement
	int AngleVoullue; //angle desiter pour la rotation
	int nbIcones; //nb d'image dans le cercle
	int SelectionEncour ; //Ou en et la possition du menu par defaut doit ETRE A 0
	OSL_IMAGE *Image; //Image pour le menu
	int TailleIconeX; //dimantion d'une Icone en X
	int TailleIconeY; // dimantion d'une Icone en Y
	int Eloignement; //Eloignement de menu par rapport a la possition d'origine
	int test_angle;
	int PossitionX; //Possition du menu en X
	int PossitionY; //Possition du menu en Y
	int LargeurAnimX;//eloignement de l'annimation entre les icones sur la largeur
	int LargeurAnimY;//eloignement de l'annimation entre les icones sur la Hauteur

} MENUSPECIAL;


extern void DevsmenuDrawImageFloat(OSL_IMAGE *img, float x, float y, float stretchX, float stretchY);
extern void DevsmenuDrawIcons_Move(MENUSPECIAL *MenuS,int sens);
extern void DevsmenuUpdateIcons_circle(MENUSPECIAL *MenuS);
extern int DevsmenuDrawIcons_Possition(MENUSPECIAL *MenuS);
extern void DevsmenuDrawIcons_circle(MENUSPECIAL *MenuS,int angle, int Eloignement);
extern MENUSPECIAL *DevsCreateMenuCircle(char *fichier, int nbIcones, int Eloignement, int SelectionEncour,int TailleIconeX,int TailleIconeY,int PossitionX, int PossitionY,int LargeurAnimX, int LargeurAnimY);
extern void DevsDeleteMenuRond(MENUSPECIAL *MenuS);



/************************************************************************************************/
/*                                                                                              */
/*                                     MATH					                                    */
/*                                                                                              */
/************************************************************************************************/
extern int Devsmod(int x, int y);
extern float Devsmod_f(float x, float y);
extern float DevsrangeAnglef(float angle);
extern float DevsadapteAnglef(float angle1, float angle2);
extern int DevssysRand( int max );
extern double DevsranddoubleMM(double min, double max) ;
extern double DevsranddoubleM(double max); 
extern double Devsranddouble() ;
extern float DevsrandfloatMM(float min, float max) ;
extern float DevsrandfloatM(float max) ;
extern float Devsrandfloat() ;
extern int DevsrandintMM(int min, int max) ;
extern int DevsrandintM(int max) ;
extern int sqrt2(unsigned int n);
/************************************************************************************************/
/*                                                                                              */
/*                                     SYSTEME				                                    */
/*                                                                                              */
/************************************************************************************************/



/************************************************************************************************/
/*                                                                                              */
/*                                     VIDEO     			                                    */
/*                                                                                              */
/************************************************************************************************/

extern void DevsMyDrawRect(int x0, int y0, int x1, int y1, OSL_COLOR color);
extern void DevsMyDrawFillRect(int x0, int y0, int x1, int y1, OSL_COLOR color);
extern void DevsMyDrawGradientRect(int x0, int y0, int x1, int y1, OSL_COLOR color1, OSL_COLOR color2, OSL_COLOR color3, OSL_COLOR color4);
extern void DevsMyDrawLine(int x0, int y0, int x1, int y1, OSL_COLOR color);
extern void DevsDrawImageSimpleFlip(OSL_IMAGE *img, int flipType);
extern void DevsSynchronisation(); //synchronise l'image a la fin de la boucle
extern void DevsDrawGradientLine(int x0, int y0, int x1, int y1, OSL_COLOR color , OSL_COLOR color2);
extern void DevsDrawGradientTriangle(int x0, int y0, int x1, int y1 , int x2, int y2, OSL_COLOR c1, OSL_COLOR c2, OSL_COLOR c3);
extern void DevsDrawCircle ( int centerX , int centerY , int radius , OSL_COLOR color );
extern void DevsDrawFillCircle ( int centerX , int centerY , int radius , OSL_COLOR color );
extern void DevsDrawImageZoom(OSL_IMAGE *img,int Zoom);

/************************************************************************************************/
/*                                                                                              */
/*                                    Fichier					                                    */
/*                                                                                              */
/************************************************************************************************/


void DevsExecEboot3xx (char *fichier);
void DevsExecEboot(const char *pbpath);
static int DevsRenommer(char *Fichier1, char *Fichier2);
static int DevsSuppFichier(char *Fichier);
static int DevsSuppDossier(char *path);
static int DevsCreeDossier(char *path);


///////////

#ifdef __cplusplus
}
#endif