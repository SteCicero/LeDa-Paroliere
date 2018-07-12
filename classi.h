#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <list>
#include <map>
using namespace std;

class tabellone
{
    //Attributi
    
    struct casella
    {
        char l;
        bool full;
    };
    casella* mat;
    int lato;
    
    friend class game;
    
    //Metodi

    void creatabellone();
    int checkdadi();
    void creadadi();
    public:
        tabellone(int);
        ~tabellone();
        char* car(int);
        
};


class dizionario
{
    //Attributi
    
    struct nodo
    {
        char l;
        bool fine;
        nodo* head;
        nodo* next;
    }*testa[26];
    
    //Metodi
    
        void crea_ramo(nodo*,const char*);
        void crea_albero();    
        int tr_ric(nodo* t,char *s);
        nodo* inschar(nodo* t,char c);
        nodo* checkchar(nodo* t, char c);
    public:
        dizionario();
        ~dizionario();
        void cancellazione(nodo*);
        int trovastringa(char*);
        void inserisciparola(const char*);
};

void lowercase(char*parola);


class game
{
    
    //Attributi
    
    map<string, bool*> hwbool;
    map<string, bool*> cwbool;
    map<string, bool*> exception;
    
    
    //Abbiamo messo la classe interfaccia friend per poter utilizzare senza
    //problemi tutti i metodi della classe game che servono per gestire la
    //partita
    friend class interfaccia;
    
    //Metodi
    
    void hgame(string);
    void cgame(int n,tabellone &tab,dizionario* d);
    void ricorsiva(int i,int a,char word[],int n,tabellone &tab,dizionario* d);
    int punteggio(map<string, bool*> lista);
    void compare();
    int fword(int i,int a,char word[],tabellone &tab,int n);
    void wordtab(int n,tabellone &tab);
    void save(const char*);
    public:
        ~game();

};
