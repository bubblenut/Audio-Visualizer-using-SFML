#include "Amplitude.h"
#include <iostream>

using namespace sf;

Amplitude::Amplitude(double sample_rate_audio, shared_ptr<FFT> fftPtr_)
    : AbstractMode(sample_rate_audio, fftPtr_)
{}

void Amplitude::update(vector<double>& audio_in)
{
    //это если что окно звука, которое показывает амплитуда. длина амплитуды крч
    size_t border = 256 * 9;

    if (points.getVertexCount() == 0) {
        points = VertexArray(LineStrip, border);
    }

    double W = WIDTH / static_cast<double>(border);
    const int color_jump = static_cast<int>(border / 256);
    for (size_t i = 0; i < border; ++i) {
        double x = i * W;
        double y = HEIGHT / 2 + audio_in[i] * 1500;
        points[i] = Vertex(Vector2f(x, y) , Color(255 - i / color_jump, i / color_jump, 0));
    }
}


void Amplitude::draw(RenderWindow& window) {    
    for (size_t i = 0; i < points.getVertexCount(); ++i) {
        
        float rectX = WIDTH / points.getVertexCount() < 1 ? 1. : WIDTH / points.getVertexCount();
        //float rectX = WIDTH / points.getVertexCount();
        float rectY = 50;

        RectangleShape rect({rectX - 0.1, rectY});
        rect.setPosition({points[i].position.x, points[i].position.y - rectY / 2});
        rect.setFillColor(points[i].color);
        window.draw(rect);
    }
    //window.draw(points);
}
