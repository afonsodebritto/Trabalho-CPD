#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>

using namespace std;

class HashTable
{
    private:
    struct jogador
    {
        int so_fifa_id;
        string player_positions;
        float rating;
        int count;

        jogador(int id, const string& positions, float player_rating, int player_count)
            : so_fifa_id(id), player_positions(positions), rating(player_rating), count(player_count)
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
        vector<int> ids;

        user(int user_id, vector<int> ids_players)
            : userID(user_id), ids(ids_players)
        {
        }
    };

    public:
        static const int hashGroups = 8000;
        list<struct jogador> table[hashGroups]; // Lista1, Index 0, Lista 2, Index 1...
        list<struct tags> table_tags[hashGroups];
        list<struct user> table_users[hashGroups];
        int hashFunction(int key);
        void insertPlayer(int id, string posicoes, float rating, int count);
        void searchPlayer(int id, string nome);
        void insertTag(string tag, int id);
        void searchTag(string tag);
        void insertUser(int userID, int playerID);
        void searchUser(int userID);
        void printTable();
};

int HashTable::hashFunction(int key)
{
    return key % hashGroups; // Key: 905, in return this function will spit out 5
}

void HashTable::insertPlayer(int id, string posicoes, float rating, int count)
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
            ptLista->player_positions = posicoes;
            ptLista->rating = rating;
            ptLista->count = count;
            // cout << "ID ja existente, jogador alterado." << endl;
            break;
        }
    }
    if(!idExiste)
    {
        lista.emplace_back(id, posicoes, rating, count);
        cout << "Novo jogador adicionado." << endl;
    }

    return;
}

void HashTable::searchPlayer(int id, string player_name)
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
                 << player_name << " "
                 << ptLista->player_positions << " " 
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

void HashTable::insertUser(int userID, int playerID)
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
            ptLista->ids.push_back(playerID);
            break;
        }
    }
    if(!idExiste)
    {
        lista.emplace_back(userID, vector<int>{playerID});
    }

    return;
}

void HashTable::searchUser(int userID)
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
            for(int n : ptLista->ids)
                cout << n << endl;
            break;
        }
    }

    if(!idExiste)
        cout << "User nao encontrado" << endl;
    return;
}