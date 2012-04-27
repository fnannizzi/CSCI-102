#ifndef BOLT_H
#define BOLT_H

#include <QImage>
#include <QRect>
#include <math.h>
#include "object.h"

class Bolt : public Object {
  
 public:
  Bolt(int x, int y);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove(int x);
  void setValid(bool);
  bool getValid();
  
  bool valid;
  bool destroyed;
  int xdist;
  int path;
  bool tracked;
  bool xless;
  
};

Bolt::Bolt(int x, int y):Object(x,y) {
  image.load("bolt.png");
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
  valid = FALSE;
  tracked = FALSE;
  xless = FALSE;
}

void Bolt::setRect(QRect rct)
{
  rect = rct;
}

bool Bolt::isDestroyed()
{
  return destroyed;
}

void Bolt::setDestroyed(bool destr) {
  destroyed = destr;
}

void Bolt::autoMove(int x) {
    if(tracked) {
	tracked = FALSE;
	if(xless)
	   xval = xval - 5;
	else
	   xval = xval + 5;
    }
    else{
      if(xval < x){	
        xval = xval + 5;
	xless = FALSE;
      }
      else{
        xval = xval - 5;
	xless = TRUE;
      }
      tracked = TRUE;
    }
    yval = yval + 4;	
    rect.moveTo(xval,yval);	
}	

void Bolt::setValid(bool val) {
  valid = val;
}

bool Bolt::getValid() {
  return valid;
}


#endif
