#include <Button2.h>
#include <HID-Project.h>
#include <Adafruit_NeoPixel.h>

#define KEY_PIN 0
#define ROTARY_PIN 1
#define VOLUME_UP_PIN 2
#define VOLUME_DOWN_PIN 3
#define NUMPIXELS 1
#define LED_PIN 11

Button2 KeySwitch;
Button2 VolumeKnob;
Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int EncoderPinALast = LOW;

void setup() {
  pinMode(VOLUME_DOWN_PIN, INPUT_PULLUP);
  pinMode(VOLUME_UP_PIN, INPUT_PULLUP);

  Consumer.begin();
  Keyboard.begin();

  KeySwitch.begin(KEY_PIN);
  KeySwitch.setClickHandler(SingleClickHandler);
  KeySwitch.setDoubleClickHandler(DoubleClickHandler);
  KeySwitch.setTripleClickHandler(TripleClickHandler);
  KeySwitch.setLongClickHandler(SingleClickHandler);

  VolumeKnob.begin(ROTARY_PIN);
  VolumeKnob.setClickHandler(VolumeSingleClickHandler);
  VolumeKnob.setLongClickHandler(VolumeSingleClickHandler);

  NeoPixel.begin();
  NeoPixel.setPixelColor(0, 0, 255, 0);
  NeoPixel.setBrightness(50);
  NeoPixel.show();
}

void loop() {
  ProcessVolumeChange();
  KeySwitch.loop();
  VolumeKnob.loop();
}

void ProcessVolumeChange() {
  int n = digitalRead(VOLUME_UP_PIN);
  if ((EncoderPinALast == LOW) && (n == HIGH)) {
    if (digitalRead(VOLUME_DOWN_PIN) == LOW) {
      Consumer.write(MEDIA_VOLUME_DOWN );
    } else {
      Consumer.write(MEDIA_VOLUME_UP );
    }
  }
  EncoderPinALast = n;
}

void VolumeSingleClickHandler(Button2& btn) {
  Serial.println("single volume click\n");
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(';');
  Keyboard.releaseAll();
}

void SingleClickHandler(Button2& btn) {
  Serial.println("click\n");
  Consumer.write(MEDIA_PLAY_PAUSE);
}
void DoubleClickHandler(Button2& btn) {
  Serial.println("double click\n");
  Consumer.write(MEDIA_NEXT);
}
void TripleClickHandler(Button2& btn) {
  Serial.println("triple click\n");
  Consumer.write(MEDIA_PREV);
}
