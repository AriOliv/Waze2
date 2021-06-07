#include <vector>
#include <iostream>
using namespace std;

/*
Esse módulo cria as funções auxiliares para o programa
o
*/

template<typename T>
void print(T words){
    cout << words << endl;
};

void print(vector<int> vetor){
    for(auto value: vetor){
         cout << value << endl;
    }
};

void print(int arr[], int length){ 
    for (int i = 0; i < length; i++)
    {
        cout << i << " = " <<arr[i]<< endl;
    }
};

