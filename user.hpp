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

//kenji

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
        void searchUser(int userID);
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

void HashTableUser::searchUser(int userID)
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
            vector<pair<int,float>> usuario_atual;
            int end = 0;
            for(auto n : ptLista->ids)
            {
                usuario_atual.push_back(n);
                end++;
            }
                
            quickSort(usuario_atual, 0, end - 1);

            int controle = 20;
            while(controle > 0)
            {
                if(end <= 0)
                    break;
                cout << usuario_atual[end - 1].first << endl;
                controle--;
                end--;
            }
            break;
        }
    }

    if(!idExiste)
        cout << "User nao encontrado" << endl;
    return;
}