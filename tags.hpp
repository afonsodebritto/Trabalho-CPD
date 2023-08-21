#ifndef TAGS_HPP
#define TAGS_HPP

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

class HashTableTags
{
    private:
    struct tags
    {
        string tag;
        vector<int> ids;

        tags(const string& tag_jogador, vector<int> ids_jogadores)
            : tag(tag_jogador), ids(ids_jogadores)
        {
        }
    };

    public:
        static const int hashGroups = 10000;
        list<struct tags> table_tags[hashGroups];
        int hashFunction(int key);
        void insertTag(string tag, int id);
        void searchTag(string tag);
        vector<int> searchTag_returnIDS(string tag);
};





int HashTableTags::hashFunction(int key)
{
    return key % hashGroups; // Key: 905, in return this function will spit out 5
}

void HashTableTags::insertTag(string tag, int id)
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

std::vector<int> intersection(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    std::vector<int> result;
    
    for (const int& value : vec1) {
        if (std::find(vec2.begin(), vec2.end(), value) != vec2.end()) {
            result.push_back(value);
        }
    }
    
    return result;
}

std::vector<int> intersectionOfLists(const std::vector<std::vector<int>>& lists) {
    if (lists.empty()) {
        return std::vector<int>();  // Return an empty vector if there are no lists
    }
    
    std::vector<int> result = lists[0];  // Initialize result with the first list
    
    for (size_t i = 1; i < lists.size(); ++i) {
        result = intersection(result, lists[i]);  // Find intersection with the next list
    }
    
    return result;
}

void HashTableTags::searchTag(string tag)
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

vector<int> HashTableTags::searchTag_returnIDS(string tag)
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
            return ptLista->ids;
        }
    }

    if(!idExiste)
        cout << "Tag nao encontrada" << endl;
    return ptLista->ids;
}


std::vector<std::string> extractQuotedParameters(const std::string& input) {
    std::vector<std::string> parameters;
    std::istringstream iss(input);

    std::string parameter;
    while (iss >> parameter) {
        if (parameter.front() == '\'' && parameter.back() == '\'') {
            // Remove single quotes and add to parameters
            parameters.push_back(parameter.substr(1, parameter.size() - 2));
            (*n_parametros)++;
        }
    }

    return parameters;
}

#endif