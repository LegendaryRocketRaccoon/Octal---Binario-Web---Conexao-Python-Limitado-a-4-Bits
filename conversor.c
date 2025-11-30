#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITOS 500
#define MAX_4_BITS 15

int validar_octal(const char *numero_str) {
    if (numero_str == NULL || strlen(numero_str) == 0) {
        return 0;
    }
    

    for (int i = 0; numero_str[i] != '\0'; i++) {
        if (numero_str[i] < '0' || numero_str[i] > '7') {
            return 0;
        }
    }
    

    unsigned long long valor_decimal = strtoull(numero_str, NULL, 8);
    
    if (valor_decimal > MAX_4_BITS) {
        printf("[ERRO] Numero octal excede o limite de 4 bits!\n");
        printf("       Valor maximo: 17 (octal) = 15 (decimal) = 1111 (binario)\n");
        return 0;
    }
    
    return 1;
}

int validar_binario(const char *numero_str) {
    if (numero_str == NULL || strlen(numero_str) == 0) {
        return 0;
    }
    

    for (int i = 0; numero_str[i] != '\0'; i++) {
        if (numero_str[i] != '0' && numero_str[i] != '1') {
            return 0;
        }
    }
    

    if (strlen(numero_str) > 4) {
        printf("[ERRO] Numero binario excede o limite de 4 bits!\n");
        printf("       Valor maximo: 1111 (binario) = 15 (decimal) = 17 (octal)\n");
        return 0;
    }
    
    return 1;
}

int octal_para_binario(const char *numero_octal, char *resultado) {
    if (!validar_octal(numero_octal)) {
        if (strtoull(numero_octal, NULL, 8) <= MAX_4_BITS) {
            printf("[ERRO] Numero octal invalido! Use apenas digitos de 0 a 7.\n");
        }
        return 0;
    }
    
    unsigned long long valor_decimal = 0;
    unsigned long long potencia = 1;
    int tamanho = strlen(numero_octal);
    

    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = numero_octal[i] - '0';
        valor_decimal += digito * potencia;
        potencia *= 8;
    }
    
    if (valor_decimal == 0) {
        strcpy(resultado, "0000");
        return 1;
    }
    

    char temp[5];
    for (int i = 3; i >= 0; i--) {
        temp[3 - i] = ((valor_decimal >> i) & 1) + '0';
    }
    temp[4] = '\0';
    strcpy(resultado, temp);
    
    return 1;
}

int binario_para_octal(const char *numero_binario, char *resultado) {
    if (!validar_binario(numero_binario)) {
        if (strlen(numero_binario) <= 4) {
            printf("[ERRO] Numero binario invalido! Use apenas digitos 0 e 1.\n");
        }
        return 0;
    }
    
    unsigned long long valor_decimal = 0;
    unsigned long long potencia = 1;
    int tamanho = strlen(numero_binario);
    

    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = numero_binario[i] - '0';
        valor_decimal += digito * potencia;
        potencia *= 2;
    }
    
    if (valor_decimal == 0) {
        strcpy(resultado, "0");
        return 1;
    }
    

    char temp[MAX_DIGITOS];
    int indice = 0;
    
    while (valor_decimal > 0) {
        int resto = valor_decimal % 8;
        temp[indice++] = '0' + resto;
        valor_decimal /= 8;
    }
    

    for (int i = 0; i < indice; i++) {
        resultado[i] = temp[indice - 1 - i];
    }
    resultado[indice] = '\0';
    
    return 1;
}

void remover_espacos(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(int argc, char *argv[]) {
    char numero[MAX_DIGITOS];
    char resultado[MAX_DIGITOS];
    int opcao;
    

    if (argc == 3) {
        opcao = atoi(argv[1]);
        strcpy(numero, argv[2]);
        remover_espacos(numero);
        
        if (opcao == 1) {

            if (octal_para_binario(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 8);
                printf("Octal: %s\n", numero);
                printf("Binario: %s\n", resultado);
                printf("Decimal: %llu\n", decimal);
                return 0;
            }
            return 1;
        }
        else if (opcao == 2) {

            if (binario_para_octal(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 2);
                printf("Binario: %s\n", numero);
                printf("Octal: %s\n", resultado);
                printf("Decimal: %llu\n", decimal);
                return 0;
            }
            return 1;
        }
        else {
            printf("[ERRO] Opcao invalida!\n");
            return 1;
        }
    }
    

    printf("==================================================\n");
    printf("  CONVERSOR DE BASES NUMERICAS (4 BITS)\n");
    printf("  Octal <-> Binario\n");
    printf("==================================================\n");
    printf("\nLimitacao: 4 bits\n");
    printf("  - Octal: 0 a 17 (max)\n");
    printf("  - Binario: 0000 a 1111 (max)\n");
    printf("  - Decimal: 0 a 15 (max)\n");
    printf("\nModo de uso:\n");
    printf("  Interativo: ./conversor\n");
    printf("  Servidor:   ./conversor <opcao> <numero>\n");
    printf("              opcao: 1=Octal->Binario, 2=Binario->Octal\n");
    printf("\nExemplo: ./conversor 1 7\n");
    printf("==================================================\n");
    
    while (1) {
        printf("\nEscolha o tipo de conversao:\n");
        printf("1 - Octal -> Binario\n");
        printf("2 - Binario -> Octal\n");
        printf("0 - Sair do programa\n");
        printf("\nDigite sua opcao (0, 1 ou 2): ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        if (opcao == 0) {
            printf("\nEncerrando o programa.\n");
            break;
        }
        else if (opcao == 1) {
            printf("\nDigite o numero em OCTAL (max 17): ");
            fgets(numero, MAX_DIGITOS, stdin);
            remover_espacos(numero);
            
            if (octal_para_binario(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 8);
                printf("\n[RESULTADO]\n");
                printf("   Octal:   %s\n", numero);
                printf("   Binario: %s (4 bits)\n", resultado);
                printf("   Decimal: %llu\n", decimal);
            }
        }
        else if (opcao == 2) {
            printf("\nDigite o numero em BINARIO (max 1111): ");
            fgets(numero, MAX_DIGITOS, stdin);
            remover_espacos(numero);
            
            if (binario_para_octal(numero, resultado)) {
                unsigned long long decimal = strtoull(numero, NULL, 2);
                

                char binario_formatado[5];
                int len = strlen(numero);
                for (int i = 0; i < 4 - len; i++) {
                    binario_formatado[i] = '0';
                }
                strcpy(binario_formatado + (4 - len), numero);
                binario_formatado[4] = '\0';
                
                printf("\n[RESULTADO]\n");
                printf("   Binario: %s (4 bits)\n", binario_formatado);
                printf("   Octal:   %s\n", resultado);
                printf("   Decimal: %llu\n", decimal);
            }
        }
        else {
            printf("\n[ERRO] Opcao invalida!\n");
        }
    }
    
    return 0;
}