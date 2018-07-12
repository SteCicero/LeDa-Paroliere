#include "interfaccia.h"

extern SDL_Surface *screen;

dizionario::dizionario()
{
    for (int i=0;i<26;i++)
        testa[i]=0;
    crea_albero();
}

int dizionario::tr_ric(nodo* t,char *s)
{
    if (t==0)return 0;
    if(*s=='\0')
    {
        if(t->fine==true)return 2;
        else return 1;
    }
    return tr_ric(checkchar(t,*s),s+1);
}

int dizionario::trovastringa(char* s)
{
    if(s==NULL)return 0;
    lowercase(s);
    int i=int(*s)-97;
    if(testa[i]) return tr_ric(testa[i],s+1);
    else return 0;
    
}

void lowercase(char*parola)
{
    for(;*parola!='\0';parola++)
    if(int(*parola)<97)*parola=char(int(*parola)+32);
}


dizionario::nodo* dizionario::checkchar(nodo* t, char c)
{
    
    if(!t->head)return 0;
    nodo*temp=t->head;
    while(temp)
    {       
        if(temp->l==c)return temp;        
        temp=temp->next;
    }
    return 0;
}

dizionario::nodo* dizionario::inschar(nodo* t,char c)
{
    nodo* nuovo=new nodo;
    nuovo->l=c;
    nuovo->fine=false;
    nuovo->next=t->head;
    nuovo->head=0;
    t->head=nuovo;
    return nuovo;
}

void dizionario::inserisciparola(const char* c)
{
    int i=int(*c)-97;
    if (!testa[i])
    {
        testa[i]=new nodo;
        testa[i]->l=*c;
        testa[i]->head=0;
        testa[i]->next=0;
        testa[i]->fine=false;
    }    
    crea_ramo(testa[i],c+1);
}

void dizionario::crea_ramo(nodo* n,const char* p)
{
    if (*p=='\0')
    {
        n->fine=true;
        return;
    }
    nodo* temp=checkchar(n,*p);
    if(!temp)
    crea_ramo(inschar(n,*p),p+1);
    else
        crea_ramo(temp,p+1);
}

void dizionario::crea_albero()
{
    fstream diz("dizionario.txt",ios::in);
    if(!diz)
    {
        scrivi("errore",450,200,0);
        scrivi("dizionario non presente",340,230,1);
        SDL_Delay(3000);
        exit(1);
    }    
    char temp[36];
    SDL_Surface *elemdx=SDL_LoadBMP("elemdx1.bmp");
    SDL_Rect rect;
    rect.x=290;
    rect.y=200;
    rect.w=8;
    rect.h=27;
    int caricamento=0;
    float j=0;
    while(diz>>temp)
    {
        int i=int(*temp)-97;
        caricamento++;
        if (!testa[i])
        {
            testa[i]=new nodo;
            testa[i]->l=*temp;
            testa[i]->head=0;
            testa[i]->next=0;
            testa[i]->fine=false;
        }
        crea_ramo(testa[i],temp+1);
        if(caricamento%1500==0)
        {
            SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);            
            rect.x+=1;
            j+=0.2;
            SDL_SetAlpha(elemdx,SDL_SRCALPHA,int(j));
            SDL_BlitSurface(elemdx,NULL,screen,&rect);
            SDL_UpdateRect(screen,rect.x,rect.y,rect.w,rect.h);
        }
    }
}

void dizionario::cancellazione(nodo *temp)
{
    if(!temp)return;
    cancellazione(temp->head);
    nodo *temp2=temp;
    while(temp2)
    {
        temp=temp->next;
        cancellazione(temp->head);
        delete temp2;
        temp2=temp;        
    }
    delete temp;
}

dizionario::~dizionario()
{
    nodo *temp;
    for(int i=0;i<26;i++)
    {
        if(testa[i])cancellazione(testa[i]->head);
    }
}
