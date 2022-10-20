/***************************************************************************************************
****************************************************************************************************
******************************             FOURY                ************************************
******************************         Jean-Francois            ************************************
******************************            DevsLib		        ************************************          
******************************                                  ************************************          
****************************************************************************************************/

#include "declaration.h"
#include "carte/niveau1/Tiles1.h"
#include "carte/niveau1/collision.h"


OSL_IMAGE *Niveau1 , *Niveau1Coll;
OSL_MAP *Niveau1Map, *Niveau1MapColl;


typedef enum {
  T_PERSO_ATTENTE,
  T_PERSO_COUR,
  T_PERSO_SAUT,
  T_PERSO_SUPERSAUT,
  T_PERSO_MARCHE,
  T_PERSO_BOULEDEBUT,
  T_PERSO_BOULECHARGE,
  T_PERSO_BOULEPART,
  T_PERSO_VRILLE,
  T_PERSO_BARRE,
  T_PERSO_MORT
 };

OBJETS *sonic[15];
OBJETS *Photo;
const float vitesseSaut = -6.0f;
const float niveauSol = 272.0f;//194.0f;
const float gravite = 0.25f;


/*
bool answer=false; 
OSL_IMAGE *theimage=oslLoadImageFile("theimage.png", OSL_IN_RAM, OSL_PF_8888); 
OSL_COLOR pixel=oslConvertColorEx(theimage->palette, OSL_PF_8888, theimage->pixelFormat, oslGetImagePixel(theimage, 10, 10)); 
if(pixel==RGB(255,0,255)) 
    answer=true; 

	*/
/*
It would be nice to do map and collisionmap, theyre the same cord so i can do something like that

bool collision(xplus,yplus)
{
bool coll=false;
OSL_IMAGE *theimage=oslLoadImageFile("theimage.png", OSL_IN_RAM, OSL_PF_8888);
OSL_COLOR pixel=oslConvertColorEx(theimage->palette, OSL_PF_8888, theimage->pixelFormat, oslGetImagePixel(theimage, y+yplus, y+yplus));
if(pixel==RGB(255,0,255))
answer=true; 
return answer;
}
But like my friend i have no idea how to check this on map.
*/




/*
====================
scolisionPixel

Verifie si il y a une colision entre 2 sprites
en Pixel Perfect !!
====================
*/
int scolisionPixel(OBJETS* img1,OSL_IMAGE *img2,int skip ) { 

	//int coll = 0;
   float img1width  = (float)img1->Animation.anim_X; 
   float img1height = (float)img1->Animation.Hauteur; 
   float img2width  = (float)img2->stretchX; 
   float img2height = (float)img2->stretchY; 
 
   if ((img1->sprite->x + img1width > img2->x) && 
       (img1->sprite->x < img2->x + img2width) && 
       (img1->sprite->y + img1height > img2->y) && 
       (img1->sprite->y < img2->y + img2height) ) { 
       //  coll = 1;                
   }      
	return 0; 

	
/*Now lets make the bouding box for which we check for a pixel collision*/

	/*To get the bounding box we do
            Ax1,Ay1______________
                |                |
                |                |
                |                |
                |    Bx1,By1____________
                |        |       |      |
                |        |       |      |
                |________|_______|      |
                         |    Ax2,Ay2   |
                         |              |
                         |              |
                         |___________Bx2,By2

	To find that overlap we find the biggest left hand cordinate
	AND the smallest right hand co-ordinate

	To find it for y we do the biggest top y value
	AND the smallest bottom y value

	Therefore the overlap here is Bx1,By1 --> Ax2,Ay2

	Remember	Ax2 = Ax1 + SA->w
			Bx2 = Bx1 + SB->w

			Ay2 = Ay1 + SA->h
			By2 = By1 + SB->h
	*/

	/*now we loop round every pixel in area of
	intersection
		if 2 pixels alpha values on 2 surfaces at the
		same place != 0 then we have a collision*/

	/*a - bottom right co-ordinates in world space*/
	int ax1 = img1->sprite->x + img1width - 1;
	int ay1 = img1->sprite->y + img1height - 1;

	/*b - bottom right co-ordinates in world space*/
	int bx1 = img2->x + img2width - 1;
	int by1 = img2->y + img2height - 1;


	int xstart = max(img1->sprite->x,img2->x);
	int xend = min(ax1,bx1);

	int ystart = max(img1->sprite->y,img2->y);
	int yend = min(ay1,by1);

	int y, x;
	for(y = ystart ; y <= yend ; y += skip)
	{
		for(x = xstart ; x <= xend ; x += skip)
		{
			//compute offsets for surfacebefore pass to TransparentPixel test
		//	if(!SDL_CollideTransparentPixel(as , x-ax , y-ay)
		//	&& !SDL_CollideTransparentPixel(bs , x-bx , y-by))

		//	OSL_COLOR pixel=oslConvertColorEx(img2->palette, OSL_PF_8888, img2->pixelFormat, oslGetImagePixel(img2, y+yplus, y+yplus));
		//	if(pixel==RGB(255,0,255))
				return 1;
		}
	}
	
	return 0;
}





/*
=================
oslCollisionMap_Sonic

// test les collisions entre 1 map et un sprite
=================
*/

int oslCollisionMap_Sonic(OSL_MAP *m,OBJETS* npc,int haut,int bas, int gauche, int droit)  
{
 int tile;
 int rel_posX ;
 int rel_posY ;


if (haut)
 {
	rel_posX = (m->scrollX + npc->sprite->x+npc->Animation.anim_X - 6 )/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;  
  if (!tile)
  {
	rel_posX = ((m->scrollX + npc->sprite->x +6  ))/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y  )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;   
  }
 
  if (!tile)
  {
	rel_posX = ((m->scrollX + npc->sprite->x  + (npc->Animation.anim_X/2)))/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;   
  }
 }

if (bas)
 {
	 rel_posX = (m->scrollX + npc->sprite->x+npc->Animation.anim_X -6 )/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y +npc->Animation.Hauteur -2 )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;  
  if (!tile)
  {
	rel_posX = (m->scrollX + npc->sprite->x +6 )/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y + npc->Animation.Hauteur - 2 )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;  
  }
  if (!tile)
  {
	rel_posX = ((m->scrollX + npc->sprite->x  + (npc->Animation.anim_X/2)))/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y + npc->Animation.Hauteur - 2 )/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;   
  }
 }


if (gauche)
 {
	rel_posX = ((m->scrollX + npc->sprite->x - 4 ))/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y - 4)/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;  

   if (!tile)
	{
	rel_posX = ((m->scrollX + npc->sprite->x - 4))/ m->tileX;
	rel_posY = (m->scrollY + npc->sprite->y +(npc->Animation.Hauteur/2))/ m->tileY;
	tile = DevsGetTile(m,rel_posX,rel_posY) ;
    }

  if (!tile)
	{
		rel_posX = ((m->scrollX + npc->sprite->x - 4 ))/ m->tileX;
		rel_posY = (m->scrollY + npc->sprite->y +(npc->Animation.Hauteur - 2))/ m->tileY;
		tile = DevsGetTile(m,rel_posX,rel_posY) ;
    }
 }

if (droit)
 {
	 	rel_posX = ((m->scrollX + npc->sprite->x + npc->Animation.anim_X + 4))/ m->tileX;
		rel_posY = (m->scrollY + npc->sprite->y -4)/ m->tileY;
		tile = DevsGetTile(m,rel_posX,rel_posY) ;
   if (!tile)
	{
		rel_posX = ((m->scrollX + npc->sprite->x + npc->Animation.anim_X + 4))/ m->tileX;
		rel_posY =  (m->scrollY + npc->sprite->y + (npc->Animation.Hauteur /2))/ m->tileY;
		tile = DevsGetTile(m,rel_posX,rel_posY) ;
    }
  
  if (!tile)
	{
		rel_posX = ((m->scrollX + npc->sprite->x + npc->Animation.anim_X + 4))/ m->tileX;
		rel_posY =  (m->scrollY + npc->sprite->y + (npc->Animation.Hauteur - 2 ))/ m->tileY;
		tile = DevsGetTile(m,rel_posX,rel_posY) ;
    }
 }


 	switch(tile)
		{
			case 0:
				// pas de collision sur le sprite 0
				return 0;
				break;
			case 1:
				// impassable
				return 1;
				break;
			case 2:
			/*	// passable uniquement par le bas ( comme pour des plateforme)
				if (haut)
				{
				return 2;
				}
				else
				{
			*/	return 1;
			//	}
				break;
			case 3:
				// case bonnus non cassable
				return 0;
				break;
			case 4:
				// case non cassable mais pas bonnus rebondit un peut
				return 1;
				break;
			case 5:	
				// teleporteur
				return 1;
				break;
			case 6:
				// Fin du niveau
				return 1;
				break;
			case 7:
				// case pour les piece
				return 1;
				break;
			case 8:
				// case pour les 1up
				return 1;
				break;
			case 9:
				// case pour les champi pour grandit
				return 1;
				break;

	}


return 0;
}

/*
=================
CopyXY

Copi les coordonner d'un objet ver un autre
=================
*/
void CopyXY(OBJETS* source,OBJETS* Destination)
{
	Destination->sprite->x = source->sprite->x;
	Destination->sprite->y = source->sprite->y + source->Animation.Hauteur - Destination->Animation.Hauteur;

}


/*
=================
ToucheNiveau1

Gestion des touche dans je jeux Sonic en lui meme
=================
*/
void ToucheNiveau1()
{
 oslReadKeys();

 	//Croix: Saut
	if (osl_keys->pressed.cross && sonic[T_PERSO_ATTENTE]->auSol)	{
		
		sonic[T_PERSO_ATTENTE]->vy = vitesseSaut; //on saute
		sonic[T_PERSO_ATTENTE]->auSol = 0; //plus au sol
/*		if (sonic[T_PERSO_ATTENTE]->type == T_PERSO_COUR)
		{
		DevsResetPossition(sonic[T_PERSO_SUPERSAUT]);//fait un reset de l'annimation saut
		sonic[T_PERSO_ATTENTE]->type = T_PERSO_SUPERSAUT;//indique que c'est l'annimation pour sauter qui et utiliser
		}else
		{
	*/	DevsResetPossition(sonic[T_PERSO_SAUT]);//fait un reset de l'annimation saut
		sonic[T_PERSO_ATTENTE]->type = T_PERSO_SAUT;//indique que c'est l'annimation pour sauter qui et utiliser
	//	}
	}


  if (osl_keys->pressed.start){
		screenshot();
	}

  //oslCollisionMap_Sonic(OSL_MAP *m,OBJETS* npc,int haut,int bas, int gauche, int droit)  
/////////////////GAUCHE////////////////////////
  /*
if (osl_keys->held.left && osl_keys->held.circle && !sonic[T_PERSO_ATTENTE]->auSol){

	DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);

	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.08f, -6.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;

	}
else if (osl_keys->held.left && !sonic[T_PERSO_ATTENTE]->auSol){

	DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);

	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.08f, -4.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;

	}
*/
  if (osl_keys->held.left && osl_keys->held.circle && !sonic[T_PERSO_ATTENTE]->auSol){

	 if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx < 0) 
	 {
		 DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);
	 }
	  else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx > 1) 
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.12f, -4.0f);
	  }

	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.08f, -6.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;

	}
else if (osl_keys->held.left && !sonic[T_PERSO_ATTENTE]->auSol){

	 if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx < 0) 
	 {
		 DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);
	 }
	 	 else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx > 1) 
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.12f, -4.0f);
	  }

	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.08f, -4.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;

	}

 else if (osl_keys->held.left && osl_keys->held.circle){

	 if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx < 0) 
	 {
		 DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);
	 }
	 else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx > 1) 
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.12f, -4.0f);
	  }


	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.08f, -6.0f);
	 if (sonic[T_PERSO_ATTENTE]->vx < -2.1f)
		{
			 sonic[T_PERSO_ATTENTE]->type = T_PERSO_COUR;
		}
	 else
		{
			sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
		}
	}
 else if (osl_keys->held.left){

	 if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx < 0) 
	 {
		 DevsSetFliphOn(sonic[T_PERSO_ATTENTE]);
	 }
	 else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx > 1) 
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.12f, -4.0f);
	  }
	 sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.06f, -4.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
	}




////////////////////Droite///////////////////////////

  else if (osl_keys->held.right && osl_keys->held.circle && !sonic[T_PERSO_ATTENTE]->auSol){

	if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx  > 0) 
	{
		DevsSetFliphOff(sonic[T_PERSO_ATTENTE]);
	}
	else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx < -1)
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.12f, 4.0f);
	  }
	  sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.08f, 6.0f);
	  sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;
	}
   else if (osl_keys->held.right && !sonic[T_PERSO_ATTENTE]->auSol){

	if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx  > 0) 
	{
		DevsSetFliphOff(sonic[T_PERSO_ATTENTE]);
	}
	else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx < -1)
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.12f, 4.0f);
	  }
	  sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.08f, 4.0f);
	  sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;
	}



  else if (osl_keys->held.right && osl_keys->held.circle){
	if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx  > 0) 
	{
		DevsSetFliphOff(sonic[T_PERSO_ATTENTE]);
	}
	else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx < -1)
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.12f, 4.0f);
	  }

	 sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.08f, 6.0f);
	 if (sonic[T_PERSO_ATTENTE]->vx > 2.1f)
	 {
		 sonic[T_PERSO_ATTENTE]->type = T_PERSO_COUR;

	 }
	 else
	 {
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
	 }
	}
  else  if (osl_keys->held.right){
	  if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx  >= 0) 
	  {
		  DevsSetFliphOff(sonic[T_PERSO_ATTENTE]);
	  }
	  else if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx < -1)
	  {
		  //on ralenti le personnage un peut plus
		sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.12f, 4.0f);
	  }
	sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.06f, 4.0f);
	 sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
	}


  else if(osl_keys->held.circle && !osl_keys->held.right && !osl_keys->held.left)
  {
		if (sonic[T_PERSO_ATTENTE]->type == T_PERSO_ATTENTE)
				sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULECHARGE;
	//	else if (sonic[T_PERSO_ATTENTE]->type == T_PERSO_ATTENTE)
	//			sonic[T_PERSO_ATTENTE]->type = T_PERSO_ATTENTE;
  
  }

/*
  else if( osl_keys->held.value && sonic[T_PERSO_ATTENTE]->auSol )
  {
		sonic[T_PERSO_ATTENTE]->type = T_PERSO_ATTENTE;

		if (sonic[T_PERSO_ATTENTE]->vx < 0.0f)sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.03f, 0.0f);
		else if (sonic[T_PERSO_ATTENTE]->vx > 0.0f)sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.03f, 0.0f);
  }
*/
  else if(!osl_keys->held.value)
  {
	  	if (sonic[T_PERSO_ATTENTE]->type == T_PERSO_BOULECHARGE)
		{
				sonic[T_PERSO_ATTENTE]->type = T_PERSO_BOULEPART;
				//faire attention au sens !!
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_ATTENTE]->vx = -8.0f;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_ATTENTE]->vx = 8.0f;
				
		}
		else 
		{
		if (sonic[T_PERSO_ATTENTE]->vx == 0)sonic[T_PERSO_ATTENTE]->type = T_PERSO_ATTENTE;
		if (sonic[T_PERSO_ATTENTE]->vx < 0.0f)
		{
			sonic[T_PERSO_ATTENTE]->vx = min(sonic[T_PERSO_ATTENTE]->vx + 0.06f, 0.0f);
			if (sonic[T_PERSO_ATTENTE]->vx > -2.0f)sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
		}
		else if (sonic[T_PERSO_ATTENTE]->vx > 0.0f)
		{
			sonic[T_PERSO_ATTENTE]->vx = max(sonic[T_PERSO_ATTENTE]->vx - 0.06f, 0.0f);
			if (sonic[T_PERSO_ATTENTE]->vx < 2.0f)sonic[T_PERSO_ATTENTE]->type = T_PERSO_MARCHE;
		}
		}
  }

 else if (osl_keys->held.up){
	//Niveau1Map->scrollY -= 3;
	}

 else if (osl_keys->held.down){
	//Niveau1Map->scrollY += 3;
	}

}



/*
=================
InitSonic

Initialise tout les annimation et parametre de sonic
=================
*/
void InitSonic()
{

	
	Photo = DevsCreerSprite(oslLoadImageFile("perso/sonic/photo.png", OSL_IN_RAM, OSL_PF_5551),0, 8 ,40,38,30);
	DevsAnimationPlay(Photo);
	Photo->sprite->x = 10;
	Photo->sprite->y = 2;



	sonic[T_PERSO_SUPERSAUT] = DevsCreerSprite(oslLoadImageFile("perso/sonic/super_saut.png", OSL_IN_RAM, OSL_PF_5551),0, 11 ,26,44,10);
	DevsAnimationPlay(sonic[T_PERSO_SUPERSAUT]);
	sonic[T_PERSO_SUPERSAUT]->sprite->x =50;
	sonic[T_PERSO_SUPERSAUT]->sprite->y =272-sonic[T_PERSO_SUPERSAUT]->Animation.Hauteur;


	//declaration pour sonic
	sonic[T_PERSO_ATTENTE] = DevsCreerSprite(oslLoadImageFile("perso/sonic/attend.png", OSL_IN_RAM, OSL_PF_5551),0, 3 ,26,45,60);
	DevsAnimationPlay(sonic[T_PERSO_ATTENTE]);
	sonic[T_PERSO_ATTENTE]->sprite->x =150;
//	sonic[T_PERSO_ATTENTE]->sprite->y =272-sonic[T_PERSO_ATTENTE]->Animation.Hauteur;
	sonic[T_PERSO_ATTENTE]->sprite->y =50;


	sonic[T_PERSO_MARCHE] = DevsCreerSprite(oslLoadImageFile("perso/sonic/marche.png", OSL_IN_RAM, OSL_PF_5551),0, 8 ,37,35,12);
	DevsAnimationPlay(sonic[T_PERSO_MARCHE]);
	sonic[T_PERSO_MARCHE]->sprite->x =150;
	sonic[T_PERSO_MARCHE]->sprite->y =272-sonic[T_PERSO_MARCHE]->Animation.Hauteur;


	sonic[T_PERSO_COUR] = DevsCreerSprite(oslLoadImageFile("perso/sonic/cour.png", OSL_IN_RAM, OSL_PF_5551),0, 4 ,35,37,12);
	DevsAnimationPlay(sonic[T_PERSO_COUR]);
	sonic[T_PERSO_COUR]->sprite->x =200;
	sonic[T_PERSO_COUR]->sprite->y =272-sonic[T_PERSO_COUR]->Animation.Hauteur;


	sonic[T_PERSO_VRILLE] = DevsCreerSprite(oslLoadImageFile("perso/sonic/spyrale.png", OSL_IN_RAM, OSL_PF_5551),0, 11 ,29,37,10);
	DevsAnimationPlay(sonic[T_PERSO_VRILLE]);
	sonic[T_PERSO_VRILLE]->sprite->x =250;
	sonic[T_PERSO_VRILLE]->sprite->y =272-sonic[T_PERSO_VRILLE]->Animation.Hauteur;


	sonic[T_PERSO_MORT] = DevsCreerSprite(oslLoadImageFile("perso/sonic/toucher.png", OSL_IN_RAM, OSL_PF_5551),0, 5 ,34,38,10);
	DevsAnimationPlay(sonic[T_PERSO_MORT]);
	sonic[T_PERSO_MORT]->sprite->x =300;
	sonic[T_PERSO_MORT]->sprite->y =272-sonic[T_PERSO_MORT]->Animation.Hauteur;


	sonic[T_PERSO_SAUT] = DevsCreerSprite(oslLoadImageFile("perso/sonic/saute.png", OSL_IN_RAM, OSL_PF_5551),0, 8 ,34,41,10);
	DevsAnimationPlay(sonic[T_PERSO_SAUT]);
	sonic[T_PERSO_SAUT]->sprite->x =350;
	sonic[T_PERSO_SAUT]->sprite->y =272-sonic[T_PERSO_MORT]->Animation.Hauteur;


	sonic[T_PERSO_BARRE] = DevsCreerSprite(oslLoadImageFile("perso/sonic/barre_tourne.png", OSL_IN_RAM, OSL_PF_5551),0, 10 ,28,80,10);
	DevsAnimationPlay(sonic[T_PERSO_BARRE]);
	sonic[T_PERSO_BARRE]->sprite->x =400;
	sonic[T_PERSO_BARRE]->sprite->y =272-sonic[T_PERSO_BARRE]->Animation.Hauteur;

	sonic[T_PERSO_BOULEDEBUT] = DevsCreerSprite(oslLoadImageFile("perso/sonic/debut_boule.png", OSL_IN_RAM, OSL_PF_5551),0, 4 ,25,34,10);
	DevsAnimationPlay(sonic[T_PERSO_BOULEDEBUT]);
	sonic[T_PERSO_BOULEDEBUT]->sprite->x =50;
	sonic[T_PERSO_BOULEDEBUT]->sprite->y =200-sonic[T_PERSO_BOULEDEBUT]->Animation.Hauteur;

	sonic[T_PERSO_BOULECHARGE] = DevsCreerSprite(oslLoadImageFile("perso/sonic/charge_boule.png", OSL_IN_RAM, OSL_PF_5551),0, 3 ,52,34,10);
	DevsAnimationPlay(sonic[T_PERSO_BOULECHARGE]);
	sonic[T_PERSO_BOULECHARGE]->sprite->x =100;
	sonic[T_PERSO_BOULECHARGE]->sprite->y =200-sonic[T_PERSO_BOULECHARGE]->Animation.Hauteur;

	sonic[T_PERSO_BOULEPART] = DevsCreerSprite(oslLoadImageFile("perso/sonic/lance_boule.png", OSL_IN_RAM, OSL_PF_5551),0, 4 ,29,34,10);
	DevsAnimationPlay(sonic[T_PERSO_BOULEPART]);
	sonic[T_PERSO_BOULEPART]->sprite->x =150;
	sonic[T_PERSO_BOULEPART]->sprite->y =200-sonic[T_PERSO_BOULEPART]->Animation.Hauteur;


}


/*
=================
GereSonic

Gere les annimation de Sonic
=================
*/
void GereSonic()
{

	
/*		DevsDrawImageAnime(sonic[T_PERSO_SUPERSAUT]);	
		DevsDrawImageAnime(sonic[T_PERSO_ATTENTE]);
		DevsDrawImageAnime(sonic[T_PERSO_MARCHE]);
		DevsDrawImageAnime(sonic[T_PERSO_COUR]);
		DevsDrawImageAnime(sonic[T_PERSO_VRILLE]);
		DevsDrawImageAnime(sonic[T_PERSO_MORT]);
		DevsDrawImageAnime(sonic[T_PERSO_SAUT]);
		DevsDrawImageAnime(sonic[T_PERSO_BARRE]);
		DevsDrawImageAnime(sonic[T_PERSO_BOULEDEBUT]);
		DevsDrawImageAnime(sonic[T_PERSO_BOULECHARGE]);
		DevsDrawImageAnime(sonic[T_PERSO_BOULEPART]);		
*/

		//selectionne l'annimation choisi
		switch (sonic[T_PERSO_ATTENTE]->type)
		{
			case T_PERSO_ATTENTE:
				DevsDrawImageAnime(sonic[T_PERSO_ATTENTE]);
				break;
			case T_PERSO_SAUT:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_SAUT]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_SAUT]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_SAUT]);
				DevsDrawImageAnime(sonic[T_PERSO_SAUT]);
				break;
			case T_PERSO_MARCHE:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_MARCHE]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_MARCHE]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_MARCHE]);
				DevsDrawImageAnime(sonic[T_PERSO_MARCHE]);
				break;
			case T_PERSO_COUR:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_COUR]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_COUR]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_COUR]);
				DevsDrawImageAnime(sonic[T_PERSO_COUR]);
				break;
			case T_PERSO_BOULEDEBUT:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_BOULEDEBUT]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_BOULEDEBUT]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_BOULEDEBUT]);
				DevsDrawImageAnime(sonic[T_PERSO_BOULEDEBUT]);
				break;
			case T_PERSO_BOULECHARGE:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_BOULECHARGE]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_BOULECHARGE]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_BOULECHARGE]);
				DevsDrawImageAnime(sonic[T_PERSO_BOULECHARGE]);
				break;
			case T_PERSO_BOULEPART:
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 1)sonic[T_PERSO_SAUT]->Animation.fliph = 1;
				if (sonic[T_PERSO_ATTENTE]->Animation.fliph == 0)sonic[T_PERSO_SAUT]->Animation.fliph = 0;
				CopyXY(sonic[T_PERSO_ATTENTE],sonic[T_PERSO_BOULEPART]);
				DevsDrawImageAnime(sonic[T_PERSO_BOULEPART]);
				break;
		}


		//verifie que le joueur a toucher le sol
		if ( sonic[T_PERSO_ATTENTE]->sprite->y + sonic[T_PERSO_ATTENTE]->Animation.Hauteur > niveauSol)
		{
			sonic[T_PERSO_ATTENTE]->vy = 0.0f;					//Au sol, la vitesse passe à zéro 
			sonic[T_PERSO_ATTENTE]->sprite->y = niveauSol - sonic[T_PERSO_ATTENTE]->Animation.Hauteur;
			sonic[T_PERSO_ATTENTE]->auSol = 1;					//Il est au sol => il pourra sauter
			sonic[T_PERSO_ATTENTE]->type = T_PERSO_ATTENTE;
		}

		

		///////////////////////////////////////////////////////////////////////
		//Déplacement vertical + Gestion gravité qui influe sur la vitesse (VY)
		if (sonic[T_PERSO_ATTENTE]->auSol == 0)
		{
			sonic[T_PERSO_ATTENTE]->sprite->y += sonic[T_PERSO_ATTENTE]->vy;
			sonic[T_PERSO_ATTENTE]->vy = sonic[T_PERSO_ATTENTE]->vy + gravite;
			/////////////////////////////check collision avec le sol
			if (oslCollisionMap_Sonic(Niveau1MapColl,sonic[T_PERSO_ATTENTE],1,0,0,0))
			{
				sonic[T_PERSO_ATTENTE]->vy = 0.0f;
				sonic[T_PERSO_ATTENTE]->sprite->y += 1;
			}else
			{
			//Gestion des collisions avec le sol
			
				while(oslCollisionMap_Sonic(Niveau1MapColl,sonic[T_PERSO_ATTENTE],0,1,0,0) ){
					sonic[T_PERSO_ATTENTE]->vy = 0.0f;					//Au sol, la vitesse passe à zéro
					sonic[T_PERSO_ATTENTE]->sprite->y -= 1;		//Remet au niveau du sol
					sonic[T_PERSO_ATTENTE]->auSol = 1;					//Il est au sol => il pourra sauter
				}

			}
			//////////////////////////
		}else
		{
		// verifie si il y a quelque chose en bas si rien fait chutter le joueur j'usqua toucher le sol
		sonic[T_PERSO_ATTENTE]->sprite->y += 1;
		if (!oslCollisionMap_Sonic(Niveau1MapColl,sonic[T_PERSO_ATTENTE],0,1,0,0))
		{
			sonic[T_PERSO_ATTENTE]->auSol = 0;
		}
		sonic[T_PERSO_ATTENTE]->sprite->y -= 1;
		////////////////////////
		}
		/////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////
		///verifie les deplacement gauche et droite du joueur et stope au besoin

		if (sonic[T_PERSO_ATTENTE]->auSol == 0)
		{

			if (sonic[T_PERSO_ATTENTE]->sprite->y <= 90 && Niveau1Map->scrollY >= 1 )
			{


			 if (Niveau1Map->scrollY <= 0)
				{
				Niveau1Map->scrollY = Niveau1MapColl->scrollY = 0;
				}
				else
				{
					Niveau1Map->scrollY -= 4;//(sonic[T_PERSO_ATTENTE]->vy *3);//player_Kirby.vy ;  
					Niveau1MapColl->scrollY -= 4;//(sonic[T_PERSO_ATTENTE]->vy *3);//player_Kirby.vy ; 
					sonic[T_PERSO_ATTENTE]->sprite->y +=4;
				}
			}

			else if ((sonic[T_PERSO_ATTENTE]->sprite->y + sonic[T_PERSO_ATTENTE]->Animation.Hauteur) >= 202 && Niveau1Map->scrollY <= ((Niveau1Map->mapSizeY*Niveau1Map->tileY)-271))
			{
				if (Niveau1Map->scrollY >= ((Niveau1Map->mapSizeY*Niveau1Map->tileY)-272))
				{
					Niveau1Map->scrollY = Niveau1MapColl->scrollY = ((Niveau1Map->mapSizeY*Niveau1Map->tileY)-272);
				}else
				{
					Niveau1Map->scrollY += sonic[T_PERSO_ATTENTE]->vy * 3;//player_Kirby.vy;  
					Niveau1MapColl->scrollY += sonic[T_PERSO_ATTENTE]->vy * 3;//player_Kirby.vy; 
					sonic[T_PERSO_ATTENTE]->sprite->y -= sonic[T_PERSO_ATTENTE]->vy * 2;

				}

			}

		}


		//////////////////////////////////////////////////////////////////////////
		//verifie que le perso et bien dans le cadre et deplace la map si besoin
 
		if(sonic[T_PERSO_ATTENTE]->Animation.fliph == 1 && sonic[T_PERSO_ATTENTE]->vx != 0)//&& sonic[T_PERSO_ATTENTE]->type == (T_PERSO_BOULEPART || T_PERSO_COUR || T_PERSO_MARCHE))
		{
			if (!oslCollisionMap_Sonic(Niveau1MapColl,sonic[T_PERSO_ATTENTE],0,0,1,0)) 
			{
				if (Niveau1Map->scrollX <= 0)
				{
					Niveau1Map->scrollX = 0; Niveau1MapColl->scrollX = 0;
					 //si en bout de map le player peut aller au bout de l'ecran
					if (sonic[T_PERSO_ATTENTE]->sprite->x > 0)
					{
						sonic[T_PERSO_ATTENTE]->sprite->x += sonic[T_PERSO_ATTENTE]->vx;
					}
					else
					{
						//rien on et au bord
					}
				 }				
				else
				 {
					if (sonic[T_PERSO_ATTENTE]->sprite->x <= 70)
					{ 
						//si en bout pas bout de map le player peut aller a un morceau de l'ecran
						sonic[T_PERSO_ATTENTE]->sprite->x = 70;
						Niveau1Map->scrollX += sonic[T_PERSO_ATTENTE]->vx * 2;  
						Niveau1MapColl->scrollX += sonic[T_PERSO_ATTENTE]->vx * 2; 
					}
					else
					{
						sonic[T_PERSO_ATTENTE]->sprite->x += sonic[T_PERSO_ATTENTE]->vx;
					}
				 }
			
			}

		}


		///////test pour la droite

		if(sonic[T_PERSO_ATTENTE]->Animation.fliph == 0 && sonic[T_PERSO_ATTENTE]->vx != 0)//&& sonic[T_PERSO_ATTENTE]->type == (T_PERSO_BOULEPART || T_PERSO_COUR || T_PERSO_MARCHE))
		{
			if (!oslCollisionMap_Sonic(Niveau1MapColl,sonic[T_PERSO_ATTENTE],0,0,0,1)) 
			{
				if (Niveau1Map->scrollX >= ((Niveau1Map->mapSizeX*Niveau1Map->tileX)-480))
				{
					Niveau1Map->scrollX = Niveau1MapColl->scrollX =  ((Niveau1Map->mapSizeX*Niveau1Map->tileX)-480);
					 //si en bout de map le player peut aller au bout de l'ecran
					if ((sonic[T_PERSO_ATTENTE]->sprite->x + sonic[T_PERSO_ATTENTE]->Animation.anim_X )< 480)
					{
						sonic[T_PERSO_ATTENTE]->sprite->x += sonic[T_PERSO_ATTENTE]->vx;
					}
					else
					{
						//rien on et au bord
					}
				 }				
				else
				 {
					if ((sonic[T_PERSO_ATTENTE]->sprite->x + sonic[T_PERSO_ATTENTE]->Animation.anim_X )> 410)
					{ 
						//si en bout pas bout de map le player peut aller a un morceau de l'ecran
						sonic[T_PERSO_ATTENTE]->sprite->x = (410 - sonic[T_PERSO_ATTENTE]->Animation.anim_X);
						Niveau1Map->scrollX += sonic[T_PERSO_ATTENTE]->vx * 2;  
						Niveau1MapColl->scrollX += sonic[T_PERSO_ATTENTE]->vx * 2; 
					}
					else
					{
						sonic[T_PERSO_ATTENTE]->sprite->x += sonic[T_PERSO_ATTENTE]->vx;
					}
				 }
			
			}
		}


/*		if ((sonic[T_PERSO_ATTENTE]->sprite->x <= (480 - sonic[sonic[T_PERSO_ATTENTE]->type]->Animation.anim_X) && sonic[T_PERSO_ATTENTE]->vx > 0) ||
			sonic[T_PERSO_ATTENTE]->sprite->x >= 0 && sonic[T_PERSO_ATTENTE]->vx < 0)
		sonic[T_PERSO_ATTENTE]->sprite->x += sonic[T_PERSO_ATTENTE]->vx;
*/

}


/*
=================
Level1Sonic

Gere les evennement du premier niveau de Sonic
=================
*/
void Level1Sonic()
{

	InitSonic();


	//Initialisation d'une carte pour un niveau
	Niveau1 = oslLoadImageFile("level/niveau1/tiles01.png", OSL_IN_RAM, OSL_PF_5551);
	Niveau1Coll = oslLoadImageFile("level/niveau1/collision_s.png", OSL_IN_RAM, OSL_PF_5551);

	//Niveau1MapColl

	//sonicTeste_map[18][64]
	Niveau1Map = oslCreateMap(
	Niveau1,       
	(void *)Tiles1_map,      
	16,16,        
	70,64,        
	OSL_MF_U16);  

	//sonicTeste_map[18][64]
	Niveau1MapColl = oslCreateMap(
	Niveau1Coll,       
	(void *)collision_map,      
	16,16,        
	70,64,        
	OSL_MF_U16); 


	while (!osl_quit)
	{

		oslStartDrawing();
		oslCls();
		ToucheNiveau1();

		oslDrawImage(blanc);

		//oslDrawImage(Niveau1);

		oslDrawMapSimple(Niveau1Map);
		//oslDrawMapSimple(Niveau1MapColl);
		
	//	CarrerMap->scrollX += 1;
		GereSonic();
	
		DevsDrawImageAnime(Photo);

		DevsAffichageTexte(Photo->sprite->x + Photo->Animation.anim_X + 2 , Photo->sprite->y + (Photo->Animation.Hauteur/2)-3 ,JAUNE,"X 2", 0);

		/////////////////////
	//	bool answer=false; 
	//OSL_IMAGE *theimage=oslLoadImageFile("theimage.png", OSL_IN_RAM, OSL_PF_8888); 
	/*	oslSyncDrawing();
		oslLockImage(Niveau1);
		OSL_COLOR pixel=oslConvertColorEx(Niveau1->palette, OSL_PF_5551, Niveau1->pixelFormat, oslGetImagePixel(Niveau1, 1, 1)); 
		u8 red, green, blue, alpha;
		oslRgbaGet5551(pixel, red, green, blue, alpha);
		oslPrintf("%i %i %i %i", red, green, blue, alpha);
		oslUnlockImage(Niveau1);
*/
		//oslPrintf("%d", oslGetImagePixel(Niveau1, 1, 1));

//if(pixel==RGB(255,0,255)) 
  //  answer=true; 

/////////////////////////

		
		//Affiche le temps au sommet de l'écran
		oslSetBkColor(RGBA(0, 0, 0, 128));
		oslSetTextColor(RGB(255, 255, 255));
	//	oslPrintf_xy(0, 0, "Temps: %i sec", (int)temps);
		//oslPrintf_xy(0, 10, "vitesse: %i", (int)(sonic[T_PERSO_ATTENTE]->vx));
		//oslPrintf_xy(0, 20, "sol: %i", (int)(sonic[T_PERSO_ATTENTE]->auSol));

		
		DevsSynchronisation();

	}


}