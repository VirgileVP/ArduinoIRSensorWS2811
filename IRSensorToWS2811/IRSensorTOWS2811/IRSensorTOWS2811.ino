#include <FastLED.h>


#define SENSOR_PIN 5
int old_value = 0;
int sensor_value = 0;

#define LED_PIN     3
#define NB_LEDS     90
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NB_LEDS];

#define UPDATES_PER_SECOND 100

int rndm_function = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    delay(1000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NB_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
    sensor_value = digitalRead(SENSOR_PIN);
    if (sensor_value == HIGH && old_value == 0)
    {
        rndm_function = random(1, 30);
        which_function(rndm_function);
        old_value = 1;
    }
    else if (sensor_value == LOW && old_value == 1)
    {
        OffAllLeds();
        old_value = 0;
    }
    delay(300);
}

void OffAllLeds()
{
    int index = 0;

    while (index < NB_LEDS)
    {
        leds[index] = CRGB::Black;
        index++;
        delay(5);
        FastLED.show();
    }
}

void which_function(int fnct)
{
    CRGB color = getColor();

    if (fnct > 20)
        OnEffect1(color);
    else if (fnct > 10)
        OnEffect2(color);
    else if (fnct > 0)
        OnEffect3(color);
}

CRGB getColor()
{
    int red = 0;
    int green = 0;
    int blue = 0;
    while (red + green + blue < 255)
    {
        red = random(0, 255);
        green = random(0, 255);
        blue = random(0, 255);
    }
    return (red, green, blue);
}

void OnEffect1(CRGB color)
{
    int index = 0;

    while (index < NB_LEDS)
    {
        leds[index] = color;
        index++;
        delay(5);
        FastLED.show();
    }
}

void OnEffect2(CRGB color)
{
    int index = 0;

    while (index < NB_LEDS / 2)
    {
        leds[NB_LEDS / 2 + index] = color;
        leds[NB_LEDS / 2 - index] = color;
        index++;
        delay(20);
        FastLED.show();
    }
}

void OnEffect3(CRGB color)
{
    int index_zone = 0;
    int index = 0;

    while (index_zone <20)
    {
        index = index_zone;
        while (index < NB_LEDS)
        {
            leds[index] = color;
            index+=20;
        }
        index_zone++;
        delay(50);
        FastLED.show();
    }
}
