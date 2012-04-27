#ifndef EEL_H
#define EEL_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "bolt.h"

class Eel : public Object {
  
 public:
  Eel(int x, int y, int s);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove(int x);
  int getBoltX(int i);
  
  Bolt *bolts[20];
  int numBolts;
  int cnt;
  int speed;
  bool destroyed;
  
};

Eel::Eel(int x, int y, int s):Object(x,y) {
  image.load("eel.png");
  speed = s;
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
  numBolts = 0;
  cnt = 0;
}

void Eel::setRect(QRect rct)
{
  rect = rct;
}

bool Eel::isDestroyed()
{
  return destroyed;
}

void Eel::setDestroyed(bool destr) {
  destroyed = destr;
}

void Eel::autoMove(int x) {
  cnt++;
  xval = xval + speed;
	
  rect.moveTo(xval,yval);	

  if((cnt % 25) == 0) {
    bolts[numBolts] = new Bolt(xval+10,yval+10);
    bolts[numBolts]->setValid(TRUE);
    numBolts++;
  }

  for(int i = 0; i < numBolts; i++){
    if(bolts[i]->valid)
      bolts[i]->autoMove(x);
  }

}

int Eel::getBoltX(int i) {
  return bolts[i]->getX();
}	

#endif
