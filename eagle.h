#ifndef EAGLE_H
#define EAGLE_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Eagle : public Target {
  
 public:
  Eagle(int x, int y, int s, bool l);
  int returnType();
  
};

Eagle::Eagle(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("eagle.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Eagle::returnType() {
  return 2;
}	

#endif
