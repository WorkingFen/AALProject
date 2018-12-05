/**
* Name: Instrukcje.cpp
* Purpose: Implementacja instrukcji
*
* @version 0.01 18/11/2017
*/

#include "Instrukcje.h"

#define DODANIE lacza.at(iteratory[ktore[id]][id])
#define MX 500

void Instrukcje::odczyt(std::vector<Wezel*> &wezly, std::vector<Lacze*> &lacza, unsigned &id_start,
                        unsigned &id_koniec, std::string &algorytm, std::vector<Lacze*> &lacza_floyda, bool &zaladowane)
{
    std::string linia;
    std::string pobrane;
    std::string puste;
    unsigned liczba_wezlow;
    unsigned liczba_laczy;
    unsigned id, w_id_0, w_id_1;
    int for_switch;
    bool opcjonalne;
    double x,y;

    this->ladowanie.open(plik + ".txt");
    if(ladowanie.good())
    {
        while(!ladowanie.eof())
        {
            ladowanie >> pobrane;
            if(pobrane == "#")
            {
                std::getline(ladowanie, puste);
                continue;
            }
            else if(pobrane == "WEZLY")
            {
                linia = pobrane;
                ladowanie >> puste;
                ladowanie >> liczba_wezlow;
            }
            else if(pobrane == "LACZA")
            {
                linia = pobrane;
                ladowanie >> puste;
                ladowanie >> liczba_laczy;
            }
            else if(pobrane == "ALGORYTM")
            {
                linia = pobrane;
                ladowanie >> puste;
                ladowanie >> algorytm;
            }
            else if(linia == "WEZLY")
            {
                id = atoi(pobrane.c_str());              ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                ladowanie >> x;
                ladowanie >> y;
                ladowanie >> opcjonalne;                           /// steiner
                //wezly.push_back(new Wezel(id, x, y)); /// to git
                wezly.push_back(new Wezel(id, x, y, opcjonalne)); /// steiner

                for(int i=1; i<liczba_wezlow; i++)
                {
                    ladowanie >> id;
                    ladowanie >> x;
                    ladowanie >> y;
                    ladowanie >> opcjonalne;
                    //wezly.push_back(new Wezel(id, x, y));     /// to git
                    wezly.push_back(new Wezel(id, x, y, opcjonalne));
                }
            }
            else if(linia == "LACZA")
            {
                id = atoi(pobrane.c_str());                    ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                ladowanie >> w_id_0;
                ladowanie >> w_id_1;
                //wezly.at(w_id_0-1)->dodaj_sasiada(w_id_1, wezly.at(w_id_1-1)->x, wezly.at(w_id_1-1)->y);/// to git
                //wezly.at(w_id_1-1)->dodaj_sasiada(w_id_0, wezly.at(w_id_0-1)->x, wezly.at(w_id_0-1)->y);/// to git
                wezly.at(w_id_0-1)->dodaj_sasiada(w_id_1, wezly.at(w_id_1-1)->x, wezly.at(w_id_1-1)->y, wezly.at(w_id_1-1)->opcjonalne);
                wezly.at(w_id_1-1)->dodaj_sasiada(w_id_0, wezly.at(w_id_0-1)->x, wezly.at(w_id_0-1)->y, wezly.at(w_id_0-1)->opcjonalne);
                lacza.push_back(new Lacze(id, wezly.at(w_id_0-1), wezly.at(w_id_1-1)));

                for(int i=1; i<liczba_laczy; i++)
                {
                    ladowanie >> id;
                    ladowanie >> w_id_0;
                    ladowanie >> w_id_1;
                    //wezly.at(w_id_0-1)->dodaj_sasiada(w_id_1, wezly.at(w_id_1-1)->x, wezly.at(w_id_1-1)->y);
                    //wezly.at(w_id_1-1)->dodaj_sasiada(w_id_0, wezly.at(w_id_0-1)->x, wezly.at(w_id_0-1)->y);
                    wezly.at(w_id_0-1)->dodaj_sasiada(w_id_1, wezly.at(w_id_1-1)->x, wezly.at(w_id_1-1)->y, wezly.at(w_id_1-1)->opcjonalne);
                    wezly.at(w_id_1-1)->dodaj_sasiada(w_id_0, wezly.at(w_id_0-1)->x, wezly.at(w_id_0-1)->y, wezly.at(w_id_0-1)->opcjonalne);
                    lacza.push_back(new Lacze(id, wezly.at(w_id_0-1), wezly.at(w_id_1-1)));
                }
            }
            else if(linia == "ALGORYTM")
            {
                if(algorytm == "SCIEZKA")
                    for_switch = 1;
                else if(algorytm == "FLOYD")
                    for_switch = 2;
                switch(for_switch)
                {
                    case 1:
                        id_start = atoi(pobrane.c_str());
                        ladowanie >> id_koniec;
                    break;

                    case 2:
                        w_id_0 = atoi(pobrane.c_str());            ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                        ladowanie >> w_id_1;
                        lacza_floyda.push_back(new Lacze(1, wezly.at(w_id_0-1), wezly.at(w_id_1-1)));
                    break;
                }
            }
        }
    }
    else
    {
        std::string wiadomosc = "An error occurred while loading from file " + plik;
        throw wiadomosc;
    }
    this->ladowanie.close();
    zaladowane = true;
}

unsigned Instrukcje::algorytm_drzewo(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka)
{
    Wezel* wierzcholek = wezly.at(0);                                    ///Wezel startowy
    unsigned cena = 0;
    bool zbadane[1000];

    for(int i=0; i<lacza.size(); i++)
    {
        zbadane[i]=false;
    }

    for(int id=2; id <= wezly.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
    {
        algorytm_dijkstry(wezly, lacza, sciezka, wierzcholek->id, id); /// droga od id start, do kazdego z wezlow
    }

    for(int i=0; i<sciezka.sciezka.size(); i++)                                             ///Liczenie kosztu drzewa rozpinaj¹cego
    {
        if(!zbadane[sciezka.sciezka.at(i)->id]){
            cena += sciezka.sciezka.at(i)->waga;
            zbadane[sciezka.sciezka.at(i)->id] = true;
        }
    }

    return cena;
}

unsigned Instrukcje::algorytm_delta(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka)
{
    Wezel* wierzcholek = wezly.at(0);                                    ///Wezel startowy
    unsigned cena = 0;
    unsigned cena_laczy = 0;
    bool zbadane[1000];

    for(int i=0; i<lacza.size(); i++)
    {
        cena_laczy += lacza.at(i)->waga;
        zbadane[i]=false;
    }

    for(int id=2; id <= wezly.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
    {
        algorytm_dijkstry(wezly, lacza, sciezka, wierzcholek->id, id); /// droga od id start, do kazdego z wezlow
    }

    for(int i=0; i<sciezka.sciezka.size(); i++)                                             ///Liczenie kosztu drzewa rozpinaj¹cego
    {
        if(!zbadane[sciezka.sciezka.at(i)->id]){
            cena += sciezka.sciezka.at(i)->waga;
            zbadane[sciezka.sciezka.at(i)->id] = true;
        }
    }

    return cena_laczy - cena;
}

unsigned Instrukcje::algorytm_dodaj(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka)
{
    unsigned obecny, najlepszy;
    Sciezka nowa_sciezka;
    Wezel* wierzcholek = wezly.at(0);                                    ///Wezel startowy
    unsigned istnieje;
    unsigned ile=0;

    najlepszy=algorytm_prima(wezly, lacza, sciezka);
    nowa_sciezka.sciezka = sciezka.sciezka;

    while(ile != wezly.size()-1)                                        ///Iteracja a¿ do ostatniego wierzcho³ka
    {
        ile++;
        for(int id=2; id <= wezly.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
        {
            istnieje = 0;
            for(int k=0; k < wierzcholek->sasiedzi.size(); k++)         ///Szukamy tego ID w wêz³ach, które sa s¹siadami; k=0 bo wektor
            {
                if(wierzcholek->sasiedzi.at(k)->id == id);             /// Polaczenie istnieje
                {
                    istnieje = 1;
                    continue;
                }
            }
            if(!istnieje)
            {
                sciezka.sciezka.clear();
                lacza.push_back(new Lacze(lacza.size(), wierzcholek, wezly.at(id-1)));

                obecny=algorytm_prima(wezly, lacza, sciezka);
                if(najlepszy>obecny)
                {
                    najlepszy = obecny;
                    nowa_sciezka.sciezka.clear();
                    nowa_sciezka.sciezka = sciezka.sciezka;
                }
                lacza.pop_back();
            }
        }
        wierzcholek = wezly.at(ile);
    }

    sciezka.sciezka = nowa_sciezka.sciezka;

    return najlepszy;
}

///Wezly jako wektor pobrany z pliku, to samo z laczami
unsigned Instrukcje::algorytm_prima(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka)
{

    Wezel* wierzcholek = wezly.at(0);                                   ///Wezel startowy
    unsigned min_waga[wezly.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool zbadane[wezly.size()+1];
    int nowe_id = 0;
    unsigned polaczenia[wezly.size()+1][wezly.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned koszt = 0;
    unsigned iteratory[MX][MX];
    unsigned ktore[wezly.size()+1];
    unsigned ile=0;

    min_waga[0]=MX;
    for(int i=1; i <=wezly.size(); i++)
    {
        min_waga[i] = MX;
        zbadane[i] = false;
        ktore[i] = i;
        iteratory[i][i] = 0;

        for(int q=1; q <=wezly.size(); q++)                             ///Wartosc poczatkowa tablic
        {
            polaczenia[i][q] = MX;
        }
        polaczenia[i][i] = 0;
    }

    zbadane[wierzcholek->id] = true;                                     ///Wierzcho³ek startowy jest zbadany
    min_waga[wierzcholek->id]=0;

    for(int iter = 0; iter < lacza.size(); iter++)      ///Tworzenie tablicy po³¹czeñ od konkretnych wêz³ów z wagami ³¹czy
    {
        polaczenia[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = lacza.at(iter)->waga;
        polaczenia[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = lacza.at(iter)->waga;
        iteratory[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
        iteratory[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
    }

    while(ile != wezly.size()-1)                                        ///Iteracja a¿ do ostatniego wierzcho³ka
    {
        ile++;
        for(int id=2; id <= wezly.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
        {
            for(int k=0; k < wierzcholek->sasiedzi.size(); k++)         ///Szukamy tego ID w wêz³ach, które sa s¹siadami; k=0 bo wektor
            {
                if(wierzcholek->sasiedzi.at(k)->id == id);             /// Polaczenie istnieje
                {
                    if(!zbadane[id])                                    ///Gdy niezbadane to dzia³aj dalej
                    {
                        if(min_waga[id] > polaczenia[wierzcholek->id][id])///Gdy waga minimalna po³¹czenia z wêz³em id jest wiêksza, od nowego po³¹czenia
                        {
                            min_waga[id] = polaczenia[wierzcholek->id][id];
                            ktore[id] = wierzcholek->id;                 ///Dla ktorego wierzcholka.id, polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        nowe_id=0;
        for(int i=1; i<=wezly.size(); i++)                                  /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(!zbadane[i])
            {
                if(min_waga[nowe_id]>min_waga[i])
                    nowe_id=i;
            }
        }
        wierzcholek = wezly.at(nowe_id-1);
        zbadane[wierzcholek->id] = true;                                  /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy n++
    }

    for(int id=2; id<=wezly.size(); id++)                                       ///Liczenie kosztu drzewa rozpinaj¹cego
    {
        sciezka.dodaj_lacze(DODANIE->id, wezly.at(ktore[id]-1), wezly.at(id-1), DODANIE->waga);      ///Zapis kolejnych przejsc algorytmu, id lacza, wezel_start, wezel_koniec
        koszt += min_waga[id];
    }


    return koszt;
}

unsigned Instrukcje::algorytm_steinera(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka)
{
    std::vector<Sciezka> sciezki;
    unsigned nowy_koszt;
    int id_start;
    int id_koniec=0;
    int naj_koszt=0;

    for(int i=0; i<wezly.size(); i++)
    {
        if(wezly.at(i)->opcjonalne==0)
        {
            id_start=(i+1);
            break;
        }
    }

    for(int i=0; i<wezly.size(); i++)
    {
        if(wezly.at(i)->opcjonalne==0)
        {
            if(id_start!=(i+1))
            {
                id_koniec=(i+1);
                algorytm_dijkstry(wezly, lacza, sciezka, id_start, id_koniec);
                sciezki.push_back(sciezka);
                sciezka.czysc();
            }
        }
    }

    for(int i=0; i<sciezka.sciezka.size(); i++)
    {
        naj_koszt += sciezka.sciezka.at(i)->koszt();
    }

    return naj_koszt;
}


///Wezly jako wektor pobrany z pliku, to samo z laczami i pobranymi id startu i konca
unsigned Instrukcje::algorytm_dijkstry(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka, unsigned id_start, unsigned id_koniec)
{
    Wezel* wierzcholek = wezly.at(id_start-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
    unsigned min_waga[wezly.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool ocechowane[wezly.size()+1];
    int nowe_id = 0;
    unsigned polaczenia[wezly.size()+1][wezly.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned koszt = 0;
    unsigned iteratory[MX][MX];
    unsigned ktore[wezly.size()+1];
    unsigned ilosc = 0;

    min_waga[0]=MX;
    for(int i=1; i <=wezly.size(); i++)
    {
        min_waga[i] = MX;
        ocechowane[i] = false;
        ktore[i] = i;
        iteratory[i][i] = MX;

        for(int q=1; q <=wezly.size(); q++)                                       ///Wartosc poczatkowa tablic
        {
            polaczenia[i][q] = MX;
        }
        polaczenia[i][i] = 0;
    }

    ocechowane[wierzcholek->id] = true;                                  ///Wierzcho³ek startowy jest zbadany
    min_waga[wierzcholek->id]=0;


    for(unsigned iter = 0; iter < lacza.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        polaczenia[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = lacza.at(iter)->waga;        ///Lacza sa nieskierowane
        polaczenia[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = lacza.at(iter)->waga;
        iteratory[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = iter;   ///Iteratory lacza miedzy odpowiednimi wezlami
        iteratory[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = iter;
    }

    while(wierzcholek->id != id_koniec)             ///Iteracja az do docelowego wierzcholka
    {
        ilosc++;
        for(int id=1; id <= wezly.size(); id++)                         ///Poszukiwany sasiad o danym ID
        {
            for(int k=0; k < wierzcholek->sasiedzi.size(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
            {
                if(wierzcholek->sasiedzi.at(k)->id == id);             /// Polaczenie istnieje
                {
                    if(!ocechowane[id])                                 ///Gdy niezbadane to dzialaj dalej
                    {
                        if(min_waga[id] > min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                        {
                            min_waga[id] = min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id];
                            ktore[id] = wierzcholek->id;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        nowe_id = 0;
        for(int i=1; i<=wezly.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(i == id_koniec)
            {
                if(ilosc == wezly.size()-1)
                    nowe_id=i;
            }
            else if(!ocechowane[i])
            {
                if(min_waga[nowe_id]>min_waga[i])
                    nowe_id=i;
            }
        }
        wierzcholek = wezly.at(nowe_id-1);
        ocechowane[wierzcholek->id] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
    }

    koszt = min_waga[wierzcholek->id];

    unsigned id = wierzcholek->id;

    while(id != id_start)                                                  ///Tworzenie sciezki
    {
        sciezka.dodaj_lacze(DODANIE->id, wezly.at(ktore[id]-1), wezly.at(id-1), DODANIE->waga);      ///Zapis kolejnych przejsc algorytmu, id, wezel_start, wezel_koniec
        id = ktore[id];
    }

    return koszt;
}

void Instrukcje::algorytm_floyda(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza,
                                     std::vector<Lacze*> lacza_floyda, std::vector<Sciezka*> &sciezki_floyda,
                                     std::vector<unsigned> &koszta)
{
    Wezel* wierzcholek;
    int min_waga[wezly.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool ocechowane[wezly.size()+1];
    int nowe_id;
    int polaczenia[wezly.size()+1][wezly.size()+1];                ///Lacza z wektora w formie tabeli
    int koszt;
    unsigned iteratory[MX][MX];
    unsigned ktore[wezly.size()+1];
    unsigned ilosc;
    Sciezka *sciezka;

    min_waga[0]=MX;

    for(int i=1; i <=wezly.size(); i++)                             ///Zerowanie polaczen i iteratorow
    {
        polaczenia[i][i] = 0;
        iteratory[i][i] = 0;

        for(int q=1; q <=wezly.size(); q++)                         ///Wartosc poczatkowa tablic
        {
            polaczenia[i][q] = MX;
        }
    }

    for(unsigned iter = 0; iter < lacza.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        polaczenia[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = lacza.at(iter)->waga;        ///Lacza sa skierowane
        iteratory[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = iter;   ///Iteratory lacza miedzy odpowiednimi wezlami
    }

    for(unsigned iteracja=0; iteracja < lacza_floyda.size(); iteracja++)
    {
        wierzcholek = wezly.at(lacza_floyda.at(iteracja)->w_id[0]-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
        nowe_id = 0;
        koszt = 0;
        ilosc = 0;

        for(int i=1; i <=wezly.size(); i++)
        {
            min_waga[i] = MX;
            ocechowane[i] = false;
            ktore[i] = i;
        }

        ocechowane[wierzcholek->id] = true;                                  ///Wierzcholek startowy jest zbadany
        min_waga[wierzcholek->id]=0;

        while(wierzcholek->id != lacza_floyda.at(iteracja)->w_id[1])             ///Iteracja az do docelowego wierzcholka
        {
            ilosc++;
            for(int id=1; id <= wezly.size(); id++)                         ///Poszukiwany sasiad o danym ID
            {
                for(int k=0; k < wierzcholek->sasiedzi.size(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
                {
                    if(wierzcholek->sasiedzi.at(k)->id == id && polaczenia[wierzcholek->id][id] != MX)             /// Polaczenie istnieje
                    {
                        if(!ocechowane[id])                                 ///Gdy niezbadane to dzialaj dalej
                        {
                            if(min_waga[id] > min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                            {
                                min_waga[id] = min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id];
                                ktore[id] = wierzcholek->id;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                            }
                        }
                    }
                }
            }
            nowe_id = 0;
            for(int i=1; i<=wezly.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
            {
                if(i == lacza_floyda.at(iteracja)->w_id[1])
                {
                    if(ilosc == wezly.size()-1)
                        nowe_id=i;
                }
                else if(!ocechowane[i])
                {
                    if(min_waga[nowe_id]>min_waga[i])
                        nowe_id=i;
                }
            }
            wierzcholek = wezly.at(nowe_id-1);
            ocechowane[wierzcholek->id] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
        }

        koszt = min_waga[wierzcholek->id];

        unsigned id = wierzcholek->id;

        sciezka = new Sciezka();
        while(id != lacza_floyda.at(iteracja)->w_id[0])                                                  ///Tworzenie sciezki
        {
            sciezka->dodaj_lacze(DODANIE->id, wezly.at(ktore[id]-1), wezly.at(id-1), DODANIE->waga);      ///Zapis kolejnych przejsc algorytmu, id, wezel_start, wezel_koniec
            id = ktore[id];
        }
        sciezki_floyda.push_back(sciezka);

        koszta.push_back(koszt);
    }

}

/// TO algorytm usun
/*unsigned Instrukcje::algorytm_usun(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka, unsigned id_start, unsigned id_koniec)
{
    Wezel* wierzcholek = wezly.at(id_start-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
    unsigned min_waga[wezly.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool ocechowane[wezly.size()+1];
    int nowe_id = 0;
    unsigned polaczenia[wezly.size()+1][wezly.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned koszt = 0;
    unsigned iteratory[MX][MX];
    unsigned ktore[wezly.size()+1];
    unsigned ilosc = 0;
    unsigned stare;

    std::vector<Lacze*>::iterator usun = lacza.begin();

    min_waga[0]=MX;
    for(int i=1; i <=wezly.size(); i++)
    {
        min_waga[i] = MX;
        ocechowane[i] = false;
        ktore[i] = i;
        polaczenia[i][i] = 0;
        iteratory[i][i] = 0;

        for(int q=1; q <=wezly.size(); q++)                                       ///Wartosc poczatkowa tablic
        {
            polaczenia[i][q] = MX;
        }
    }
    ocechowane[wierzcholek->id] = true;                                  ///Wierzcho³ek startowy jest zbadany
    min_waga[wierzcholek->id]=0;


    for(unsigned iter = 0; iter < lacza.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        polaczenia[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = lacza.at(iter)->waga;        ///Lacza sa nieskierowane
        polaczenia[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = lacza.at(iter)->waga;
        iteratory[lacza.at(iter)->w_id[0]][lacza.at(iter)->w_id[1]] = iter;   ///Iteratory lacza miedzy odpowiednimi wezlami
        iteratory[lacza.at(iter)->w_id[1]][lacza.at(iter)->w_id[0]] = iter;
    }

    while(wierzcholek->id != id_koniec)   ///Iteracja az do docelowego wierzcholka
    {
        ilosc++;
        for(int id=1; id <= wezly.size(); id++)                         ///Poszukiwany sasiad o danym ID
        {
            for(int k=0; k < wierzcholek->sasiedzi.size(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
            {
                if(wierzcholek->sasiedzi.at(k)->id == id);             /// Polaczenie istnieje
                {
                    if(!ocechowane[id])                                 ///Gdy niezbadane to dzialaj dalej
                    {
                        if(ilosc==1)
                        {
                            if(min_waga[id] > min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id])   ///Ustawiam wage na 1 krawedzi
                            {
                                min_waga[id] = min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id];
                                ktore[id] = wierzcholek->id;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                            }
                        }
                        else
                        {
                            if(min_waga[id] > min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id])   ///Dla reszty krawedzi
                            {
                                stare=wierzcholek->id;
                                wierzcholek = wezly.at(id);

                                if(wierzcholek->sasiedzi.size() > 1)           /// Jesli jest jeszcze jakis inny sasiad - czyli graf spojny
                                {
                                    usun[iteratory[wierzcholek->id][stare]];
                                    lacza.erase(usun);
                                }
                                min_waga[id] = min_waga[wierzcholek->id]+polaczenia[wierzcholek->id][id];
                                ktore[id] = stare;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                            }
                        }
                    }
                }
            }
        }
        nowe_id = 0;
        for(int i=1; i<=wezly.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(i == id_koniec)
            {
                if(ilosc == wezly.size()-1)
                    nowe_id=i;
            }
            else if(!ocechowane[i])
            {
                if(min_waga[nowe_id]>min_waga[i])
                    nowe_id=i;
            }
        }
        wierzcholek = wezly.at(nowe_id-1);
        ocechowane[wierzcholek->id] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
    }

    koszt = min_waga[wierzcholek->id];

    unsigned id = wierzcholek->id;

    while(id != id_start)                                                  ///Tworzenie sciezki
    {
        sciezka.dodaj_lacze(DODANIE->id, wezly.at(ktore[id]-1), wezly.at(id-1));      ///Zapis kolejnych przejsc algorytmu, id, wezel_start, wezel_koniec
        id = ktore[id];
    }

    return koszt;
}*/

