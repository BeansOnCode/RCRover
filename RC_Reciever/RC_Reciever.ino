#include <NRF24L01_W.h>

NRF24L01_W radio(7, 8);

//Assign Ports for motor controls
const int LEFT_FWD = 2;
const int LEFT_EN = 9;
const int LEFT_REV = 3;
const int RIGHT_FWD = 4;
const int RIGHT_EN = 10;
const int RIGHT_REV = 5;

//Initialize horizontal and vertical signed variables (for direction)
int HOR = 0;
int VER = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  radio.begin();
  radio.setReceiveAddress("AZ490");
  radio.setTransmitAddress("AZ480");

  radio.setChannel(83);

  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);

  //enable motor driver function
  digitalWrite(LEFT_EN, HIGH);
  digitalWrite(RIGHT_EN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

    //Default system to not run when on input
    uint8_t RFWD = LOW;
    uint8_t RREV = LOW;
    uint8_t LFWD = LOW;
    uint8_t LREV = LOW;

  if(radio.available())
  {
    RemoteData data = radio.readRemoteData();


    //normalize to 0 for reverse and forward or left and right 
    //Check for deadzone of 25 to ignore minor error values
    HOR = abs(data.vx - 130) < 25 ? 0 : data.vx - 130;
    VER = abs(data.vy - 130) < 25 ? 0 : data.vy - 130;

    //Check directions of Ver and Horizontal
    if(HOR < 0 && VER == 0)
    {
      RREV = HIGH;
      LREV = HIGH;
    }else if(HOR > 0 && VER ==0)
    {
      RFWD = HIGH;
      LFWD = HIGH;
    }else if(HOR == 0 && VER < 0)
    {
      RFWD = HIGH;
      LREV = HIGH;
    }else if(HOR == 0 && VER > 0)
    {
      RREV = HIGH;
      LFWD = HIGH;
    }
  }

  //Write out the output 
  digitalWrite(LEFT_FWD, LFWD);
  digitalWrite(RIGHT_FWD, RFWD);
  digitalWrite(LEFT_REV, LREV);
  digitalWrite(RIGHT_REV, RREV);

  delay(50);

}
