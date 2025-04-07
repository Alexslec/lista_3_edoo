#include <iostream>
#include <utility>
#include <fstream>
#include <list>
#include <cmath>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

//IMPORTANTE: 4 bases nitrogenedas para 6 posicoes, totalizam 4096 possibilidades.
//A funcao de espalhamento se baseia nessas 4096 possibilidades, impedindo colisao!

class HashTable{
	private:
		//Define a hash table como vetor que recebe um par: string e inteiro:
		static const int possibilities = 4096;
		vector<pair<string, int>>table[possibilities];
	public:
		//Insere a string e suas repeticoes
		void insert(string codon, int apparitions){
			//Encontra a posicao a ser inserida
			int position = hashfunction(codon);
			//Checa se ja esta na hash
			bool answer = check(codon);
			if(answer == true){
				//Adiciona +1 a repeticao:
				add(codon);
			}else{
				//Insere na HashTable:
				table[position].push_back({codon, apparitions});
			}
		}

		//Encontra a posicao do codon:
		int hashfunction(string codon){
			//Primeiro: Associe um valor a cada letra:
			//A(0);T(1);C(2);G(3);
			//Depois: multiplique cada valor por 4 elevado ao indice invertido:
			//AAAAAA -> 000000 -> 0*4^5 + 0*4^4 + ... 0*4^0;
			//Ou seja, faz uso do valor na BASE 4!
			char arraySix[6];
			string letter;
			int value;
			
			int key = 0;
			
			strcpy(arraySix, codon.c_str());
			
			int loop = 5;
			
			for(int i = 0; i < 6; i++){
				
				letter = arraySix[i];
				
				//Condicionais
				if(letter == "A"){
					value = 0;	
				}
				else if( letter == "T"){
					value = 1;
				}
				else if(letter == "C"){
					value = 2;
				}
				else{
					value = 3;
				}
				
				key += value*(pow(4, loop));
				loop -= 1;
				
			}
			return key;
		}
	//Checa se o codon se repete ou nao:
	bool check(string codon){
		bool ending = false;
		for(int i = 0; i < 4096; i++){
			for(auto it : table[i]){
				if(it.first == codon){
					ending = true;
					break;
				}
			}
		}
		if(ending == false){
			return false;
		}else{
			return true;
		}
	}

	//Adiciona a string e o seu numero de repeticoes na table:
	int add(string codon){
		for(int i = 0; i < 4096; i++){
			for(auto& it : table[i]){
				if(it.first == codon){
					it.second += 1;
					break;
				}
			}
		}
		return 0;
	}

	//Foi preciso especificar esse operador porque vivia dando erro
	vector<pair<string, int>>& operator[](int index){
		return table[index];
	}
};
		
int main(){
	
	//Cria a Hastable:
	HashTable DNA;
	//Variavel e Arrays uteis:
	string line;
	char lineArray[60];
	char arraySix[6];
	
	//Variavel para abrir e pegar o arquivo input:
	ifstream input;
	input.open("sequences.fasta.txt");
	
	int loop = 0;
	
	//Cria um lopp e percorre linha, por linha:
	while(getline(input, line)){
		
		strcpy(lineArray, line.c_str());
		
		for(int i = 0; i < 60; i++){
			arraySix[loop] = lineArray[i];
			loop += 1;
			
			if(loop == 6){
				string codon(arraySix, 6);
				//Insere na Table: string e numero de repeticoes, ateh o momento eh 1:
				DNA.insert(codon, 1);
				loop = 0;
			}	
		}
		
	}

	//Variavel para preencher o arquivo do output:
	ofstream result;
	result.open("result.txt");

	//Preenche o arquivo em duas colunas: o codon de 6 bases nitrogenadas e o quanto se repete:
	for(int i = 0; i < 4096; i++){
		for(auto it : DNA[i]){
			result<<left<<setw(7)<<it.first<<setw(7)<<it.second<<"\n";
		}
	}


	return 0;
}

