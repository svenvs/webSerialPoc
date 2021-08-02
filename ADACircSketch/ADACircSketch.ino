#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BUTTON_LEFT   19
#define BUTTON_RIGHT   4

#define PIXEL_PIN    17

#define PIXEL_COUNT 10

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

boolean oldStateBUTTON_LEFT = HIGH;
boolean oldStateBUTTON_RIGHT = HIGH;

String command;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello Computer");
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'

}

void loop() {
  boolean newStateBUTTON_LEFT = digitalRead(BUTTON_LEFT);
  boolean newStateBUTTON_RIGHT = digitalRead(BUTTON_RIGHT);

  if(Serial.available()){
    String command = Serial.readStringUntil('\n');
    command.trim();
    executeCommand(command);
  }

  oldStateBUTTON_LEFT = newStateBUTTON_LEFT;
  oldStateBUTTON_RIGHT = newStateBUTTON_RIGHT;
}

void executeCommand(String command) {
    Serial.print("You typed: " );
    Serial.println(command);
    if(command.equals("red")){
      colorWipe(strip.Color(255,   0,   0), 50); 
    }
    if(command.equals("blue")){
      colorWipe(strip.Color(0,   0,   255), 50); 
    }
    if(command.equals("green")){
      colorWipe(strip.Color(0,   255,   0), 50); 
    }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
