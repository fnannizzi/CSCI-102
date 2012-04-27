#ifndef METEOR_H
#define METEOR_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "target.h"

class Meteor : public Target {
  
 public:
  Meteor(int x, int y, int s, bool l);
  int returnType();
  
};

Meteor::Meteor(int x, int y, int s, bool l):Target(x,y,s,l) {
  image.load("meteor.png");
  if(l)
    image = image.transformed(QMatrix().scale(-1,1));
  rect = image.rect();
  rect.translate(x,y);
}

int Meteor::returnType() {
  return 1;
}	

#endif
