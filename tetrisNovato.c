// Visualizar a fila atual
// Jogar (remover) a peça da frente
// Inserir automaticamente uma nova peça no final da fila
// ⚙️ Funcionalidades do Sistema:
#include <stdio.h>
#include <stdlib.h>

#define MAX_PECA 5
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
    inicializarFila(&fila);

    int opcao;
    do {
        printf("Escolha uma opção:\n");
        printf("1. Jogar peça\n");
        printf("2. Inserir nova peça\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca pecaRemovida;
                removerPeca(&fila, &pecaRemovida);
                printf("Peça jogada: ID=%d, Tipo=%c\n", pecaRemovida.id, pecaRemovida.tipo);
                break;
            }
            case 2: {
                Peca novaPeca = gerarPeca();
                inserirPeca(&fila, novaPeca);
                printf("Nova peça inserida: ID=%d, Tipo=%c\n", novaPeca.id, novaPeca.tipo);
                break;
            }
            case 3:
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
    } while (opcao != 3);

    return 0;
}
