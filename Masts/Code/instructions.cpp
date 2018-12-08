/**
* Name: instructions.cpp
* Purpose: Implementation of instructions
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "instructions.h"

#define ADD edges.at(iterators[which[id]][id])
#define MX 500

void Instructions::read(std::vector<Vertex*> &vertices, std::vector<Edge*> &edges, unsigned &idStart,
                        unsigned &idFinish, std::string &algorithm, std::vector<Edge*> &floydsEdges, bool &loaded)
{
    std::string line;
    std::string response;
    std::string hollow;
    unsigned verticesNum;
    unsigned edgesNum;
    unsigned id, idVer0, idVer1;
    int forSwitch;
    double x,y;

    this->loading.open("Resources/" + file + ".txt");
    if(loading.good())
    {
        while(!loading.eof())
        {
            loading >> response;
            if(response == "#")
            {
                std::getline(loading, hollow);
                continue;
            }
            else if(response == "VERTICES")
            {
                line = response;
                loading >> hollow;
                loading >> verticesNum;
            }
            else if(response == "EDGES")
            {
                line = response;
                loading >> hollow;
                loading >> edgesNum;
            }
            else if(response == "ALGORITHM")
            {
                line = response;
                loading >> hollow;
                loading >> algorithm;
            }
            else if(line == "VERTICES")
            {
                id = atoi(response.c_str());              ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                loading >> x;
                loading >> y;
                vertices.push_back(new Vertex(id, x, y)); /// to git

                for(int i=1; i<verticesNum; i++)
                {
                    loading >> id;
                    loading >> x;
                    loading >> y;
                    vertices.push_back(new Vertex(id, x, y));     /// to git
                }
            }
            else if(line == "EDGES")
            {
                id = atoi(response.c_str());                    ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                loading >> idVer0;
                loading >> idVer1;
                vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->x, vertices.at(idVer1-1)->y);/// to git
                vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->x, vertices.at(idVer0-1)->y);/// to git
                edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1)));

                for(int i=1; i<edgesNum; i++)
                {
                    loading >> id;
                    loading >> idVer0;
                    loading >> idVer1;
                    vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->x, vertices.at(idVer1-1)->y);
                    vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->x, vertices.at(idVer0-1)->y);
                    edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1)));
                }
            }
            else if(line == "ALGORITHM")
            {
                if(algorithm == "PATH")
                    forSwitch = 1;
                else if(algorithm == "FLOYD")
                    forSwitch = 2;
                switch(forSwitch)
                {
                    case 1:
                        idStart = atoi(response.c_str());
                        loading >> idFinish;
                    break;

                    case 2:
                        idVer0 = atoi(response.c_str());            ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                        loading >> idVer1;
                        floydsEdges.push_back(new Edge(1, vertices.at(idVer0-1), vertices.at(idVer1-1)));
                    break;
                }
            }
        }
    }
    else
    {
        std::string msg = "An error occurred while loading from file " + file;
        throw msg;
    }
    this->loading.close();
    loaded = true;
}

///Wezly jako wektor pobrany z pliku, to samo z edgesmi
unsigned Instructions::primsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path)
{

    Vertex* vertex = vertices.at(0);                                   ///Vertex startowy
    unsigned minScale[vertices.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool checked[vertices.size()+1];
    int newID = 0;
    unsigned connections[vertices.size()+1][vertices.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned cost = 0;
    unsigned iterators[MX][MX];
    unsigned which[vertices.size()+1];
    unsigned num=0;

    minScale[0]=MX;
    for(int i=1; i <=vertices.size(); i++)
    {
        minScale[i] = MX;
        checked[i] = false;
        which[i] = i;
        iterators[i][i] = 0;

        for(int q=1; q <=vertices.size(); q++)                             ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
        connections[i][i] = 0;
    }

    checked[vertex->id] = true;                                     ///Wierzcho³ek startowy jest zbadany
    minScale[vertex->id]=0;

    for(int iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy po³¹czeñ od konkretnych wêz³ów z wagami ³¹czy
    {
        connections[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = edges.at(iter)->scale;
        connections[edges.at(iter)->idVer[1]][edges.at(iter)->idVer[0]] = edges.at(iter)->scale;
        iterators[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
        iterators[edges.at(iter)->idVer[1]][edges.at(iter)->idVer[0]] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
    }

    while(num != vertices.size()-1)                                        ///Iteracja a¿ do ostatniego wierzcho³ka
    {
        num++;
        for(int id=2; id <= vertices.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
        {
            for(int k=0; k < vertex->neighbours.size(); k++)         ///Szukamy tego ID w wêz³ach, które sa s¹siadami; k=0 bo wektor
            {
                if(vertex->neighbours.at(k)->id == id);             /// Polaczenie istnieje
                {
                    if(!checked[id])                                    ///Gdy niechecked to dzia³aj dalej
                    {
                        if(minScale[id] > connections[vertex->id][id])///Gdy waga minimalna po³¹czenia z wêz³em id jest wiêksza, od nowego po³¹czenia
                        {
                            minScale[id] = connections[vertex->id][id];
                            which[id] = vertex->id;                 ///Dla ktorego wierzcholka.id, polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        newID=0;
        for(int i=1; i<=vertices.size(); i++)                                  /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(!checked[i])
            {
                if(minScale[newID]>minScale[i])
                    newID=i;
            }
        }
        vertex = vertices.at(newID-1);
        checked[vertex->id] = true;                                  /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy n++
    }

    for(int id=2; id<=vertices.size(); id++)                                       ///Liczenie kosztu drzewa rozpinaj¹cego
    {
        path.addEdge(ADD->id, vertices.at(which[id]-1), vertices.at(id-1), ADD->scale);      ///Zapis kolejnych przejsc algorithmu, id lacza, wezel_start, wezel_koniec
        cost += minScale[id];
    }


    return cost;
}

///Wezly jako wektor pobrany z pliku, to samo z laczami i pobranymi id startu i konca
unsigned Instructions::dijkstrasAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path, unsigned idStart, unsigned idFinish)
{
    Vertex* vertex = vertices.at(idStart-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
    unsigned minScale[vertices.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool marked[vertices.size()+1];
    int newID = 0;
    unsigned connections[vertices.size()+1][vertices.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned cost = 0;
    unsigned iterators[MX][MX];
    unsigned which[vertices.size()+1];
    unsigned quantity = 0;

    minScale[0]=MX;
    for(int i=1; i <=vertices.size(); i++)
    {
        minScale[i] = MX;
        marked[i] = false;
        which[i] = i;
        iterators[i][i] = MX;

        for(int q=1; q <=vertices.size(); q++)                                       ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
        connections[i][i] = 0;
    }

    marked[vertex->id] = true;                                  ///Wierzcho³ek startowy jest zbadany
    minScale[vertex->id]=0;


    for(unsigned iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        connections[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = edges.at(iter)->scale;        ///Lacza sa nieskierowane
        connections[edges.at(iter)->idVer[1]][edges.at(iter)->idVer[0]] = edges.at(iter)->scale;
        iterators[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = iter;   ///Iteratory edges miedzy odpowiednimi wezlami
        iterators[edges.at(iter)->idVer[1]][edges.at(iter)->idVer[0]] = iter;
    }

    while(vertex->id != idFinish)             ///Iteracja az do docelowego wierzcholka
    {
        quantity++;
        for(int id=1; id <= vertices.size(); id++)                         ///Poszukiwany sasiad o danym ID
        {
            for(int k=0; k < vertex->neighbours.size(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
            {
                if(vertex->neighbours.at(k)->id == id);             /// Polaczenie istnieje
                {
                    if(!marked[id])                                 ///Gdy niechecked to dzialaj dalej
                    {
                        if(minScale[id] > minScale[vertex->id]+connections[vertex->id][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                        {
                            minScale[id] = minScale[vertex->id]+connections[vertex->id][id];
                            which[id] = vertex->id;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        newID = 0;
        for(int i=1; i<=vertices.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(i == idFinish)
            {
                if(quantity == vertices.size()-1)
                    newID=i;
            }
            else if(!marked[i])
            {
                if(minScale[newID]>minScale[i])
                    newID=i;
            }
        }
        vertex = vertices.at(newID-1);
        marked[vertex->id] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
    }

    cost = minScale[vertex->id];

    unsigned id = vertex->id;

    while(id != idStart)                                                  ///Tworzenie sciezki
    {
        path.addEdge(ADD->id, vertices.at(which[id]-1), vertices.at(id-1), ADD->scale);      ///Zapis kolejnych przejsc algorithmu, id, wezel_start, wezel_koniec
        id = which[id];
    }

    return cost;
}

void Instructions::floydsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                                     std::vector<Edge*> floydsEdges, std::vector<Path*> &floydsPaths,
                                     std::vector<unsigned> &costs)
{
    Vertex* vertex;
    int minScale[vertices.size()+1];                                  ///Wagi polaczen do danych wezlow
    bool marked[vertices.size()+1];
    int newID;
    int connections[vertices.size()+1][vertices.size()+1];                ///Lacza z wektora w formie tabeli
    int cost;
    unsigned iterators[MX][MX];
    unsigned which[vertices.size()+1];
    unsigned quantity;
    Path *path;

    minScale[0]=MX;

    for(int i=1; i <=vertices.size(); i++)                             ///Zerowanie polaczen i iteratorow
    {
        connections[i][i] = 0;
        iterators[i][i] = 0;

        for(int q=1; q <=vertices.size(); q++)                         ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
    }

    for(unsigned iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        connections[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = edges.at(iter)->scale;        ///Lacza sa skierowane
        iterators[edges.at(iter)->idVer[0]][edges.at(iter)->idVer[1]] = iter;   ///Iteratory edges miedzy odpowiednimi wezlami
    }

    for(unsigned iteration=0; iteration < floydsEdges.size(); iteration++)
    {
        vertex = vertices.at(floydsEdges.at(iteration)->idVer[0]-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
        newID = 0;
        cost = 0;
        quantity = 0;

        for(int i=1; i <=vertices.size(); i++)
        {
            minScale[i] = MX;
            marked[i] = false;
            which[i] = i;
        }

        marked[vertex->id] = true;                                  ///Wierzcholek startowy jest zbadany
        minScale[vertex->id]=0;

        while(vertex->id != floydsEdges.at(iteration)->idVer[1])             ///Iteracja az do docelowego wierzcholka
        {
            quantity++;
            for(int id=1; id <= vertices.size(); id++)                         ///Poszukiwany sasiad o danym ID
            {
                for(int k=0; k < vertex->neighbours.size(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
                {
                    if(vertex->neighbours.at(k)->id == id && connections[vertex->id][id] != MX)             /// Polaczenie istnieje
                    {
                        if(!marked[id])                                 ///Gdy niechecked to dzialaj dalej
                        {
                            if(minScale[id] > minScale[vertex->id]+connections[vertex->id][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                            {
                                minScale[id] = minScale[vertex->id]+connections[vertex->id][id];
                                which[id] = vertex->id;          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                            }
                        }
                    }
                }
            }
            newID = 0;
            for(int i=1; i<=vertices.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
            {
                if(i == floydsEdges.at(iteration)->idVer[1])
                {
                    if(quantity == vertices.size()-1)
                        newID=i;
                }
                else if(!marked[i])
                {
                    if(minScale[newID]>minScale[i])
                        newID=i;
                }
            }
            vertex = vertices.at(newID-1);
            marked[vertex->id] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
        }

        cost = minScale[vertex->id];

        unsigned id = vertex->id;

        path = new Path();
        while(id != floydsEdges.at(iteration)->idVer[0])                                                  ///Tworzenie sciezki
        {
            path->addEdge(ADD->id, vertices.at(which[id]-1), vertices.at(id-1), ADD->scale);      ///Zapis kolejnych przejsc algorithmu, id, wezel_start, wezel_koniec
            id = which[id];
        }
        floydsPaths.push_back(path);

        costs.push_back(cost);
    }

}

