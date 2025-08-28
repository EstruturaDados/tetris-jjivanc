// Visualizar a fila atual
// Jogar (remover) a peça da frente
// Inserir automaticamente uma nova peça no final da fila
// ⚙️ Funcionalidades do Sistema:
#include <stdio.h>
#include <stdlib.h>

#define MAX_PECA 5
#define MAX_PILHA 3
// Tipo de peca 'I', 'O', 'T', 'L’ (1,2,3,4)
typedef struct{
    char tipo;
    int id;
} Peca;
typedef struct{
    Peca items[MAX_PECA];
    int inicio;
    int fim;
    int tamanho;
} Fila;
typedef struct{
    Peca items[MAX_PILHA];
    int topo;
} Pilha;
int pilhaVazia(Pilha *p){
    return p->topo == -1;
}
int pilhaCheia(Pilha *p){
    return p->topo == MAX_PILHA - 1;
}
void inicializarPilha(Pilha *p){
    p->topo = -1;
}
void inicializarFila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}
int filaVazia(Fila *fila){
    return fila->tamanho == 0;
}
int filaCheia(Fila *fila){
    return fila->tamanho == MAX_PECA;
}
void inserirPeca(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }
    fila->items[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % MAX_PECA;
    fila->tamanho++;
}
void removerPeca(Fila *fila,Peca *peca) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não é possível remover peça.\n");
        return;
    }
    *peca = fila->items[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_PECA;
    fila->tamanho--;
}
void empilhar(Pilha *p, Peca peca){
    if(!pilhaCheia(p)){
        p->items[++p->topo] = peca;
    }else {
        printf("Pilha cheia!\n");
    }
};
void desempilhar(Pilha *p, Peca *peca){
    if(!pilhaVazia(p)){
        *peca = p->items[p->topo--];
    }else {
        printf("Pilha vazia!\n");
    }
}
void exibirPilha(Pilha *p){
    if(!pilhaVazia(p)){
        for(int i = p->topo; i >= 0; i--){
            printf("ID: %d, Tipo: %c\n", p->items[i].id, p->items[i].tipo);
        }
    }else {
        printf("Pilha vazia!\n");
    }
}
Peca gerarPeca() {
    Peca novaPeca;
    int id = rand() % 1000; // Gera um ID aleatório
    char tipo = rand() % 4 + 1;
    tipo = (tipo == 1) ? 'I' : (tipo == 2) ? 'O' : (tipo == 3) ? 'T' : 'L';
    novaPeca.tipo = tipo;
    novaPeca.id = id;
    return novaPeca;
}
int main(){
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    for(int i =0; i < MAX_PECA; i++){
        Peca novaPeca = gerarPeca();
        inserirPeca(&fila, novaPeca);
    }

    // Exibir estado atual da fila
    printf("Estado atual da fila:\n");
    for (int i = 0; i < fila.tamanho; i++) {
        Peca p = fila.items[(fila.inicio + i) % MAX_PECA];
        printf("ID=%d, Tipo=%c\n", p.id, p.tipo);
    }
    int opcao;
    do {
        printf("Escolha uma opção:\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Jogar Peça Reservada\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca pecaRemovida;
                removerPeca(&fila, &pecaRemovida);
                printf("Peça jogada: ID=%d, Tipo=%c\n", pecaRemovida.id, pecaRemovida.tipo);
                Peca novaPeca = gerarPeca();
                inserirPeca(&fila, novaPeca);
                break;
            }
            case 2: {
                if(!pilhaCheia(&pilha)){
                    Peca pecaReservada;
                    removerPeca(&fila, &pecaReservada);
                    printf("Peça Reservada: ID=%d, Tipo=%c\n", pecaReservada.id, pecaReservada.tipo);
                    empilhar(&pilha, pecaReservada);
                    printf("Estado atual da pilha de peças reservadas:\n");
                    exibirPilha(&pilha);
                }else {
                    printf("Pilha cheia! Não é possível reservar nova peça.\n");
                }
                break;
            }
            case 3: {
                if(!pilhaVazia(&pilha)){
                    Peca pecaJogada;
                    desempilhar(&pilha, &pecaJogada);
                    printf("Peça Jogada: ID=%d, Tipo=%c\n", pecaJogada.id, pecaJogada.tipo);
                    printf("Estado atual da pilha de peças reservadas:\n");
                    exibirPilha(&pilha);
                }else {
                    printf("Não há peças reservadas para jogar.\n");
                }
                break;
            }
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        // Exibir estado atual da fila
        printf("Estado atual da fila:\n");
        for (int i = 0; i < fila.tamanho; i++) {
            Peca p = fila.items[(fila.inicio + i) % MAX_PECA];
            printf("ID=%d, Tipo=%c\n", p.id, p.tipo);
        }
        
    } while (opcao != 4);

    return 0;
}