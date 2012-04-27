// Author: Francesca Nannizzi
// Class: CS102
// Date: 04.08.12
// - - - - - - - - - - - - - -

#include "game.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QLayout>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv); 
    
  Game window;  
  window.setWindowTitle("Shooter");
  window.resize(800,500);
  window.startGame();
  window.show();

  return app.exec();
}


