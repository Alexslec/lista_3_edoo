#include <iostream>
#include <stack>
#include <string>
using namespace std;

//Funcao Main
int main(){
	
	//Declaracao de variaveis e pilhas
	int cases;
	
	//cout<<"Quantos tests cases?"<<endl;
	cin>>cases;
	
	//Array para armazenar os valores recebidos
	int numbers[cases];
	for(int i=0; i < cases; i++){
		cin>> numbers[i];
	};
	
	//Pilha (array) para empilhar os valores;
	int pilha[cases];
	//Pilha(array) para empilhar os valores de "pilha" em reverso;
	string pilhaAuxiliar[cases];
	//Indice da array, para ajudar a simular a pilha, com a ordem reversa;
	int position = (cases - 1);
	for(int i = 0; i < cases; i++){
		pilha[position] = numbers[i];
		position -= 1;
	}
	
	//Algoritmo para o stackulator 3000:
	//Toda vez que um + aparece, isso gera um debito de 1 para o valor abaixo na pilha "pagar"
	int debt = 0;
	//Posicao
	position = (cases - 1);
	//String para guardar os resultados
	string Output = "1";
	//Loop que implementa o stackulator 3000
	for(int i = 0; i < cases; i++){
		
		int element = pilha[i];
		int increment = debt;

		int countLoops = 0;
		while((element - 1) > increment){
			countLoops += 1;
			increment += 1;
			debt -= 1;
			Output.append("1+");
		}
		
		//Insere o "d"
		if(pilha[i + 1] == 1 && element == 1 && debt == 0){
			Output = "d";
		}
		//Insere na pilha o valor, para printar depois
		pilhaAuxiliar[position] = Output;
		position -= 1;
		Output = "1";
	}
	
	//Prints finais
	for(int i = 0; i < cases ; i++){
		string x = pilhaAuxiliar[i];
		cout<<x;
	}
	
	
	return 0;
}
