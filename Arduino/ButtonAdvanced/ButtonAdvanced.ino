#include <Button2.h>


//#include <Keyboard.h>
#include <HID-Project.h>
#include <Adafruit_NeoPixel.h>
#include <SwitchPack.h>

#define KEY_PIN 0
#define ROTARY_PIN 1
#define VOLUME_UP_PIN 2
#define VOLUME_DOWN_PIN 3
#define NUMPIXELS 1
#define LED_PIN 11
#define REACTION_TIME 500


int val;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
long firstPixelHueBase = 20000;

Button2 KeySwitch;
Click VolumeKnob(ROTARY_PIN, PULLUP);
Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  Consumer.begin();
  Keyboard.begin();
  NeoPixel.begin();
  VolumeKnob.begin();
  KeySwitch.begin(KEY_PIN);

  pinMode(VOLUME_DOWN_PIN, INPUT_PULLUP);
  pinMode(VOLUME_UP_PIN, INPUT_PULLUP);

  NeoPixel.setBrightness(100);

  KeySwitch.setClickHandler(clickIt);
  KeySwitch.setDoubleClickHandler(doubleClick);
  KeySwitch.setTripleClickHandler(tripleClick);
  KeySwitch.setLongClickHandler(longClick);

  int pixelHue = firstPixelHueBase + (65536L / NeoPixel.numPixels()) - 512;
  NeoPixel.setPixelColor(0, 0, 128, 0);
  NeoPixel.show();
}

void loop() {
  n = digitalRead(VOLUME_UP_PIN);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(VOLUME_DOWN_PIN) == LOW) {
      Consumer.write(MEDIA_VOLUME_DOWN );
    } else {
      Consumer.write(MEDIA_VOLUME_UP );
    }
  }
  encoder0PinALast = n;

  if (VolumeKnob.clicked()) {
    Serial.println("A SHORT press is detected");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(';');
    Keyboard.releaseAll();
    delay(300);
  }

  KeySwitch.loop();
}


void clickIt(Button2& btn) {
  Serial.println("click\n");
  Consumer.write(MEDIA_PLAY_PAUSE);
}
void doubleClick(Button2& btn) {
  Serial.println("double click\n");
  Consumer.write(MEDIA_NEXT);
}
void tripleClick(Button2& btn) {
  Serial.println("triple click\n");
  Consumer.write(MEDIA_PREV);
}
void longClick(Button2& btn) {
  Serial.println("long click\n");
  Consumer.write(MEDIA_PLAY_PAUSE);
}
