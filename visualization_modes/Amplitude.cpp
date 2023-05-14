#include "Amplitude.h"

using namespace sf;

Amplitude::Amplitude(double sample_rate_audio)
    : AbstractMode(sample_rate_audio) 
{}

void Amplitude::update(vector<double>& audio_in)
{   
    size_t border = 256 * 100;
    if (points.getVertexCount() == 0) {
         points = VertexArray(LineStrip, border);
    }
    double W = WIDTH / static_cast<double>(border);
    const int color_jump = static_cast<int>(border / 256);
    for (size_t i = 0; i < border; ++i) { 
        double x = i * W;       
        double y = HEIGHT / 2 + audio_in[i] * 1000;             
        points[i] = Vertex(Vector2f(x, y) , Color(255 - i / color_jump, i / color_jump, 0));
    }    
}


void Amplitude::draw(RenderWindow& window) {
    window.draw(points);
}
