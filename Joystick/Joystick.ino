int X = A0;
int XValue = 0;
int Y = A1;
int YValue = 0;
int SW = 28;
int SWValue = 0;
int pin_LED_R = 10;
int pin_LED_Y = 11;
int pin_LED_W = 12;

void setup() {
  Serial.begin(115200); //serial begin at 115200 baud
  pinMode(pin_LED_R,OUTPUT);
}

void loop() {
  XValue = analogRead(X);
  YValue = analogRead(Y);
  SWValue = digitalRead(SW);
  Serial.print("XValue: ");
  Serial.print(XValue);
  Serial.print("\t");
  Serial.print("YValue: ");
  Serial.print(YValue);
  Serial.print("\t");
  Serial.print("SWValue: ");
  Serial.println(SWValue);
  delay(200);
  if(XValue < 514 && YValue < 501){
    digitalWrite(pin_LED_R,1);
    digitalWrite(pin_LED_Y,0);
    digitalWrite(pin_LED_W,0);
  }
  else if(XValue >= 514 && YValue < 501){
    digitalWrite(pin_LED_R,0);
    digitalWrite(pin_LED_Y,1);
    digitalWrite(pin_LED_W,0);
  }
  else{
    digitalWrite(pin_LED_R,0);
    digitalWrite(pin_LED_Y,0);
    digitalWrite(pin_LED_W,0);
  }
}
