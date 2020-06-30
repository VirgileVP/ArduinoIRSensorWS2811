#include <FastLED.h>


#define SENSOR_PIN 5
int old_value = 0;
int sensor_value = 0;

#define LED_PIN     3
#define NB_LEDS     90
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NB_LEDS];

#define UPDATES_PER_SECOND 100

int rndm_function = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    delay(1000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NB_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
    sensor_value = digitalRead(SENSOR_PIN);
    //Serial.print("read = ");
    //Serial.println(sensor_value);
    if (sensor_value == LOW && old_value == 1)
    {
        Serial.print("sensor = ");
        Serial.println(sensor_value);
        rndm_function = random(1, 3);
        which_function(rndm_function);
        Serial.println(rndm_function);
        //OnEffect1(CRGB(255, 125, 40));
        //FastLED.show();
        old_value = 0;
    }
    if (sensor_value == HIGH && old_value == 0)
    {
        OffAllLeds();
        Serial.print("sensor = ");
        Serial.println(sensor_value);
        old_value = 1;
    }
    //FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void OffAllLeds()
{
    int index = 0;

    while (index < NB_LEDS)
    {
        leds[index] = CRGB::Black;
        index++;
        delay(10);
        FastLED.show();
    }
}

void which_function(int fnct)
{
    CRGB color = CRGB(255, 125, 50);

    if (fnct == 1)
        OnEffect1(color);
    else if (fnct == 2)
        OnEffect2(color);
    else if (fnct == 3)
        OnEffect3(color);
}

void OnEffect1(CRGB color)
{
    int index = 0;

    while (index < NB_LEDS)
    {
        leds[index] = color;
        index++;
        delay(10);
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
        delay(15);
        FastLED.show();
    }
}

void OnEffect3(CRGB color)
{
    int index_zone = 0;
    int index = 0;

    while (index_zone < 10)
    {
        index = index_zone;
        while (index < NB_LEDS)
        {
            leds[index] = color;
            index+=10;
        }
        index_zone++;
        delay(15);
        FastLED.show();
    }
}
