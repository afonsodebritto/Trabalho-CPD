#include <iostream>
#include <string>

struct jogador {
    // sofifa_id
    int id;
    // name
    std::string nome;
    // player_positions
    std::string posicoes;
};

struct nodo {
    struct jogador player;
    struct nodo* prox;
};

struct nodo* insere(struct nodo* ptLista, struct jogador player)
{
    struct nodo* ptAux;
    ptAux->player = player;
    ptAux->prox = NULL;
    if(ptLista != NULL)
    {
        struct nodo* ptLista2;
        ptLista2 = ptLista;
        while(ptLista2 != NULL)
        {
            ptLista2 = ptLista2->prox;
        }
        ptLista2 = ptAux;
        return ptLista;
    }
    ptLista = ptAux;
    return ptLista;
}

// Função pra ver se o número é primo
bool is_prime(unsigned int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

// Função pra calcular o próximo primo
unsigned int next_prime(unsigned int n) {
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

int hashing(int x, int n)
{
    int total_chaves = n;
    total_chaves = total_chaves * 1.2;
    // Acha o prox primo maior ou igual ao total de chaves
    // acrescido de 20%
    int n12 = next_prime(total_chaves);
    int posicao;
    posicao = x % n12;
    return posicao;
}

int main()
{
    static struct nodo* hash_table[1000] = {NULL};
    struct jogador jogador_fifa;
    std::cin >>
}










