#ifndef POOP_H
#define POOP_H

#include <QImage>
#include <QRect>
#include <math.h>
#include "object.h"

class Poop : public Object {
  
 public:
  Poop(int x, int y);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove(int x);
  bool valid;
  void setValid(bool);
  
 private:
  bool destroyed;
  int xdist;
  int path;
  bool tracked;
  bool xless;
  
};

Poop::Poop(int x, int y):Object(x,y) {
  image.load("poop.png");
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
}

void Poop::setRect(QRect rct) {
  rect = rct;
}

bool Poop::isDestroyed() {
  return destroyed;
}

void Poop::setDestroyed(bool destr) {
  destroyed = destr;
}

void Poop::autoMove(int x) {
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

void Poop::setValid(bool val) {
  valid = val;
}

#endif
