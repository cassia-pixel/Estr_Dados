#include <cstdio>
#include <cctype>
#include <cstring>

#define MIN 3
#define MAX 20


bool diminuiPalavra(char []);  /*Protótipo de função que transforma palavra em minúsculo
                                e verifica se ela é menor que 3 e maior que 20*/

/* Célula de uma lista encadeada de ocorrências, armazena um inteiro */ 
class Ocorrencia {
  friend class ListaO;

public:
  Ocorrencia(int linha); // Construtor padrão
  ~Ocorrencia();         // Destrutor padrão    

private:
  int linha;
  Ocorrencia *prox;
};


/* Lista encadeada de ocorrências, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaO {
public:
  ListaO();               // Construtor padrão
  ~ListaO();              // Destrutor padrão
  void insere(int linha); // Recebe um inteiro e insere na lista
  void escreve();         // Escreve os elementos da lista

private:
  Ocorrencia *inicio; // Início da lista
  Ocorrencia *fim;    // Fim da lista
};


/* Célula de uma lista encadeada de palavras, armazena uma cadeia de caracteres */
class Palavra {
  friend class ListaP;

public:
  Palavra(char p[]);      // Construtor padrão
  ~Palavra();             // Destrutor padrão
  void insere(int linha); // Insere uma ocorrência na lista de ocorrências
  void escreve();         // Escreve a palavra e suas ocorrências

private:
  char p[MAX];        // A palavra em si
  ListaO ocorrencias; // Lista de ocorrências
  Palavra *prox;      // Próxima Palavra na lista
};


/* Lista encadeada de palavras, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaP {
public:
  ListaP();                  // Construtor padrão
  ~ListaP();                 // Destrutor padrão
  Palavra *insere(char p[]); // Recebe uma palavra e insere na lista, devolvendo um ponteiro para o objeto inserido
  Palavra *busca(char p[]);  // Busca e devolve o objeto de uma palavra na lista
  void escreve();            // Escreve os elementos da lista

private:
  Palavra *inicio; // Início da lista
  Palavra *fim;    // Fim da lista
};


/* Tabela de dispersão que guarda um índice de palavras */
class TabelaDispersao {
public:
  TabelaDispersao();  // Construtor padrão
  ~TabelaDispersao(); // Destrutor padrão
  void escreve();     // Escreve a tabela (incluindo fator de carga)
  void novaOcorrencia(char p[], int linha); // Registra uma nova ocorrência de uma palavra
  
private:
  static const int TAMANHO = 47; // Tamanho da tabela
  ListaP tabela[TAMANHO];        // Listas da tabela
  float n_chaves_inseridas = 0;  //Nova variável que criei para contar o número de chaves inseridas na lista

  int valor(char p[]); // Valor da palavra p
  int h(int valor);     // Função de hash
};

int main(int argc, char *argv[]) {
  
  TabelaDispersao tab;  //Tabela hash
  FILE *arqEntrada;     
  int linha, i; //Variáveis pra contar linha e para andar nas posições do vetor palavra
  char palavra[MAX + 1], letra; //Vetor de caratceres que vai guardar uma palavra e char letra para leitura do arquivo

  arqEntrada = fopen(argv[1], "r");

  linha = 1;  //Começa lendo a linha 1
  i = 0;      //Começa na posição 0 do vetor 

  //Fazendo leitura de arquivo
  while(!feof(arqEntrada)){ 
    letra = fgetc(arqEntrada);   //Lendo letra por letra

    //Se for uma letra, será colocado no vetor
    if((letra >= 'A' && letra <= 'Z') || (letra >= 'a' && letra <= 'z') ) {
      palavra[i] = letra;         //Colocando as letras na string palavra
      i++;
    }
    else{ //Caso contrário, significa que a palavra já acabou
      palavra[i] = '\0'; //Colocando o caractere que indica final da palavra     

      if(diminuiPalavra(palavra) == true) {     //Verificando se a palavra tem entre 3 e 20 letras
        tab.novaOcorrencia(palavra, linha);     //Registrando nova ocorrência
      }

      //"Zerando" string
      for(int k = 0; k <  MAX; ++k) {
        palavra[k] = 0; 
      }
      i = 0;  //Reinicializando variável i

      if(letra == '\n') {         //Contando as linhas
        linha++;
      }
    }
    if(i == MAX) {    //Se a variável i atingir o limite 
      i = 0;          //Zera i
      for(int k = 0; k <  MAX + 1; ++k) {   //Zera string
        palavra[k] = 0; 
      }
    }
  }

  tab.escreve();  //Escrevendo a tabela

  fclose(arqEntrada); //Fechando arquivo

  return 0;

}

//Construtor de Ocorrencia
Ocorrencia::Ocorrencia(int l) {

  linha = l;     //Atribuição de linha
  prox = NULL;   //Colocando próximo como nulo
}

//Destrutor de Ocorrencia
Ocorrencia::~Ocorrencia() {

}

//Construtor de ListaO
ListaO::ListaO() {
  inicio = NULL;  //Colocando inicio e final como nulos
  fim = NULL;
}

//Destrutor ListaO
ListaO::~ListaO() {
  Ocorrencia *aux;  //Cria uma Ocorrencia auxiliar 

  for(aux = inicio; aux != NULL; aux = inicio) {  //Percorre a lista deletando cada elemento alocado
    inicio = inicio->prox;    //Atualiza o inicio para a próxima ocorrência
    delete aux;               //Deleta a ocorrência
  }  
}

//Função que escreve a lista de ocorrências
void ListaO::escreve() {
  Ocorrencia *aux; 

  for(aux = inicio; aux != NULL; aux = aux->prox) { //Percorre a lista com uma Ocorrencia auxiliar

    if(aux->prox == NULL) { //Se chegar no final da lista, imprime a linha e fecha o parênteses
      printf("%d", aux->linha);
    }
    else if(aux->prox != NULL) {  //Se ainda não for o final da lista, imprime a linha e continua a impressão
      printf("%d,", aux->linha);
    }
  }
}

//Insere uma Ocorrência na lista de ocorrências
void ListaO::insere(int linha) {

  if(inicio == NULL) {  //Se não houver nenhum elemento na lista
    Ocorrencia *novaOcorrencia = new Ocorrencia(linha);
    inicio = novaOcorrencia; 
    fim = novaOcorrencia;
  } 
  else{  //Se houver um elemento ou mais na lista
      if(fim->linha != linha) {   //Verifica se a linha a ser inserida não está na lista
        Ocorrencia *novaOcorrencia = new Ocorrencia(linha);
        fim->prox = novaOcorrencia;
        fim = novaOcorrencia;
      }
  }
}

//Construtor de palavra
Palavra::Palavra(char palavra[MAX]) {
  
  strcpy(p, palavra); //Copia palavra para p
  prox = NULL;        //Coloca o próximo como nulo 

}

//Destrutor de palavra
Palavra::~Palavra() {

}

//Função que irá inserir uma linha na lista de ocorrências
void Palavra::insere(int linha) {
  ocorrencias.insere(linha);
}

//Função que escreve uma palavra
void Palavra::escreve() {
  printf(" %s(", p);       //Escreve uma palavra e abre parênteses para imprimir as linhas
  ocorrencias.escreve();  //Chama função para escrever a lista de ocorrências
  printf(")");
}

//Construtor de ListaP
ListaP::ListaP() {
  inicio = NULL;  //Coloca inicio e fim como nulos 
  fim = NULL;
}

//Destrutor de ListaP
ListaP::~ListaP() {
  Palavra *aux; 

  for(aux = inicio; aux != NULL; aux=inicio) {  //Percorre a lista inteira com uma Palavra auxiliar  
    inicio = inicio->prox;  //Atualiza o início para a próxima palavra
    delete aux;   //Deleta cada elemento da lista 
  }
}

//Insere uma Palavra nova na lista
Palavra* ListaP::insere(char p[]) {

  Palavra *novaPalavra = new Palavra(p); //Cria uma nova palavra
  
  if(inicio == NULL) {       //Verifica se não tem nenhuma palavra na lista 
    inicio = novaPalavra;    //Caso não tenha, insere a palavra no inicio
    fim = novaPalavra;      //e atribui o novo final da lista
  }
  else {   //Se existir uma palavra ou mais na lista
    fim->prox = novaPalavra; 
    fim = novaPalavra;
  }
  
  return novaPalavra;
}

//Verifica se uma palavra já está inserida na lista
Palavra* ListaP::busca(char p[]) {
  Palavra *x;
  
  if(inicio == NULL) {  //Se a lista estiver vazia
    return NULL;
  }

  for(x = inicio; x != NULL; x = x->prox){    //Percorre a lista inteira
    if(strcmp(x->p, p) == 0) {                //Compara os elementos
      return x;
    }
  }

  return NULL;
}

//Chama a função escreve para cada palavra
void ListaP::escreve() {
  Palavra *aux; 

  for(aux = inicio; aux != NULL; aux = aux->prox) { //Percorre a lista chamando escreve para as palavras
    aux->escreve();
  }
}

//Construtor de TabelaDispersao
TabelaDispersao::TabelaDispersao() {

}

//Destrutor de TabelaDispersão
TabelaDispersao::~TabelaDispersao() {

}

//Escreve a tabela de dispersão
void TabelaDispersao::escreve() {
  for(int i = 0; i < TAMANHO; i++) {    
    printf("%d:", i);      //Imprime as 46 posições da tabela
    tabela[i].escreve();    //Chama função para imprimir as listas em cada posição da tabela
    printf("\n");
  }
  printf("Fator de carga: %f\n", n_chaves_inseridas / TAMANHO); //Imprime fator de carga da tabela
}

//Recebe uma nova ocorrência de linha e palavra e as coloca na tabela 
void TabelaDispersao::novaOcorrencia(char p[MAX], int linha) {

  int pos;  //Posição 

  pos = h(valor(p));    //Calcula posição da palavra na tabela  
  Palavra *palavra = tabela[pos].busca(p);    //Verifica se a palavra já está na tabela 
  
  if(palavra == NULL) { //Se a palavra não existir na lista 
    palavra = tabela[pos].insere(p);  //Insere a palavra na lista
    n_chaves_inseridas++;  //Incrementa o número de chaves inseridas
  }
  palavra->insere(linha); //Insere a nova linha na tabela 
}

//Função que calcula o valor de uma palavra de acordo com a tabela ASCII
int TabelaDispersao::valor(char p[MAX]) {
  int valor = 0;

  for(int i = 0; p[i] != '\0'; ++i) {
    valor += p[i];    //Soma o valor de cada letra da palavra
  }

  return valor;
}

//Função que calcula a posição de uma letra na palavra de acorodo com seu valor
int TabelaDispersao::h(int valor) {  
    return valor % 47;  
}

//Função que transforma letras maiúsculas em minúsculas e verifica seu tamanho
bool diminuiPalavra(char *palavra) {     
  
  if(strlen(palavra) >= MIN && strlen(palavra) <= MAX) {  //Verifica se a palavra é maior que 3 e menor que 20  
    
    for(int i = 0; palavra[i] != '\0'; ++i) {       
    //Se a palavra estiver dentro do alfabeto, seja ela minúscula ou maiúscula 
    palavra[i] = tolower(palavra[i]);                                 
    }
    return true;  //Se a palavra for menor que 3 e maior que 20
  }   
  return false;   //Se a palavra for menor que 3 ou maior que 20
}