#include <stdio.h>
#include "forca.h"
#include <stdlib.h>
#include <time.h>
#include <string.h> /*Biblioteca responsavel por strlen()*/
  /* A funcao strlen() busca o tamanho de um array */

/* Variaveis globais */
char palavra_secreta[TAMANHO_PALAVRA];
char chutes[26];
int chutes_dados = 0;

void abertura (){
  printf("***************************\n");
  printf("*      Jogo da Forca      *\n");
  printf("***************************\n\n");

  printf("Seja bem vindo a este tradicionalissimo jogo! Voce devera tentar adivinhar a palavra secreta antes de ser enforcado, tome cuidado pois no 5 erro, voce perdera!\n\n");
  }

void chuta () {
  char chute;
  scanf(" %c", &chute); /* Para que o scanf ignore o enter, voce precisa adicionar um espaco antes do %c, pois tudo pode ser considerado um char, inclusive o proprio enter */
  printf("\n");
  chutes[(chutes_dados)] = chute;
    (chutes_dados) ++;
}

int ja_chutou(char letra){
  int achou = 0;

  for (int j = 0; j < chutes_dados; j++){
    if (chutes[j] == letra){
      achou = 1;
      break;
    }
  }
  return achou;
}

void desenha_forca () {

  int erros = chutes_errados();

  /* Abaixo são If's ternarios, onde o print é exbido um se verdadeiro ou outro se falso */
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

  for (int i = 0; i < strlen(palavra_secreta); i++){
    int achou = ja_chutou(palavra_secreta[i]);
    
    if (achou){
      printf("%c ", palavra_secreta[i]);
    }
    else {
      printf("_ ");
    }
  }
  printf("\n\n");
}

void adiciona_palavra () {
  char quer;
  
  printf("Você deseja adicionar uma nova palavra no jogo? (S/N)\n");
  scanf(" %c", &quer);

  if (quer == 'S') {
    char nova_palavra[TAMANHO_PALAVRA];
    
    printf("\nQual a nova palavra?\n");
    scanf("%s", nova_palavra);

    FILE* f;
    f = fopen("palavras.txt", "r+");

  if (f == 0){
    printf("Desculpe, banco de dados indisponível :(\n\n");
    exit(1);
  }

    int qtd;
    fscanf(f,"%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", nova_palavra);

    printf("\nPalavra adicionada com sucesso!\n");

    fclose(f);
  }
}

void escolhe_palavra (){
  FILE* f;
  
  f = fopen("palavras.txt", "r"); /* Abre o arquivo */
  if (f == 0){
    printf("Desculpe, banco de dados indisponível :(\n\n");
    
    exit(1); /* Com a função exit (>=1) o programa finalizará com a informação que o programa deu problema, com (0) fianalizará com a informação que tudo ocorreu bem */
  }

  int qtd_de_palavras; /* Verificando a quantidade de palavras no arquivo */
  fscanf(f, "%d", &qtd_de_palavras);
  
  srand(time(0));
  int randomico = rand() % qtd_de_palavras;

  for (int i = 0; i <= randomico; i++){
    fscanf(f, "%s", palavra_secreta);
  }

  fclose(f);
}

int acertou () {
  for (int i = 0; i < strlen(palavra_secreta); i++){
    if (!ja_chutou(palavra_secreta[i])){ /* Se não chutei alguma letra existente na palavra secreta, ainda não ganhei */
      return 0;
    }
  }
  return 1; /* Se todas as letras da palavra secreta foram chutadas, retornará verdadeiro e o usuario terá ganhado */
}

int chutes_errados () {
  int erros = 0;
  
  for (int i = 0; i < chutes_dados; i++){
    int existe = 0;
    
    /* Dentro dessa função, o programa irá avaliar se a letra chutada pelo usuario existe dentro da palavra secreta, caso exista, a variavel existe receberá 1 se tornando verdadeira. Se não, existe será falso, e adicionará a variavel erros +1 */
    
    for (int j = 0; j < strlen(palavra_secreta); j++){
      if (chutes[i] == palavra_secreta[j]){
        
        existe = 1;
        break;
      }
    }
    if (!existe) erros++; /* !existe é a negação da váriavel, ou seja, ela é falsa */
  }
  
  return erros;
}

int enforcou () {

  return chutes_errados() >= 5; /* A função retornará verdadeiro (=1) ou falso (=0) para assim, quem chamar a função, seguir como desejar */
}

int main() {
  escolhe_palavra();
  abertura ();

  do{
    desenha_forca ();
    chuta();
    
  }  while (!enforcou() && !acertou()); /*! é a negação de uma variável*/

  if (acertou()){
    printf("\nParabéns, voce ganhou!\n\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

  }
  else {
    printf("\nVoce perdeu, a palavra secreta era %s\n\n", palavra_secreta);
    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
    printf("                          \n\n");
  }
  
  adiciona_palavra();

  printf("\n\nObrigado por jogar o nosso jogo!\n");
}