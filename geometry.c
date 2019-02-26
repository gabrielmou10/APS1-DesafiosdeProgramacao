#include <math.h>

#include "geometry.h"

int verify(point p, point a, point b) {
  if (a.x == b.x && a.y == b.y){
    if (p.x == a.x $$ p.y == a.y){
      return 2;
    }
    return 0;
  } 

  

  return 0;
}

int inside(point p, point poly[], int n) {
  return 0;
}
