#include<bits/stdc++.h>
#include<stdbool.h>
using namespace std;

typedef struct lista{
    bool folha;
    int dado[4]{};
    int countD;
    struct lista *filho[5]{};

    lista(){
        folha=true;
        countD=0;
        for(int k=0;k<5;k++){
            this->dado[k]=-1;
        }
    }

}lista;

void split(lista *raiz, lista *noPai, lista *no, int dado_inserido, int filho);
void splitRaiz(lista **no, int dado_inserido);
void insertionSort(int v[], int length);
void insercao(lista **raiz, int di);
lista *busca(lista *raiz, int db);
lista *buscaPai(lista *raiz, lista *no, int di, int *filho);
lista *buscaInsercao(lista *raiz, int db);
void remocaoFolha(lista *raiz, int dado);
void remocaoIndice(int dado);
void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado);
void emprestimoDir(lista *irmao, lista *pai, lista *alvo, int dado);
void combinacao(lista *filhos);


int main() {
    lista  *raiz=NULL;
    insercao(&raiz, 20);
    insercao(&raiz, 40);
    insercao(&raiz, 60);
    insercao(&raiz, 80);
    insercao(&raiz, 70);
    insercao(&raiz, 10);
    insercao(&raiz, 30);
    insercao(&raiz, 15);


    return 0;
}

void remocaoFolha(lista *raiz, int dado){
    lista *noAlvo = NULL, *noPai = NULL, *aux = NULL;
    int encontrado = 0, i = 0;
    noAlvo = busca(raiz, dado);
    noPai = raiz;
    while(encontrado != 1){
        aux = NULL;
        i = 0;
        while(aux != noAlvo && i <= 4){
            aux = noPai->filho[i];
            i++;
        }
        if(aux == noAlvo){
            encontrado = 1;
        }else{
            if(dado < noPai->dado[0]){
                noPai = noPai->filho[0];
            }else if(dado > noPai->dado[0] && dado < noPai->dado[1]){
                noPai = noPai->filho[1];
            }else if(dado > noPai->dado[1] && dado < noPai->dado[2]){
                noPai = noPai->filho[2];
            }else if(dado > noPai->dado[2] && dado < noPai->dado[3]){
                noPai = noPai->filho[3];
            }else if (dado > noPai->dado[3]){
                noPai = noPai->filho[4];
            }
        }
    }

    int j = 0;
    while (noAlvo->dado[j] != dado)
    {
        j++;
    }
    if(noAlvo->countD > 2){
        noAlvo->dado[j] = -1;
        insertionSort(noAlvo->dado, 4);
    }else if(noAlvo->countD == 2){
        if(noPai->filho[i-1]->countD > 2 && noPai->filho[i+1]->countD == 2){
            emprestimoEsq(noPai->filho[i-1], noPai, noAlvo, dado);
            noAlvo->dado[j] = -1;
            insertionSort(noAlvo->dado, 4);
        }else if (noPai->filho[i - 1]->countD == 2 && noPai->filho[i + 1]->countD > 2){
            emprestimoDir(noPai->filho[i+1], noPai, noAlvo, dado);
            noAlvo->dado[j] = -1;
            insertionSort(noAlvo->dado, 4);
        }else if (noPai->filho[i - 1]->countD > 2 && noPai->filho[i + 1]->countD > 2){
            emprestimoEsq(noPai->filho[i - 1], noPai, noAlvo, dado);
            noAlvo->dado[j] = -1;
            insertionSort(noAlvo->dado, 4);
        }
    }
}

void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado){
    int i = 0, j = 0;
    while(pai->dado[i] < dado){
        i++;
    }
    alvo->dado[3] = pai->dado[i-1];
    while(pai->filho[i-1]->dado[j] != -1){
        j++;
    }
    pai->dado[i - 1] = pai->filho[i - 1]->dado[j - 1];
    pai->filho[i - 1]->dado[j - 1] = -1;
}

void emprestimoDir(lista *irmao, lista *pai, lista *alvo, int dado)
{
    int i = 0;
    while (pai->dado[i] < dado)
    {
        i++;
    }
    alvo->dado[3] = pai->dado[i + 1];
    pai->dado[i + 1] = pai->filho[i + 1]->dado[0];
    pai->filho[i + 1]->dado[0] = -1;
    insertionSort(pai->filho[i + 1]->dado, 4);
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

void split(lista *raiz, lista *noPai, lista *no, int dado_inserido, int filho){
    int aux[5],i,k, aux1=0, aux2, qtdFilho;
    bool operador= false;
    lista *p, *q;
    for(i=0;i<6;i++){//vetor auxiliar para ordenar o dado a fim de fazer o split
        if(i!=5)
            aux[i]=no->dado[i];
        else
            aux[i]=dado_inserido;
    }
    insertionSort(aux, 5);
    p = (lista *) malloc(sizeof(lista));// criação do nó resultado do split
    p = new lista();
    qtdFilho=(noPai->countD+1);
    if(qtdFilho==filho)
        noPai->filho[1]=p;
    else{
        aux2=4;//posicao final do vetor
        while(aux2!=filho) {
            aux2--;
            swap(noPai->filho[aux2 - 1], noPai->filho[aux2]);
        }
        noPai->filho[filho + 1]=p;
    }
    for(k=0; k<5; k++){
        if((noPai->dado[k]<0)&&(operador==false)){
            noPai->dado[k]=aux[2];
            operador=true;
        }
        if(k>1)
            no->dado[k]=-1;
        if(k>2){
            p->dado[aux1] = aux[k];
            aux1++;
        }
        if((k==4)&&(noPai->dado[k]==-1)){//significa que precisa de outro split
            q=buscaPai(raiz, noPai, dado_inserido, &filho);
            if(q!=raiz){
                split(raiz, q, noPai, dado_inserido, filho);
            }
            else{
                splitRaiz(&q, dado_inserido);
            }
        }
    }
}

void splitRaiz(lista **no, int dado_inserido) {
    int aux[5], i, k, aux1 = 0;
    lista *p, *q;
    for (i = 0; i < 5; i++) {//vetor auxiliar para ordenar o dado a fim de fazer o split
        if (i != 4)
            aux[i] = (*no)->dado[i];
        else
            aux[i] = dado_inserido;
    }
    insertionSort(aux, 5);
    p = (lista *) malloc(sizeof(lista));// criação do nó resultado do split
    q = (lista *) malloc(sizeof(lista));// criação do nó resultado do split
    q = new lista();
    p = new lista();
    q->countD=2;
    p->countD=1;
    p->dado[0] = aux[2];
    p->filho[0] = *no;
    p->filho[1] = q;
    p->folha= false;
    for (k = 0; k < 5; k++) {
        if (k > 1)
            (*no)->dado[k] = -1;
        if (k > 2) {
            q->dado[aux1] = aux[k];
            aux1++;
        }
    }
    if((*no)->filho[0] != nullptr) {
        for (int auxiliar = 0; auxiliar < 3; auxiliar++) {
            q->filho[auxiliar] = (*no)->filho[auxiliar + 3];
        }
    }
    (*no)=p;
    (*no)->filho[0]->countD=2;
}

void insercao(lista **raiz, int di){
    lista *p,*q;
    int filho, aux[4], k=1;
    bool operador=false;
    if(*raiz== nullptr){
        p = (lista *) malloc(sizeof(lista));
        p=new lista();
        p->dado[0]=di;
        p->countD=1;
        (*raiz)=p;
    }
    else{
        p=buscaInsercao(*raiz, di);
        if(p->countD<4){
            while((k<4)&&(operador==false)) {
                if(p->dado[k]==-1) {
                    p->dado[k] = di;
                    operador = true;
                }
                k++;
            }
            if(k==2) {
                insertionSort(p->dado, 2);
            }
            else if(k==3){
                insertionSort(p->dado, 3);
            }
            else
                insertionSort(p->dado, 4);
            p->countD++;
        }
        else if(p!=(*raiz)){
            q=buscaPai(*raiz, p, di, &filho);
            split(*raiz, q, p, di, filho);
        }
        else if(p==(*raiz)){
            splitRaiz(&(*raiz), di);
        }
    }
    return;
}

lista *busca(lista *raiz, int db){
    int i;
    lista *p=raiz;
    while(p!= nullptr) {
        i=-1;
        while ((db <= p->dado[i]) && (i < 5)) {
            i++;
        }
        if(p->dado[i]==db){
            return p;
        }
        else if(p->filho[i+1]== nullptr) {
            return nullptr;
        }
        else
            p=p->filho[i+1];
    }
    return nullptr;
}

lista *buscaInsercao(lista *raiz, int db){
    int i;
    lista *p=raiz;
    while(p->folha== false) {
        i=-1;
        while ((db <= p->dado[i]) && (i < 5)) {
            i++;
        }
            p=p->filho[i+1];
    }
    return p;
}

lista *buscaPai(lista *raiz, lista *no, int di, int *filho) {
    int i=-1;
    lista *p = raiz;
    while (p->filho[i + 1] != no) {
        i = -1;
        while ((di <= p->dado[i]) && (i < 5)) {
            i++;
        }
        if(p->filho[i+1]==no){
            *filho=i+1;
            return p;
        }
        else
            p=p->filho[i+1];
    }
}
