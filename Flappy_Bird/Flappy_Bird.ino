#include<gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

  // define the wiring of the LED screen
  const uint8_t CLK = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;


const int BIRD_ACCELERATION = 1;
const int TUNNEL_DIAMETER = 3;
const int BIRD_X_POS = 2;
const int BIRD_Y_POS = 7;

void printGameOver(int numTunnels);

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

class Color {
public:
  int red;
  int green;
  int blue;
  Color() {
    red = 0;
    green = 0;
    blue = 0;
  }
  Color(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }
  uint16_t to_333() const {
    return matrix.Color333(red, green, blue);
  }
};

const Color BLACK(0, 0, 0);
const Color RED(4, 0, 0);
const Color ORANGE(6, 1, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 4, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(1, 0, 2);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 4, 4);

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
  Tunnel(int gapPosNew) {
    gapPos = gapPosNew;
    // where the matrix pannel ends/ tunnel starts
    xPos = 32;
  }
  /* 
       R: nothing
       M: nothing
       E: returns xPos
    */
  int getXPos() {
    return xPos;
  }

  /* 
       R: nothing
       M: nothing
       E: returns gapPos
    */
  int getGapPos() {
    return gapPos;
  }

  /* 
       R: nothing
       M: matrix
       E: draws the tunnel in green first and then redraws the gap as black
    */
  void draw() {
    for (int col = xPos; col < xPos + TUNNEL_DIAMETER; col++) {
      for (int row = 0; row < 16; row++)
        matrix.drawPixel(col, row, GREEN.to_333());
    }
    for (int col = xPos; col < xPos + TUNNEL_DIAMETER; col++) {
      for (int row = gapPos; row < gapPos + 8; row++) {
        matrix.drawPixel(col, row, BLACK.to_333());
      }
    }
  }
  /* 
       R: nothing
       M: matrix
       E: redraws the whole wood area to be black
    */
  void erase() {
    for (int row = 0; row < 16; row++) {
      for (int col = xPos; col < xPos + TUNNEL_DIAMETER; col++) {
        matrix.drawPixel(col, row, BLACK.to_333());
      }
    }
  }
  /* 
       R: nothing
       M: matrix
       E: moves the tunnel one point to the left
    */
  void move() {
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
  Bird() {
    xPos = BIRD_X_POS;
    yPos = 7;
    velocity = 0;
    acceleration = BIRD_ACCELERATION;
  }
  /* 
       R: nothing
       M: nothing
       E: returns xPos
    */
  int getXPos() {
    return xPos;
  }
  /* 
       R: nothing
       M: nothing
       E: returns yPos
    */
  int getYPos() {
    return yPos;
  }

  /* 
       R: nothing
       M: velocity
       E: adds position to velocity
    */
  void updateVelocity() {
    velocity += acceleration;
  }

  /* 
       R: nothing
       M: matrix
       E: draws the bird
    */
  void draw() {
    for (int row = yPos; row < yPos + 2; row++) {
      for (int col = xPos; col < xPos + 3; col++) {
        matrix.drawPixel(col, row, YELLOW.to_333());
      }
    }
    matrix.drawPixel(xPos + 1, yPos, BLUE.to_333());
    matrix.drawPixel(xPos + 2, yPos, BLACK.to_333());
  }
  /* 
       R: nothing
       M: matrix
       E: redraws the bird black
    */
  void erase() {
    for (int row = yPos; row < yPos + 2; row++) {
      for (int col = xPos; col < xPos + 3; col++) {
        matrix.drawPixel(col, row, BLACK.to_333());
      }
    }
    matrix.drawPixel(xPos + 1, yPos, BLACK.to_333());
    matrix.drawPixel(xPos + 2, yPos, BLACK.to_333());
  }

  /* 
       R: nothing
       M: yPos, matrix
       E: increments the birds y value by velocity
    */
  void fall() {
    erase();
    yPos += velocity;
    updateVelocity();
    draw();
  }

  /* 
       R: nothing
       M: yPos, matric
       E: increments the y value up (this will be done repetetivly after every tap for a time interval)
    */
  void fly() {
    erase();
    yPos -= 1;
    velocity = 0;
    draw();
  }
};


class Game {
private:
  unsigned long time;
  Bird flappy;
  int numTunnels;
  bool buttonPressed;
  Tunnel tunnel_1 = Tunnel(int(random(2, 11)));
  Tunnel tunnel_2 = Tunnel(int(random(2, 11)));
  // might have to change to unassigned long;
  int button_press_time = 0;
  int current_bird_y_pos = 0;

public:
    /* 
       R: nothing
       M: buttonPressed
       E: sets buttonPressed to button_pressed
    */
    Game(bool button_pressed) {
    buttonPressed = button_pressed;
  }
  /* 
       R: nothing
       M: nothing
       E: returns number of tunnels passed
    */
  int getNumTunnels() {
    return numTunnels;
  }

  /* 
       R: nothing
       M: nothing
       E: returns true if the bird hit the tunnel
    */
  bool birdHit() {
    // assuming that tunnel_1 has been created
      if (flappy.getXPos() >= tunnel_1.getXPos() - 3 && flappy.getXPos() <= tunnel_1.getXPos() + TUNNEL_DIAMETER){
        if (flappy.getYPos() < tunnel_1.getGapPos() || flappy.getYPos() > tunnel_1.getGapPos() + 7){
          return true;
        } 
      }
      if (flappy.getXPos() >= tunnel_2.getXPos() - 3 && flappy.getXPos() <= tunnel_2.getXPos() + TUNNEL_DIAMETER){
        if (flappy.getYPos() < tunnel_2.getGapPos() || flappy.getYPos() > tunnel_2.getGapPos() + 7){
          return true;
        } 
      }
      else if(flappy.getYPos() > 15 || flappy.getYPos() == 0){
        return true;
      }
      return false;
  }

    /* 
       R: nothing
       M: nothing
       E: create two tunnel varriables that are a set length distance from each other and keep moving them
          reinitialize them after a certain amount of time
          move the bird
          increment the number of tunnels when tunnel goes out of frame
    */
  void update(bool button_pressed) {
    buttonPressed = button_pressed;
    time = millis();
    if (!birdHit()){
      // create a tunnel every 10th second
      if ((time % 10800) == 0){
        // creates new tunnel end of pannel
        tunnel_2 = Tunnel(random(1, 9));
      }
      // creates tunnel every 5th second
      else if ((time % 5400) == 0){
        // creates new tunnel at end of the pannel
        tunnel_1 = Tunnel(random(3, 11));
      }
      // detect the number of tunnels
      if ((flappy.getXPos() == tunnel_1.getXPos() || flappy.getXPos() == tunnel_2.getXPos()) && time % 312 == 0){
        numTunnels += 1;
      }
      // TODO: fix random magic numbers
      // ensure that the tunnels goes thorugh the screen every 10 seconds
      if (time % 281 == 0){
        tunnel_1.move();
        tunnel_2.move();
      }
      // this way we buffer the jump time and make sure that the button can't be held
      if (buttonPressed && button_press_time == 0){
        button_press_time = millis();
        current_bird_y_pos = flappy.getYPos();
      }
      // stop the bird from flying 2 pixels up
      if (current_bird_y_pos == flappy.getYPos() + 2){
        button_press_time = 0;
        current_bird_y_pos = 0;
      }
      // make the bird fly (done at a rate 3 times as fast as the tunnels move)
      if (button_press_time != 0 && time % 126 == 0){
        flappy.fly();
      }

      // the bird falls if not flying (done at a rate 2 times as much as when tunnels move)
      if (button_press_time == 0 && time % 198 == 0){
        flappy.fall();
      }
    }
    else{
      printGameOver(numTunnels);
    }
  }
};

Game game(digitalRead(BUTTON_PIN_NUMBER) == HIGH);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
}



void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  game.update(button_pressed);
}
  /* 
  R: nothing
  M: nothing
  E: prints game over for a certain amount of time
*/
void printGameOver(int numTunnels) {
  matrix.fillScreen(BLACK.to_333());
  matrix.setCursor(0, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(RED.to_333());
  matrix.print("GAME");
  matrix.print(" ");
  matrix.print("OVER");
  matrix.print(numTunnels);
  matrix.print(" ");
  matrix.print("Tunnels");
  }