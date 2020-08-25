#include <cstdio>
#include <climits>
#include <string>
#include <algorithm>

using std::string;

class Heap
{
public:
  Heap(); //construtor padrão
  Heap(const int n, const int dados[]); //construtor 
  Heap(const Heap& outro);  //construtor de cópia padrão
  ~Heap();  //destrutor
  Heap& operator=(const Heap& outro); //operador de atribuição: ele libera a memória do heap atual e copia novos valorescopia(outro)
  void escreve_niveis();  
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);   //insere um novo numero  
  int consulta_maxima();  //consulta o numero de maior valor
  int extrai_maxima();    //extrai o numero de maior valor 
  void altera_prioridade(int i, int p);   
  
private:
  int *S;   //vetor heap
  int n;    //numero de elementos inseridos
  int capacidade; //capacidade do vetor 
  static const int TAMANHO_INICIAL = 4;   //tamanho inicial do vetor
  int pai(int i);   
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


int main(void)
{
  Heap h; // construtor Heap()
  
  for (int i = 1; i <= 10; i++) 
    h.insere(i);   //insere um elemento de 1 até 10 na heap
  printf("h:\n");
  h.escreve();      //escreve heap


  h.extrai_maxima();  //extrai o numero maximo da heap
  h.altera_prioridade(0, -3);   //altera a prioridade entre 0 e -3


  printf("h:\n");
  h.escreve();      //escreve heap  

  int v[] = {1,2,3,4,5};    //vetor com 5 elementos
  
  //erro aqui
  Heap h2(5, v); // construtor Heap(int n, int dados[])  
  h2.insere(15);  //insere o numero 15
  printf("h2:\n");
  h2.escreve();
    
  Heap h3(h2); // construtor de cópia padrão
  h2.insere(30); //insere o numero 30 
  printf("h3:\n");
  h3.escreve();

  Heap h4 = h2; // construtor de cópia padrão
  h2.insere(40);  //insere o numero 40 
  printf("h4:\n");
  h4.escreve();
  
  h = h2; // operador de atribuição, sem constructor ou constructor de cópia
  h.insere(100);  //insere o numero 100
  printf("h2:\n");
  h2.escreve(); //depois do operator 
  printf("h:\n");
  h.escreve();

  h = Heap(5, v); // construtor Heap(int n, int dados[]), seguido de atribuição (de cópia, não transferência (move))
  printf("h:\n");
  h.escreve();

  h.extrai_maxima();
  h.altera_prioridade(0, -2);
  printf("h:\n");
  h.escreve();
    
  return 0;
}

//Construtor padrão
Heap::Heap() {
  capacidade = TAMANHO_INICIAL;   //Define capacidade inicial
  n = 0;    //Número de elementos inseridos é zero
  S = new int[capacidade];  //Alocando espaço na memória
}

//Construtor 
Heap::Heap(const int n, const int dados[]) {    

  this->n = 0;  //Número de elementos inseridos é zero
  capacidade = TAMANHO_INICIAL; //Capacidade inicial

  if(n > capacidade) 
    capacidade = capacidade * 2;  //Dobra capacidade do vetor

  S = new int[capacidade];    //Aloca espaço na memória

  for(int i = 0; i < n; ++i) { 
    insere(dados[i]);   //Começa a inserir os elementos
  }
}

//Construtor de cópia
Heap::Heap(const Heap& outro) {

  capacidade = outro.capacidade;  //Copia a capacidade do outro vetor
  S = new int[capacidade];        //Aloca espaço na memória
  n = outro.n;                    //Copia número de elementos inseridos no outro vetor

  std::copy(&outro.S[0], &outro.S[n], &S[0]);   //Copia os elementos para o novo vetor
}

//Operador de atribuição
Heap& Heap::operator=(const Heap& outro) {

  delete S; //Apaga o antigo vetor

  if(this == &outro)  //Verifica se não está copiando o mesmo heap
    return *this;
  
  S = new int[outro.capacidade];    //Aloca novamente um espaço na memória
  n = outro.n;                      //Copia o número de elementos inseridos 
  capacidade = outro.capacidade;    //Define nova capacidade

  std::copy(&outro.S[0], &outro.S[n], &S[0]); //Copia o novo vetor

  return *this;   //Retorna o vetor "novo"
}

//Destrutor
Heap::~Heap() {

}

//Imprime elementos
void Heap::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(int i = 0; i < n; ++i) {  //Mudei auto const &elemento: S 

    printf("%d ", S[i]);  //Imprime elementos
    if (++escritos == fim_nivel) {  
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

//Imprime os "traços"
void Heap::escreve(const string& prefixo, int i) {    //Antes era prefixo = "" e i = 0;
  if (i < n) {  //Onde era capacidade coloquei n porque estava imprimindo lixo 
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < n - 1;
    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" ); 

    printf("%d\n", S[i]);
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

//Insere elementos
void Heap::insere(int p) {
  
  if(n >= capacidade) { //Verifica se o número de elementos é maior que a capacidade
    
    int v[capacidade];  //Cria um vetor para copiar os elementos de S
    
    for(int k = 0; k < capacidade; k++) 
      v[k] = S[k];  //Copia os elementos de S

    delete S; //Deleta S
    S = new int[capacidade * 2]; //Aloca S com o dobro da capacidade

    for(int j = 0; j < capacidade; j++) {
      S[j] = v[j];    //Copia os elementos anteriores do antigo S para o novo 
    }
    capacidade = capacidade * 2;  //Dobra a capacidade
  }

  S[n] = p;   //Insere o novo elemento
  n = n + 1;  //Aumenta o número de elementos inseridos
  sobe(n - 1);//Sobe o novo elemento se ele for maior que o pai 
}

//Retorna o maior número da heap
int Heap::consulta_maxima() {
  return S[0];
}

//Extrai o maior número da heap
int Heap::extrai_maxima() {
  int maior;

  if(n > 0) {     //Verifica se há algum elemento inserido
    maior = S[0]; //"Pega" o maior número
    S[0] = S[n - 1];  //Coloca o último elemento da heap na primeira posição
    n = n - 1;        //Diminui o número de elementos inseridos
    desce(0);         //Desce o elemento na primeira posição
  }
  else 
    return INT_MIN;
}

//Altera a prioridade de um número S[i] por p
void Heap::altera_prioridade(int i, int p) {
  if(p < S[i]) {  //Verifica se o elemento é maior que o S[i]
    printf("ERRO: nova prioridade é menor que da célula\n");  //Se não for, imprime uma mensagem de erro
  }
  else {
    S[i] = p; //Coloca o novo elemento na posição
    sobe(i);  //Sobe se esse elemento for maior que o pai
  }
}

//Retorna o pai de um elemento 
int Heap::pai(int i) {
  return (i - 1) / 2;
}

//Retorna o filho esquerdo
int Heap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

//Retorna o filho direito
int Heap::direito(int i) {
  return 2 * (i + 1);
}

//Troca S[i] e S[j] de posições
void Heap::troca(int i, int j) {
  int aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

//Desce um elemento
void Heap::desce(int i) { 
  int esq, dir, maior; 
  
  esq = esquerdo(i);
  dir = direito(i); 

  if(esq < n && S[esq] > S[i]){ //Verifica se o filho esquerdo é maior que o pai
    maior = esq;
  }
  else {
    maior = i;  //Caso o pai ainda seja maior que o filho esquerdo
  }
  if(dir < n && S[dir] > S[maior]) {   //Verifica se o filho direito é o maior
    maior = dir;
  }
  if(maior != i) {   //Se o maior não for o pai
    troca(i, maior); //Troca os elementos
    desce(maior);    //Desce o elemento que ficou no índice de maior
  }
}

//Sobe um elemento
void Heap::sobe(int i) {
  
  while(S[pai(i)] < S[i]) { //Enquanto o pai for maior que o filho
    troca(i, pai(i));       //Troca os elementos de posição
    i = pai(i);             //i recebe o índice do pai
  } 
}
