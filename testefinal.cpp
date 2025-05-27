#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100

// estrutura basica dos alunos
typedef struct {
    char nome[50];
    char rgm[9];
    int idade;
    float A1;
    float A2;
    float AF;
    float notaFinal;
    int emRecuperacao; // 1 se esta em recuperacao, 0 se nao
} Aluno;

// funcoes do programa
void cadastrarAluno(Aluno *alunos, int *totalAlunos);
void consultarAlunos(Aluno *alunos, int totalAlunos);
void apagarDados(Aluno *alunos, int *totalAlunos);
void calcularNotas(Aluno *aluno);
void exibirMenu();

int main() {
    Aluno alunos[MAX_ALUNOS];
    int totalAlunos = 0;
    int qtdInicial = 0;
    int opcao;

    printf("quantos alunos voce quer cadastrar? ");
    scanf("%d", &qtdInicial);
    getchar(); // limpa buffer

    if (qtdInicial > MAX_ALUNOS) {
        printf("limite maximo de alunos eh %d\n", MAX_ALUNOS);
        return 1;
    }

    while (1) {
        exibirMenu();
        printf("sua opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                if (totalAlunos < qtdInicial) {
                    cadastrarAluno(alunos, &totalAlunos);
                } else {
                    printf("voce ja cadastrou o maximo de alunos permitido\n");
                }
                break;
            case 2:
                consultarAlunos(alunos, totalAlunos);
                break;
            case 3:
                apagarDados(alunos, &totalAlunos);
                break;
            case 4:
                printf("saindo do programa...\n");
                return 0;
            default:
                printf("opcao invalida. tenta de novo.\n");
        }
    }
}

// menu na tela
void exibirMenu() {
    printf("\n=== menu principal ===\n");
    printf("1. cadastrar aluno\n");
    printf("2. consultar alunos\n");
    printf("3. apagar todos os dados\n");
    printf("4. sair\n");
}

// funcao para cadastrar
void cadastrarAluno(Aluno *alunos, int *totalAlunos) {
    Aluno novo;

    printf("nome do aluno: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // tira o \n

    printf("RGM (8 digitos): ");
    scanf("%s", novo.rgm);
    getchar(); // limpa buffer

    printf("idade: ");
    scanf("%d", &novo.idade);
    getchar(); // limpa buffer

    printf("nota da A1 (0 a 5): ");
    scanf("%f", &novo.A1);
    getchar();

    printf("nota da A2 (0 a 5): ");
    scanf("%f", &novo.A2);
    getchar();

    calcularNotas(&novo);

    alunos[*totalAlunos] = novo;
    (*totalAlunos)++;

    printf("aluno cadastrado com sucesso!\n");
}

// mostra todos os alunos
void consultarAlunos(Aluno *alunos, int totalAlunos) {
    if (totalAlunos == 0) {
        printf("nenhum aluno cadastrado ainda\n");
        return;
    }

    printf("\n=== lista de alunos ===\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("nome: %s | RGM: %s | idade: %d | A1: %.2f | A2: %.2f | AF: %.2f | nota final: %.2f",
            alunos[i].nome,
            alunos[i].rgm,
            alunos[i].idade,
            alunos[i].A1,
            alunos[i].A2,
            alunos[i].AF,
            alunos[i].notaFinal
        );

        if (alunos[i].emRecuperacao) {
            printf(" (em recuperacao)");
        }

        printf("\n");
    }
}

// limpa tudo
void apagarDados(Aluno *alunos, int *totalAlunos) {
    *totalAlunos = 0;
    printf("todos os dados foram apagados\n");
}

// logica da nota e recuperacao
void calcularNotas(Aluno *aluno) {
    float soma = aluno->A1 + aluno->A2;
    aluno->emRecuperacao = 0;

    if (soma <= 5) {
        printf("aluno precisa fazer a prova de recuperacao (AF)\n");
        printf("nota da AF (0 a 5): ");
        scanf("%f", &aluno->AF);
        getchar();

        // troca a menor nota pela AF
        if (aluno->A1 < aluno->A2) {
            aluno->A1 = aluno->AF;
        } else {
            aluno->A2 = aluno->AF;
        }
    } else {
        aluno->AF = 0;
    }

    aluno->notaFinal = aluno->A1 + aluno->A2;

    if (aluno->notaFinal < 6) {
        aluno->emRecuperacao = 1;
        printf("nota final: %.2f | aluno ainda esta de recuperacao\n", aluno->notaFinal);
    } else {
        printf("nota final valida: %.2f\n", aluno->notaFinal);
    }
}

