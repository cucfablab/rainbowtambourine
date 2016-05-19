#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9 //this is the data out pin for your WS2812s!!
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


int r, b, g = 0;
float a = 0;


void setup() {
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  attachInterrupt(digitalPinToInterrupt(3), newColor, RISING); //when the piezo is tapped, set new color. switch digitalPinToInterrupt() to what works for you

}

void loop() {
  
  while(a > 0){    
    
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(int(r * a),int(g * a),int(b * a))); //set strip color, multiplying each r,g,b value by the fading alpha channel. truncate result with int()
    }
    
    strip.show();
    if(a > 0) a =- 0.01; //decrement brightness (a for alpha channel) with each loop cycle. Use a larger number for a faster fade.
    
    delay(1);

  }

}

void newColor(){
  r = random(255);
  g = random(255);
  b = random(255);
  a = 1; //set brightness to full every time the tambourine is tapped, with a random r,g,b value
}


