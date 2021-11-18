#include <Button2.h>


//#include <Keyboard.h>
#include <HID-Project.h>
#include <Adafruit_NeoPixel.h>
#include <SwitchPack.h>

#define KEY_PIN 0
#define ROTARY_PIN 1
#define VOLUME_UP_PIN 2
#define VOLUME_DOWN_PIN 3

int val;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
long firstPixelHueBase = 20000;

#define NUMPIXELS 1
#define LED_PIN 11
#define REACTION_TIME 500

Button2 button;

//class Button {
//    private:
//        bool _state;
//        uint8_t _pin;
//
//    public:
//        Button(uint8_t pin) : _pin(pin) {}
//
//        void begin() {
//            pinMode(_pin, INPUT_PULLUP);
//            _state = digitalRead(_pin);
//        }
//
//        bool isReleased() {
//            bool v = digitalRead(_pin);
//            if (v != _state) {
//                _state = v;
//                if (_state) {
//                    return true;
//                }
//            }
//            return false;
//        }
//};

//Button myButton(KEY_PIN);
Click clicker(ROTARY_PIN, PULLUP);
//DoubleClick key(KEY_PIN, PULLUP, REACTION_TIME);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  //  pinMode(KEY_PIN, INPUT_PULLUP);
  //  pinMode(ROTARY_PIN, INPUT_PULLUP);
  pinMode (VOLUME_DOWN_PIN, INPUT_PULLUP);
  pinMode (VOLUME_UP_PIN, INPUT_PULLUP);

  Consumer.begin();
  Keyboard.begin();
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(100);
  clicker.begin();
  //  myButton.begin();
  button.begin(KEY_PIN);
  //  key.begin();
  //  key.setMaxClicks(3);
  button.setClickHandler(clickIt);
  button.setDoubleClickHandler(doubleClick);
  button.setTripleClickHandler(tripleClick);
  button.setLongClickHandler(longClick);
}

void loop() {
  n = digitalRead(VOLUME_UP_PIN);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(VOLUME_DOWN_PIN) == LOW) {
      Consumer.write(MEDIA_VOLUME_DOWN );
      int pixelHue = firstPixelHueBase + (65536L / pixels.numPixels()) - 512;
      pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(pixelHue)));
      firstPixelHueBase = pixelHue;
      pixels.show();
    } else {
      Consumer.write(MEDIA_VOLUME_UP );
      int pixelHue = firstPixelHueBase + (65536L / pixels.numPixels()) + 512;
      pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(pixelHue)));
      firstPixelHueBase = pixelHue;
      pixels.show();
    }
    Serial.print (encoder0Pos);
    Serial.println ("/");
  }
  encoder0PinALast = n;
  //  if (myButton.isReleased()) {
  //    Serial.println(F("Released"));
  //  }


  //
  //  switch (key.clickCount()) {
  //    case 1:
  //      Consumer.write(MEDIA_PLAY_PAUSE);
  //      Serial.println(1);
  ////      delay(REACTION_TIME);
  ////      Keyboard.releaseAll();
  //      break;
  //    case 2:
  //      Consumer.write(MEDIA_NEXT);
  //      Serial.println(2);
  ////      delay(REACTION_TIME);
  ////      Keyboard.releaseAll();
  //      break;
  //    case 3:
  //      Consumer.write(MEDIA_PREV);
  //      Serial.println(3);
  ////      delay(REACTION_TIME);
  ////      Keyboard.releaseAll();
  //      break;
  //    default:
  //      Keyboard.releaseAll();
  //      break;
  //  }

  //  if (key.clickCount() > 0) {
  //    Serial.println(key.clickCount());
  //  }



  if (clicker.clicked()) {

    Serial.println("A SHORT press is detected");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(';');
    Keyboard.releaseAll();
    delay(300);
  }
  int currentState = digitalRead(KEY_PIN);
  int rotaryState = digitalRead(ROTARY_PIN);
  button.loop();
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
