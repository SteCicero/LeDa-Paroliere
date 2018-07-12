#include "interfaccia.h"

SDL_Surface *screen; //puntatore a SDL_Surface per inizializzare il video
SDL_Surface *font[2];//puntatori a SDL_Surface per caricare i font per scrivere

int main (int argc, char *argv[])
{    
    //SDL_Init è una funzione di libreria che serve a inizializzare
    //l'ambiente SDL    
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0))exit(-1);   
    //Caricamento dell'icona nell'angolo in alto della finestra
    SDL_WM_SetIcon(SDL_LoadBMP("icona.bmp"),NULL); 
    //Caricamento del titolo della finestra
    SDL_WM_SetCaption("LeDa",NULL);
    //Impostazione della risoluzione del video
    screen = SDL_SetVideoMode(1000, 600, 24, SDL_HWSURFACE);   
    if ( screen == NULL )exit(1); 
    font[0]=SDL_LoadBMP("charn.bmp");
    font[1]=SDL_LoadBMP("char.bmp");       
    interfaccia GUI;
    return 0;
}
