#ifndef GOOSE_H
#define GOOSE_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Goose : public Target {
  
 public:
  Goose(int x, int y, int s, bool l);
  int returnType();
  
};

Goose::Goose(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("goose.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Goose::returnType() {
  return 1;
}	

#endif
