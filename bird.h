#ifndef BIRD_H
#define BIRD_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Bird : public Target {
  
 public:
  Bird(int x, int y, int s, bool l);
  int returnType();
  
};

Bird::Bird(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("bird.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Bird::returnType() {
  return 1;
}	

#endif
