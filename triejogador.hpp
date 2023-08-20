#include <iostream>
#include <vector>

using namespace std;

const int ASCII_SIZE = 255;

struct TrieNode
{
    struct TrieNode* filhos[ASCII_SIZE];
    // fim_palavra é true se o nodo apontar pra última letra de uma palavra
    bool fim_palavra;
    int id;
};

struct jogador
{
    string nome;
    int id;
};

struct jogador getJogador(string nome, int id)
{
    struct jogador player;

    player.id = id;
    player.nome = nome;

    return player;
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

vector<struct jogador> collectWords(struct TrieNode* root, string prefix, vector<struct jogador>& names)
{
    if(root == nullptr)
        return names;

    if(root->fim_palavra)
    {
        names.push_back(getJogador(prefix, root->id));
    }

    for(int i = 0; i < ASCII_SIZE; i++)
    {
        if(root->filhos[i])
        {
            char ch = i;
            collectWords(root->filhos[i], (prefix + ch), names);
        }
    }

    return names;
}

vector<struct jogador> searchPrefix(struct TrieNode* root, string prefix, vector<struct jogador>& names)
{
    struct TrieNode* ptArvore = root;

    for(int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i];
        if(index < 0 || index >= ASCII_SIZE)
            return names;
        ptArvore = ptArvore->filhos[index];
    }

    names = collectWords(ptArvore, prefix, names);

    cout << names[0].nome << endl;
    return names;
}
