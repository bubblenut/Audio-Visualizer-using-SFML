#include "Rave.h"

using namespace sf;
using namespace std;

Rave::Rave(double sample_rate_audio) 
    : AbstractMode(sample_rate_audio), 
    CenterCircle(1, 3)
{
    fft.LazyInit(sample_rate_audio);
    CenterCircle.setFillColor(sf::Color::Black);
    CenterCircle.setOutlineThickness(5.);
    CenterCircle.setOutlineColor(sf::Color::Red);
}

void Rave::update(vector<double>& audio_in) {
    auto audio_spectre = fft.Calculate(audio_in);
    Hz.resize(audio_spectre->size());
    double re = (*audio_spectre)[20].real();
    double im = (*audio_spectre)[20].imag();
    Hz[20] = sqrt(re * re + im * im);
}

void Rave::draw(sf::RenderWindow& window) {
    // double W = window.getSize().x;
    // double H = window.getSize().y;
    double R = Hz[20];
    double normalizedR = 1 / (1 + pow(M_E, -1 * R));
    
    CenterCircle.setRadius(log10(max(R, 0.)) * 256);
    CenterCircle.setPosition({WIDTH / 2 - CenterCircle.getRadius(), HEIGHT / 2 - CenterCircle.getRadius()});
    CenterCircle.setOutlineColor({255, 255, 255, CenterCircle.getRadius()});
    //CenterCircle.rotate(90 / 55);
    
    window.draw(CenterCircle);
    //доделать отрисовку рейв мода
}
