//#include<bits/stdc++.h>
#include <rpcndr.h>
#include <stdio.h>
#include <stdlib.h>
#include "QuickSort.h"

//using namespace std;

typedef struct lista{
    boolean folha;
    int chaves[3];
    struct lista *pai;
    struct lista *links[4];
    /*lista(){
        for(int i=0;i<4;i++)
            folha=false;
    }*/
}lista;

void split(lista *no, int dado, int ordem);
lista *busca(lista *raiz, int dado);
void insereNoPai(lista *pai, int dado, int ordem);
void insere(lista *raiz, int dado, int ordem);
//void insertionSort(int v[], int length);

int main() {
    return 0;
}
/*
void insertionSort(int v[], int length){
    int temp, i, j;
    for(i = 1; i < length; i++){
        temp = v[i];

        for(j = i-1; j >=0 && v[j] > temp; j--){
            v[j+1] = v[j];
            v[j] = temp;
        }
    }
}*/

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
    int i, j, k = 0;
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
        quicksort(nova->chaves, ordem - 1);
        //linkar o pai com os dois nós (atual e nova)-
        if (atual->pai == NULL)
        {
            lista *novaRaiz;
            novaRaiz = (lista *)malloc(sizeof(lista));
            novaRaiz->chaves[0] = dado;
            novaRaiz->links[0] = atual;
            novaRaiz->links[1] = nova;
        }
        else
        {
            inserirNoPai(atual->pai, atual->chaves[medio + 1], ordem);
            while (atual->pai->links[k] != NULL)
            {
                k++;
            }
            atual->pai->links[k] = nova;
        }
    }else{
        atual->chaves[medio + 1] = dado;
        quickSort(atual->chaves, ordem - 1);
        //linkar o pai com os dois nós (atual e nova)
        if(atual->pai == NULL){
            lista *novaRaiz;
            novaRaiz = (lista *)malloc(sizeof(lista));
            novaRaiz->chaves[0] = dado;
            novaRaiz->links[0] = atual;
            novaRaiz->links[1] = nova;
        }else{
            inserirNoPai(atual->pai, atual->chaves[medio + 1], ordem);
            while (atual->pai->links[k] != NULL){
                k++;
            }
            atual->pai->links[k] = nova;
        }
    }
}

void insereNoPai(lista *pai, int dado, int ordem){
    int i = 0, cheio = 0;
    if(pai->chaves[ordem-2] != -1){
        cheio = 1;
    }
    if(cheio == 1){
        split(pai, dado, ordem);
    }else if(cheio == 0){
        int aux = 0;
        while(aux == 0){
            if(pai->chaves[i] != -1){
                i++;
            }else{
                aux = 1;
            }
        }
        pai->chaves[i] = dado;
        quickSort(pai->chaves, ordem - 1);
    }
}

lista *busca(lista *raiz, int dado){
    if (dado == raiz->chaves[0] || dado == raiz->chaves[1] || dado == raiz->chaves[2] || dado == raiz->chaves[3]){
        return raiz;
    }
    else if (dado < raiz->chaves[0]){
        busca(raiz->links[0], dado);
    }
    else if (dado > raiz->chaves[0] && dado < raiz->chaves[1]){
        busca(raiz->links[1], dado);
    }
    else if (dado > raiz->chaves[1] && dado < raiz->chaves[2]){
        busca(raiz->links[2], dado);
    }
    else if (dado > raiz->chaves[2] && dado < raiz->chaves[3]){
        busca(raiz->links[3], dado);
    }
    else if (dado > raiz->chaves[3]){
        busca(raiz->links[4], dado);
    }
}