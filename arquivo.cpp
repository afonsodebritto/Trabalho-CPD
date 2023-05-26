#include <iostream>
#include <fstream>
#include <vector>

void le_arquivo();

int main()
{
    le_arquivo();
    return 0;
}

void le_arquivo()
{
    int numero;
    int tamanho;
    int i;
    // Abre o arquivo
    std::ifstream arquivo("entrada1.txt");
    // Inicializa um vetor de tamanho indeterminado
    std::vector<int> elementos;

    // Verifica se o arquivo foi aberto
    if(!arquivo.is_open())
    {
        std::cerr << "Arquivo nao foi aberto" << std::endl;
    }

    // Enquanto o a variável número estiver recebendo um inteiro do arquivo
    while(arquivo >> numero)
    {
        tamanho = numero;
        // Pega o primeiro elemento da linha e muda a capacidade do vetor usando este valor como tamanho
        elementos.resize(tamanho);
        std::cout<< "Inicio do vetor" << std::endl;
        // Enquanto o tamanho atual do vetor for diferente da sua capacidade
        i = 0;
        while(i < tamanho)
        {
            // Lê um número do arquivo e coloca no vetor
            arquivo >> numero;
            std::cout<< numero << " ";
            elementos.push_back(numero);
            i++;
        }
        // Chama o shellsort com o vetor
        std::cout << std::endl;
        std::cout << "Fim do vetor"  << std::endl;
    }

}
