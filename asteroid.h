#ifndef ASTEROID_H
#define ASTEROID_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Asteroid : public Target {
  
 public:
  Asteroid(int x, int y, int s, bool l);
  int returnType();
  
};

Asteroid::Asteroid(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("asteroid.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Asteroid::returnType() {
  return 1;
}	

#endif
