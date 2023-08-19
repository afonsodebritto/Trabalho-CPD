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

void collectWords(struct TrieNode* root, string prefix)
{
    if(root == nullptr)
        return;

    if(root->fim_palavra)
    {
        cout << prefix << endl; 
    }

    for(int i = 0; i < ASCII_SIZE; i++)
    {
        if(root->filhos[i])
        {
            char ch = i;
            collectWords(root->filhos[i], (prefix + ch));
        }
    }
}

void searchPrefix(struct TrieNode* root, string prefix)
{
    struct TrieNode* ptArvore = root;

    for(int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i];
        if(index < 0 || index >= ASCII_SIZE)
            return;
        ptArvore = ptArvore->filhos[index];
    }

    collectWords(ptArvore, prefix);
}
