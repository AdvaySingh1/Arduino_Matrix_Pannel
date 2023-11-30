
void #include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;


// TODO: change constant nums
const int BIRD_ACCELERATION = 0;
const int TUNNEL_DIAMETER = 0;
const int BIRD_X_POS = 0;
const int BIRD_Y_POS = 0;

void printNumLogs(int numTunnels);
void printGameOver();

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

class Tunnel {
  private:
    int xPos;
    // R: the following varibale refers to the top left of the gap in the diameter.
    int gapPos;

  public:
    /* 
       R: gap pos is a random number between certain values
       M: gapPos, xPos
       E: Sets gapPos to gapPosNew and xPos to rightmost point on matric
    */
    Tunnel(gapPosNew){
      gapPos = gapPosNew;
      // where the matrix pannel ends/ tunnel starts
      xPos = 32;
    }
    /* 
       R: nothing
       M: nothing
       E: returns xPos
    */
    int getXPos(){
      return xPos;
    }

    /* 
       R: nothing
       M: nothing
       E: returns gapPos
    */
    int getGapPos(){
      return gapPos;
    }

    /* 
       R: nothing
       M: matrix
       E: draws the tunnel in green first and then redraws the gap as black
    */
    void draw(){
      // TODO fixme
    }
    /* 
       R: nothing
       M: matrix
       E: redraws the whole wood area to be black
    */
    void erase(){
      // TODO fixme
    }
    /* 
       R: nothing
       M: matrix
       E: moves the tunnel one point to the left
    */
    void move(){
      erase();
      xPos -= 1;
      draw();
    }

};


class Bird {
  private:
    int xPos = 0;
    int yPos = 0;
    int velocity = 0;
    int acceleration = 0;

  public:
    /* 
       R: nothing
       M: xPos, yPos, velocity, acceleration
       E: Sets xPos to BIRD_X_POS
          Sets yPos to BIRD_Y_POS
          Sets velocity to initial value;
          Sets acceleration to BIRD_ACCELERATION;
    */
    Bird(){
      xPos = BIRD_X_POS;
      yPos = BIRD_Y_POS;
      velocity = 0;
      acceleration = BIRD_ACCELERATION;
    }
    /* 
       R: nothing
       M: nothing
       E: returns xPos
    */
    int getXPos(){
      return xPos;
    }
    /* 
       R: nothing
       M: nothing
       E: returns yPos
    */
    int getYPos(){
      return yPos;
    }

    /* 
       R: nothing
       M: velocity
       E: adds position to velocity
    */
    void updateVelocity(){
      velocity += acceleration;
    }

    /* 
       R: nothing
       M: matrix
       E: draws the bird
    */
    void draw(){
      // TODO fixme
    }
    /* 
       R: nothing
       M: matrix
       E: redraws the bird black
    */
    void erase(){
      // TODO fixme
    }

    /* 
       R: nothing
       M: yPos, matrix
       E: increments the birds y value by velocity
    */
    void fall(){
      erase();
      yPos += velocity;
      draw()
    }

    /* 
       R: nothing
       M: yPos, matric
       E: increments the y value up (this will be done repetetivly after every tap for a time interval)
    */
    void fly(){
      erase();
      yPos -= velocity;
      draw()
    }


};


class Game {
  private:
    unsigned long time;
    Bird flappy;
    int numTunnels;



  public:
    /* 
       R: nothing
       M: nothing
       E: returns number of tunnels passed
    */
    int getNumTunnels(){
      return numTunnels;
    }
    /* 
       R: nothing
       M: nothing
       E: create two tunnel varriables that are a set length distance from each other and keep moving them
          reinitialize them after a certain amount of time
          move the bird
          increment the number of tunnels when tunnel goes out of frame
    */
    void update(){
      time = millis()
      // TODO fixme
      return;
    }
    
    /* 
       R: nothing
       M: nothing
       E: returns true if the bird hit the tunnel
    */
    bool birdHit(){
      // TODO fixme
      return false;
    }

};

Game game;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();

}



void loop() {
  if (game.birdHit()){
    printGameOver();
    printNumLogs(game.getNumTunnels);
  }
  else{
    game.update();
  }

}
/* 
  R: nothing
  M: nothing
  E: prints number of tunnels passed
*/
void printNumLogs(int numTunnels){
  // TODO Fixme
}
/* 
  R: nothing
  M: nothing
  E: prints game over for a certain amount of time
*/
void printGameOver(){
  unsigned long time;
  time = millis();
  // TODO: firxme
}
