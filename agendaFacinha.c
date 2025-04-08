#include <stdio.h>

struct Contato {
    char nome[128];
    char telefone[15];
};

typedef struct Contato Contato;

int cadastrar(Contato contato[], int *totalContato) {
    if (*totalContato >= 50) {
        printf("Agenda está cheia\n");
        return 0;
    }

    printf("Qual o NOME da pessoa: ");
    scanf(" %s", contato[*totalContato].nome);
    printf("Qual o telefone da pessoa (ex: 63985038937): ");
    scanf(" %s", contato[*totalContato].telefone);

    (*totalContato)++;
    return 1;
}

void imprimirAgenda(Contato contato[], int *totalContato) {
    for (int i = 0; i < *totalContato; i++) {
        printf("-------------------------------\n");
        printf("Contato %d\n", i + 1); // Ajustando para base 1
        printf("NOME: %s\n", contato[i].nome);

        // Formatando telefone com máscara
        printf("TELEFONE: (%c%c) %c %s\n", contato[i].telefone[0], contato[i].telefone[1], contato[i].telefone[2], contato[i].telefone + 3);
    }
}

void deletarContato(Contato contato[], int *totalContato) {
    if (*totalContato == 0) {
        printf("A agenda está vazia! Nenhum contato para deletar.\n");
        return;
    }

    imprimirAgenda(contato, totalContato);

    int numeroDeletar;
    printf("Digite o número do contato que deseja deletar (1 a %d): ", *totalContato);
    scanf("%d", &numeroDeletar);

    // Verificar se o índice é válido
    if (numeroDeletar < 1 || numeroDeletar > *totalContato) {
        printf("Número inválido! Tente novamente.\n");
        return;
    }

    // Ajustar para índice do vetor (base 0)
    numeroDeletar--;

    // Deslocar contatos para preencher o espaço vazio
    for (int i = numeroDeletar; i < *totalContato - 1; i++) {
        contato[i] = contato[i + 1];
    }

    (*totalContato)--;

    printf("Contato deletado com sucesso!\n");
    imprimirAgenda(contato, totalContato);
}

int main() {
    Contato contato[50];
    int valor = 1;
    int totalContato = 0;

    do {
        printf("----------AGENDINHA FACINHA----------------------\n");
        printf("Digite [1] para cadastrar um novo número\n");
        printf("Digite [2] para imprimir agenda na tela\n");
        printf("Digite [3] para deletar um contato\n");
        printf("Digite [4] para salvar em arquivo CSV\n");
        printf("Digite [5] para sair (as alterações serão salvas)\n");
        scanf("%d", &valor);

        switch (valor) {
            case 1:
                cadastrar(contato, &totalContato);
                break;
            case 2:
                imprimirAgenda(contato, &totalContato);
                break;
            case 3:
                deletarContato(contato, &totalContato);
                break;
            case 4:
                // salvar em CSV 
                break;
            case 5:
                continue;
        }

    } while (valor != 5);

    return 0;
}