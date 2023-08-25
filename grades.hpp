#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include "./sorting.hpp"
#include <algorithm>

using namespace std;

class HashTableGrades
{
    private:
    struct grade
    {
        int id;
        float global;
        int count;

        grade(int id, float global, int count)
            : id(id), global(global), count(count)
        {
        }
    };



    public:
        static const int hashGroups = 50000;
        list<struct grade> table_grade[hashGroups];
        int hashFunction(int key);
        void insertGrade(int id, float rating);
        void searchGrade(int id, string nome);
        void att_global();
        float searchGrade_global(int id);
        int searchGrade_count(int id);
};





int HashTableGrades::hashFunction(int key)
{
    return key % hashGroups; // Key: 905, in return this function will spit out 5
}

void HashTableGrades::att_global()
{
    
    for(int hashValue = 0;  hashValue <= hashGroups; hashValue ++) {

        auto& lista = table_grade[hashValue];
        auto ptLista = begin(lista);
        for(; ptLista != end(lista); ptLista++)
        {
            float global = ptLista->global;
            int count = ptLista->count;
            ptLista->global =  global  / count; //média global do jogador
        }
    }
}

void HashTableGrades::insertGrade(int id, float rating)
{
    int hashValue = hashFunction(id);
    auto& lista = table_grade[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->id == id)
        {
            idExiste = true;
            ptLista->global += rating;
            ptLista->count += 1;
            
            return;
        }
    }
    if(!idExiste)
    {

        lista.emplace_back(id, rating, 1);
        
    }

    return;
}

float HashTableGrades::searchGrade_global(int id)
{
    int hashValue = hashFunction(id);
    auto& lista = table_grade[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    float global = 0.0;
  
    for(; ptLista != end(lista); ptLista++)
    {

        if(ptLista->id == id)
        {
            idExiste = true;

            global = ptLista->global;
            
            return global;
        }
    }

    return global;
    
}

int HashTableGrades::searchGrade_count(int id)
{
    int hashValue = hashFunction(id);
    auto& lista = table_grade[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    int count = 0;
  
    for(; ptLista != end(lista); ptLista++)
    {

        if(ptLista->id == id)
        {
            idExiste = true;

            count = ptLista->count;
            
            return count;
        }
    }


    return count;

}
