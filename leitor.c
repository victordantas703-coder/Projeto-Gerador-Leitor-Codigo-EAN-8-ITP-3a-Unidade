#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h" // Tabela de dígitos do EAN-8 //

void extrair_codigo (char *nome) {

    // Abrir o arquivo para leitura //
    FILE *arquivo = fopen(nome, "rb");
    if (arquivo == NULL) {  // Verificar se o arquivo foi aberto com sucesso //
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Elementos do cabeçalho //
    char formato[3]; //Formato do arquivo //
    int largura, altura; // Dimensões da imagem //

    // Ler cabeçalho //
    fscanf(arquivo, "%s\n", formato);    // Ler o formato do arquivo //
    if (strcmp(formato, "P1") != 0) { // Verificar se é PBM (P1) //
        printf("Arquivo não é do formato PBM (P1)\n");
        fclose(arquivo);
        return;
    }

    fscanf(arquivo, "%d %d\n", &largura, &altura);  // Ler largura e altura //

    // Alocar memória para matriz de pixels //
    int **pixels = NULL;
    pixels = malloc(altura * sizeof(int*)); // Alocar linhas //
    for (int i = 0; i < altura; i++) {
        pixels[i] = malloc(largura * sizeof(int)); // Alocar colunas //
    }

    // Ler dados dos pixels //
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int pixel;
            fscanf(arquivo, "%d\n", &pixel); // Ler cada pixel (0 ou 1) //
            pixels[i][j] = pixel;
        }
    }
    fclose(arquivo); // Fechar o arquivo após a leitura //

    // Procurar primeiro pixel preto (1) //
    int inicio_coluna= 0;
    int inicio_linha = 0;
    int achou = 0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (pixels[i][j] == 1) {
                inicio_linha = i; // Linha do primeiro pixel preto //
                inicio_coluna = j; // Coluna do primeiro pixel preto //
                achou = 1;
                break;
            }
        }
        if(achou) break;
    }

    // Medir largura da barra(área) //
    int largura_barra = 0;
    for (int j = inicio_coluna; j < largura; j++) {
        if (pixels[inicio_linha][j] == 1) {
            largura_barra++;
        } else {
            break;
        }
    }

    // Alocar memoria para vetor do código de barras //
    char *codigo_barras = NULL;
    codigo_barras = malloc(67 * sizeof(char)); // Código de barras tem 67 barras brancas ou pretas //

    // Extrair código de barras //
    for (int i = 0; i < 67; i++) {
        int bit_temporario = pixels[inicio_linha][inicio_coluna + i*largura_barra]; // Ler o pixel correspondente à barra atual //
        switch(bit_temporario){ // Converter o pixel para caractere '0' ou '1' //
            case 0: codigo_barras[i] = '0'; break;
            case 1: codigo_barras[i] = '1'; break;
            default: 
            printf("Não há um código de barras ou o código de barras é inválido\n");
            for (int i = 0; i < altura; i++) {
                free(pixels[i]);
            }
            free(pixels);
            free(codigo_barras);
            return;
        }
    }
    codigo_barras[67] = '\0';

    // Verificar se o código de barras possui os marcadores corretos //
    if (strncmp(codigo_barras, inicio_fim_codigo, 3) != 0 || // Verificar marcador de início //
        strncmp(codigo_barras + 31, separador_centro, 5) != 0 || // Verificar marcador central //
        strncmp(codigo_barras + 64, inicio_fim_codigo, 3) != 0) { // Verificar marcador de fim //
        printf("Não há um código de barras ou o código de barras é inválido\n");
        for (int i = 0; i < altura; i++) {
            free(pixels[i]);
        }
        free(pixels);
        free(codigo_barras);
        return;
    }

    // Verificar se o código de barras tem o tamanho correto //
    if (strlen(codigo_barras) != 67) {
        printf("Não há um código de barras ou o código de barras é inválido\n");
        for (int i = 0; i < altura; i++) {
            free(pixels[i]);
        }
        free(pixels);
        free(codigo_barras);
        return;
    }

    // Alocar memoria para identificador do código de barras //
    int *identificador = NULL;
    identificador = malloc(8 * sizeof(int)); // Identificador tem 8 dígitos //

    // Conversor de L-code //
    for(int i = 0; i < 4; i++){ // 4 dígitos, do L-code //
        char digito_temporario[8] = "";
        for(int j = 0; j < 7; j++){ // 7 barras(bits) por dígito //
            digito_temporario[j] = codigo_barras[3 + i*7 + j]; // 3: 101 (indicador de início) // i*7: posição do dígito // j: posição do bit //
        }
        for(int k = 0; k < 10; k++){ // Transformar o dígito em número no padrão L-code do EAN-8 //
            if(strcmp(digito_temporario,tabela_digitos_esquerda[k]) == 0){
                identificador[i] = k;
                break;
            }
        }
    }

    // Conversor de R-code//
    for(int i = 4; i < 8; i++) { // 4 últimos dígitos, do R-code //
        char digito_temporario[8] = "";
        for(int j = 0; j < 7; j++) { // 7 barras(bits) por dígito //
            digito_temporario[j] = codigo_barras[8 + i*7 + j];  // 8: 101 (marcador de início) + 01010 (marcador central) // i*7: posição do dígito // j: posição do bit //
        }
        for(int k = 0; k < 10; k++) { /// Transformar o dígito em número no padrão L-code do EAN-8 //
            if(strcmp(digito_temporario,tabela_digitos_direita[k]) == 0){
                identificador[i] = k;
                break;
            }
        }
    }
    
    // Validar código de barras usando dígito verificador //
    int soma_par = 0;
    int soma_impar = 0;
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            soma_impar += identificador[i];
        } else {
            soma_par += identificador[i];
        }
    }
    int total = soma_impar * 3 + soma_par; //Ipar tem peso 3, par tem peso 1 //
    int digito_verificador = (10 - (total % 10)) % 10; // Cálculo do dígito verificador //
    if (digito_verificador != identificador[7]) { // o dígito verificador é o ultimo//
        printf("Não há um código de barras ou o código de barras é inválido\n");
            for (int i = 0; i < altura; i++) {
            free(pixels[i]);
        }
        free(pixels);
        free(codigo_barras);
        free(identificador);
        return;
    }

    // Exibir identificador do código de barras //
    printf("Código de barras lido com sucesso:\n");
    for(int i = 0; i < 8; i++) {
        printf("%d", identificador[i]); // Imprimir cada dígito do identificador //
    }
    printf("\n");
    
    // Liberar memória alocada //
    for (int i = 0; i < altura; i++) {
        free(pixels[i]);
    }
    free(pixels);
    free(codigo_barras);
    free(identificador);
}

int main(int argc, char* argv[]) {
    char *nome_arquivo;
    if (argc != 2) {
        printf("\n");
        printf("Erro: Número incorreto de argumentos.\n");
        printf("Digite %s --help para mais informações.\n", argv[0]);
        printf("\n");
        exit(-1);
    } else {
        if (strcmp(argv[1], "--help") == 0) { // Se o usuário solicitar ajuda //
            printf("\n");
            printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
            printf("Lê um código de barras EAN-8 de um arquivo do tipo PBM (P1).\n");
            printf("Argumentos:\n");
            printf("  <nome_do_arquivo>     Nome do arquivo que contém o código de barras.\n\n");
            printf("\n");
            exit(0);
        } else { // Leitura do nome do arquivo //
            nome_arquivo = malloc((strlen(argv[1]) + 1) * sizeof(char)); // Alocar memória para o nome do arquivo //
            strcpy(nome_arquivo,argv[1]); // Nome do arquivo fornecido como argumento //
            if(strstr(argv[1],".pbm") != NULL){ // Se o nome do arquivo no argumento já contém a extensão .pbm //
                extrair_codigo(nome_arquivo); // Chamar função para ler o arquivo //
                free(nome_arquivo); // Liberar memória alocada para o nome do arquivo //
            
            } else { // Se o nome do arquivo no argumento não contém a extensão .pbm //
                nome_arquivo = realloc(nome_arquivo, (strlen(argv[1]) + 5) * sizeof(char)); // Re-alocar memória para adicionar .pbm ao nome do arquivo //
                strcat(nome_arquivo,".pbm"); // Adicionar .pbm ao nome do arquivo //
                extrair_codigo(nome_arquivo); // Chamar função para ler o arquivo //
                free(nome_arquivo); // Liberar memória alocada para o nome do arquivo //
            }
        }
    }
}
