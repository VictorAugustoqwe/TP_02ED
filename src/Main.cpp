#include <iostream>
#include <fstream>
#include <string>

#include "Info.h"

using namespace std;

//Imprime todos os elementos do vetor seguintos as especificações "nome dado"
void Print(Info *vetor, int n){
    for(int i = 0; i < n; i++){
        cout << vetor[i]._nome << " " << vetor[i]._dado << endl;
    } 
}

//Função que implementa o radixSort e ordena a partir de uma string de bits
void RadixSorting(Info *vetor, int esq, int dir, int nbits, int tamanho){
    int pontEsq = esq;
    int pontDir = dir;
    Info aux;
    if(dir <= esq || nbits > 7) return;
    while(pontEsq != pontDir){
        while(vetor[pontEsq]._dado[nbits] == '0' && (pontEsq < pontDir)) pontEsq++;
        while(vetor[pontDir]._dado[nbits] == '1' && (pontDir > pontEsq)) pontDir--;
        aux = vetor[pontEsq];
        vetor[pontEsq] = vetor[pontDir];
        vetor[pontDir] = aux;

    }
    if(vetor[dir]._dado[nbits] == '0') pontDir++;
    RadixSorting(vetor, esq, pontDir-1, nbits+1, tamanho);
    RadixSorting(vetor, pontDir, dir, nbits+1, tamanho);
}

//Função para facicilitar chamada do RadixSort
void RadixSort(Info *vetor, int tamanho){
    RadixSorting(vetor, 0, tamanho-1, 0, tamanho);
}

//Ordena os dois trechos pré-ordenados (esq-meio e meio-dir) utilizando o vetor auxiliar
void Merge(Info *vetor, Info *vetorExtra, int esq, int meio, int dir){
    int percorreEsq = esq;
    int percorreDir = meio + 1;
    int percorreOrig = esq;
    while(percorreEsq <= meio && percorreDir <= dir){
        if(vetor[percorreEsq]._nome <= vetor[percorreDir]._nome){
            vetorExtra[percorreOrig] = vetor[percorreEsq];
            percorreEsq++;
        } else{
            vetorExtra[percorreOrig] = vetor[percorreDir];
            percorreDir++;
        }
        percorreOrig++;
    }

    while(percorreEsq <= meio){
        vetorExtra[percorreOrig] = vetor[percorreEsq];
        percorreOrig++;
        percorreEsq++;
    }

    while(percorreDir <= dir){
        vetorExtra[percorreOrig] = vetor[percorreDir];
        percorreOrig++;
        percorreDir++;
    }

    for(int i = esq; i <= dir; i++){
        vetor[i] = vetorExtra[i];
    }
}

//Faz chamadas recursivas para dividir o vetor e chama a função que ordena os trechos
void MergeSorting(Info *vetor, Info *vetorExtra, int esq, int dir){
    if (esq < dir){
        int meio;
        meio = ((esq + dir)/2);
        MergeSorting(vetor, vetorExtra, esq, meio);
        MergeSorting(vetor, vetorExtra, meio+1, dir);
        Merge(vetor, vetorExtra, esq, meio, dir);
    }
}

//Função para facicilitar chamada do MergeSort
void MergeSort(Info *vetor, int tamanho){
    Info *vetorExtra = new Info[tamanho];
    MergeSorting(vetor, vetorExtra, 0, tamanho-1);
    delete[] vetorExtra;
}

//Saatifaz a condição de heap a par
void Refaz(int esq, int dir, Info *vetor){
    int pai, filho;
    Info chavePai;
    pai = esq;
    filho = pai * 2;
    chavePai = vetor[pai];
    while(filho <= dir){
        if(filho < dir)
            if(vetor[filho]._dado < vetor[filho + 1]._dado) filho++;
        if(chavePai._dado >= vetor[filho]._dado) break;
        vetor[pai] = vetor[filho];
        pai = filho;
        filho = pai * 2;
    }
    vetor[pai] = chavePai;
}

//Cria um heap a partir do vetor
void Constroi(Info *vetor, int n){
    int Esq;
    Esq = n / 2 + 1;
    while (Esq > 0){
        Esq--;
        Refaz(Esq, n-1, vetor);
    }
}

//Função de organização do HeapSort
void HeapSort(Info *vetor, int n){
    int esq, dir;
    Info max;
    Constroi(vetor, n);
    esq = 0;
    dir = n - 1;
    while(dir > 0){
        max = vetor[0];
        vetor[0] = vetor[dir];
        vetor[dir] = max;
        dir--;
        Refaz(esq, dir, vetor);
    }
}

//Cria partição escolhendo um pivô para ordenar e posicionando elementos maiores que o pivo à direita e menores à esquerda 
void Particao(int esq, int dir, int *pontEsq, int *pontDir, Info *vetor){
    Info pivo, aux;
    *pontEsq = esq;
    *pontDir = dir;
    pivo = vetor[(*pontEsq + *pontEsq)/2];
    do{
        while(pivo._nome > vetor[*pontEsq]._nome) (*pontEsq)++;
        while(pivo._nome < vetor[*pontDir]._nome) (*pontDir)--;
        if(*pontEsq <= *pontDir){
            aux = vetor[*pontEsq];
            vetor[*pontEsq] = vetor[*pontDir];
            vetor[*pontDir] = aux;
            (*pontEsq)++;
            (*pontDir)--;
        }
    } while(*pontEsq <= *pontDir);
}

//Faz chamadas recursivas para dividir o vetor já ordenando nas divisões usando Partição para criar o pivô e ordenar
void Ordena(int esq, int dir, Info *vetor){
    int pontEsq;
    int pontDir;
    Particao(esq, dir, &pontEsq, &pontDir, vetor);
    if(esq < pontDir) Ordena(esq, pontDir, vetor);
    if(pontEsq < dir) Ordena(pontEsq, dir, vetor);
}

//Função para facicilitar chamada do QuickSort.
void QuickSort(Info *vetor, int n){
    Ordena(0, n-1, vetor);
}

//Lê entradas e abre o arquivo executando as ordenações conforme a configuração e quantidade de entradas passadas.
int main(int argc, char* argv[]){

    int nlinhas, posEspaco, configOrdenacao;
    string nomeAtual, linha, dadoAtual;

    try{
        if(argv[1] == NULL){
            cout << "Nome do Arquivo Faltando!" << endl;
            return 1;
        }
        if(argv[2] == NULL){
            cout << "Configuração de Ordenação Faltando!" << endl;
            return 1;
        }
        if(argv[3] == NULL){
            cout << "Número de Linhas Faltando!" << endl;
            return 1;
        }
        ifstream arquivo(argv[1]);
        configOrdenacao = stoi(argv[2]);
        nlinhas = stoi(argv[3]);

        Info *arrayParaOrdenar = new Info[nlinhas];
        if(nlinhas < 0){
            cout << "Numero de Linhas Incorreto!" << endl;
            return 1;
        }
        for(int i = 0; i < nlinhas; i++){
            getline(arquivo, linha);
            posEspaco = linha.find(" ");
            nomeAtual = linha.substr(0,posEspaco);
            dadoAtual = linha.substr(posEspaco + 1);
            arrayParaOrdenar[i]._nome = nomeAtual;
            arrayParaOrdenar[i]._dado = dadoAtual;
        }

        switch (configOrdenacao){
            case 1:
                HeapSort(arrayParaOrdenar, nlinhas);
                QuickSort(arrayParaOrdenar, nlinhas);
                Print(arrayParaOrdenar, nlinhas);
                break;
            case 2:
                RadixSort(arrayParaOrdenar, nlinhas);
                QuickSort(arrayParaOrdenar, nlinhas);
                Print(arrayParaOrdenar, nlinhas);
                break;
            case 3:
                HeapSort(arrayParaOrdenar, nlinhas);
                MergeSort(arrayParaOrdenar, nlinhas);
                Print(arrayParaOrdenar, nlinhas);
                break;
            case 4:
                RadixSort(arrayParaOrdenar, nlinhas);
                MergeSort(arrayParaOrdenar, nlinhas);
                Print(arrayParaOrdenar, nlinhas);
                break;

            default:
                cout << "Configuração Incorreta" << endl;
                return 1;
                break;
        }
        delete[] arrayParaOrdenar;
    }catch(const char* e){
        cerr << e;
        return 1;
    }
    return 0;
}