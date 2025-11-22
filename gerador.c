# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "definitions.h"

const char numeros_impressao[10][7][8] = {

    {
        "0000000",
        "0011100",
        "0100010",
        "0100010",
        "0100010",
        "0100010",
        "0011100"
    }, // 0

    {
        "0000000",
        "0001000",
        "0011000",
        "0001000",
        "0001000",
        "0001000",
        "0011100"
    }, // 1

    {
        "0000000",
        "0011100",
        "0100010",
        "0000100",
        "0001000",
        "0010000",
        "0111110"
    }, // 2

    {
        "0000000",
        "0011100",
        "0100010",
        "0000100",
        "0001100",
        "0100010",
        "0011100"
    }, // 3

    {
        "0000000",
        "0000100",
        "0001100",
        "0010100",
        "0111110",
        "0000100",
        "0000100"
    }, // 4

    {
        "0000000",
        "0111110",
        "0100000",
        "0111100",
        "0000010",
        "0100010",
        "0011100"
    }, // 5

    {
        "0000000",
        "0011100",
        "0100010",
        "0100000",
        "0111100",
        "0100010",
        "0011100"
    }, // 6

    {
        "0000000",
        "0111110",
        "0000010",
        "0000100",
        "0001000",
        "0010000",
        "0010000"
    }, // 7

    {
        "0000000",
        "0011100",
        "0100010",
        "0011100",
        "0100010",
        "0100010",
        "0011100"
    }, // 8

    {
        "0000000",
        "0011100",
        "0100010",
        "0100010",
        "0011110",
        "0000010",
        "0011100"
    } // 9

};

void gerador_codigo_barras(FILE *codigo_barras, int codigo[], int espacamento, int quat_pixel_area, int altura_codigo, char *nome_arquivo){
    codigo_barras = fopen(nome_arquivo, "w");
    
    int altura_numeros_impressao = 7*quat_pixel_area;
    int altura_imagem = altura_codigo + altura_numeros_impressao + 2*espacamento;
    int largura_imagem = 2*espacamento + 67*quat_pixel_area;
    
    fprintf(codigo_barras, "P1\n");
    fprintf(codigo_barras, "%d %d\n", largura_imagem, altura_imagem);
    
    // Espaçamento acima do código
    for(int i = 0; i < espacamento; i++){
        for(int i = 0; i < largura_imagem; i++){
            fprintf(codigo_barras, "0");
        }
        fprintf(codigo_barras, "\n");
    }
    
    // Impressão do código de barras
    for(int i = 0; i < altura_codigo; i++){
        
        // Espaçamento da esquerdo
        for(int j = 0; j < espacamento; j++){
            fprintf(codigo_barras, "0");
        }
        
        // Marcador de início
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", inicio_fim_codigo[j]);
            }
        }
        
        // 4 primeiros dígitos
        for(int d = 0; d < 4; d++){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < quat_pixel_area; k++){
                    fprintf(codigo_barras, "%c", tabela_digitos_esquerda[codigo[d]][j]);
                }
            }
        }
        
        // Marcador central
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", separador_centro[j]);
            }
        }
        
        // 4 últimos dígitos
        for(int d = 4; d < 8; d++){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < quat_pixel_area; k++){
                    fprintf(codigo_barras, "%c", tabela_digitos_direita[codigo[d]][j]);
                }
            }
        }
        
        // Marcador de fim
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", inicio_fim_codigo[j]);
            }
        }
        
        // Espaçamento direito
        for(int j = 0; j < espacamento; j++){
            fprintf(codigo_barras, "0");
        }

        fprintf(codigo_barras, "\n");
    }

    // Impressão dos números abaixo do código de barras
    for(int i = 0; i < altura_numeros_impressao; i++){
        
        int camada_digito = i / quat_pixel_area; // Linha de bits da fonte dos números que será imprimida
        
        // Espaçamento da esquerdo
        for(int j = 0; j < espacamento; j++){
            fprintf(codigo_barras, "0");
        }

        // Marcador de início
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", inicio_fim_codigo[j]);
            }
        }

        // 4 primeiros números
        for(int d = 0; d < 4; d++){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < quat_pixel_area; k++){
                    fprintf(codigo_barras, "%c", numeros_impressao[codigo[d]][camada_digito][j]);
                }
            }
        }

        // Marcador central
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", separador_centro[j]);
            }
        }

        // 4 últimos números
        for(int d = 4; d < 8; d++){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < quat_pixel_area; k++){
                    fprintf(codigo_barras, "%c", numeros_impressao[codigo[d]][camada_digito][j]);
                }
            }
        }

        // Marcador de fim
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < quat_pixel_area; k++){
                fprintf(codigo_barras, "%c", inicio_fim_codigo[j]);
            }
        }

        // Espaçamento direito
        for(int j = 0; j < espacamento; j++){
            fprintf(codigo_barras, "0");
        }

        fprintf(codigo_barras, "\n");
    }

    // Espaçamento abaixo do código
    for(int i = 0; i < espacamento; i++){
        for(int i = 0; i < largura_imagem; i++){
            fprintf(codigo_barras, "0");
        }
        fprintf(codigo_barras, "\n");
    }
}

int main(int argc, char* argv[]){
    int codigo[8];
    int soma_digito_identificador = 0;
    int espacamento = 4; // Padrão de 4 pixels de espaçamento
    int quat_pixel_area = 3; // Padrão de 3 pixels de quantidade de pixels por área
    int altura_codigo = 50; // Padrao de 50 pixels de altura do código de barras
    
    char *nome_arquivo;
    nome_arquivo = calloc(20, sizeof(char));
    strcpy(nome_arquivo, "codigo_sem_nome.pbm");  // Nome do arquivo caso o usuario não especifique um

    FILE *codigo_barras;

    if(argc < 2){
        printf("\n");
        printf("Erro: Número insuficiente de argumentos.\n");
        printf("Digite %s --help para mais informações.\n", argv[0]);
        printf("\n");
        exit(-1);
    }else{
        if(strcmp(argv[1], "--help") == 0){
            printf("\n");
            printf("Uso: %s <código EAN-8> [opções]\n", argv[0]);
            printf("Gera um código de barras EAN-8 a partir do código fornecido.\n\n");
            printf("Argumentos:\n");
            printf("  <código EAN-8>        Código numérico de 8 dígitos para gerar o código de barras.\n\n");
            printf("Opções:\n");
            printf("  e:<valor>             Define o espaçamento da imagem (padrão: 4).\n");
            printf("  a:<valor>             Define a quantidade de pixels por área (padrão: 3).\n");
            printf("  h:<valor>             Define a altura do código de barras (padrão: 50).\n");
            printf("  n:<nome_arquivo>      Define o nome do arquivo de saída.\n");
            printf("\n");
            exit(0);
        }

        if(strlen(argv[1]) != 8){
            printf("\n");
            printf("Erro: Código inválido! O código EAN-8 precisa ter 8 dígitos.\n");
            printf("\n");
            exit(-1);
        }
        for(int i = 0; i < 8; i++){
            if(!isdigit(argv[1][i])){
                printf("\n");
                printf("Erro: Código inválido! O código EAN-8 possui apenas dígitos numéricos.\n");
                printf("\n");
                exit(-1);
            }
            codigo[i] = argv[1][i] - '0'; // Operação com o código do caractere na tabela ASCII
        }
        
        for(int i = 1; i <= 7; i++){
            if(i % 2 == 0){
                soma_digito_identificador += codigo[i-1];
            }else{
                soma_digito_identificador += codigo[i-1]*3;
            }
        }
        int digito_identificador = 10 - (soma_digito_identificador % 10);
        if(digito_identificador == 10) digito_identificador = 0;
        if(digito_identificador != codigo[7]){
            printf("\n");
            printf("Erro: Código inválido! Dígito verificador não corresnponde com os valores anteriores.\n");
            printf("\n");
            exit(-1);
        }

        for(int i = 2; i < argc; i++){
            if(argv[i][0] == 'e' && argv[i][1] == ':'){
                espacamento = atoi(&argv[i][2]);
            }
            else if(argv[i][0] == 'a' && argv[i][1] == ':'){
                quat_pixel_area = atoi(&argv[i][2]);
            }
            else if(argv[i][0] == 'h' && argv[i][1] == ':'){
                altura_codigo = atoi(&argv[i][2]);
            }
            else if(argv[i][0] == 'n' && argv[i][1] == ':'){
                nome_arquivo = realloc(nome_arquivo, strlen(&argv[i][2]) * sizeof(char));
                strcpy(nome_arquivo, &argv[i][2]);
                strcat(nome_arquivo, ".pbm");
            }else{
                printf("\n");
                printf("Erro: Há argumentos inválidos.\n");
                printf("Digite %s --help para mais informações.\n", argv[0]);
                printf("\n");
                exit(-1);
            }
        }

        codigo_barras = fopen(nome_arquivo, "r");
        if(codigo_barras != NULL){
            char opcao;
            printf("\n");
            printf("Aviso: O arquivo %s já existe.\n", nome_arquivo);
            printf("Deseja sobrescrevê-lo? (s/n): ");
            scanf(" %c", &opcao);
            if(opcao == 's' || opcao == 'S'){
                fclose(codigo_barras);
                gerador_codigo_barras(codigo_barras, codigo, espacamento, quat_pixel_area, altura_codigo, nome_arquivo);
                printf("\n");
                printf("Arquivo %s sobrescrito com sucesso.\n", nome_arquivo);
                printf("\n");
                free(nome_arquivo);
                exit(0);
            }
            else if(opcao == 'n' || opcao == 'N'){
                printf("\n");
                printf("Arquivo já existente.\n");
                printf("\n");
                fclose(codigo_barras);
                free(nome_arquivo);
                exit(-1);
            }else{
                printf("\n");
                printf("Erro: Opção inválida.\n");
                printf("\n");
                fclose(codigo_barras);
                free(nome_arquivo);
                exit(-1);
            }
        }else{
            gerador_codigo_barras(codigo_barras, codigo, espacamento, quat_pixel_area, altura_codigo, nome_arquivo);
            printf("\n");
            printf("Arquivo %s criado com sucesso.\n", nome_arquivo);
            printf("\n");
            free(nome_arquivo);
            exit(0);
        }
    }

}


