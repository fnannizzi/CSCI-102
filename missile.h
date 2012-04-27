#ifndef MISSILE_H
#define MISSILE_H

#include <QImage>
#include <QRect>
#include "object.h"

class Missile : public Object {
  
 public:
  Missile(int x, int y);
  bool valid;
  void autoMove();
  void setValid(bool);
  
};

Missile::Missile(int x, int y):Object(x,y) {
  image.load("BB.png");
  rect = image.rect();
  rect.translate(x,y);
}

void Missile::autoMove() {
  if(valid){	
    yval = yval - 10;	
    rect.moveTo(xval,yval);
  }	
}	

void Missile::setValid(bool val) {
	valid = val;
}

#endif
