#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include "./sorting.hpp"
#include <algorithm>

class HashTablePlayer
{
    private:
    struct jogador
    {
        int so_fifa_id;
        string player_name;
        string player_positions;
        float rating;
        int count;

        jogador(int so_fifa_id, string player_positions, string player_name, float player_rating, int player_count)
            : so_fifa_id(so_fifa_id), player_positions(player_positions), player_name(player_name), rating(player_rating), count(player_count)
        {
        }
    };

    public:
        static const int hashGroups = 10000;
        list<struct jogador> table[hashGroups]; // Lista1, Index 0, Lista 2, Index 1...
        int hashFunction(int key);
        void insertPlayer(int id, string posicoes, string nome, float rating, int count);
        void searchPlayer(int id);
        float getRating(int id);
};

int HashTablePlayer::hashFunction(int key)
{
    return key % hashGroups; // Key: 905, in return this function will spit out 5
}

void HashTablePlayer::insertPlayer(int id, string posicoes, string nome, float rating, int count)
{
    int hashValue = hashFunction(id);
    auto& lista = table[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->so_fifa_id == id)
        {
            idExiste = true;
            //ptLista->player_name = nome;
            ptLista->player_positions = posicoes;
            ptLista->rating = rating;
            ptLista->count = count;
            // cout << "ID ja existente, jogador alterado." << endl;
            return;
        }
    }
    if(!idExiste)
    {
        lista.emplace_back(id, posicoes, nome, rating, count);
    }

    return;
}

void HashTablePlayer::searchPlayer(int id)
{
    int hashValue = hashFunction(id);
    auto& lista = table[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    int consultas = 0;
    for(; ptLista != end(lista); ptLista++)
    {
        consultas++;
        if(ptLista->so_fifa_id == id)
        {
            idExiste = true;
            cout << ptLista->so_fifa_id << " "
                 << ptLista->player_name << " "
                 << ptLista->player_positions << " "
                 << ptLista->rating << " " 
                 << ptLista->count << endl;
            break;
        }
    }

    if(!idExiste)
    {
        cout << id << " "
             << "MISS" << " "
             << consultas << endl;
    }

    return;
}

float HashTablePlayer::getRating(int id)
{
    int hashValue = hashFunction(id);
    auto& lista = table[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->so_fifa_id == id)
        {
            idExiste = true;
            if(ptLista->count >= 1000)
                return ptLista->rating;
            else
                return -1;
        }
    }

    if(!idExiste)
        return -1;
}
