#ifndef ScrollingDotsEffect_h
#define ScrollingDotsEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

class ScrollingDotsEffect : public EffectsFather{

    public:
        ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        unsigned long _tiempoColorPuntosDesplazables = 0; 
        const int _cantidadLedsDesplazables = 250;//Cantidad de Leds / 2
        int _ledsDesplazables[250];
};

#endif