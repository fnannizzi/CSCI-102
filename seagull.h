#ifndef GULL_H
#define GULL_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "poop.h"

class Gull : public Object {
  
 public:
  Gull(int x, int y, int s);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove(int x);
  
  Poop *poops[20];
  int numPoops;
  int cnt;
  int speed;
  bool destroyed;
  
};

Gull::Gull(int x, int y, int s):Object(x,y) {
  image.load("gull.png");
  speed = s;
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
  numPoops = 0;
  cnt = 0;
}

void Gull::setRect(QRect rct) {
  rect = rct;
}

bool Gull::isDestroyed() {
  return destroyed;
}

void Gull::setDestroyed(bool destr) {
  destroyed = destr;
}

void Gull::autoMove(int x) {
  cnt++;
  xval = xval + speed;
	
  rect.moveTo(xval,yval);	

  if((cnt % 25) == 0) {
    poops[numPoops] = new Poop(xval+10,yval+10);
    poops[numPoops]->setValid(TRUE);
    numPoops++;
  }

  for(int i = 0; i < numPoops; i++){
    if(poops[i]->valid)
      poops[i]->autoMove(x);
  }

}	

#endif
