#ifndef FISH_H
#define FISH_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Fish : public Target {
  
 public:
  Fish(int x, int y, int s, bool l);
  int returnType();
  
};

Fish::Fish(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("fish.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Fish::returnType() {
  return 1;
}

#endif
