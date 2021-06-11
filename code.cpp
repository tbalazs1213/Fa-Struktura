#include <iostream>

using namespace std;

struct csucs
{
    int ertek;
    int gyerekDB;
    int maxGyerek;
    csucs** gyerekek;
};

csucs* UjCsucs(int ertek)
{
    csucs* uj = new csucs;
    uj->ertek = ertek;
    uj->gyerekDB = 0;
    uj->maxGyerek = 0;
    uj->gyerekek = NULL;
    return uj;
}

void hozzaadas(csucs* szulo, csucs* gyerek)
{
    if(szulo == NULL || gyerek == NULL) return;
    if(szulo->gyerekDB == szulo->maxGyerek)
    {
        int meret = szulo->maxGyerek + 2;
        csucs** uj = new csucs*[meret];
        for(int i = 0; i < szulo->gyerekDB; i++)
        {
            uj[i] = szulo->gyerekek[i];
        }
        szulo->maxGyerek = meret;
        if(szulo->gyerekek != NULL)
        {
            delete[] szulo->gyerekek;
        }
        szulo->gyerekek = uj;
    }
    szulo->gyerekek[szulo->gyerekDB] = gyerek;
    szulo->gyerekDB++;
}

inline void tab(int db)
{
    for(int i = 0; i < db; i++)
    {
        cout << "\t";
    }
}

void kiir(csucs* cs, int szint)
{
    if(cs == NULL) return;
    cout << cs->ertek << endl;
    for(int i = 0; i < cs->gyerekDB; i++)
    {
        tab(szint);
        cout << "'-->";
        kiir(cs->gyerekek[i], szint + 1);
    }
}

void felszabadit(csucs* cs)
{
    if(cs == NULL) return;
    for(int i = 0; i < cs->gyerekDB; i++)
    {
        felszabadit(cs->gyerekek[i]);
    }
    delete[] cs->gyerekek;
    delete cs;
}

int main()
{
    csucs* gyoker = UjCsucs(1);
    hozzaadas(gyoker, UjCsucs(11));
    hozzaadas(gyoker->gyerekek[0], UjCsucs(111));
    hozzaadas(gyoker->gyerekek[0], UjCsucs(112));
    hozzaadas(gyoker, UjCsucs(12));
    hozzaadas(gyoker, UjCsucs(13));
    kiir(gyoker, 0);
    felszabadit(gyoker);
    return 0;
}
