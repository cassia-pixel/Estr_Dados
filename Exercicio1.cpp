#include <iostream>
#include <cstdlib>
#include <string>

using namespace std; 
using std::string;

class Data {
    public:
    int dia;
    int mes; 
    int ano;
};

class Funcionario {
    public:
        Data d1;
        string nome;
        string departamento; 
        double salario; 
        string entradaBanco;
        string rg;

        void recebeAumento (double x) {
            if(this->salario <= 1045) {
                this->salario = this->salario + 1045;
            }
        }

        double calculaGanhoAnual (){
            return this->salario = this->salario * 12;
        }

        Funcionario (string nome, string departamento, double salario, string entradaBanco, 
        string rg, int dia, int mes, int ano) {
            this->nome = nome;
            this->departamento = departamento;
            this->salario = salario;
            this->entradaBanco = entradaBanco;
            this->rg = rg; 

            this->d1.dia = dia;
            this->d1.mes = mes;
            this->d1.ano = ano;
        }
};

int main (void) {
   // double quantoGanha;

    Funcionario fun1("maria elina", "catando latinha", 123.980, "12/04/2020", "1234567", 22, 01, 1999);
    Funcionario fun2(fun1);

   // quantoGanha = fun1.calculaGanhoAnual();

   // fun1.recebeAumento(fun1.salario);

    cout << "o nome do funcionario é " << fun1.nome << endl;
    cout <<"o nome do funcionario é " <<fun2.nome << endl;

}