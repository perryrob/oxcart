/*********************************************************************
OxCart display.
https://github.com/nox771/i2c_t3/blob/master/examples/advanced_slave/advanced_slave.ino
*********************************************************************/

#include <Adafruit_GFX.h>
#include <sharp_mem_disp.h>
#include <i2c_t3.h>

// DISPLAY
#define SCK 20
#define MOSI 21
#define SS 22

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

#define LED_1_OFF 0x11
#define LED_2_OFF 0x12
#define LED_3_OFF 0x13
#define LED_1_ON  0x14
#define LED_2_ON  0x15
#define LED_3_ON  0x16

#define TXT_CMD   0x20
#define CLEAR_CMD 0x50

#define LED_1_PIN  13
#define LED_2_PIN  11
#define LED_3_PIN  12

#define I2C_ADDR 0x20

int LAST_REFRESH;

volatile uint8_t cmd;

uint8_t x ;
uint8_t y ;
uint8_t size ;
uint8_t color ;
char buff[32];

void PrintHex8(uint8_t data ) {
  Serial.print("0x"); 
  if (data<0x10) {Serial.print("0");} 
  Serial.println(data,HEX); 
}

void setup(void) 
{
  Wire.begin(I2C_SLAVE, I2C_ADDR, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  pinMode(LED_1_PIN,OUTPUT);
  pinMode(LED_2_PIN,OUTPUT);
  pinMode(LED_3_PIN,OUTPUT);

  // start & clear the display
  display.begin();
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Bluesky 2 I2C");

  LAST_REFRESH = millis();
}

void loop(void) 
{

  // Screen must be erefreshed at least once per second
  if (millis() - LAST_REFRESH > 500 ) {
    display.refresh();    
    LAST_REFRESH = millis();
  }
}

void receiveEvent(size_t count) {
  if(count) { 
    cmd = Wire.readByte();
    if (cmd != 0) {
      Serial.print("receiveEvent: ");
      Serial.print(count);
      Serial.print(" receiveEvent CMD: ");
      PrintHex8(cmd);
    }
    switch(cmd) {
    case LED_1_OFF:
        digitalWrite(LED_1_PIN, 0);
        Serial.println("LED 1 OFF");
        break;
    case LED_2_OFF:
      digitalWrite(LED_2_PIN, 0);
      Serial.println("LED 2 OFF");
      break;
    case LED_3_OFF:
      digitalWrite(LED_3_PIN, 0);
      Serial.println("LED 3 OFF");
      break;          
    case LED_1_ON:
      digitalWrite(LED_1_PIN, 1);
      Serial.println("LED 1 ON");
      break;
    case LED_2_ON:
      digitalWrite(LED_2_PIN, 1);
      Serial.println("LED 2 ON");
      break;
    case LED_3_ON:
      digitalWrite(LED_3_PIN, 1);
      Serial.println("LED 3 ON");
      break;          
    case TXT_CMD:
      /************************************************************
       * Put text on the display
       *        CMD   X     Y  size  color
       * format 0x20 0x00 0x00 0x01  0x00  [data]
       */
      x = Wire.readByte();
      y = Wire.readByte();
      size = Wire.readByte();
      color = Wire.readByte();
      memset( buff, 0, 32);
      for(uint8_t i=0; Wire.available(); ++i) {
        buff[i] = char(Wire.readByte());
        Serial.print( buff[i] );
      }
      Serial.println("");
      display.setTextSize(size);
      display.setTextColor(color);
      display.setCursor(x,y);
      display.println(buff);
      Serial.println("TEXT CMD");
      break;
    case CLEAR_CMD:
      digitalWrite(LED_1_PIN, 0);
      digitalWrite(LED_2_PIN, 0);
      digitalWrite(LED_3_PIN, 0);
      display.clearDisplay();
      Serial.println("CLEAR CMD");
      break;
    }
  }
}

void testReceiveEvent(size_t count) {
  while( Wire.available() ) {
    cmd = Wire.readByte();
    PrintHex8(cmd);
  }
}
