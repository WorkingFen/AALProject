/**
* Name: Instrukcje.h
* Purpose: Deklaracja instrukcji
*
* @version 0.01 18/11/2017
*/
#pragma once

#include "Lacze.h"
#include "Wezel.h"
#include "Sciezka.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#define MX 500

class Instrukcje{
    private:
        std::ifstream ladowanie;

    public:
        std::string plik;
        void odczyt(std::vector<Wezel*> &wezly, std::vector<Lacze*> &lacza, unsigned &id_start,
                    unsigned &id_koniec, std::string &algorytm, std::vector<Lacze*> &lacza_floyda, bool &zaladowane);

        unsigned algorytm_prima(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka);

        unsigned algorytm_steinera(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka);

        unsigned algorytm_dijkstry(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka, unsigned id_start, unsigned id_koniec);

        void algorytm_floyda(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza,
                                 std::vector<Lacze*> lacza_floyda, std::vector<Sciezka*> &sciezki_floyda,
                                 std::vector<unsigned> &koszta);

        unsigned algorytm_dodaj(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka);

        unsigned algorytm_drzewo(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka);

        unsigned algorytm_delta(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka);


        //unsigned algorytm_usun(std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, Sciezka &sciezka, unsigned id_start, unsigned id_koniec);

};
