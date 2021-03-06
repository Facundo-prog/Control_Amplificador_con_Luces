#include <Arduino.h>
#include <AudioControl.h>


AudioControl::AudioControl(byte pinAudio){
    _pinAudio = pinAudio;
    pinMode(_pinAudio, INPUT);
}

void AudioControl::setDetectionFrequency(int frequency){
    if(frequency >= 0){_frecuenciaDeteccion = frequency;}
}


void AudioControl::setDetectionSilence(bool value, int readingFrequency, int ruinValue, float minimumPeakValue){
    _deteccionMute = value;
    if(readingFrequency >= 0){_frecuenciaDeteccionSilencio = readingFrequency;}
    if(ruinValue >= 0){_valorDeRuido = ruinValue;}
    if(minimumPeakValue >= 0){_valorMinimoPico = minimumPeakValue;}
}


bool AudioControl::getStateMute(){
    return _estadoMute;
}


float AudioControl::getAudio(){

    float val;
    float diferencia;

    if((micros() - _timpoDeteccionAudio) >= _frecuenciaDeteccion){

        val = analogRead(_pinAudio);
        diferencia = val - _valorAudioAnterior;
        _valorAudioAnterior = val;
        _timpoDeteccionAudio = millis();

        if(diferencia >= _valorMinimoPico && _deteccionMute == true){
            _estadoMute = false;
            _valorMute += diferencia;
        }
        return (0)>(diferencia)?(0):(diferencia);
    }
    return 0;
}


float AudioControl::readAudio(){

    float valFinal = getAudio();
    if(_deteccionMute == true){deteccionDeSilencio();}else{_estadoMute = false;}
    return valFinal;
}


void AudioControl::deteccionDeSilencio(){

    if(millis() > _tiempoMute + _frecuenciaDeteccionSilencio){

        if((_valorMute <= _valorDeRuido) && (_estadoMute == false)){
            _estadoMute = true;
        }
        _valorMute = 0.00;
        _tiempoMute = millis();
    }
}