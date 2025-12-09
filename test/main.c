#include <stdio.h>
#include <string.h>
#include "../include/libdimas.h"

int main() {
    ConfigMenu cm;
    int escolha;

    // Configurando o menu
    strcpy(cm.titulo, "=== Menu de Teste LibDimas ===");
    strcpy(cm.opcoes, "Opcao 1;Opcao 2;Opcao 3;Sair");
    strcpy(cm.separador, ";");

    // Chamando o menu
    printf("Iniciando teste do menu...\n");
    escolha = menu(cm);

    // Exibindo o resultado
    printf("\nOpcao escolhida: %d\n", escolha);

    return 0;
}
