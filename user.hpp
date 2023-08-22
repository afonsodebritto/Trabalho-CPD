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


class HashTableUser
{
    private:
    struct user
    {
        int userID;
        vector<pair<int, float>> ids;

        user(int user_id, vector<pair<int, float>> ids_players)
            : userID(user_id), ids(ids_players)
        {
        }
    };

    public:
        static const int hashGroups = 10000;
        list<struct user> table_users[hashGroups];
        int hashFunction(int key);
        void insertUser(int userID, int playerID, float playerGrade);
        vector<pair<int,float>> searchUser(int userID, int* size);
};





int HashTableUser::hashFunction(int key)
{
    return key % hashGroups;
}

void HashTableUser::insertUser(int userID, int playerID, float playerGrade)
{
    int hashValue = hashFunction(userID);

    auto& lista = table_users[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->userID == userID)
        {
            idExiste = true;
            ptLista->ids.push_back({playerID, playerGrade});
            return;
        }
    }
    if(!idExiste)
    {
        vector<pair<int,float>> ids;
        ids.push_back(make_pair(playerID, playerGrade));
        lista.emplace_back(userID, ids);
    }

    return;
}

vector<pair<int,float>> HashTableUser::searchUser(int userID, int* size)
{
    vector<pair<int,float>> usuario_players;
    int hashValue = hashFunction(userID);

    auto& lista = table_users[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->userID == userID)
        {
            idExiste = true;
            for(auto n : ptLista->ids)
            {
                usuario_players.push_back(n);
                (*size)++;   
            }
        
        quickSort(usuario_players, 0, (*size) - 1);
        return usuario_players;

        break;
        }
    }

    return usuario_players;
}