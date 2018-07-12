#include "classi.h"

void tabellone::creatabellone()
{
    char dado[6];
    ifstream f("Dadi.in");          // apre il file contenente i dadi
    srand(time(NULL));
    for(int i=0;i<lato*lato;i++)
    {
        f>>dado;
        int k=rand()%6;
        int p;
        do
        {
            p=rand()%(lato*lato);
        }while(mat[p].full);
        mat[p].l=dado[k];
        mat[p].full=true;        
    }
    for(int i=0;i<lato*lato;i++)
    mat[i].full=false;
}


int tabellone::checkdadi()          //controlla il numero di dadi nel file dadi.in
{
    ifstream f("Dadi.in");
    char c;    
    int quanti=0;
    while(f.get(c))
        if(c==' ')quanti++;
    f.close();
    return quanti;
}

void tabellone::creadadi()     //crea i dadi mancanti nel file dadi.in
{
    char vocali[5]={'a','e','i','o','u'};
    char consonanti[21]={'b','c','d','f','g','l','m','n','p','q','r','s','t','v','z','h','k','j','y','w','x'};
    fstream f("Dadi.in",ios::out|ios::app);
    char dado[6];
    srand(time(NULL));
    int check=checkdadi();
    for (int j=0;j<lato*lato-check;j++)
    {
        for (int i=0;i<6;i++)
        {
            if ((i==0)||(i==3)||(i==5))
                dado[i]=vocali[rand()%5];    //inserimento vocali in 2 facce di ogni dado
            else
                dado[i]=consonanti[rand()%21];
            f<<dado[i];
        }
        f<<" ";
    }
}
      
tabellone::tabellone(int n)                 //costruttore del tabellone
{
    lato=n;
    mat=new casella[lato*lato];
    for(int i=0;i<lato*lato;i++)
    mat[i].full=false;
    creadadi();
    creatabellone();
}

tabellone::~tabellone()
{
    delete[] mat;
}

char* tabellone::car(int i)
{
    return &mat[i].l;
}
