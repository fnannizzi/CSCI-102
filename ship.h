#ifndef SHIP_H
#define SHIP_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Ship : public Target {
  
 public:
  Ship(int x, int y, int s, bool l);
  int returnType();
  
};

Ship::Ship(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("ship.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Ship::returnType() {
  return 2;
}	

#endif
