/**
* Name: Sciezka.h
* Purpose: Deklaracja sciezka
*
* @version 0.01 18/11/2017
*/
#pragma once

#include <iostream>
#include "Lacze.h"

class Sciezka{
    public:
        std::vector<Lacze*> sciezka;

        Sciezka()
        {
        }

        void dodaj_lacze(unsigned id, Wezel* start, Wezel* koniec, unsigned waga)
        {
            sciezka.push_back(new Lacze(id, start, koniec, waga));
        }

        void czysc()
        {
            for(int i=0; i<sciezka.size(); i++)
                sciezka.at(i)->zeruj();
        }
};
