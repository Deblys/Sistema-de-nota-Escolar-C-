LEIA COM ATENÇAO FOI O MAXIMO DE RESUMO QUE FIZ 
EU NAO SEI MEXER COM C, ESTOU APRENDENDO.

// ANOTAÇOES 

#include <stdio.h>    // aqui a gente chama uma "biblioteca" que deixa usar comandos como printf() e scanf()
#include <stdlib.h>   // essa é outra biblioteca que ajuda com coisas como sair do programa, mexer com memória, etc.
#include <string.h>   // essa aqui serve pra trabalhar com textos (strings), como comparar nomes ou cortar o \n do final

#define MAX_ALUNOS 100   // aqui a gente define o máximo de alunos que o sistema vai aceitar: 100

// agora a gente cria um tipo novo chamado "Aluno"

typedef struct {
    char nome[50];      // nome do aluno (pode ter até 49 letras + fim de texto)
    char rgm[9];        // o RGM do aluno (8 números + um espaço pro fim de texto)
    int idade;          // idade do aluno (um número inteiro tipo 18, 20)
    float A1;           // nota da primeira prova (vai de 0.0 até 5.0)
    float A2;           // nota da segunda prova
    float AF;           // nota da prova de recuperação (se precisar)
    float notaFinal;    // média final (pode ir de 0 até 10)
    int emRecuperacao;  // se for 1, o aluno tá de recuperação; se for 0, passou
} Aluno;   // isso tudo aqui agora se chama "Aluno"

// aqui a gente só avisa o que vai ter no programa

void cadastrarAluno(Aluno *alunos, int *totalAlunos);
void consultarAlunos(Aluno *alunos, int totalAlunos);
void apagarDados(Aluno *alunos, int *totalAlunos);
void calcularNotas(Aluno *aluno);
void exibirMenu();

//  A parte principal do programa começa aqui

int main() { 

    Aluno alunos[MAX_ALUNOS];   // criamos uma "lista" (vetor) de alunos com espaço pra até 100
    int totalAlunos = 0;        // esse numero vai contando quantos alunos já cadastramos
    int qtdInicial = 0;         // essa é a quantidade que o usuário vai dizer que quer cadastrar
    int opcao;                  // aqui vai guardar a escolha do menu

    printf("quantos alunos voce quer cadastrar? ");
    scanf("%d", &qtdInicial);    // o usuário digita um número, e guardamos ele em qtdInicial
    getchar();                   // aqui a gente limpa o ENTER que o cara digitou

    if (qtdInicial > MAX_ALUNOS) {
        printf("limite maximo de alunos eh %d\n", MAX_ALUNOS);
        return 1;   // se o cara colocou mais que 100, o programa para aqui
    }

    while (1) {
        exibirMenu(); // mostra o menu com as opcoes

        printf("sua opcao: ");
        scanf("%d", &opcao);  // o usuario digita uma opcao do menu
        getchar(); // de novo limpamos o ENTER

        switch (opcao) {
            case 1:
                if (totalAlunos < qtdInicial) {
                    cadastrarAluno(alunos, &totalAlunos); // chama a funcao pra cadastrar aluno
                } else {
                    printf("voce ja cadastrou o maximo de alunos permitido\n");
                }
                break;

            case 2:
                consultarAlunos(alunos, totalAlunos); // mostra os alunos
                break;

            case 3:
                apagarDados(alunos, &totalAlunos); // limpa tudo
                break;

            case 4:
                printf("saindo do programa...\n"); // fecha tudo
                return 0;

            default:
                printf("opcao invalida. tenta de novo.\n");
        }
    }
}

void exibirMenu() {
    printf("\n=== menu principal ===\n");
    printf("1. cadastrar aluno\n");
    printf("2. consultar alunos\n");
    printf("3. apagar todos os dados\n");
    printf("4. sair\n");
}

void cadastrarAluno(Aluno *alunos, int *totalAlunos) {
    Aluno novo;

    printf("nome do aluno: ");
    fgets(novo.nome, sizeof(novo.nome), stdin); // lê o nome com espaços
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // tira o ENTER do final

// aqui e para a idade e o rgm

    printf("RGM (8 digitos): ");
    scanf("%s", novo.rgm);
    getchar();

    printf("idade: ");
    scanf("%d", &novo.idade);
    getchar();

// aqui e as avaliacoes 

    printf("nota da A1 (0 a 5): ");
    scanf("%f", &novo.A1);
    getchar();

    printf("nota da A2 (0 a 5): ");
    scanf("%f", &novo.A2);
    getchar();

// aqui chama pra caucular 

    calcularNotas(&novo);

// aqui bota o aluno na lista e atualiza o contador 

    alunos[*totalAlunos] = novo;
    (*totalAlunos)++;

    printf("aluno cadastrado com sucesso!\n");
}

//aqui mostra os alunos e cadastro 

void consultarAlunos(Aluno *alunos, int totalAlunos) {
    if (totalAlunos == 0) {
        printf("nenhum aluno cadastrado ainda\n");
        return;
    }

    printf("\n=== lista de alunos ===\n");

// aqui mostra os dados de todos os alunos 

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

// aqui apaga tudo 

void apagarDados(Aluno *alunos, int *totalAlunos) {
    *totalAlunos = 0;
    printf("todos os dados foram apagados\n");
}

// aqui caucula notas e recuperacao

void calcularNotas(Aluno *aluno) {
    float soma = aluno->A1 + aluno->A2;
    aluno->emRecuperacao = 0;

// aqui e a soma pra ve se ficou de recuperacao

    if (soma <= 5) {
        printf("aluno precisa fazer a prova de recuperacao (AF)\n");
        printf("nota da AF (0 a 5): ");
        scanf("%f", &aluno->AF);
        getchar();

        // trocamos a menor nota pela AF
        if (aluno->A1 < aluno->A2) {
            aluno->A1 = aluno->AF;
        } else {
            aluno->A2 = aluno->AF;
        }
    } else {
        aluno->AF = 0;
    }

// aqui calcula a nota final 

    aluno->notaFinal = aluno->A1 + aluno->A2;

    if (aluno->notaFinal < 6) {
        aluno->emRecuperacao = 1;
        printf("nota final: %.2f | aluno ainda esta de recuperacao\n", aluno->notaFinal);
    } else {
        printf("nota final valida: %.2f\n", aluno->notaFinal);
    }
