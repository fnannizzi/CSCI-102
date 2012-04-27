#ifndef TARGET_H
#define TARGET_H

#include <QImage>
#include <QRect>
#include "object.h"

class Target : public Object {
  
 public:
  Target(int x, int y, int s, bool l);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove();
  int speed;
  bool destroyed;
  int returnType();
  bool left;
  
};

Target::Target(int x, int y, int s, bool l):Object(x,y) {
  speed = s;
  destroyed = FALSE;
  left = l;
}

void Target::setRect(QRect rct)
{
  rect = rct;
}

bool Target::isDestroyed()
{
  return destroyed;
}

void Target::setDestroyed(bool destr) {
  destroyed = destr;
}

void Target::autoMove() {
  if(left)	
    xval = xval - speed;
  else
    xval = xval + speed;
      	
  rect.moveTo(xval,yval);	
}

int Target::returnType() {
  return 0;
}	

#endif
