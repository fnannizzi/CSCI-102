#ifndef GAME_H
#define GAME_H

#include "shooter.h"
#include "object.h"
#include "bolt.h"
#include "poop.h"
#include "beam.h"
#include "duck.h"
#include "missile.h"
#include "fish.h"
#include "eel.h"
#include "bubble.h"
#include "seagull.h"
#include "goose.h"
#include "eagle.h"
#include "bird.h"
#include "ship.h"
#include "meteor.h"
#include "asteroid.h"
#include "ufo.h"
#include "target.h"
#include <time.h>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QApplication>
#include <QPixmap>
#include <QPalette>

class Game : public QWidget {
  
 public:
  Game(QWidget *parent = 0);
  ~Game();
  void startGame();
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void keyPressEvent(QKeyEvent *event);
  
  void pauseGame();
  void launchMissile();
  void stopGame();
  void victory();
  void checkCollision(int i);
  int score;
  int lives;
  
 private:
  int x;
  int timerId;
  int numMissiles;
  Target *targets[7];
  Eel *eels[2];
  Gull *gulls[2];
  UFO *UFOs[2];
  Shooter *shooter;
  Missile *missiles[80];
  
  void newDuck(int i);
  bool duckLeft;
  void newFish(int i);
  bool fishLeft;
  void newEel(int i);
  bool eelLeft;
  void newBubble(int i);
  bool bubbleLeft;
  void newGull(int i);
  bool gullLeft;
  void newEagle(int i);
  bool eagleLeft;
  void newBird(int i);
  bool birdLeft;
  void newGoose(int i);
  bool gooseLeft;
  void newShip(int i);
  bool shipLeft;
  void newAsteroid(int i);
  bool asteroidLeft;
  void newMeteor(int i);
  bool meteorLeft;
  void newUFO(int i);
  bool gameOver;
  bool gameWon;
  bool gameStarted;
  bool paused;
  bool level1;
  bool level2;
  bool level3;
  
};

static const int numEels = 2;
static const int numGulls = 2;
static const int numTargets = 6;
static const int numUFOs = 1;

Game::Game(QWidget *parent): QWidget(parent) { // constructor
  qApp->setStyleSheet("QWidget {background-image: url(./pond.png) }");  

  x = 0;
  gameOver = FALSE;
  gameWon = FALSE;
  paused = FALSE;
  gameStarted = FALSE;
  duckLeft = FALSE;
  fishLeft = FALSE;
  eelLeft = FALSE;
  bubbleLeft = FALSE;
  gullLeft = FALSE;
  eagleLeft = FALSE;
  birdLeft = FALSE;
  gooseLeft = FALSE;
  shooter = new Shooter();
  numMissiles = 0;
  lives = 5;
  score = 0;
  level1 = TRUE;
  level2 = FALSE;
  level3 = FALSE;
  for(int i = 0; i < numEels; i++){
    eels[i] = NULL;
  }  
}

Game::~Game() { // destructor
  delete shooter;
  for (int i = 0; i < numEels; i++) {
    delete eels[i];
  }
  for (int i = 0; i < numGulls; i++) {
    delete gulls[i];
  }
  for (int i = 0; i < numTargets; i++) {
    delete targets[i];
  }
  for(int i = 0; i < numUFOs; i++){
    delete UFOs[i];
  }
}

void Game::paintEvent(QPaintEvent *event) { // paints objects
  QPainter painter(this);
  
  if (gameOver) { // game lost, display game over screen
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Game Over");
    
    painter.setFont(font);
    int h = height();
    int w = width();
    
    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Game Over");
  }
  else if(gameWon) { // game won, display victory screen
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Victory");
    
    painter.setFont(font);
    int h = height();
    int w = width();
    
    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Victory");
  }
  else { // game still in play mode, paint game objects
    painter.drawImage(shooter->getRect(), shooter->getImage());    
    for (int i = 0; i < numTargets; i++) {	
      if (!targets[i]->isDestroyed()) // paint various target objects, will change depending on level
	painter.drawImage(targets[i]->getRect(), targets[i]->getImage()); 
    }
    for (int i = 0; i < numMissiles; i++) {	
      if (missiles[i]->valid)  // paint missiles
	painter.drawImage(missiles[i]->getRect(), missiles[i]->getImage());
    }   
    if(level1) { // paint eels and bolts for level 1
      for (int i = 0; i < numEels; i++) {	
	if (!eels[i]->isDestroyed()) {
	  painter.drawImage(eels[i]->getRect(), eels[i]->getImage());
	  for(int j = 0; j < eels[i]->numBolts; j++){
	    if(eels[i]->bolts[j]->valid)
	      painter.drawImage(eels[i]->bolts[j]->getRect(), eels[i]->bolts[j]->getImage());
	  }
	}
      }
    }     
    if(level2){	// paint gulls and poops for level 2    
      for (int i = 0; i < numGulls; i++) {	
	if (!gulls[i]->isDestroyed()) {
	  painter.drawImage(gulls[i]->getRect(), gulls[i]->getImage());
	  for(int j = 0; j < gulls[i]->numPoops; j++){
	    if(gulls[i]->poops[j]->valid)
	      painter.drawImage(gulls[i]->poops[j]->getRect(), gulls[i]->poops[j]->getImage());
	  }
	}
      }
    }
    if(level3){	// paint UFOs and beams for level 3  
      for (int i = 0; i < numUFOs; i++) {	
	if (!UFOs[i]->isDestroyed()) {
	  painter.drawImage(UFOs[i]->getRect(), UFOs[i]->getImage());
	  for(int j = 0; j < UFOs[i]->numBeams; j++){
	    if(UFOs[i]->beams[j]->valid)
	      painter.drawImage(UFOs[i]->beams[j]->getRect(), UFOs[i]->beams[j]->getImage());
	  }
	}
      }
    }     
  }
}
  
void Game::timerEvent(QTimerEvent *event) { // run game logic
  srand( time(NULL) );
  for (int i = 0; i < numMissiles; i++) { // move missiles
    if(missiles[i]->valid){
      if(missiles[i]->yval > 0)
        missiles[i]->autoMove();
      else
        missiles[i]->setValid(FALSE);  
    }
  }
  for (int i = 0; i < numTargets; i++) { // move targets, check collision
    if(((targets[i]->xval < 860) && (targets[i]->xval > -60)) && (!targets[i]->isDestroyed())) { // if targets on screen and not destroyed already
      targets[i]->autoMove();
      checkCollision(i);
    }
    else{
      targets[i]->setDestroyed(TRUE);
      if(level1){
	if(i % 5 == 0)
	  newDuck(i);
	else {
	  if(i % 2 == 0)
	    newFish(i);
	  else
	    newBubble(i);
	}
      }
      if(level2){
	if(i % 5 == 0)
	  newEagle(i);
	else {
	  if(i % 2 == 0)
	    newGoose(i);
	  else
	    newBird(i);
	}
      }
      if(level3){
	if(i % 5 == 0)
	  newShip(i);
	else {
	  if(i % 2 == 0)
	    newAsteroid(i);
	  else
	    newMeteor(i);
	}
      }      
     }
     update();
    }
  if(level1) { // move eels in level 1
    for (int i = 0; i < numEels; i++) { 
      if (!eels[i]->isDestroyed()) {
	if((eels[i]->xval < 860) && (eels[i]->xval > -60)){
	  eels[i]->autoMove(shooter->xval);
	  checkCollision(i);
	}
	else
	  eels[i]->setDestroyed(TRUE);
      }
      else
	newEel(i);
    }
  }
  if(level2) { // move gulls for level 2
    for(int i = 0; i < numGulls; i++) {
      if((!gulls[i]->isDestroyed()) && ((gulls[i]->xval < 860) && (gulls[i]->xval > -60))) {
	gulls[i]->autoMove(shooter->xval);
        checkCollision(i);
      }
      else{
	gulls[i]->setDestroyed(TRUE);
	newGull(i);
      }
    }
  }
  if(level3) { // move UFOs for level 3
    for(int i = 0; i < numUFOs; i++) {
      if((!UFOs[i]->isDestroyed()) && ((UFOs[i]->xval < 860) && (UFOs[i]->xval > -60))) {
	UFOs[i]->autoMove(shooter->xval);
        checkCollision(i);
      }
      else{
	UFOs[i]->setDestroyed(TRUE);
	newUFO(i);
      }
    }
  }
  update();
}

void Game::keyPressEvent(QKeyEvent *event) { // gather user input from keyboard
  switch (event->key()) {
  case Qt::Key_Left: { // move shooter left
    for (int i=1; i<=5; i++)
      shooter->moveLeft();
  }
    break;
  case Qt::Key_Right: { // move shooter right
    for (int i=1; i<=5; i++)
      shooter->moveRight();
  }
    break;
  case Qt::Key_P: { // pause or unpause
    pauseGame();
  }
  case Qt::Key_H: {
    if(level1){
      level2 = TRUE;
      level1 = FALSE;
      startGame();
    }
    else if(level2){
      level3 = TRUE;
      level2 = FALSE;
      startGame();
    }
  }
    break;
  case Qt::Key_Space: { // shoot missiles or exit
    //if(gameWon || gameOver)
      //qApp->exit();
    //else
      launchMissile();
  }
    break;
  case Qt::Key_Escape: // exit
    {
      qApp->exit();
    }
    break;
  default:
    QWidget::keyPressEvent(event);
  }
}

void Game::startGame() { // set up game at start

  gameOver = FALSE; 
  gameWon = FALSE; 
  gameStarted = TRUE;
  timerId = startTimer(100);  
  srand( time(NULL) );
  score = 0; 
  lives = 5;
  
  if(level1){ // initialize targets for level 1
    for (int i = 0; i < numTargets; i++) {
      if(i % 5 == 0)
        newDuck(i);
      else {
        if(i % 2 == 0)
	  newFish(i);
        else
          newBubble(i);
      }
    }
    for (int i = 0; i < numEels; i++) {
      newEel(i);
    }
  }
  if(level2){ // initialize targets for level 2
    qApp->setStyleSheet("QWidget {background-image: url(./sky.png) }");  
    for (int i = 0; i < numTargets; i++) {
      if(i % 5 == 0)	
        newEagle(i);
      else {
        if(i % 2 == 0)
          newGoose(i);
        else
          newBird(i);
      }
    }
    for (int i = 0; i < numGulls; i++) {
      newGull(i);
    }
  }
  if(level3){ // initialize targets for level 3
    qApp->setStyleSheet("QWidget {background-image: url(./space.png) }");  
    for (int i = 0; i < numTargets; i++) {
      if(i % 5 == 0)	
        newShip(i);
      else {
        if(i % 2 == 0)
          newAsteroid(i);
        else
          newMeteor(i);
      }
    }
    for (int i = 0; i < numUFOs; i++) {
      newUFO(i);
    }
  }
}

void Game::pauseGame() { // pause or unpause
  if (paused) { 
    timerId = startTimer(100);
    paused = FALSE;
  } 
  else {
    paused = TRUE;
    killTimer(timerId); 
  }
}

void Game::launchMissile() { // launch missile
  if(numMissiles == 79){
    missiles[numMissiles] = new Missile((shooter->xval + 10),450);
    missiles[numMissiles]->setValid(TRUE);
    numMissiles = 0;
  }
  else{
    missiles[numMissiles] = new Missile((shooter->xval + 10),450);
    missiles[numMissiles]->setValid(TRUE);
    numMissiles++;
  }
}

void Game::checkCollision(int i) { // check collision between missiles and objects
  for(int j = 0; j < numMissiles; j++){ // check targets 
    if(missiles[j]->valid){
      if(((targets[i]->xval) < (missiles[j]->xval + 20)) && ((targets[i]->xval) > (missiles[j]->xval - 20))){
	if(((targets[i]->yval) < (missiles[j]->yval + 10)) && ((targets[i]->yval) > (missiles[j]->yval - 10))){
	  targets[i]->setDestroyed(TRUE);
	  missiles[j]->setValid(FALSE);
	  if(targets[i]->returnType() == 1)
	    score++;
	  //else
	    //score--;
	  break;
	}	
      }
      if(level1){ // check eels
	if(((eels[i]->xval) < (missiles[j]->xval + 30)) && ((eels[i]->xval) > (missiles[j]->xval - 30))){
	  if(((eels[i]->yval) < (missiles[j]->yval + 10)) && ((eels[i]->yval) > (missiles[j]->yval - 10))){
	    eels[i]->setDestroyed(TRUE);
	    missiles[j]->setValid(FALSE);
	    score++;
	    break;
	  }	
	}
      }
      else if (level2) { // check gulls
	if(((gulls[i]->xval) < (missiles[j]->xval + 30)) && ((gulls[i]->xval) > (missiles[j]->xval - 30))){
	  if(((gulls[i]->yval) < (missiles[j]->yval + 10)) && ((gulls[i]->yval) > (missiles[j]->yval - 10))){
	    gulls[i]->setDestroyed(TRUE);
	    missiles[j]->setValid(FALSE);
	    score++;
	    break;
	  }	
	}
      }
      else if(level3){ // check UFOs
	if(((UFOs[i]->xval) < (missiles[j]->xval + 20)) && ((UFOs[i]->xval) > (missiles[j]->xval - 20))){
	  if(((UFOs[i]->yval) < (missiles[j]->yval + 10)) && ((UFOs[i]->yval) > (missiles[j]->yval - 10))){
	    UFOs[i]->setDestroyed(TRUE);
	    missiles[j]->setValid(FALSE);
	    score++;
	    break;
	  }	
	}
      }      
    }
  }  
  /*if(level1){  // check to see if bolts have collided with shooter
    for(int j = 0; j < (eels[i]->numBolts); j++){
      if(eels[i]->bolts[j]->valid){
      	//if(((eels[i]->getBoltX(j)) < (shooter->xval + 20)) && ((eels[i]->bolts[j]->xval) > (shooter->xval - 20))){
	 if(((eels[i]->bolts[j]->xval) < (shooter->xval + 20)) && ((eels[i]->bolts[j]->xval) > (shooter->xval - 20))){
	    if(((eels[i]->bolts[j]->yval) < (shooter->yval + 20)) && ((eels[i]->bolts[j]->yval) > (shooter->yval - 20))){
	      lives--;
	      eels[i]->bolts[j]->setValid(FALSE);
	  }
	}
      }
    }
  }*/
  //else if(level2){ // check to see if poops have collided with shooter
  /*
    for(int j = 0; j < (gulls[i]->numPoops); j++){
      if(((gulls[i]->poops[j]->xval) < (shooter->xval + 20)) && ((gulls[i]->poops[j]->xval) > (shooter->xval - 20))){
	if(((gulls[i]->poops[j]->yval) < (shooter->yval + 20)) && ((gulls[i]->poops[j]->yval) > (shooter->yval - 20))){
	  //lives--;
	  //gulls[i]->poops[j]->setValid(FALSE);
	}
      }
    }*/
 // }
  //if(level3){ // check to see if beams have collided with shooter
  /* 
    for(int j = 0; j < (UFOs[i]->numBeams); j++){
      if(UFOs[i]->beams[j]->valid){
	if(((UFOs[i]->beams[j]->xval) < (shooter->xval + 20)) && ((UFOs[i]->beams[j]->xval) > (shooter->xval - 20))){
	  if(((UFOs[i]->beams[j]->yval) < (shooter->yval + 20)) && ((UFOs[i]->beams[j]->yval) > (shooter->yval - 20))){
	    //lives--;
	    //UFOs[i]->beams[j]->setValid(FALSE);
	  }
	}
      }
    }*/
 // }  
  if(lives == 0){
    stopGame();
  }
  if(score == 30){
    score = 0; 
    lives = 5;
    if(level3){
      victory();
    }
    else{
      if(level1){
        level2 = TRUE;
        level1 = FALSE;
      }
      else if(level2){
        level3 = TRUE;
        level2 = FALSE;      
      }  
      killTimer(timerId);
      for(int j = 0; j < numTargets; j++){
        targets[i]->setDestroyed(TRUE);
      }
      startGame();
    }
  }
}

void Game::victory() { // run game won logic
  killTimer(timerId); 
  gameWon = TRUE; 
  gameStarted = FALSE;
}

void Game::stopGame() { // run game lost logic
  killTimer(timerId);    
  gameOver = TRUE;      
  gameStarted = FALSE;
}

void Game::newDuck(int i) { 
  int speed = ((rand() % 5) + 3);
  int y = ((rand() % 200) + 50);
  if(duckLeft){
    targets[i] = new Duck(850,y,speed,duckLeft);
    duckLeft = FALSE;
  }
  else{
    targets[i] = new Duck(-50,y,speed,duckLeft);  
    duckLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newFish(int i) {
  int y = ((rand() % 300) + 100);
  int speed = ((rand() % 6) + 4);
  if(fishLeft){
  targets[i] = new Fish(850,y,speed,fishLeft);  
  fishLeft = FALSE;
  }
  else{
  targets[i] = new Fish(-50,y,speed,fishLeft);
  fishLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newBubble(int i) {
  int y = ((rand() % 200) + 50);
  int speed = ((rand() % 5) + 1);
  if(bubbleLeft){
  targets[i] = new Bubble(850,y,speed,bubbleLeft);
  bubbleLeft = FALSE;  
  }
  else{
  targets[i] = new Bubble(-50,y,speed,bubbleLeft);
  bubbleLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newEel(int i) {
  int speed = ((rand() % 8) + 6);
  int y = ((rand() % 200) + 100);
  eels[i] = new Eel(-50,y,speed);
  eels[i]->setDestroyed(FALSE);
}

void Game::newGull(int i) {
  int speed = ((rand() % 8) + 6);
  int y = ((rand() % 200) + 100);
  gulls[i] = new Gull(-50,y,speed);
  gulls[i]->setDestroyed(FALSE);
}

void Game::newUFO(int i) {
  int speed = ((rand() % 8) + 6);
  int y = ((rand() % 100) + 100);
  UFOs[i] = new UFO(-50,y,speed);
  UFOs[i]->setDestroyed(FALSE);
}

void Game::newEagle(int i) {
  int speed = ((rand() % 5) + 1);
  int y = ((rand() % 100) + 50);
  if(eagleLeft){
  targets[i] = new Eagle(850,y,speed,eagleLeft);
  eagleLeft = FALSE;  
  }
  else{
  targets[i] = new Eagle(-50,y,speed,eagleLeft);
  eagleLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newBird(int i) {
  int y = ((rand() % 300) + 100);
  int speed = ((rand() % 6) + 2);
  if(birdLeft){
  targets[i] = new Bird(850,y,speed,birdLeft);
  birdLeft = FALSE;  
  }
  else{
  targets[i] = new Bird(-50,y,speed,birdLeft);
  birdLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newGoose(int i) {
  int y = ((rand() % 200) + 50);
  int speed = ((rand() % 5) + 1);
  if(gooseLeft){
  targets[i] = new Goose(850,y,speed,gooseLeft);
  gooseLeft = FALSE;  
  }
  else{
  targets[i] = new Goose(-50,y,speed,gooseLeft);
  gooseLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newShip(int i) {
  int y = ((rand() % 200) + 50);
  int speed = ((rand() % 8) + 2);
  if(shipLeft){
  targets[i] = new Ship(850,y,speed,shipLeft);
  shipLeft = FALSE;  
  }
  else{
  targets[i] = new Ship(-50,y,speed,shipLeft);
  shipLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newAsteroid(int i) {
  int y = ((rand() % 200) + 50);
  int speed = ((rand() % 5) + 1);
  if(asteroidLeft){
  targets[i] = new Asteroid(850,y,speed,asteroidLeft);
  asteroidLeft = FALSE;  
  }
  else{
  targets[i] = new Asteroid(-50,y,speed,asteroidLeft);
  asteroidLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

void Game::newMeteor(int i) {
  int y = ((rand() % 200) + 50);
  int speed = ((rand() % 5) + 5);
  if(meteorLeft){
  targets[i] = new Meteor(850,y,speed,meteorLeft);
  meteorLeft = FALSE;  
  }
  else{
  targets[i] = new Asteroid(-50,y,speed,meteorLeft);
  meteorLeft = TRUE;
  }
  targets[i]->setDestroyed(FALSE);
}

#endif
