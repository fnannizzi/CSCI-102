#ifndef SHOOTER_H
#define SHOOTER_H

#include <QImage>
#include <QRect>
#include "object.h"

class Shooter : public Object {
  
 public:
  Shooter();
  
 public:
  void moveLeft();
  void moveRight();
  
};

Shooter::Shooter():Object(){
  image.load("shooter.png");
  xval = 380;
  yval = 450;
  rect = image.rect();
  rect.translate(xval,yval);
}

void Shooter::moveLeft() {
  if (rect.left() >= 2){
    xval--;
    rect.moveTo(xval,yval);
  }
}

void Shooter::moveRight() {
  if (rect.right() <= 798){
    xval++;
    rect.moveTo(xval,yval);
  }
}

#endif
