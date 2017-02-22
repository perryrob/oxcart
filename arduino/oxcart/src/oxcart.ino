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


#define LED_1_PIN  13
#define LED_2_PIN  11
#define LED_3_PIN  12

#define ON 0x01
#define OFF 0x00

#define I2C_ADDR 0x20

int LAST_REFRESH;

volatile uint8_t led_addr;
volatile uint8_t cmd;
volatile uint8_t led_status;

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
  int color=0;
  int x=0;
  int y=0;
  int size=8;

  display.setTextColor(  color );
  display.setCursor(x,y);
  display.setTextSize(size);
  display.print( "not impl" );
    
  // Screen must be erefreshed at least once per second
  if (millis() - LAST_REFRESH > 500 ) {
    display.refresh();    
    Serial.println("LOOP");
    LAST_REFRESH = millis();
  }
}

void receiveEvent(size_t count) {
  Serial.print("receiveEvent: ");
  Serial.println(count);
  if(count) { 
    cmd = Wire.readByte();
    Serial.print("receiveEvent CMD: ");
    Serial.println(cmd);
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
    }
  }
}
