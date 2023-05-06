#include "Amplitude.h"

using namespace sf;

Amplitude::Amplitude(const vector<double>& audio_in, double sample_rate_audio, int sample_rate_fft)
    :AbstractMode(audio_in, sample_rate_audio, sample_rate_fft) {}

void Amplitude::update()
{   
    const int color_jump = static_cast<int>(audio.size() / 256);
    for (int i = 0; i < audio.size(); ++i) {
        //уточнить че за хуйня в заполнении Y внутри Vector2f, уточнить константы
        points[i] = Vertex(Vector2f(0.f, //x
        static_cast<float>(HEIGHT / 2)) + Vector2f(i / static_cast<float>(audio.size()) * WIDTH, audio[i] * static_cast<float>(0.008)),
        Color(255 - i / color_jump, 0, i / color_jump));
    }
}


void Amplitude::draw(RenderWindow& window) {
    window.draw(points);
}