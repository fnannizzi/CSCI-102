#ifndef BUBBLE_H
#define BUBBLE_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Bubble : public Target {
  
 public:
  Bubble(int x, int y, int s, bool l);
  int returnType();
  
};

Bubble::Bubble(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("bubble.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Bubble::returnType() {
  return 1;
}

#endif
