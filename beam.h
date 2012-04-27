#ifndef BEAM_H
#define BEAM_H

#include <QImage>
#include <QRect>
#include <math.h>
#include "object.h"

class Beam : public Object {
  
 public:
  Beam(int x, int y);
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

Beam::Beam(int x, int y):Object(x,y) {
  image.load("beam.png");
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
}

void Beam::setRect(QRect rct) {
  rect = rct;
}

bool Beam::isDestroyed() {
  return destroyed;
}

void Beam::setDestroyed(bool destr) {
  destroyed = destr;
}

void Beam::autoMove(int x) {
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

void Beam::setValid(bool val) {
  valid = val;
}

#endif
