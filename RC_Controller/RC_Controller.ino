#include <NRF24L01_W.h>

NRF24L01_W radio(7, 8);

//Set pins for Joysticks
const int HOR = A0;
const int VER = A1;
const int SW = 2;

void setup() {
  Serial.begin(9600);

  //Set up pin for switch (not used)
  pinMode(SW, INPUT_PULLUP);

  radio.begin();
  radio.setReceiveAddress("AZ480");
  radio.setTransmitAddress("AZ490");

  radio.setChannel(83);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Read Joystick Positions Vertical, Horizontal
  RemoteData data;

  //Read info from joystick
  data.vx = analogRead(HOR)/4;
  data.vy = analogRead(VER)/4;
  data.sw = !digitalRead(SW);

  //send data
  radio.write(data);

  //Serial.println(analogRead(HOR));
}
