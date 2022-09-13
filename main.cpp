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

void split(lista *raiz, lista *no, int dado_inserido);
void splitRaiz(lista **no, int dado_inserido);
void insertionSort(int v[], int length);
void insercao(lista **raiz, int di);
lista *busca(lista *raiz, int db, int insercao);
void remocaoFolha(lista *raiz, int dado);
void remocaoIndice(int dado);
void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado);
void emprestimoDir(lista *irmao, lista *pai, lista *alvo, int dado);
void combinacao(lista *irmao, lista *pai, lista *alvo, int dado);

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
            noAlvo->dado[j] = -1;
            emprestimoDir(noPai->filho[i+1], noPai, noAlvo, dado);
            insertionSort(noAlvo->dado, 4);
        }else if (noPai->filho[i - 1]->countD > 2 && noPai->filho[i + 1]->countD > 2){
            noAlvo->dado[j] = -1;
            emprestimoEsq(noPai->filho[i - 1], noPai, noAlvo, dado);
            insertionSort(noAlvo->dado, 4);
        }else if (noPai->filho[i - 1]->countD == 2 && noPai->filho[i + 1]->countD == 2){
            noAlvo->dado[j] = -1;
            combinacao(noPai->filho[i - 1], noPai, noAlvo, dado);
        }
    }
}

void combinacao(lista *irmao, lista *pai, lista *alvo, int dado){
    int i = 0, j = 0;
    while (pai->dado[i] < dado){
        i++;
    }
    alvo->dado[3] = pai->dado[i - 1];
    pai->dado[i - 1] = -1;
    insertionSort(alvo->dado, 4);
    pai->filho[i-1]->dado[2] = alvo->dado[2];
    pai->filho[i-1]->dado[3] = alvo->dado[3];
    do{
        pai->filho[i] = NULL;
        pai->filho[i] = pai->filho[i+1];
        i++;
    }while(i != 4);
    insertionSort(pai->dado, 4);
}

void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado)
{
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

void split(lista *raiz, lista *no, int dado_inserido){
    int aux[5],i,k, aux1=0, aux2=3, qtdFilho, aux3, w, filho;
    bool operador= false;
    lista *p, *(Pai), *auxBusca;
    for(i=0;i<5;i++){//vetor auxiliar para ordenar o dado a fim de fazer o split
        if(i!=4)
            aux[i]=no->dado[i];
        else
            aux[i]=dado_inserido;
    }
    insertionSort(aux, 5);
    p = (lista *) malloc(sizeof(lista));// criação do nó resultado do split
    p = new lista();
    p->pai=no->pai;
    Pai=no->pai;
    qtdFilho=(Pai->countD+1);
    w=0;
    while(aux3!=1){
        if(Pai->filho[w]==no){
            filho=w;
            aux3=1;
        }
        else
            w++;
    }
    if(qtdFilho==filho)
        Pai->filho[filho+1]=p;
    else{
        aux2=4;//posicao final do vetor
        Pai->filho[aux2]=p;
        while(aux2!=filho+1) {//abrir espaco no vetor para alocar o filho
            if(Pai->filho[aux2-1]!= nullptr){
            swap(Pai->filho[aux2 - 1], Pai->filho[aux2]);
            }
            else{
                Pai->filho[aux2 - 1]=Pai->filho[aux2];
                Pai->filho[aux2]= nullptr;
            }
            aux2--;
        }
    }
    for(k=0; k<5; k++){
        if((Pai->dado[k]<0)&&(operador==false)){
            Pai->dado[k]=aux[2];
            insertionSort(Pai->dado, k+1);
            operador=true;
        }
        if(k<2){
            no->dado[k]=aux[k];
        }
        if(k>1)
            no->dado[k]=-1;
        if(k>2){
            p->dado[aux1] = aux[k];
            aux1++;
        }
        if((k==4)&&(Pai->dado[k]==-1)){//significa que precisa de outro split
            if(Pai->pai!=raiz){
                split(raiz,Pai, dado_inserido);
            }
            else{
                splitRaiz(&Pai->pai, dado_inserido);
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
        p->countD++;
        (*raiz)=p;
    }
    else{
        p=busca(*raiz, di, 1);
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
            q=busca(*raiz, di, 1);
            split(*raiz, p, di);
        }
        else if(p==(*raiz)){
            splitRaiz(&(*raiz), di);
        }
    }
}


lista *busca(lista *raiz, int db, int insercao){
    int i, aux=0;
    lista *p=raiz;
    while(aux!=1) {
        i=0;
        while ((db > p->dado[i]) && (i < 4)&&(p->dado[i]!=-1)) {
            i++;
        }
        if(insercao==0) {
            if (p->dado[i] == db) {
                return p;
            } else if (p->filho[i] == nullptr) {
                return nullptr;
            }

        }
        else {
            if (p->folha == true) {
                return p;
            }
        }
        p = p->filho[i];
        if((i==3)&&(p->dado[i]<db)){
            p=p->filho[i+1];
        }
    }
}


