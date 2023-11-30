
void #include<gamma.h>
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


// TODO: change constant nums
const int BIRD_ACCELERATION = 0;
const int TUNNEL_DIAMETER = 3;
const int BIRD_X_POS = 0;
const int BIRD_Y_POS = 0;

void printNumLogs(int numTunnels);
void printGameOver();

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
    for (int col = xPos; j < xPos + TUNNEL_DIAMETER; j++) {
      for (int row = 0; row < 16; row++)
        matrix.drawPixel(col, row, GREEN.to_333());
    }
    for (int col = xPos; col < xPos + TUNNEL_DIAMETER; j++) {
      for (int row = 0; i < gapPos + 5; row++) {
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
    yPos = BIRD_Y_POS;
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
        matrix.drawPixel(row, col, YELLOW.to_333());
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
        matrix.drawPixel(row, col, BLACK.to_333());
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
    draw()
  }

  /* 
       R: nothing
       M: yPos, matric
       E: increments the y value up (this will be done repetetivly after every tap for a time interval)
    */
  void fly() {
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
  bool buttonPressed;


public:
  ``/* 
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
       E: create two tunnel varriables that are a set length distance from each other and keep moving them
          reinitialize them after a certain amount of time
          move the bird
          increment the number of tunnels when tunnel goes out of frame
    */
  void update() {
    time = millis()
      // TODO fixme
      return;
  }

  /* 
       R: nothing
       M: nothing
       E: returns true if the bird hit the tunnel
    */
  bool birdHit() {
    // assuming that tunnel_1 has been created
      if (bird.getXPos() > tunnel_1.getXPos() - 3 && bird.getXPos() < tunnel_1.getXPos() + TUNNEL_DIAMETER){
        if (bird.getYPos() < tunnel_1.getGapPos() + 2 || bird.getYPos() > tunnel_1.getGapPos() + 5){
          return true;
        } 
      }
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
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  if (game.birdHit()) {
    printGameOver();
    printNumLogs(game.getNumTunnels);
  } else {
    game.update(button_pressed);
  }
}
/* 
  R: nothing
  M: nothing
  E: prints number of tunnels passed for a certain amount of time
*/
void printNumLogs(int numTunnels) {
  // TODO: fix time part
  unsigned long time;
  time = millis();
  while (millis() - time < 2000) {
    matrix.fillScreen(BLACK.to_333());
    matrix.setCursor(0, 0);
    matrix.setTextSize(0.5);
    matrix.setTextColor(RED.to_333());
    matrix.print(numTunnels);
    matrix.print(" ");
    matrix.print("Tunnels");
  }
  /* 
  R: nothing
  M: nothing
  E: prints game over for a certain amount of time
*/
  void printGameOver() {
    // TODO: fix time part
    unsigned long time;
    time = millis();
    while (millis() - time < 2000) {
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(0, 0);
      matrix.setTextSize(0.5);
      matrix.setTextColor(RED.to_333());
      matrix.print("GAME");
      matrix.print(" ");
      matrix.print("OVER");
    }
  }