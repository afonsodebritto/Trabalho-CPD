#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std::chrono;

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
    // Abre os arquivos
    std::ifstream input("entrada1.txt");
    std::ofstream output("saida2.txt");
    // Inicializa um vetor de tamanho indeterminado
    std::vector<int> elementos;
    // Cria uma string para guardar a sequencia utilizada
    std::string sequencia;

    // Verifica se os arquivos foram abertos
    if(!input.is_open())
    {
        std::cerr << "Arquivo nao foi aberto" << std::endl;
    }
    if(!output.is_open())
    {
        std::cerr << "Arquivo de saida nao foi aberto" << std::endl;
    }

    // Enquanto o a variável número estiver recebendo um inteiro do arquivo
    while(input >> numero)
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
            input >> numero;
            std::cout<< numero << " ";
            elementos.push_back(numero);
            i++;
        }

        // Pega o tempo de início da execução do shellsort
        auto comeco = high_resolution_clock::now();
        // Chama o shellsort com o vetor
        // Pega o tempo depois que a função foi executada
        auto fim = high_resolution_clock::now();
        // Subtrai um do outro para achar a duração em microssgundos
        auto duracao = duration_cast<seconds>(fim - comeco);
        output << sequencia << "," << tamanho << ","  << duracao.count() << "Processador" << std::endl;
    }

    input.close();
    output.close();

}
