#include "Amplitude.h"

using namespace sf;

Amplitude::Amplitude(double sample_rate_audio)
    : AbstractMode(sample_rate_audio) 
{}

void Amplitude::update(vector<double>& audio_in)
{   
    const int color_jump = static_cast<int>(audio_in.size() / 256);
    for (int i = 0; i < audio_in.size(); ++i) {
        //уточнить че за хуйня в заполнении Y внутри Vector2f, уточнить константы
        points[i] = Vertex(Vector2f(0.f, //x
        static_cast<float>(HEIGHT / 2)) + Vector2f(i / static_cast<float>(audio_in.size()) * WIDTH, audio_in[i] * static_cast<float>(0.008)),
        Color(255 - i / color_jump, 0, i / color_jump));
    }
}


void Amplitude::draw(RenderWindow& window) {
    window.draw(points);
}