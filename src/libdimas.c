#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libdimas.h"

int menu(const ConfigMenu *cm) // Recebe ponteiro
{
    int valorRetornado = 0;
    int countOpcoes = 0;
    int entradaValida;
    char temp[256]; 
    char *buff = NULL;
    char *res = NULL;
    
    // 1. PREPARAÇÃO (Feita apenas uma vez)
    // Precisamos contar as opções ANTES de entrar no loop para alocar o buffer corretamente
    strcpy(temp, cm->opcoes);
    res = strtok(temp, cm->separador);
    while (res != NULL) {
        countOpcoes++;
        res = strtok(NULL, cm->separador);
    }

    // Calcula tamanho do buffer (digitos + \n + \0)
    // Melhoria: snprintf(NULL, 0, "%d", countOpcoes) daria o tamanho exato de digitos, 
    // mas sua lógica /10 + 3 funciona bem para inteiros simples.
    int tam_buff = (countOpcoes / 10) + 3;

    // ALOCAÇÃO FORA DO LOOP (Evita Memory Leak)
    buff = (char *)malloc(tam_buff * sizeof(char));
    if (!buff) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return -1;
    }

    // 2. LOOP DE INTERAÇÃO
    do {
        entradaValida = 1; // Assume válido até provar o contrário
        
        // Limpa a tela (Linux/Unix)
        // Dica: Sequências ANSI são mais leves que system("clear")
        printf("\033[H\033[J"); 

        printf("%s\n", cm->titulo);
        
        // Re-tokenizar para imprimir (pois strtok destrói a string original na 1ª passada)
        strcpy(temp, cm->opcoes);
        int i = 0;
        res = strtok(temp, cm->separador);
        while (res != NULL) {
            printf("[%d] - %s\n", ++i, res);
            res = strtok(NULL, cm->separador);
        }

        printf("Selecione a opcao: ");
        
        // Limpa buffer alocado antes de usar
        memset(buff, 0, tam_buff); 

        if (fgets(buff, tam_buff, stdin) == NULL) {
             entradaValida = 0; // Erro de leitura
        } else {
            // Verifica o \n
            size_t len = strlen(buff);
            if (len > 0 && buff[len-1] != '\n') {
                // Buffer estourou (usuário digitou demais)
                entradaValida = 0;
                // Limpa o resto do stdin
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Erro: Entrada muito longa.\n");
            } else {
                // Remove o \n se existir para o atoi funcionar limpo
                buff[strcspn(buff, "\n")] = 0;
                
                // Validação numérica simples
                char *endptr;
                valorRetornado = (int)strtol(buff, &endptr, 10); // strtol é mais seguro que atoi
                
                if (endptr == buff || *endptr != '\0') {
                    // Não converteu nada ou tem lixo (ex: "1a")
                    entradaValida = 0;
                    printf("Erro: Digite apenas numeros.\n");
                } else if (valorRetornado < 1 || valorRetornado > countOpcoes) {
                    entradaValida = 0;
                    printf("Opcao invalida (1-%d).\n", countOpcoes);
                }
            }
        }

        if (!entradaValida) {
            printf("Pressione ENTER para tentar novamente...");
            getchar(); // Pausa para o usuário ler o erro
        }

    } while (!entradaValida);

    free(buff);
    return valorRetornado;
}