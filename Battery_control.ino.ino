#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

//Project adjusted to Arduino Nano.
//Using an OLED I2C to show the results
//Pin-number avaliable at http://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics
#define SDA 7
#define SCL 8
#define greenLight 10
#define yellowLight 11
#define redLight 12
#define battery 19
#define DISPLAY_ADDRESS 0x70

//OLED defines
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//setup the arduino
void setup() {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(redLight,OUTPUT);
  pinMode(battery, INPUT);
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  
  /*
  disp.begin(DISPLAY_ADDRESS);
  disp.clear();
  disp.writeDisplay();
  */
}

//change the LED's lights
void changeLights(const double& voltage){
  if(voltage > 14.5 && voltage < 17){
    digitalWrite(greenLight, HIGH);
    delay(1000);
    digitalWrite(greenLight, LOW);
  }
  else if(voltage > 14 && voltage <= 14.5){
    for(int i = 0; i < 2; i++){
        digitalWrite(yellowLight, HIGH);
        delay(500);
        digitalWrite(yellowLight, LOW);
    }
  }
  else{
    for(int i = 0; i < 4; i++){
        digitalWrite(redLight, HIGH);
        delay(250);
        digitalWrite(redLight, LOW);
    }
  }
  return;
}

//main loop. Calculate and show current voltage, while showing voltage on LED
//Updating every 2 seconds
void loop() {
  double voltage = 1024 * analogRead(battery); //convert to voltage by mul with 1024
  while(1){
    voltage = 1024 * analogRead(battery);
    Serial.print(voltage); 
    changeLights(voltage);
    delay(2000);
  }
}
