#include "Rave.h"

using namespace sf;
using namespace std;

Rave::Rave(double sample_rate_audio) 
    : AbstractMode(sample_rate_audio), 
    CenterCircle(1, 70)
{
    fft.LazyInit(sample_rate_audio);
    CenterCircle.setFillColor(sf::Color::Black);
    CenterCircle.setOutlineThickness(4.);
    CenterCircle.setOutlineColor(sf::Color::Red);
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
    // double W = window.getSize().x;
    // double H = window.getSize().y;

    double W = WIDTH ;
    double H = HEIGHT;

    double radius = Hz[100];
    CenterCircle.setRadius(radius);
    CenterCircle.setPosition({W / 2 - CenterCircle.getRadius(), H / 2 - CenterCircle.getRadius()});
    CenterCircle.setOutlineColor({255, 255, 255, CenterCircle.getRadius() - 100});
    //CenterCircle.rotate(90 / 55);
    
    window.draw(CenterCircle);
    //доделать отрисовку рейв мода
}
