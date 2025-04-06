#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
using namespace std;

int main(){

    //Variaveis uteis 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int values[26];
    string letters;
    string value;
    int number;


    //cout<<"Quais os valores de cada letra?"<<endl;
    //Guarda o valor de cada letra do alfabeto:
    getline(cin, value);

    stringstream line(value);
    int loop = 0;

    while(line >> number){
        values[loop] = number;
        loop +=1;
    }
    
    //cout<<"Insira as letras"<<endl;
    cin>>letters;

    //Cria uma array para as letras e outra array para guardar os valores conforme o indice:
    string letter[letters.size()];
    int valuePerIndex[letters.size()];

    //Pega a string do input e joga em uma array:
    for(int i = 0; i < letters.size(); i++){
        letter[i] = letters[i];
        for(int j = 0; j < 26; j++){
            if(letters[i] == alphabet[j]){
                valuePerIndex[i] = values[j];
            }
        }
    }

    //cria uma array que guarda a soma:
    int sum[letters.size()];

    //Soma a valor das letras ate a letra atual, e guarda:
    for(int i = 0; i < letters.size(); i++){
        int sum_result = 0;
        int index = i +1;
        for(int j = 0; j < index; j++){
            sum_result += valuePerIndex[j];
        }
        sum[i] = sum_result;

    }

    //Deaclaracao da table:
    vector<pair<string, int>> table[letters.size()];

    //Preenche a table:
    for(int i = 0; i < letters.size(); i++){
        table[i].push_back({letter[i], sum[i]});
    }

    //Valor das substrings validas:
    int AB = 0;

    //Para atender os criterios de A e B;
    //Compara-se uma letra com a outra(it_1.first == it_2.first);
    //E checa se a diferenca entre it_1.second e it_2.second e valuePerIndex[i] == 0;
    //Se for, eh uma substring valida.
    for(int i = 0; i < letters.size(); i++){
        for(auto it_1 : table[i]){

            for(int j = 0; j < letters.size(); j++){
                for(auto it_2 : table[j]){

                    if(it_1.first == it_2.first && (it_1.second - it_2.second - valuePerIndex[i]) == 0){
                        AB += 1;
                    }

                }
            }

        }
    }

    //Print Final;
    cout<<AB<<endl;
    return 0;
}