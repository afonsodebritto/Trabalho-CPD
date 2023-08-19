#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include "./parser.hpp"
#include "./hashtable.hpp"
#include "./triejogador.hpp"

using namespace aria::csv;
using namespace std;

int main()
{
    /*
    int aux = 0;
    int flag = 3;
    string id_jogador;
    string nome_jogador;
    string posicoes_jogador;

    HashTable HT;

    CsvParser parser(std::cin);

    int i = 1;
    for(;;){
        auto field = parser.next_field();
        switch (field.type) {
        case FieldType::DATA:
            if(flag > 0)
            {
                flag--;
                break;
            }
            if(aux == 0)
            {
                id_jogador = *field.data;
                aux++;
            }
            else if(aux == 1)
            {
                nome_jogador = *field.data;
                aux++;
            }
            else if(aux == 2)
            {
                posicoes_jogador = *field.data;
                //cout << id_jogador << " " << nome_jogador << " " << posicoes_jogador << endl;
                int id = stoi(id_jogador);
                HT.insertItem(id, nome_jogador, posicoes_jogador);
                aux = 0;
            }
            break;
        case FieldType::ROW_END:
            break;
        case FieldType::CSV_END:
            i = 0;
            break;
        }
        if(i == 0)
            break;
    }
    */
 
    /*
    struct TrieNode *root = getNode();
 
    // Construct trie
    insert(root, "Fernando Pras", 2);
    insert(root, "Cristaldo", 3);
    insert(root, "Lionel Messi", 4);
    insert(root, "Fernando Alvarenga", 7);

    searchPrefix(root, "Fer");
    */

    HashTable HT;

    HT.insertUser(1234, 556);
    HT.insertUser(1223, 456);
    HT.insertUser(1234, 879);

    HT.searchUser(1234);
    HT.searchUser(234);

    HashTable HT2;
    HT2.insertPlayer(1234, "LW, MC", 8.987, 25);
    HT2.insertPlayer(145, "CB", 8.91, 56);
    HT2.searchPlayer(1234, "Neymar");
    HT2.searchPlayer(145, "Sergio Ramos");

    HashTable H3;
    H3.insertTag("Dribler", 1234);
    H3.insertTag("Striker", 1345);
    H3.searchTag("Dribler");

    return 0;
}
