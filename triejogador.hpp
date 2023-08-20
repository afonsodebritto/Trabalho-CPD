#ifndef TRIEJOGADOR_HPP
#define TRIEJOGADOR_HPP

#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int ASCII_SIZE = 255;

struct TrieNode
{
    struct TrieNode* filhos[ASCII_SIZE];
    // fim_palavra é true se o nodo apontar pra última letra de uma palavra
    bool fim_palavra;
    int id;
};

struct player
{
    string nome;
    int id;
};

// Cria um nodo da árvore
struct TrieNode* getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->fim_palavra = false;

    for(int i = 0; i < ASCII_SIZE; i++)
        pNode->filhos[i] = NULL;

    return pNode;
}

void insert(struct TrieNode* root, string nome, int id_fifa)
{
    struct TrieNode* ptArvore = root;

    for(int i = 0; i < nome.length(); i++)
    {
        int index = nome[i];
        
        if(ptArvore->filhos[index] == NULL)
        {
            ptArvore->filhos[index] = getNode();
        }
        ptArvore = ptArvore->filhos[index];
    }

    // Marca o último caracter como fim de palavra
    // E adiciona o ID
    ptArvore->fim_palavra = true;
    ptArvore->id = id_fifa;
}

bool search(struct TrieNode* root, string nome)
{
    struct TrieNode* ptArvore = root;

    for(int i = 0; i < nome.length(); i++)
    {
        int index = nome[i];
        if(!ptArvore->filhos[index])
            return false;

        ptArvore = ptArvore->filhos[index];
    }

    return(ptArvore->fim_palavra);
}

void collectWords(struct TrieNode* root, string prefix, vector<int>* players)
{
    if(root == nullptr)
        return;

    if(root->fim_palavra)
    {
        players->push_back({root->id});
    }

    for(int i = 0; i < ASCII_SIZE; i++)
    {
        if(root->filhos[i])
        {
            char ch = i;
            collectWords(root->filhos[i], (prefix + ch), players);
        }
    }

}

vector<int> searchPrefix(struct TrieNode* root, string prefix)
{
    vector<int> players;
    struct TrieNode* ptArvore = root;

    for(int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i];
        if(index < 0 || index >= ASCII_SIZE)
            return players;
        ptArvore = ptArvore->filhos[index];
    }

    collectWords(ptArvore, prefix, &players);

    return players;
}

#endif // TRIEJOGADOR_HPP