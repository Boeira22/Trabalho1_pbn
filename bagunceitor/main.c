// para exec:
// .\bagunceitor.exe .\predio32.jpg OU .\bagunceitor.exe .\mercadoPublico.jpg

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image_write.h>
#include <stb_image.h>
#include <math.h>

// Um pixel Pixel (24 bits)
typedef struct {
  unsigned char r, g, b;
} Pixel;

// Uma imagem Pixel
typedef struct {
  int width, height;  // largura, altura
  int channels;       // qtd de canais (3 , R G B)
  Pixel* pixels;
} Img;

// As 2 imagens, entrada (que vai ser alterada) saída (que vai receber a entrada modificada)
Img in, out, aux, reversa;

// Protótipos
void load(char* name, Img* pic);
void confundir(Pixel* src, Pixel* dst, int w, int h);
void difundir(Pixel* src, Pixel* dst, int w, int h);
void desconfundir(Pixel* src, Pixel* dst, int w, int h);
void desdifundir(Pixel* src, Pixel* dst, int w, int h);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("bagunceitor [origem]\n");
    exit(1);
  }

  // Carrega a imagem original
  load(argv[1], &in);

  // Exibe as dimensões na tela, para conferência
  printf("Origem   : %s %d x %d\n", argv[1], in.width, in.height);

  printf("Processando...\n");

  // Cria imagem de saída e "zera" ela
  int tam = in.width * in.height; //quantos pixels a imagem tem
  out = in;
  out.pixels = malloc(tam * sizeof(Pixel)); // pede pra memoria pelo tamanho de pixels
  memset(out.pixels, 0, tam * sizeof(Pixel)); // preenche cm 0

  aux = in; //buffer auxiliar
  aux.pixels = malloc(tam * sizeof(Pixel));

  reversa = in;
  reversa.pixels = malloc(tam * sizeof(Pixel));

  confundir(in.pixels, aux.pixels, in.width, in.height); // original manda pro aux
  difundir(aux.pixels, out.pixels, in.width, in.height); // aux manda pra saida

  desconfundir(out.pixels, aux.pixels, out.width, out.height);
  desdifundir(aux.pixels, reversa.pixels, out.width, out.height);

  // Grava a imagem como PNG para registro
  stbi_write_png("saida.png", out.width, out.height, 3, out.pixels, 0);
  stbi_write_png("saidaReversa.png", reversa.width, reversa.height, 3, reversa.pixels, 0);

  free(in.pixels);
  free(out.pixels);
  free(aux.pixels);
  free(reversa.pixels);
}

void confundir(Pixel* src, Pixel* dst, int w, int h){
  Pixel(*pin)[w] = (Pixel(*)[w])src; //cast (src = onde ler)
  Pixel(*pout)[w] = (Pixel(*)[w])dst; //cast (dst = onde escrever)
    for (int i = 0; i < h; i++) { //linha
    for (int j = 0; j < w; j++) { //coluna
      pout[i][j].r = pin[i][j].r ^ 113;
      pout[i][j].g = pin[i][j].g ^ 50;
      pout[i][j].b = pin[i][j].b ^ 222;
    }
  }
}

void difundir(Pixel* src, Pixel* dst, int w, int h){
  Pixel(*pin)[w] = (Pixel(*)[w])src;
  Pixel(*pout)[w] = (Pixel(*)[w])dst;
    for (int i = 0; i < h; i++) { //linha
    for (int j = 0; j < w; j++) { //coluna
      pout[i][j] = pin[i][(j+i*2)%w];
    }
  }
}

void desconfundir(Pixel* src, Pixel* dst, int w, int h){
  Pixel(*pin)[w] = (Pixel(*)[w])src; //cast 
  Pixel(*pout)[w] = (Pixel(*)[w])dst; 
    for (int i = 0; i < h; i++) { //linha
    for (int j = 0; j < w; j++) { //coluna
      pout[i][j].r = pin[i][j].r ^ 113; //aplicar dnv volta 
      pout[i][j].g = pin[i][j].g ^ 50;
      pout[i][j].b = pin[i][j].b ^ 222;
    }
  }
}

void desdifundir(Pixel* src, Pixel* dst, int w, int h){
   Pixel(*pin)[w] = (Pixel(*)[w])src; //cast
  Pixel(*pout)[w] = (Pixel(*)[w])dst;
    for (int i = 0; i < h; i++) { //linha
    for (int j = 0; j < w; j++) { //coluna
      pout[i][(j+i*2)%w] = pin[i][j];
    }
  }
}

void load(char* name, Img* pic) {
  pic->pixels =
      (Pixel*)stbi_load(name, &pic->width, &pic->height, &pic->channels, 0);
  if (!pic->pixels) {
    printf("Erro de leitura: %s\n", stbi_failure_reason());
    exit(1);
  }
  printf("Load: %d x %d x %d\n", pic->width, pic->height, pic->channels);
  // Exibe um bloco de 8 x 8 pixels em hexadecimal (teste)
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("[%02X %02X %02X] ", pic->pixels[i].r, pic->pixels[i].g,
             pic->pixels[i].b);
    }
    printf("\n");
  }
}

/*
void voltar()
      pout[i][j].r = pin[i][j].r ^ 113;
      pout[i][j].g = pin[i][j].g ^ 2017;
      pout[i][j].b = pin[i][j].b ^ 1995;

      pout[i][j].r = pout[i][j].b + (i * 15) + (j * 3);
      pout[i][j].g = pout[i][j].r + (i * 23) + (j * 5);
      pout[i][j].b = pout[i][j].g + (i * 7) + (j);
*/