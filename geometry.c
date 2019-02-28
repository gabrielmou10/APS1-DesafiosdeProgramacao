#include "geometry.h"
#include <math.h>
#include <stdlib.h>

int verify(point p, point a, point b) {
  //Se os pontos a e b sao iguais retornar 0
  if (abs(a.x - b.x) < 0.000001 && abs(a.y - b.y) < 0.000001) {
    //Mas caso a=b E p=a entao p esta exatamente sobre a aresta e retornamos 2
    if (abs(a.x - p.x) < 0.000001 && abs(a.y - p.y) < 0.000001) {
      return 2;
    }
    return 0;
  }

  //Calcula dot e cross product e faz comparacoes para edge cases de mesma linha (https://www.lucidar.me/en/mathematics/check-if-a-point-belongs-on-a-line-segment/)
  int ab_x = b.x - a.x;
  int ab_y = b.y - a.y;
  int ap_x = p.x - a.x;
  int ap_y = p.y - a.y;
  int dot = ap_x * ab_x + ap_y * ab_y;
  int cross = ap_y * ab_x - ap_x * ab_y;
  int squareAB = pow(ab_x, 2) + pow(ab_y, 2);
  if (cross == 0 && dot >= 0 && dot <= squareAB) {
    return 2;
  }

  //Vamos agora definir um ponto final de raio para simular um segmento e ver se ele cruza (segmento finalP)
  point finalray;
  finalray.x = p.x + 3000;
  finalray.y = p.y;

  //Variaveis helpers para os calculos abaixo de cruzamento de segmentos. Utilizar as de cima, que sao ints, estava causando floating point exception
  float fab_x = b.x - a.x;
  float fab_y = b.y - a.y;
  float fap_x = a.x - p.x;
  float fap_y = a.y - p.y;

  //https://stackoverflow.com/questions/3838329/how-can-i-check-if-two-segments-intersect
  float r = (((fap_x) * (finalray.y - p.y)) - ((fap_y) * (finalray.x - p.x))) / ((finalray.x - p.x) * (fab_y));
  float s = (((fap_x) * (fab_y)) - ((fap_y) * (fab_x))) / ((finalray.x - p.x) * (fab_y));

  //verifica se o vetor finalP e o vetor AB se cruzam
  if (0 <= r && r <= 1 && 0 <= s && s <= 1) {
    //checagem de vertices, verificando se um movimento no sentido horario (aumento de y) iria atingir uma aresta
    if (p.y == a.y) {
      if (a.y > b.y) {
        return 1;
      } else {
        return 0;
      }
    } else if (p.y == b.y) {
      if (b.y > a.y) {
        return 1;
      } else {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

int inside(point p, point poly[], int n) {

  int collisions = 0;
  //Vamos agora implementar o ray casting e "atirar" raios em multiplas direcoes
  for (int i = 1; i <= n - 1; i++) {
    //Aplicamos nossa funcao verify para cada n(lado do poligono)
    int verifyside = verify(p, poly[i - 1], poly[i]);

    // Caso o ponto estiver em cima de uma aresta retorna 1
    if (verifyside == 2) {
      return 1;
    }
    //Caso nao, somamos o numero de colisoes com arestas do poligono
    if (verifyside == 1) {
      collisions++;
    }
  }

  int finalside = verify(p, poly[n - 1], poly[0]);

  if (finalside == 2) {
    return 1;
  }
  if (finalside == 1) {
    collisions++;
  }

  //Ray casting - verifica se numero de cruzamentos e par ou impar
  //se for par ele nao pertence ao poligono, do contrario ele esta dentro do poligono
  int rest = collisions % 2;
  if (rest == 0) {
    return 0;
  } else {
    return 1;
  }
}
