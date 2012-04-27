#ifndef UFO_H
#define UFO_H

#include <QImage>
#include <QRect>
#include "object.h"
#include "beam.h"

class UFO : public Object {
  
 public:
  UFO(int x, int y, int s);
  void resetState();
  bool isDestroyed();
  void setDestroyed(bool);
  void setRect(QRect);
  void autoMove(int x);
  
  Beam *beams[20];
  int numBeams;
  int cnt;
  int speed;
  bool destroyed;
  
};

UFO::UFO(int x, int y, int s):Object(x,y) {
  image.load("ufo.png");
  speed = s;
  destroyed = FALSE;
  rect = image.rect();
  rect.translate(x,y);
  numBeams = 0;
  cnt = 0;
}

void UFO::setRect(QRect rct) {
  rect = rct;
}

bool UFO::isDestroyed() {
  return destroyed;
}

void UFO::setDestroyed(bool destr) {
  destroyed = destr;
}

void UFO::autoMove(int x) {
  cnt++;
  if(xval < (x - 150))
    xval = xval + speed;
  //else
    //xval = xval - speed;
	
  rect.moveTo(xval,yval);	

  if((cnt % 50) == 0) {
    beams[numBeams] = new Beam(xval+10,yval+10);
    beams[numBeams]->setValid(TRUE);
    numBeams++;
  }

  for(int i = 0; i < numBeams; i++){
    if(beams[i]->valid)
      beams[i]->autoMove(x);
  }

}	

#endif
