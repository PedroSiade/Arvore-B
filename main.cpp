#include<bits/stdc++.h>
#include <rpcndr.h>

using namespace std;

typedef struct lista{
    boolean folha;
    int chaves[4];
    struct lista *links[5];
    lista(){
        for(int i=0;i<4;i++)
            folha=false;
    }
}lista;

void split(lista *no, int ddado, int ordem);
void insertionSort(int v[], int length);

int main() {
    return 0;
}

void insertionSort(int v[], int length){
    int temp, i, j;
    for(i = 1; i < length; i++){
        temp = v[i];

        for(j = i-1; j >=0 && v[j] > temp; j--){
            v[j+1] = v[j];
            v[j] = temp;
        }
    }
}

void split(lista *no, int dado, int ordem){
    /*int aux[5];
    for(int i=0;i<6;i++){
        if(i!=5)
        aux[i]=v->dado[i];
        else
            aux[i]=di;
    }
    insertionSort(aux, 5);
    lista *p, *r;
    p = (lista *) malloc(sizeof(lista));*/
    
    int inicio = 0, final = (ordem - 2);
    int medio = (inicio + final)/2;
    int i, j;
    lista *nova, *atual;
    atual = no;
    nova = (lista *) malloc(sizeof(lista));
    for(i = 0, j = medio + 1; i <= medio, j <= ordem - 2; i++, j++){
        nova->chaves[i] = atual->chaves[j];
        atual->chaves[j] = -1;
        nova->chaves[j] = -1;
    }
    if(dado > atual->chaves[medio]){
        nova->chaves[i+1] = dado;
        quicksort(nova->chaves);
        //linkar o pai com os dois nós (atual e nova)
        inserir(nova->chaves[0]);
    }else{
        atual->chaves[medio + 1] = dado;
        quickSort(atual->chaves);
        //linkar o pai com os dois nós (atual e nova)
        inserir(atual->chaves[medio + 1]);
    }
}
