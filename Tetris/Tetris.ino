#include <LedControl.h>

#define DIN 10 //purple wire
#define CLK 12 //yellow wire
#define CS 11 //red wire
LedControl lc = LedControl(DIN, CLK, CS, 4);

#define ButtonLeft 5
#define ButtonRight 7
#define Buzzer 21

bool board[8][8] = {0};

int xPos = 3;
int yPos = 0;
int prevX = xPos;
int prevY = yPos;

unsigned long lastMoveDown = 0;
int moveSpeed = 500; // ms

int lastButtonStatus_L = HIGH, currButtonStatus_L = HIGH;
int lastButtonStatus_R = HIGH, currButtonStatus_R = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(ButtonLeft, INPUT_PULLUP);
  pinMode(ButtonRight, INPUT_PULLUP);
  initDisplay();
}

void loop() {
  // Read current button state
  currButtonStatus_L = digitalRead(ButtonLeft);
  currButtonStatus_R = digitalRead(ButtonRight);


  readButtons();     // check for edge
  updatePiece();     // automatic downward movement
  drawPiece();       // draw on LED

  if (board[yPos + 1][xPos] && yPos + 1 == 1){
    Serial.println("Over");
    restartGame();
    delay(1000);
  }

  // Save previous state for next loop
  lastButtonStatus_L = currButtonStatus_L;
  lastButtonStatus_R = currButtonStatus_R;
}

// ------------------ Functions ------------------

void initDisplay() {
  for (int m = 0; m < 4; m++) {
    lc.shutdown(m, false);
    lc.setIntensity(m, 8);
    lc.clearDisplay(m);
  }
}

void drawPiece() {
  // Clear only previous position
  lc.setLed(3, prevX, prevY, false);

  // Draw new position
  lc.setLed(3, xPos, yPos, true);

  // Save current position for next frame
  prevX = xPos;
  prevY = yPos;
}

void readButtons() {
  // Detect LEFT button press (edge detection)
  if (lastButtonStatus_L == HIGH && currButtonStatus_L == LOW) {
    moveLeft();
  }

  // Detect RIGHT button press
  if (lastButtonStatus_R == HIGH && currButtonStatus_R == LOW) {
    moveRight();
  }
}

void moveLeft() {
  xPos = max(0, xPos - 1);
}

void moveRight() {
  xPos = min(7, xPos + 1);
}

void updatePiece() {
  digitalWrite(Buzzer, 0);
  unsigned long currentMillis = millis();

  if (currentMillis - lastMoveDown >= moveSpeed) {
    if (checkCollisionBelow()) {
      // Piece lands
      board[yPos][xPos] = true;
      resetPiece();
    } else {
      // Keep falling
      yPos++;
    }
    lastMoveDown = currentMillis;
  }
}

bool checkCollisionBelow() {
  // Hit bottom?
  printLine();
  if (yPos >= 7) return true;

  // Hit another block?
  if (board[yPos + 1][xPos]) return true;

  return false;
}

void printLine(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      Serial.print(board[i][j]);
    }
    Serial.println();
  }
}

void clearAll(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      board[i][j] = 0;
    }
  }

  lc.clearDisplay(0);
}

void resetPiece() {
  yPos = 0;
  xPos = 3;
  prevX = xPos;
  prevY = yPos;
}

void restartGame() {
  clearAll();
  resetPiece();
  lastMoveDown = millis();
}
