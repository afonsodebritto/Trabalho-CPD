#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include <utility>

using namespace std;

//kenji

class HashTable
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

    struct tags
    {
        string tag;
        vector<int> ids;

        tags(const string& tag_jogador, vector<int> ids_jogadores)
            : tag(tag_jogador), ids(ids_jogadores)
        {
        }
    };

    struct user
    {
        int userID;
        vector<pair<int, float>> ids;

        user(int user_id, vector<pair<int, float>> ids_players)
            : userID(user_id), ids(ids_players)
        {
        }
    };

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
        static const int hashGroups = 10000;
        list<struct jogador> table[hashGroups]; // Lista1, Index 0, Lista 2, Index 1...
        list<struct tags> table_tags[hashGroups];
        list<struct user> table_users[hashGroups];
        list<struct grade> table_grade[hashGroups];
        int hashFunction(int key);
        void insertPlayer(int id, string posicoes, string nome, float rating, int count);
        void searchPlayer(int id);
        void insertTag(string tag, int id);
        void searchTag(string tag);
        void insertUser(int userID, int playerID, float playerGrade);
        vector<int> searchUser(int userID);
        void printTable();
        void insertGrade(int id, float rating);
        void searchGrade(int id, string nome);
        void att_global();
        float searchGrade_global(int id);
        int searchGrade_count(int id);
};





int HashTable::hashFunction(int key)
{
    return key % hashGroups; // Key: 905, in return this function will spit out 5
}

void HashTable::att_global()
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

void HashTable::insertGrade(int id, float rating)
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

float HashTable::searchGrade_global(int id)
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

int HashTable::searchGrade_count(int id)
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




void HashTable::insertPlayer(int id, string posicoes, string nome, float rating, int count)
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

void HashTable::searchPlayer(int id)
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

void HashTable::insertTag(string tag, int id)
{
    int sum = 0;
    for(int i = 0; i < tag.length(); i ++)
    {
        sum += tag[i];
    }

    int hashValue = hashFunction(sum);

    auto& lista = table_tags[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->tag == tag)
        {
            idExiste = true;
            ptLista->ids.push_back(id);
            break;
        }
    }
    if(!idExiste)
    {
        lista.emplace_back(tag, vector<int>{id});
    }

    return;
}

/*
void HashTable::printTable()
{
    for(int i{}; i < hashGroups; i++)
    {
        if(table[i].size() == 0) continue;

        auto ptLista = table[i].begin();
        for(; ptLista != table[i].end(); ptLista++)
        {
            cout << "so_fifa_id: " << ptLista->so_fifa_id << endl <<
            " player_name: " << ptLista->player_name <<
            " player_positions: " << ptLista->player_positions << endl;
        }
    }
}
*/

void HashTable::searchTag(string tag)
{
    int sum = 0;
    for(int i = 0; i < tag.length(); i ++)
    {
        sum += tag[i];
    }

    int hashValue = hashFunction(sum);

    auto& lista = table_tags[hashValue];
    auto ptLista = begin(lista);
    bool idExiste = false;
    for(; ptLista != end(lista); ptLista++)
    {
        if(ptLista->tag == tag)
        {
            idExiste = true;
            for(int n : ptLista->ids)
                cout << n << endl;
            break;
        }
    }

    if(!idExiste)
        cout << "Tag nao encontrada" << endl;
    return;
}

void HashTable::insertUser(int userID, int playerID, float playerGrade)
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
        lista.emplace_back(userID, vector<int>{playerID});
    }

    return;
}

vector<int> HashTable::searchUser(int userID)
{
    vector<int> players_user;
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
                players_user.push_back(n.first);
            break;
        }
    }

    if(!idExiste)
        cout << "User nao encontrado" << endl;
    return players_user;
}

#endif // HASHTABLE_HPP