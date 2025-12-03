# Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade
![Git Hub](https://img.shields.io/badge/github-repository-blue?logo=github)
![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![ITP-UFRN](https://img.shields.io/badge/ITP-UFRN-blue.svg)

## Sumário

- [Introdução](#introdução)
- [Uso do gerador de código de barras EAN-8](#uso-do-gerador-de-código-de-barras-EAN-8)
- [Uso do leitor de código de barras EAN-8](#uso-do-leitor-de-código-de-barras-EAN-8)
- [Integrantes/Colaboradores](#integrantescolaboradores)

## Introdução

Projeto de gerador e leitor de códigos de barras padrão EAN-8 para a matéria de Introdução às Técnicas de Programação do curso de BTI/UFRN.

## Uso do gerador de código de barras EAN-8:

1. Certifique-se que o comando `gcc` está presente no seu sistema operacional;

2. Caso tenha o comando `git` instalado no seu sistema operacional, copie e execute o seguinte comando no seu terminal:
``` bash
git clone https://github.com/victordantas703-coder/Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade.git
```

ou baixe o arquivo compactado do projeto [por aqui](https://github.com/victordantas703-coder/Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade/archive/refs/heads/main.zip) e extraia a pasta contida nele;

3. No terminal, acesse a pasta onde os arquivos `gerador.c` e `definitions.h` estão localizados usando o comando `cd`;

4. Execute o seguinte comando: `gcc gerador.c -o <nome_do_executável>`;

5. Por fim, crie um código de barras EAN-8 executando o novo arquivo criado com `<./<nome_do_executável> <código EAN-8> [opções]`.
            

Argumentos:
  
 - `<código EAN-8>`        Código numérico de 8 dígitos para gerar o código de barras.

Opções:
  
 - `e:<valor>`             Define o espaçamento da imagem (padrão: 4)
  
 - `a:<valor>`             Define a quantidade de pixels por área (padrão: 3)
  
 - `h:<valor>`             Define a altura do código de barras (padrão: 50)
  
 - `n:<nome_arquivo>`      Define o nome do arquivo de saída


## Uso do leitor de código de barras EAN-8:

1. Certifique-se que o comando `gcc` está presente no seu sistema operacional;

2. Caso tenha o comando `git` instalado no seu sistema operacional, copie e execute o seguinte comando no seu terminal:
``` bash
git clone https://github.com/victordantas703-coder/Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade.git
```

ou baixe o arquivo compactado do projeto [por aqui](https://github.com/victordantas703-coder/Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade/archive/refs/heads/main.zip) e extraia a pasta contida nele;

3. No terminal, acesse a pasta onde os arquivos `leitor.c` e `definitions.h` estão localizados usando o comando `cd`;

4. Execute o seguinte comando: `gcc leitor.c -o <nome_do_executável>`;

5. Por fim, leia um código de barras EAN-8 executando o novo arquivo criado com `<./<nome_do_executável> <nome_do_arquivo_pbm>`.

Argumentos:
  
 - `<nome_do_arquivo_pbm>`        Nome do arquivo `.pbm` contendo o código de barras para tradução.


## Integrantes/Colaboradores:

PEDRO AUGUSTO CARVALHO DE FREITAS GOUVEIA FIDALGO

VICTOR MATHEUS DE ABREU DANTAS
