#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

#define MIN 3  //minimo de letras em uma palavra
#define MAX 20 //maximo de letras em uma palavra 
//inicializacao de classes 

class Lista {
public:
    Lista(char palavra[MAX]);    //construtor
    ~Lista();   //destrutor
    char chave[MAX];
    int *proximoPalavra;
    int *inicioOcorrencia;
};

Lista (char palavra[MAX]) {  //construtor da lista de palavras

}
~Lista() ;  //destrutor

class Ocorrencias {
public:    
    int numeroOcorrencia;
    int *proximo;
};

class Tabela {
public:
    Tabela ();
    ~Tabela ();
private:
    static const int tamanho = 47;
   // Tabela tabela.Tabela(47);
};

Tabela () {
    Tabela *tabela = new Tabela[tamanho];
   // tabela[posicao] = lista->chave;  usar isso pra inserir. Obs: não esquecer de verificar se já não tem alguma palavra na lista
}

void inserir(char palavra[MAX]) {
    int valor; 
    int posicao; 

    valor = calculaValor(palavra);
    posicao = calculaPosicao(valor);

    
}

int calculaPosicao(int valor) {     //funcao h(p) com outro nome
    int posicao = 0;
    posicao = valor % 47;   //posicao em que a palavra vai ficar

    return posicao;
}   

int calculaValor(char palavra[MAX]) {   //calcula o valor da palavra na tabela ASCII
    int valor = 0;

    for(int i = 0; palavra[i] != '\0'; ++i) {
        valor += atoi(palavra[i]);  //perguntar para o professor se pode usar a funcao atoi da biblioteca cstdlib
    }

    return valor;
}

int main(int argc, char *argv[]) {

    Tabela *tabela();
    char comparar[MAX]; //string que vai guardar uma palavra do arquivo de cada vez     
    FILE arqEntrada;

    arqEntrada = argv[0];   //pegando o arquivo de entrada 
    fscanf(arq_entrada[i], "%20[A-Za-zÀ-ú]%*[^A-Za-zÀ-ú]", comparar);   //ver como se faz a leitura em arquivo 
    tolower(comparar);  //colocando as letras em minusculo
    
}