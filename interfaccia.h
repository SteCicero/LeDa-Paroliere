#include <SDL/SDL.h>
#include <windows.h>
#include <fstream>
#include "classi.h"
using namespace std;

void scrivi(const char *c,int x,int y,int grandezza);

class interfaccia
{
    // Attributi
    
    SDL_Event event;
    SDL_Surface *number;
    SDL_Surface *sfondo,*sfondo_game;
    SDL_Cursor *mouse;   
    tabellone *t;
    dizionario *d;
    game *g;    
    char* parola;
    int tab_x,
        tab_y,
        lato,
        dim_casella;
        
    // Funzioni
    
        void scrivinum(int c,int x,int y);
        int punteggio(int,int,int);
        void stampacasella(char* c,int cw,int ch,
                    int x,int y,int lato,bool segna);
        void casella_testo(int x,int y,int w,int h);
        void dissolvi(SDL_Surface* sur,int x, int y,int start,int end,int time);
        void coloracasella(int,map<string,bool*>);
        void riquadro(int x,int y,int color);
        SDL_Cursor* init_system_cursor(const char *image[]);
    public:
        interfaccia();
        ~interfaccia();
        void menu(int x,int y);
        void scorrimento(int x,int y,int h,map<string,bool*> lista,int delay=0);
        void opzioni(int,int);
        void stampatabellone(int,int,int);
        SDL_Surface *caricabmp(char*,int,int,int,bool bg=true,int delay=0);
        void tastiera(int&);
        void gioco();
};
