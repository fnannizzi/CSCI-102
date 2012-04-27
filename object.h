#ifndef OBJECT_H
#define OBJECT_H

#include <QImage>
#include <QRect>

class Object {
 public:

   Object();
   Object(int y);
   Object(int x, int y);
   ~Object();	
   QRect getRect();
   QImage & getImage();
   int getX();
   	
   QImage image;
   QRect rect;
   int xval, yval;

 };

Object::Object(){
  xval = 0;
  yval = 0;
}

Object::Object(int y){
  xval = 0;
  yval = y;
}

Object::Object(int x, int y){
  xval = x;
  yval = y;
}

Object::~Object(){}

QRect Object::getRect() {
  return rect;
}

QImage & Object::getImage() {
  return image;
}

int Object::getX() {
  return xval;
}

#endif
