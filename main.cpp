#include<bits/stdc++.h>
#include <rpcndr.h>

using namespace std;

typedef struct lista{
    boolean folha;
    int dado[4];
    struct lista *f[5];
    lista(){
        for(int i=0;i<4;i++)
            folha=false;
    }
}lista;

void split(lista v, int di);
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

void split(lista *v, int di){
    int aux[5];
    for(int i=0;i<6;i++){
        if(i!=5)
        aux[i]=v->dado[i];
        else
            aux[i]=di;
    }
    insertionSort(aux, 5);
    lista *p, *r;
    p = (lista *) malloc(sizeof(lista));
    r= (lista *) malloc(sizeof(lista));
    p->dado[2]=aux[2];
    if(p->f[0]==NULL) {
        p->f[0] = v;
        p->f[1] = r;
    }
    else if((p->f[0]!=NULL)&&(p->f[1]==NULL)){
        p->f[1] = v;
        p->f[2] = r;
    }
    else if((p->f[0]!=NULL)&&(p->f[1]!=NULL)&&(p->f[2]!=NULL)){
        p->f[2] = v;
        p->f[3] = r;
    }
    else if((p->f[0]!=NULL)&&(p->f[1]!=NULL)&&(p->f[2]!=NULL)&&(p->f[3]=NULL)){
        p->f[3] = v;
        p->f[4] = r;
    }
    else{
        p->f[4] = v;
        p->f[5] = r;
    }
}
