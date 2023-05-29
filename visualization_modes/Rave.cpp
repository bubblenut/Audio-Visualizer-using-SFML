#include "Rave.h"

using namespace sf;
using namespace std;

Rave::Rave(double sample_rate_audio) 
    : AbstractMode(sample_rate_audio) {
    fft.LazyInit(sample_rate_audio);
}

void Rave::update(vector<double>& audio_in) {
    auto audio_spectre = fft.Calculate(audio_in);
    Hz.resize(audio_spectre->size());
    for (size_t i = 0; i < audio_spectre->size(); ++i) {
        double re = (*audio_spectre)[i].real();
        double im = (*audio_spectre)[i].imag();
        Hz[i] = log(sqrt(re * re + im * im)) * 100;
    }
}

void Rave::draw(sf::RenderWindow& window) {
    double W = window.getSize().x;
    double H = window.getSize().y;
    //доделать отрисовку рейв мода
}