#include "interfaccia.h"

extern SDL_Surface* screen;
extern SDL_Surface *font[2];

static const char *arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

SDL_Cursor *interfaccia::init_system_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case '.':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case 'X':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  return SDL_CreateCursor(data, mask, 32, 32, 0, 0);
}

interfaccia::interfaccia()
{
    number=SDL_LoadBMP("numn.bmp");     
    SDL_Surface *caricamento=caricabmp("caricamento.bmp",0,0,255,false);
    delete caricamento;
    d=new dizionario;
    sfondo=caricabmp("intro.bmp",0,0,255,false);
    sfondo_game=SDL_LoadBMP("sfondo_game.bmp");
    SDL_SetColorKey(font[0],SDL_SRCCOLORKEY,0);
    SDL_SetColorKey(font[1],SDL_SRCCOLORKEY,0);    
    parola=new char;
    parola[0]='\0';
    mouse=init_system_cursor(arrow);  
    SDL_SetCursor(mouse);      
    SDL_UpdateRect(screen,0,0,0,0);
    lato=4; 
    menu(1000/2-280/2,150);
}

interfaccia::~interfaccia()
{
    delete number;
    delete sfondo;
    delete sfondo_game;
    delete mouse;
    delete d;
    SDL_Quit();
}

void interfaccia::dissolvi(SDL_Surface* sur,int x ,int y,int start,int end,int time)
{
    SDL_Rect rect;
    rect.h=sur->h;
    rect.w=sur->w;    
    rect.y=y;
    rect.x=x;        
    if(start<end)
        for(int j=start;j<=end;j+=15)
        {                
            SDL_SetAlpha(sur,SDL_SRCALPHA,j);
            SDL_BlitSurface(sur,NULL,screen,&rect);                    
            SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);
            if(time)
            SDL_Delay(time);
        }
        else
        for(int j=start;j>=end;j-=15)
        {
            SDL_BlitSurface(sfondo,&rect,screen,&rect);
            SDL_SetAlpha(sur,SDL_SRCALPHA,j);
            SDL_BlitSurface(sur,NULL,screen,&rect);                    
            SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);
            if(time)
            SDL_Delay(time);
        }        
}

void interfaccia::opzioni(int x,int y)
{
    SDL_Surface *el=caricabmp("exit.bmp",x,y+2*97,75,true,50),
                *meno=caricabmp("meno.bmp",x+90,y+48,75,true),
                *piu=caricabmp("piu.bmp",x+154,y+48,75,true),
                *dimens=caricabmp("dimensione.bmp",x,y,255,true); 
    SDL_Rect rect;
    rect.x=x+122;
    rect.y=y+48; 
    rect.w=32;
    rect.h=32;
    SDL_FillRect(screen,&rect,0);
    SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);
    scrivinum(lato,x+128,y+50);
    int done=0;
    int mousex,mousey;    
    while (!done)
    {
        /* Check for events */
        while (SDL_PollEvent (&event))
        {
            SDL_GetMouseState(&mousex,&mousey);
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:{                    
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        if(mousey>=y+48&&mousey<y+48+32&&mousex>=x+154&&mousex<x+186)
                        {
                            if(lato<8)
                            lato++;
                            scrivinum(lato,x+128,y+50);    
                        }
                        if(mousey>=y+48&&mousey<y+48+32&&mousex>=x+90&&mousex<x+122)
                        {
                            if(lato>3)
                            lato--;
                            scrivinum(lato,x+128,y+50);    
                        }                        
                        if(mousey>y+2*97&&mousey<=y+3*97&&mousex>=x&&mousex<x+el->w){
                            done=1;
                            break;
                        }
                    } 
                                                           
                    break;
                }
                case SDL_MOUSEMOTION:{
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mousey>y+2*97&&mousey<=y+3*97&&mousex>=x&&mousex<x+el->w)
                    {
                        dissolvi(el,x,y+2*97,75,255,0);
                    }
                    break;
                }
            }
        }
    }
    delete el;
    delete meno;
    delete piu;
    delete dimens;
}
void interfaccia::menu(int x,int y)
{
    SDL_Surface *el[3];
    SDL_Surface *menu=caricabmp("menuprincipale.bmp",280,4,255,true,50);
    el[0]=caricabmp("gioca.bmp",x,y,75,true,50);
    el[1]=caricabmp("opzioni.bmp",x,y+97,75,true,50);
    el[2]=caricabmp("exit.bmp",x,y+2*97,75,true,50);  
    int mousex,mousey;    
    int done=0;
    while (!done)
    {
        /* Check for events */
        while (SDL_PollEvent (&event))
        {
            SDL_GetMouseState(&mousex,&mousey);
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:{                    
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                            if(mousey>=y&&mousey<=y+97&&mousex>=x&&mousex<x+el[0]->w)
                            {
                                for(int i=0;i<3;i++)
                                dissolvi(el[i],x,y+i*97,255,0,10);
                                gioco();
                                dissolvi(sfondo,0,0,0,255,50);
                                dissolvi(menu,280,4,0,255,50);                                
                                for(int i=0;i<3;i++)
                                dissolvi(el[i],x,y+i*97,0,50,50);
                                break;
                            }
                            if(mousey>y+57&&mousey<=y+2*97&&mousex>=x&&mousex<x+el[1]->w)
                            {
                                dissolvi(sfondo,0,0,0,255,50);                                
                                opzioni(x,y);
                                dissolvi(sfondo,0,0,0,255,50);
                                dissolvi(menu,280,4,0,255,50);                                
                                for(int i=0;i<3;i++)
                                dissolvi(el[i],x,y+i*97,0,50,50);                                
                                break;
                            }
                            if(mousey>y+2*57&&mousey<=y+3*97&&mousex>=x&&mousex<x+el[2]->w){
                                done=1;
                                break;
                            }
                    }
                    break;
                }
                case SDL_MOUSEMOTION:{
                    if(mousey>=y&&mousey<=y+97&&mousex>=x&&mousex<x+el[0]->w)
                    {
                        dissolvi(el[1],x,y+97,75,75,0);
                        dissolvi(el[2],x,y+2*97,75,75,0);
                        dissolvi(el[0],x,y,75,255,0);
                    }
                    if(mousey>y+97&&mousey<=y+2*97&&mousex>=x&&mousex<x+el[1]->w)
                    {
                        dissolvi(el[2],x,y+2*97,75,75,0);
                        dissolvi(el[0],x,y,75,75,0);
                        dissolvi(el[1],x,y+97,75,255,0);                        
                    }
                    if(mousey>y+2*97&&mousey<=y+3*97&&mousex>=x&&mousex<x+el[2]->w)
                    {
                        dissolvi(el[1],x,y+97,75,75,0);
                        dissolvi(el[0],x,y,75,75,0);
                        dissolvi(el[2],x,y+2*97,75,255,0);
                    }                                        
                    break;
                }
                case SDL_QUIT:{
                    done = 1;
                    break;
                }
            }
        }
        SDL_UpdateRect(screen,0,0,0,0);
    }   
    for(int i=0;i<3;i++)
    delete el[i];
    delete menu;
}

void interfaccia::casella_testo(int x,int y,int w,int h)
{
    SDL_Rect bordo,sfondo;
    bordo.x=x;
    bordo.y=y;
    bordo.w=w;
    bordo.h=h;
    sfondo.x=x+2;
    sfondo.y=y+2;
    sfondo.w=w-4;
    sfondo.h=h-4;
    int colorb = SDL_MapRGB (screen->format, 240,132,16);
    int colors = SDL_MapRGB (screen->format, 0, 0, 0);
    SDL_FillRect(screen,&bordo,colorb);
    SDL_FillRect(screen,&sfondo,colors);    
    SDL_UpdateRect(screen,x,y,w,h);
    scrivi("inserisci le parole qui sotto",x,y-20,1);
}

void interfaccia::scorrimento(int x,int y,int h,map<string,bool*> lista,int delay)
{
    map<string,bool*>::iterator j=lista.begin();
    for(int i=0;i<h&&j!=lista.end();i++)
    j++;
    int i=0;
    for(i;i<22&&j!=lista.end();i++)
    {
        scrivi("               ",x,y+22*i,1);
        scrivi(j->first.c_str(),x,y+22*i,1);
        j++;
        if(delay)
        SDL_Delay(delay);        
    }
    scrivi("               ",x,y+22*i,1);
}

void interfaccia::tastiera(int &i)
{
    char* c=new char[2]; 
    c[0]=char(event.key.keysym.sym);
    c[1]='\0';

    if(int(c[0])==8)
         {
            c[0]=' ';
            if(i>0)i--;
            parola[i]='\0';
            scrivi(c,300+i*13+3,545,1);
         }
    else if(c[0]<='z'&&c[0]>='a'&&i*17+3<350)
         {
            scrivi(c,300+i*13+3,545,1);            
            parola[i]=c[0];
            parola[i+1]=c[1];            
            i++;
         }
    if(int(c[0])==13&&*parola!='\0'&&strlen(parola)<=15)
    {
        for(i;i>=0;i--)
        scrivi(" ",300+i*13+3,545,1);
        string p=parola;
        g->hgame(p);
        scorrimento(10,50,0,g->hwbool);
        parola[0]='\0';
        i=0;
    }
    delete[] c;
}

void interfaccia::coloracasella(int pos,map<string,bool*> lista)
{
    map<string,bool*>::iterator l=lista.begin();
    for(int i=0;i<pos&&l!=lista.end();i++)
    {
        l++;
    }
    for(int i=0;i<lato*lato&&l!=lista.end();i++)
    {
        if(l->second[i])stampacasella(t->car(i),17,20,
                    i%lato*50+tab_x,int(i/lato)*50+tab_y,50,true);
    }
}

void interfaccia::riquadro(int x,int y,int color)
{
    SDL_Rect cornice,cornice2;
    cornice.x=x+2;
    cornice.y=y+2;  
    cornice.w=17*16;
    cornice.h=22*22;
    cornice2.x=x;
    cornice2.y=y;  
    cornice2.w=17*16+4;
    cornice2.h=22*22+4;    
    SDL_FillRect(screen,&cornice2,color);    
    SDL_FillRect(screen,&cornice,SDL_MapRGB (screen->format, 0, 0, 0));    
    SDL_UpdateRect(screen,cornice2.x,cornice2.y,cornice2.w,cornice2.h);
    SDL_Surface *frecciasu,*frecciagiu;
    frecciasu=caricabmp("up.bmp",x+221,y+2,255,true,0);
    frecciagiu=caricabmp("down.bmp",x+221,y+409,255,true,0);    
}    

void interfaccia::gioco()
{
    t=new tabellone(lato);
    int done=0; 
    char *c=new char;
    int i=0,j=0,k=0;
    tab_x=1000/2-50*lato/2;
    tab_y=600/2-50*lato/2;     
    dissolvi(sfondo_game,0,0,0,255,50);
    SDL_Surface *titolo_game=caricabmp("game.bmp",1000/2-139/2,0,255,true,50);  
    stampatabellone(tab_x,tab_y,50);
    SDL_Surface *player=caricabmp("giocatore.bmp",0,0,255,true,20);
    SDL_Surface *pc=caricabmp("computer.bmp",1000-142,0,255,true,20);     
    riquadro(3,43,SDL_MapRGB (screen->format, 0, 255, 0)); 
    riquadro(724,43,SDL_MapRGB (screen->format, 0, 0, 255));
    casella_testo(300,540,405,30);
    SDL_Surface *fine=caricabmp("fine.bmp",1000/2-95/2,570,255,true,50);       
    g=new game;
    while (!done)
    {

        /* Check for events */
        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:{
                tastiera(i);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                if(event.button.button==SDL_BUTTON_WHEELUP)scorrimento(10,50,--k,g->hwbool);
                int size=g->hwbool.size();
                if(size>22&&k<size-22)
                if(event.button.button==SDL_BUTTON_WHEELDOWN)scorrimento(10,50,++k,g->hwbool);                
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    int mousex,mousey;
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mousex>=1000/2-95/2&&mousex<=1000/2+95/2&&mousey>=570)
                    {    
                        g->cgame(lato,*t,d);
                        done=1;break;
                    }
                    int size1=g->hwbool.size();                    
                    if(mousey>=45&&mousey<=45+78)
                        if(mousex>=217&&mousex<=217+52)scorrimento(10,50,--k,g->hwbool);
                    if(mousey>=409+43&&mousey<=409+43+73)
                    {
                        if(size1>22&&k<size1-22)
                        if(mousex>=217&&mousex<=217+52)scorrimento(10,50,++k,g->hwbool);
                    }                               
                }
                if(k<0)k=0;
                break;
            }
            case SDL_QUIT:
                exit(1);
                break;
            default:
                break;
            }
        }
    } 
    for(int q=0;q<3;q++)
    scrivi("                        ",300,510+q*20,0);     
    scrivi("   clicca sulle parole per",300,520,1);   
    scrivi(" visualizzarle sul tabellone",300,540,1);       
    g->compare();
    if(!g->exception.empty())g->wordtab(lato,*t);    
    scorrimento(727,50,0,g->cwbool,10);
    delete fine;
    fine=caricabmp("prosegui.bmp",1000/2-95/2,570,255,true,50);
    riquadro(3,43,SDL_MapRGB (screen->format, 0, 255, 0)); 
    scorrimento(10,50,0,g->hwbool);        
    done=0;
    punteggio(g->punteggio(g->hwbool),160,547);
    scrivi("punti",5,547,0);    
    punteggio(g->punteggio(g->cwbool),880,547);
    scrivi("punti",725,547,0);          
    while (!done)
    {

        /* Check for events */
        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:{ 
                if(event.button.button==SDL_BUTTON_WHEELUP)
                {
                    int mousex,mousey;
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mousey>=50&&mousey<=50+22*22)
                    {
                        if(mousex>=727&&mousex<=944)scorrimento(727,50,--j,g->cwbool);
                        if(mousex>=10&&mousex<=217)scorrimento(10,50,--k,g->hwbool);
                    }
                }
                int size1=g->hwbool.size();
                int size=g->cwbool.size();
                
                if(event.button.button==SDL_BUTTON_WHEELDOWN)
                {
                    int mousex,mousey;
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mousey>=50&&mousey<=50+22*22)
                    {
                        if(size>22&&j<size-22)
                        if(mousex>=727&&mousex<=944)scorrimento(727,50,++j,g->cwbool);
                        if(size1>22&&k<size1-22)
                        if(mousex>=10&&mousex<=217)scorrimento(10,50,++k,g->hwbool);
                    }
                }
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    stampatabellone(tab_x,tab_y,0);
                    int mousex,mousey;
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mousex>=1000/2-95/2&&mousex<=1000/2+95/2&&mousey>=570)
                    {    
                        done=1;break;
                    }                        
                    if(mousey>=45&&mousey<=45+78)
                    {
                        if(mousex>=944&&mousex<=944+52)scorrimento(727,50,--j,g->cwbool);
                        if(mousex>=217&&mousex<=217+52)scorrimento(10,50,--k,g->hwbool);
                    }                        
                    if(mousey>=409+43&&mousey<=409+43+73)
                    {
                        if(size>22&&j<size-22)
                        if(mousex>=944&&mousex<=944+52)scorrimento(727,50,++j,g->cwbool);
                        if(size1>22&&k<size1-22)
                        if(mousex>=217&&mousex<=217+52)scorrimento(10,50,++k,g->hwbool);
                    }                        
                    if(mousey>=50&&mousey<=50+22*22)
                    {
                        if(mousex>=727&&mousex<=944)
                        coloracasella((mousey-50)/22+j,g->cwbool);
                        if(mousex>=10&&mousex<=217)
                        coloracasella((mousey-50)/22+k,g->hwbool);
                    }
                }
                if(k<0)k=0;
                if(j<0)j=0;                                    
                punteggio(g->punteggio(g->hwbool),160,547);
                scrivi("punti",5,547,0);    
                punteggio(g->punteggio(g->cwbool),880,547);
                scrivi("punti",725,547,0);                                        
                break;
            }
            case SDL_QUIT:
                exit(1);
                break;
            default:
                break;
            }
        }
    } 
    done=0;
    j=0;
    done=0;
    map<string, bool*>::iterator p=g->exception.begin();
    if(p!=g->exception.end())
    {
        SDL_Surface *pirandello=caricabmp("exception.bmp",0,0,255,0,50);        
        SDL_Rect rect,rect2;
        rect.x=595-3;
        rect.y=150-3;
        rect.w=50*5+6;
        rect.h=50*4+6-30;
        rect2.x=595;
        rect2.y=150;
        rect2.w=50*5;
        rect2.h=50*4-30;
        SDL_FillRect(screen,&rect,SDL_MapRGB (screen->format,227,240,13));    
        SDL_FillRect(screen,&rect2,SDL_MapRGB (screen->format,0,0,0));
        SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);            
        scrivi("vuoi inserire",600,170,0);
        scrivi("nel dizionario",600,230,0);        
        SDL_Surface *si=caricabmp("si.bmp",625,300,255,1);
        SDL_Surface *no=caricabmp("no.bmp",725,300,255,1);    
        delete pirandello;
        delete si;
        delete no;        
    }
    for(;p!=g->exception.end();p++)
    {
        done=0;
        scrivi("                ",600,200,1);
        scrivi(p->first.c_str(),600,200,1);
        while(!done) 
        {
            /* Check for events */
            while (SDL_PollEvent (&event))
            {
                switch (event.type)
                {
                    case SDL_KEYDOWN:{  
                        if (int(event.key.keysym.sym)==27){done=1;break;}
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:{
                        int mousex,mousey;
                        SDL_GetMouseState(&mousex,&mousey);
                        if(mousex>=630&&mousex<=721&&mousey>=300&&mousey<=344)
                        {
                            g->save(p->first.c_str());
                            d->inserisciparola(p->first.c_str());
                            done=1;                    
                        }
                        if(mousex>=730&&mousex<=821&&mousey>=300&&mousey<=344)
                        {
                            done=1;                    
                        }                        
                        break;
                    }
                }
            }
        }
    }
    delete titolo_game;    
    delete player;
    delete pc;
    delete fine;    
    delete g;
}

SDL_Surface* interfaccia::caricabmp(char* filename,int x,int y,int alpha,bool bg,int delay)
{
    SDL_Surface *image;
    image = SDL_LoadBMP(filename);
    if (image->format->palette && screen->format->palette)
    {
        SDL_SetColors(screen, image->format->palette->colors, 0,
                  image->format->palette->ncolors);
    }
    SDL_Rect rect;  
    if(bg)
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB (screen->format, 255, 255, 255));  
    rect.w=image->w;
    rect.h=image->h;
    rect.x=x;
    rect.y=y;     
    dissolvi(image,x,y,0,alpha,delay);
    return image;
}

void scrivi(const char *c,int x,int y,int grandezza)
{
    int lettera=int(*c)-97;
    SDL_Rect rect,rect2;
    rect2.x=x;
    rect2.y=y;
    if(grandezza==0)
    {
        rect2.w=17;
        rect2.h=20;
        rect.x=17*lettera;
        rect.y=0;
        rect.w=17;
        rect.h=20;
    }
    else
    {
        rect2.w=15;
        rect2.h=17;
        rect.x=13*lettera;
        rect.y=0;
        rect.w=13;
        rect.h=17;
    }        
    if(*c==' ')SDL_FillRect(screen,&rect2,SDL_MapRGB (screen->format, 0, 0, 0));
    else SDL_BlitSurface(font[grandezza],&rect,screen,&rect2);
    SDL_UpdateRect(screen,x,y,rect2.w,rect2.h);
    if(*++c!='\0')
    if(grandezza==0)scrivi(c,x+17,y,grandezza);
    else scrivi(c,x+14,y,grandezza);    
}

int interfaccia::punteggio(int c,int x,int y)
{
    if(c<10)
    {
        scrivinum(c,x,y);
        return c*10;
    }
    else
    {
        scrivinum(c-punteggio(int(c/10),x-17,y),x,y);
        return c*10;
    }
}
void interfaccia::scrivinum(int c,int x,int y)
{
    SDL_Rect rect,rect2;
    rect2.x=x;
    rect2.y=y;
    rect2.w=17;
    rect2.h=18;
    rect.x=17*c;
    rect.y=0;
    rect.w=17;
    rect.h=18;
    SDL_BlitSurface(number,&rect,screen,&rect2);
    SDL_UpdateRect(screen,x,y,rect2.w,rect2.h);
}

void interfaccia::stampacasella(char* c,int cw,int ch,
                    int x,int y,int lato,bool segna)
{
    int i=int(*c)-97;
    int centrox=lato/2-cw/2-1+x;
    int centroy=lato/2-ch/2+1+y;    
    SDL_Rect sfondo,bordo,rect[2];
    sfondo.x=x+2;
    sfondo.y=y+2;
    sfondo.w=sfondo.h=lato-4;
    bordo.x=x;
    bordo.y=y;
    bordo.w=bordo.h=lato;
    int color1,color;
    if(!segna)
    {
        color1 = SDL_MapRGB (screen->format,26,20,51); 
        color = SDL_MapRGB (screen->format,33,25,191);
    }   
    else
    {
        color1 = SDL_MapRGB (screen->format,50,38,170);
        color = SDL_MapRGB (screen->format,0,0,0);
    }
    SDL_FillRect (screen, &bordo,color1);    
    SDL_FillRect (screen, &sfondo, color);    
    scrivi(c,centrox,centroy,0);
    SDL_UpdateRect(screen,x,y,lato,lato);
}

void interfaccia::stampatabellone(int x,int y,int delay)
{
    dim_casella=50;
    SDL_Rect rect,rect2;
    rect.x=x-3;
    rect.y=y-3;
    rect.w=50*lato+6;
    rect.h=50*lato+6;
    rect2.x=x;
    rect2.y=y;
    rect2.w=50*lato;
    rect2.h=50*lato;
    SDL_FillRect(screen,&rect,SDL_MapRGB (screen->format,227,240,13));    
    SDL_FillRect(screen,&rect2,SDL_MapRGB (screen->format,0,0,0));
    SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);
    for(int i=0;i<lato*lato;i++)
    {
        stampacasella(t->car(i),17,20,i%lato*dim_casella+x,
                        int(i/lato)*dim_casella+y,dim_casella,false);
        if(delay)SDL_Delay(delay);
    }
}
