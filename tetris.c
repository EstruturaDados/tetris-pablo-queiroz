#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // Tamanho fixo da fila

// Struct que representa uma peça do Tetris Stack
typedef struct {
    char nome;   // Tipo da peça ('I', 'O', 'T', 'L')
    int id;      // Identificador único da peça
} Peca;

// Struct da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;


// -------- PROTÓTIPOS --------
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
Peca gerarPeca();
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void exibirFila(Fila *f);


// -------- FUNÇÕES --------

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Gera automaticamente uma peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    static int contadorID = 0;

    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;

    return nova;
}

// Insere peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠️ A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove peça da frente da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {'?', -1};

    if (filaVazia(f)) {
        printf("\n⚠️ Nenhuma peça para jogar. A fila está vazia!\n");
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// Exibe o estado completo da fila
void exibirFila(Fila *f) {
    printf("\n-----------------------------");
    printf("\n   Fila de Peças Futuras");
    printf("\n-----------------------------\n");

    if (filaVazia(f)) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}


// ---------------- PROGRAMA PRINCIPAL ----------------
int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    // Preenche a fila inicialmente com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        exibirFila(&fila);

        printf("\nOpções:");
        printf("\n1 - Jogar peça (dequeue)");
        printf("\n2 - Inserir nova peça (enqueue)");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;
            }

            case 2: {
                enqueue(&fila, gerarPeca());
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
