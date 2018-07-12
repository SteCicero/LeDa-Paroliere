#include "classi.h"

int game::fword(int i,int a,char word[],tabellone &tab,int n)
{
    int flag=1;
    if((tab.mat[i-n].l==word[a])&&(tab.mat[i-n].full==false)&& flag &&-1<i-n)
    {
        tab.mat[i-n].full=true;
        a++;
        flag=fword(i-n,a,word,tab,n);
        a--;
        tab.mat[i-n].full=false;
    }
    if(((i-1)%n!=n-1)&&(tab.mat[i-1].l==word[a])&&(tab.mat[i-1].full==false)&& flag && -1<i-1)
    {
        tab.mat[i-1].full=true;
        a++;
        flag=fword(i-1,a,word,tab,n);
        a--;
        tab.mat[i-1].full=false;
    }
    if(((i+1)%n!=0)&&(tab.mat[i+1].l==word[a])&&(tab.mat[i+1].full==false)&& flag && i+1<n*n)
    {
        tab.mat[i+1].full=true;
        a++;
        flag=fword(i+1,a,word,tab,n);
        a--;
        tab.mat[i+1].full=false;
    }
    if((tab.mat[i+n].l==word[a])&&(tab.mat[i+n].full==false)&& flag && i+n<n*n)
    {
        tab.mat[i+n].full=true;
        a++;
        flag=fword(i+n,a,word,tab,n);
        a--;
        tab.mat[i+n].full=false;
    }
    if(((i-n+1)%n!=0)&&(tab.mat[i-n+1].l==word[a])&&(tab.mat[i-n+1].full==false)&& flag && -1<i-n+1)
    {
        tab.mat[i-n+1].full=true;
        a++;
        flag=fword(i-n+1,a,word,tab,n);
        a--;
        tab.mat[i-n+1].full=false;
    }
    if((i%n!=0)&&(tab.mat[(i-n)-1].l==word[a])&&(tab.mat[(i-n)-1].full==false)&& flag && -1<(i-n)-1)
    {
        tab.mat[(i-n)-1].full=true;
        a++;
        flag=fword((i-n)-1,a,word,tab,n);
        a--;
        tab.mat[(i-n)-1].full=false;
    }
    if(((i+n-1)%n!=n-1)&&(tab.mat[i+n-1].l==word[a])&&(tab.mat[i+n-1].full==false)&& flag && i+n-1<n*n)
    {
        tab.mat[i+n-1].full=true;
        a++;
        flag=fword(i+n-1,a,word,tab,n);
        a--;
        tab.mat[i+n-1].full=false;
    }
    if((i%n!=n-1)&&(tab.mat[i+n+1].l==word[a])&&(tab.mat[i+n+1].full==false)&& flag && i+n+1<n*n)
    {
        tab.mat[i+n+1].full=true;
        a++;
        flag=fword(i+n+1,a,word,tab,n);
        a--;
        tab.mat[i+n+1].full=false;
    }
    if(word[a]=='\0') return 0;
    else return flag;
}

void game::wordtab(int n,tabellone &tab)
{
    bool found=false;
    int a;
    string s;
    char word[20];
    map<string,bool*>::iterator p,c;
    p=exception.begin();
    while(p!=exception.end())
    {
        s=p->first;
        strcpy(word,s.c_str());
        a=0;
        lowercase(word);
        for(int i=0;i<n*n && found==false;i++)
        {
            if (tab.mat[i].l==word[a])
            {
                tab.mat[i].full=true;
                a++;
                if(fword(i,a,word,tab,n)==0)
                {
                    found=true;
                }
                else
                {
                    a=0;
                    for(int b=0;b<n*n;b++)
                    tab.mat[b].full=false;
                }
            }
        }
        if (found==false)
        {
            c=p;
            p++;
            exception.erase(c);
        }
        else p++;
        found=false;
        for(int i=0;i<n*n;i++)
        tab.mat[i].full=false;
    }
}

void game::ricorsiva(int i,int a,char cword[],int n,tabellone &tab,dizionario *d)
{
    a++;
    cword[a+1]='\0';
    if((tab.mat[i-n].full==false)&& -1<i-n)
    {
        tab.mat[i-n].full=true;
        cword[a]=tab.mat[i-n].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i-n].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i-n,a,cword,n,tab,d);
                        tab.mat[i-n].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i-n,a,cword,n,tab,d);
                        tab.mat[i-n].full=false;
                        break;
                    }
        }
    }
    if(((i-1)%n!=n-1)&&(tab.mat[i-1].full==false)&& -1<i-1)
    {
        tab.mat[i-1].full=true;
        cword[a]=tab.mat[i-1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i-1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i-1,a,cword,n,tab,d);
                        tab.mat[i-1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i-1,a,cword,n,tab,d);
                        tab.mat[i-1].full=false;
                        break;
                    }
        }
    }
    if(((i+1)%n!=0)&&(tab.mat[i+1].full==false)&& i+1<n*n)
    {
        tab.mat[i+1].full=true;
        cword[a]=tab.mat[i+1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i+1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i+1,a,cword,n,tab,d);
                        tab.mat[i+1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i+1,a,cword,n,tab,d);
                        tab.mat[i+1].full=false;
                        break;
                    }
        }
    }
    if((tab.mat[i+n].full==false)&& i+n<n*n)
    {
        tab.mat[i+n].full=true;
        cword[a]=tab.mat[i+n].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i+n].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i+n,a,cword,n,tab,d);
                        tab.mat[i+n].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i+n,a,cword,n,tab,d);
                        tab.mat[i+n].full=false;
                        break;
                    }
        }
    }
    if(((i-n+1)%n!=0)&&(tab.mat[i-n+1].full==false)&& -1<i-n+1)
    {
        tab.mat[i-n+1].full=true;
        cword[a]=tab.mat[i-n+1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i-n+1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i-n+1,a,cword,n,tab,d);
                        tab.mat[i-n+1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i-n+1,a,cword,n,tab,d);
                        tab.mat[i-n+1].full=false;
                        break;
                    }
        }
    }
    if((i%n!=0)&&(tab.mat[(i-n)-1].full==false)&& -1<(i-n)-1)
    {
        tab.mat[(i-n)-1].full=true;
        cword[a]=tab.mat[(i-n)-1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[(i-n)-1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva((i-n)-1,a,cword,n,tab,d);
                        tab.mat[(i-n)-1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva((i-n)-1,a,cword,n,tab,d);
                        tab.mat[(i-n)-1].full=false;
                        break;
                    }
        }
    }
    if(((i+n-1)%n!=n-1)&&(tab.mat[i+n-1].full==false)&& i+n-1<n*n)
    {
        tab.mat[i+n-1].full=true;
        cword[a]=tab.mat[i+n-1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i+n-1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i+n-1,a,cword,n,tab,d);
                        tab.mat[i+n-1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i+n-1,a,cword,n,tab,d);
                        tab.mat[i+n-1].full=false;
                        break;
                    }
        }
    }
    if((i%n!=n-1)&&(tab.mat[i+n+1].full==false)&& i+n+1<n*n)
    {
        tab.mat[i+n+1].full=true;
        cword[a]=tab.mat[i+n+1].l;
        switch(d->trovastringa(cword))
        {
            case 0:{
                        tab.mat[i+n+1].full=false;
                        break;
                    }
            case 1:{
                        ricorsiva(i+n+1,a,cword,n,tab,d);
                        tab.mat[i+n+1].full=false;
                        break;
                    }
            case 2:{
                        bool* p=new bool[n*n];
                        for(int x=0;x<n*n;x++)
                            p[x]=tab.mat[x].full;
                        cwbool[cword]=p;
                        ricorsiva(i+n+1,a,cword,n,tab,d);
                        tab.mat[i+n+1].full=false;
                        break;
                    }
        }
    }
    a--;
    cword[a+1]='\0';
}

void game::hgame(string hword)
{
   if(hword[0]=='1') return;
        if(strlen(hword.c_str())<4)
        {
            return;
        }
    hwbool[hword]=NULL;
}

void game::cgame(int n,tabellone &tab,dizionario* d)
{
    char cword[20];
    int a;
    for(int i=0;i<n*n;i++)
    {
        a=0;
        cword[a]=tab.mat[i].l;
        tab.mat[i].full=true;
        ricorsiva(i,a,cword,n,tab,d);
        for(int j=0;j<n*n;j++)
        tab.mat[j].full=false;
    }
}

void game::compare()
{
    bool found=false;
    map<string, bool*>::iterator z,p,a;
    for(p=hwbool.begin();p!=hwbool.end();)
    {
        found=false;
        for(z=cwbool.begin();z!=cwbool.end();z++)
        {
            if(p->first==z->first)
            {
                hwbool[z->first]=z->second;
                found=true;
                p++;
                break;
            }
        }
        if(found==false)
        {
            a=p;
            a++;
            exception[p->first]=p->second;
            hwbool.erase(p);
            p=a;
        }
    }
}

int game::punteggio(map<string, bool*> lista)
{
    map<string, bool*>::iterator p=lista.begin();
    int punti=0;
    string w;
    while(p!=lista.end())
    {
        w=p->first;
        punti=punti+w.length()-3;
        p++;
    }
    return punti;
}

void game::save(const char* a)
{
    fstream out("dizionario.txt",ios::out|ios::app);;
            out<<a<<"\n";
}

game::~game()
{
    exception.clear();
    hwbool.clear();
    cwbool.clear();
}
