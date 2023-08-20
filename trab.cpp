#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include "./hashtable.hpp"
#include "./triejogador.hpp"


using namespace std;

int main()
{
    cout <<  "." << endl;
    

    //pre-processing data


    //começo da leitura de rating.csv

    std::ifstream ratingcsv ("minirating.csv");

    if (!ratingcsv.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }
    

    HashTable HT_PLAYER;
    HashTable HT_USER;
    HashTable HT_GRADE;


    std::string line;

    string user_id, sofifa_id, rating;
    int user, sofifa;
    float  grade;

    std::getline(ratingcsv, line); //para desconsiderar a primeira linha que tem apenas "user_id,sofifa_id,rating"


    while (std::getline(ratingcsv, user_id, ',')) {

        // Use getline para separar as colunas usando a vírgula como delimitador
        std::getline(ratingcsv, sofifa_id, ',');       
        std::getline(ratingcsv, rating, '\n');
        

        user = stoi(user_id);
        sofifa = stoi(sofifa_id);
        grade = stof(rating);

        HT_GRADE.insertGrade(sofifa, grade);

        //coloco na hash que coloca em uma lista encadada todos os jogadores que o user avaliou

        HT_USER.insertUser(user, sofifa);
        
    }

    ratingcsv.close();

    HT_GRADE.att_global();

    //fim da leitura de rating.csv




    //começo da leitura do players.csv

    //começo da leitura do players.csv


    struct TrieNode* raiz;
    raiz = getNode();


    
    std::ifstream playerscsv ("players.csv");

    if (!playerscsv.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::getline(playerscsv, line); //para desconsiderar a primeira linha que tem apenas "sofifa_id,name,player_positions"

    string name, player_positions, lixo;  //reusar sofifa_id da leitura do rating.csv
    //reusar int sofifa também

    while (std::getline(playerscsv, sofifa_id, ',')) {
 

        // Use getline para separar as colunas usando a vírgula como delimitador
        std::getline(playerscsv, name, ',');


        char firstChar = ratingcsv.peek();

        if (firstChar == '"') 
        {
            std::getline(playerscsv, player_positions, '"'); // Ler até a primeira aspa
            std::getline(playerscsv, player_positions, '"'); // Ler a parte entre as aspas  

            //std::getline(playerscsv, lixo, '\n'); // Ler o\n

        }else 
        {
            std::getline(playerscsv, player_positions, '\n');
        }


        sofifa = stoi(sofifa_id);

        

        float global_rating =  HT_GRADE.searchGrade_global(sofifa);
        int count = HT_GRADE.searchGrade_count(sofifa);

        //inserindo as informaçoes na nossa hash principal (int id, const string& positions, float player_rating, int player_count)

        HT_PLAYER.insertPlayer(sofifa, player_positions, global_rating, count);

        insert(raiz, name, sofifa);

    }

    playerscsv.close();

    //HT_PLAYER.searchPlayer(158023);
    vector<struct player> jogadores = searchPrefix(raiz, "Fer");

    for(struct player jogador : jogadores)
        HT_PLAYER.searchPlayer(jogador.id, jogador.nome);

        

    return 0;
}
