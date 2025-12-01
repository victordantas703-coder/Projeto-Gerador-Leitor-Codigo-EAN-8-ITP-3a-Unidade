# Projeto-Gerador-Leitor-Codigo-EAN-8-ITP-3a-Unidade
Projeto de gerador e leitor de códigos de barras padrão EAN-8 para a matéria de Introdução às Técnicas de Programação do curso de BTI/UFRN

## Uso do gerador de código EAN-8:

1. Certifique-se que o comando `gcc` está presente no seu sistema operacional;

2. No terminal, acesse a pasta onde o arquivo gerador.c está localizado;

3. Execute o seguinte comando: `gcc gerador.c -o <nome_do_exetável>`;

4. Por fim, execute o novo arquivo criado com `<./<nome_do_exetável> <código EAN-8> [opções]`.
            

Argumentos:
  
  `<código EAN-8>`        Código numérico de 8 dígitos para gerar o código de barras.

Opções:
  
  `e:<valor>`             Define o espaçamento da imagem (padrão: 4)
  
  `a:<valor>`             Define a quantidade de pixels por área (padrão: 3)
  
  `h:<valor>`             Define a altura do código de barras (padrão: 50)
  
  `n:<nome_arquivo>`      Define o nome do arquivo de saída


## Uso do leitor de código EAN-8:
  


## Integrantes/Colaboradores:

PEDRO AUGUSTO CARVALHO DE FREITAS GOUVEIA FIDALGO

VICTOR MATHEUS DE ABREU DANTAS
