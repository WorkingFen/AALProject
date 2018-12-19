/**
* Name: algorithms.cpp
* Purpose: Implementation of algorithms
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "algorithms.h"

#define ADD edges.at(iterators[which[id]][id])
#define MX 500

///Wezly jako wektor pobrany z pliku, to samo z edgesmi
unsigned Algorithms::primsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path)
{

    Vertex* vertex = vertices.at(0);                                            ///Vertex startowy
    unsigned minScale[vertices.size()+1];                                       ///Wagi polaczen do danych wezlow
    bool checked[vertices.size()+1];
    unsigned newID = 0;
    unsigned connections[vertices.size()+1][vertices.size()+1];                ///Lacza z wektora w formie tabeli
    unsigned cost = 0;
    unsigned iterators[MX][MX];
    unsigned which[vertices.size()+1];
    unsigned num=0;

    minScale[0]=MX;
    for(unsigned i=1; i <=vertices.size(); i++)
    {
        minScale[i] = MX;
        checked[i] = false;
        which[i] = i;
        iterators[i][i] = 0;

        for(unsigned q=1; q <=vertices.size(); q++)                             ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
        connections[i][i] = 0;
    }

    checked[vertex->getID()] = true;                                     ///Wierzcho³ek startowy jest zbadany
    minScale[vertex->getID()]=0;

    for(unsigned iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy po³¹czeñ od konkretnych wêz³ów z wagami ³¹czy
    {
        connections[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = edges.at(iter)->getScale();
        connections[edges.at(iter)->getIDVer(1)][edges.at(iter)->getIDVer(0)] = edges.at(iter)->getScale();
        iterators[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
        iterators[edges.at(iter)->getIDVer(1)][edges.at(iter)->getIDVer(0)] = iter;   ///Iteratory ³acza dla odpowiednich wez³ow
    }

    while(num != vertices.size()-1)                                        ///Iteracja a¿ do ostatniego wierzcho³ka
    {
        num++;
        for(unsigned id=2; id <= vertices.size(); id++)                         ///Poszukiwany s¹siad o danym ID; Zaczynamy od ID=2 bo 1 zbadana
        {
            for(int k=0; k < vertex->getNeighboursSize(); k++)           ///Szukamy tego ID w wêz³ach, które sa s¹siadami; k=0 bo wektor
            {
                if(vertex->getNeighbourID(k) == id)                     /// Polaczenie istnieje
                {
                    if(!checked[id])                                    ///Gdy niechecked to dzia³aj dalej
                    {
                        if(minScale[id] > connections[vertex->getID()][id])///Gdy waga minimalna po³¹czenia z wêz³em id jest wiêksza, od nowego po³¹czenia
                        {
                            minScale[id] = connections[vertex->getID()][id];
                            which[id] = vertex->getID();                 ///Dla ktorego wierzcholka.id, polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        newID=0;
        for(unsigned i=1; i<=vertices.size(); i++)                                  /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
        {
            if(!checked[i])
            {
                if(minScale[newID]>minScale[i])
                    newID=i;
            }
        }
        vertex = vertices.at(newID-1);
        checked[vertex->getID()] = true;                                  /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy n++
    }

    for(unsigned id=2; id<=vertices.size(); id++)                                       ///Liczenie kosztu drzewa rozpinaj¹cego
    {
        path.addEdge(ADD->getID(), vertices.at(which[id]-1), vertices.at(id-1), ADD->getScale());      ///Zapis kolejnych przejsc algorithmu, id lacza, wezel_start, wezel_koniec
        cost += minScale[id];
    }


    return cost;
}

///Wezly jako wektor pobrany z pliku, to samo z laczami i pobranymi id startu i konca
unsigned Algorithms::dijkstrasAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path, unsigned idStart, unsigned idFinish)
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
    for(unsigned i=1; i <=vertices.size(); i++)
    {
        minScale[i] = MX;
        marked[i] = false;
        which[i] = i;
        iterators[i][i] = MX;

        for(unsigned q=1; q <=vertices.size(); q++)                                       ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
        connections[i][i] = 0;
    }

    marked[vertex->getID()] = true;                                  ///Wierzcho³ek startowy jest zbadany
    minScale[vertex->getID()]=0;


    for(unsigned iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        connections[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = edges.at(iter)->getScale();        ///Lacza sa nieskierowane
        connections[edges.at(iter)->getIDVer(1)][edges.at(iter)->getIDVer(0)] = edges.at(iter)->getScale();
        iterators[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = iter;   ///Iteratory edges miedzy odpowiednimi wezlami
        iterators[edges.at(iter)->getIDVer(1)][edges.at(iter)->getIDVer(0)] = iter;
    }

    while(vertex->getID() != idFinish)             ///Iteracja az do docelowego wierzcholka
    {
        quantity++;
        for(unsigned id=1; id <= vertices.size(); id++)                         ///Poszukiwany sasiad o danym ID
        {
            for(int k=0; k < vertex->getNeighboursSize(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
            {
                if(vertex->getNeighbourID(k) == id)             /// Polaczenie istnieje
                {
                    if(!marked[id])                                 ///Gdy niechecked to dzialaj dalej
                    {
                        if(minScale[id] > minScale[vertex->getID()]+connections[vertex->getID()][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                        {
                            minScale[id] = minScale[vertex->getID()]+connections[vertex->getID()][id];
                            which[id] = vertex->getID();          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                        }
                    }
                }
            }
        }
        newID = 0;
        for(unsigned i=1; i<=vertices.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
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
        marked[vertex->getID()] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
    }

    cost = minScale[vertex->getID()];

    unsigned id = vertex->getID();

    while(id != idStart)                                                  ///Tworzenie sciezki
    {
        path.addEdge(ADD->getID(), vertices.at(which[id]-1), vertices.at(id-1), ADD->getScale());      ///Zapis kolejnych przejsc algorithmu, id, wezel_start, wezel_koniec
        id = which[id];
    }

    return cost;
}

void Algorithms::floydsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges,
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

    for(unsigned i=1; i <=vertices.size(); i++)                             ///Zerowanie polaczen i iteratorow
    {
        connections[i][i] = 0;
        iterators[i][i] = 0;

        for(unsigned q=1; q <=vertices.size(); q++)                         ///Wartosc poczatkowa tablic
        {
            connections[i][q] = MX;
        }
    }

    for(unsigned iter = 0; iter < edges.size(); iter++)      ///Tworzenie tablicy polaczen od konkretnych wezlow z wagami laczy
    {
        connections[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = edges.at(iter)->getScale();        ///Lacza sa skierowane
        iterators[edges.at(iter)->getIDVer(0)][edges.at(iter)->getIDVer(1)] = iter;   ///Iteratory edges miedzy odpowiednimi wezlami
    }

    for(unsigned iteration=0; iteration < floydsEdges.size(); iteration++)
    {
        vertex = vertices.at(floydsEdges.at(iteration)->getIDVer(0)-1);                          ///Wezel startowy, zaczynamy od elementu o id-1, bo tablica
        newID = 0;
        cost = 0;
        quantity = 0;

        for(unsigned i=1; i <=vertices.size(); i++)
        {
            minScale[i] = MX;
            marked[i] = false;
            which[i] = i;
        }

        marked[vertex->getID()] = true;                                  ///Wierzcholek startowy jest zbadany
        minScale[vertex->getID()]=0;

        while(vertex->getID() != floydsEdges.at(iteration)->getIDVer(1))             ///Iteracja az do docelowego wierzcholka
        {
            quantity++;
            for(unsigned id=1; id <= vertices.size(); id++)                         ///Poszukiwany sasiad o danym ID
            {
                for(int k=0; k < vertex->getNeighboursSize(); k++)         ///Szukamy tego ID w wezlach, które sa sasiadami; k=0 bo wektor
                {
                    if(vertex->getNeighbourID(k) == id && connections[vertex->getID()][id] != MX)             /// Polaczenie istnieje
                    {
                        if(!marked[id])                                 ///Gdy niechecked to dzialaj dalej
                        {
                            if(minScale[id] > minScale[vertex->getID()]+connections[vertex->getID()][id])   ///Gdy poprzednio zapisana waga jest wieksza od obecnie rozpatrywanej sciezki
                            {
                                minScale[id] = minScale[vertex->getID()]+connections[vertex->getID()][id];
                                which[id] = vertex->getID();          ///Dla ktorego wierzcholek.id , polaczenie z ID jest najmniejsze, nadpisujemy
                            }
                        }
                    }
                }
            }
            newID = 0;
            for(unsigned i=1; i<=vertices.size(); i++)                               /// Szukamy sąsiada o najmniejszej wadze, by do niego przejsc
            {
                if(i == floydsEdges.at(iteration)->getIDVer(1))
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
            marked[vertex->getID()] = true;                          /// Zbadalismy juz kolejny wierzcholek, od wierzcholek.id bo juz zwiekszylismy nowe_id++
        }

        cost = minScale[vertex->getID()];

        unsigned id = vertex->getID();

        path = new Path();
        while(id != floydsEdges.at(iteration)->getIDVer(0))                                                  ///Tworzenie sciezki
        {
            path->addEdge(ADD->getID(), vertices.at(which[id]-1), vertices.at(id-1), ADD->getScale());      ///Zapis kolejnych przejsc algorithmu, id, wezel_start, wezel_koniec
            id = which[id];
        }
        floydsPaths.push_back(path);

        costs.push_back(cost);
    }

}

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::linearAlgorithm(std::vector<Vertex*> vertices){
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned actualDis = 0;
    unsigned bestDis = 0;
    unsigned prevDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;

    unsigned backVertex = vertices.size();

    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    for(unsigned frontVertex = 0; backVertex != 0 ; frontVertex = (frontVertex+1)%len){
        if(actualDis >= averageDis){
            if(prevDis == averageDis || actualDis  == averageDis){
                bestVer.first = vertices.at(backVertex%len);
                if((prevDis-averageDis) == 0){
                    bestVer.second = vertices.at(frontVertex);
                    result.first = prevDis;
                }
                else{
                    bestVer.second = vertices.at((frontVertex+1)%len);
                    result.first = actualDis;
                }
                result.second = bestVer;
                return result;
            }
            else if(bestDis > averageDis && bestDis < actualDis){
                if((bestDis - averageDis) > (averageDis - prevDis)){
                    bestVer.first = vertices.at(backVertex%len);
                    bestVer.second = vertices.at(frontVertex);
                    bestDis = prevDis;
                }
            }
            else if(bestDis < averageDis && bestDis > prevDis){
                if((averageDis - bestDis) > (actualDis - averageDis)){
                    bestVer.first = vertices.at(backVertex%len);
                    bestVer.second = vertices.at((frontVertex+1)%len);
                    bestDis = actualDis;
                }
            }
            else if((bestDis < averageDis && bestDis < prevDis) || (bestDis > averageDis && bestDis > actualDis)){
                bestVer.first = vertices.at(backVertex%len);
                if((actualDis - averageDis) >= (averageDis - prevDis)){
                    bestVer.second = vertices.at(frontVertex);
                    bestDis = prevDis;
                }
                else{
                    bestVer.second = vertices.at((frontVertex+1)%len);
                    bestDis = actualDis;
                }
            }
            actualDis-=vertices.at(backVertex%len)->getDistance();
            backVertex = (backVertex%len)+1;
            continue;
        }
        prevDis = actualDis;
        actualDis += vertices.at(frontVertex)->getDistance();
    }
    result.first = bestDis;
    result.second = bestVer;
    return result;
}

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::mastsAlgorithm(std::vector<Vertex*> vertices){
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned actualDis = 0;
    unsigned bestDis = 0;
    unsigned prevDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;

    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    for(unsigned chosen = 0; chosen < len; chosen++){
        for(unsigned temp = chosen; temp != len; temp = (temp+1)%len){
            actualDis += vertices.at(temp)->getDistance();
            if(actualDis >= averageDis){
                if(prevDis == averageDis || actualDis  == averageDis){
                    bestVer.first = vertices.at(chosen);
                    if((prevDis-averageDis) == 0){
                        bestVer.second = vertices.at(temp);
                        result.first = prevDis;
                    }
                    else{
                        bestVer.second = vertices.at((temp+1)%len);
                        result.first = actualDis;
                    }
                    result.second = bestVer;
                    return result;
                }
                else if(bestDis > averageDis && bestDis < actualDis){
                    if((bestDis - averageDis) > (averageDis - prevDis)){
                        bestVer.first = vertices.at(chosen);
                        bestVer.second = vertices.at(temp);
                        bestDis = prevDis;
                    }
                }
                else if(bestDis < averageDis && bestDis > prevDis){
                    if((averageDis - bestDis) > (actualDis - averageDis)){
                        bestVer.first = vertices.at(chosen);
                        bestVer.second = vertices.at((temp+1)%len);
                        bestDis = actualDis;
                    }
                }
                else if((bestDis < averageDis && bestDis < prevDis) || (bestDis > averageDis && bestDis > actualDis)){
                    bestVer.first = vertices.at(chosen);
                    if((actualDis - averageDis) >= (averageDis - prevDis)){
                        bestVer.second = vertices.at(temp);
                        bestDis = prevDis;
                    }
                    else{
                        bestVer.second = vertices.at((temp+1)%len);
                        bestDis = actualDis;
                    }
                }
                break;
            }
            prevDis = actualDis;
        }
        prevDis = 0;
        actualDis = 0;
    }
    result.first = bestDis;
    result.second = bestVer;
    return result;
}

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::bruteAlgorithm(std::vector<Vertex*> vertices){
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned actualDis = 0;
    unsigned bestDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;

    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    for(unsigned chosen = 0; chosen < len; chosen++){
        for(unsigned target = (chosen+1)%len; target != chosen; target = (target+1)%len){
            for(unsigned temp = chosen; temp != target; temp = (temp+1)%len)
                actualDis += vertices.at(temp)->getDistance();
            if(actualDis <= averageDis && actualDis > bestDis){
                bestVer.first = vertices.at(chosen);
                bestVer.second = vertices.at(target);
                bestDis = actualDis;
            }
            actualDis = 0;
        }
    }
    result.first = bestDis;
    result.second = bestVer;
    return result;
}
