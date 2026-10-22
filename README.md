# Bagunceitor — Confusão e Difusão de Imagens em C

Programa em C que "bagunça" uma imagem aplicando as duas operações clássicas de cifras, **confusão** e **difusão**, e depois desfaz o processo para recuperar a imagem original.

## Como funciona

1. **Confusão:** cada canal de cor (R, G, B) de cada pixel passa por um XOR com uma chave fixa, escondendo a relação entre a cor original e a cor final.
2. **Difusão:** os pixels de cada linha são deslocados com um padrão que depende da própria linha, espalhando a informação pela imagem.
3. **Reversão:** as operações inversas são aplicadas na ordem contrária (desdifundir e depois desconfundir), gerando de volta a imagem original.

O programa gera dois arquivos: `saida.png` (imagem embaralhada) e `saidaReversa.png` (imagem recuperada).

## Destaques técnicos

- Manipulação direta de memória com `malloc`, `memset` e `free`
- Uso de ponteiros para matrizes de tamanho variável (VLA) para tratar o vetor de pixels como uma matriz 2D
- Leitura e escrita de imagens com as bibliotecas [stb_image](https://github.com/nothings/stb)
- Build multiplataforma com **Makefile** (Windows/MinGW, Linux e macOS) e **CMake**

## Como compilar e rodar

```bash
cd bagunceitor
make
./bagunceitor predio32.jpg      # ou mercadoPublico.jpg
```

## Equipe

Trabalho da disciplina de Programação de Baixo Nível (PUCRS), feito por Eduardo Boeira, Eduardo Ortiz e Pablo Acosta.
