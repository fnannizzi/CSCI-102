#ifndef DUCK_H
#define DUCK_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Duck : public Target {
  
 public:
  Duck(int x, int y, int s, bool l);
  int returnType();
  
};

Duck::Duck(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("duck.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Duck::returnType() {
  return 2;
}	

#endif
