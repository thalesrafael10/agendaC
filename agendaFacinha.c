#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contato {
    char nome[128];
    char telefone[15];
};

typedef struct Contato Contato;

void carregarAgenda(Contato contato[], int *totalContato) {
    FILE *arquivo = fopen("agenda.csv", "r");
    if (arquivo == NULL) {
        printf("Nenhuma agenda existente encontrada.\n");
        return;
    }

    *totalContato = 0;
    while (fscanf(arquivo, "%[^,], %[^\n]\n", contato[*totalContato].nome, contato[*totalContato].telefone) == 2) {
        (*totalContato)++;
        if (*totalContato >= 50) break; // Limite de contatos
    }

    fclose(arquivo);
}

void salvarAgenda(Contato contato[], int totalContato) {
    FILE *arquivo = fopen("agenda.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a agenda!\n");
        return;
    }

    for (int i = 0; i < totalContato; i++) {
        fprintf(arquivo, "%s,%s\n", contato[i].nome, contato[i].telefone);
    }

    fclose(arquivo);
}

int cadastrar(Contato contato[], int *totalContato) {
    if (*totalContato >= 50) {
        printf("Agenda está cheia\n");
        return 0;
    }

    printf("Qual o NOME da pessoa: ");
    scanf(" %[^\n]", contato[*totalContato].nome);
    printf("Qual o telefone da pessoa (ex: 63985038937): ");
    scanf(" %[^\n]", contato[*totalContato].telefone);

    (*totalContato)++;
    return 1;
}

void imprimirAgenda(Contato contato[], int totalContato) {
    if (totalContato == 0) {
        printf("Agenda vazia!\n");
        return;
    }

    for (int i = 0; i < totalContato; i++) {
        printf("-------------------------------\n");
        printf("Contato %d\n", i + 1);
        printf("NOME: %s\n", contato[i].nome);
        printf("TELEFONE: (%c%c) %c %s\n", contato[i].telefone[0], contato[i].telefone[1], contato[i].telefone[2], contato[i].telefone + 3);
    }
}

void deletarContato(Contato contato[], int *totalContato) {
    if (*totalContato == 0) {
        printf("A agenda está vazia! Nenhum contato para deletar.\n");
        return;
    }

    imprimirAgenda(contato, *totalContato);

    int numeroDeletar;
    printf("Digite o número do contato que deseja deletar (1 a %d): ", *totalContato);
    scanf("%d", &numeroDeletar);

    if (numeroDeletar < 1 || numeroDeletar > *totalContato) {
        printf("Número inválido! Tente novamente.\n");
        return;
    }

    numeroDeletar--;
    for (int i = numeroDeletar; i < *totalContato - 1; i++) {
        contato[i] = contato[i + 1];
    }

    (*totalContato)--;
    printf("Contato deletado com sucesso!\n");
}

int main() {
    Contato contato[50];
    int totalContato = 0;

    carregarAgenda(contato, &totalContato);

    int valor;
    do {
        printf("----------AGENDINHA FACINHA----------------------\n");
        printf("Digite [1] para cadastrar um novo número\n");
        printf("Digite [2] para imprimir agenda na tela\n");
        printf("Digite [3] para deletar um contato\n");
        printf("Digite [4] para salvar manualmente\n");
        printf("Digite [5] para sair e salvar\n");
        scanf("%d", &valor);

        switch (valor) {
            case 1:
                cadastrar(contato, &totalContato);
                break;
            case 2:
                imprimirAgenda(contato, totalContato);
                break;
            case 3:
                deletarContato(contato, &totalContato);
                break;
            case 4:
                salvarAgenda(contato, totalContato);
                printf("Agenda salva!\n");
                break;
            case 5:
                salvarAgenda(contato, totalContato);
                printf("Saindo... Sua agenda foi salva com sucesso!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (valor != 5);

    return 0;
}