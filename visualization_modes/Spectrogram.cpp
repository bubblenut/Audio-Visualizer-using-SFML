#include "Spectrogram.h"

#include <iostream>


using namespace std;

using namespace sf;

Spectrogram::Spectrogram(double sample_rate_audio)
    : AbstractMode(sample_rate_audio)
    , RowPosition(0)
    , Matrix(HEIGHT, vector<double>(WIDTH))
    , Start(0)
    , End(HEIGHT)
{
    fft.LazyInit(sample_rate_audio);
}

void Spectrogram::update(vector<double>& audio_in) {
    auto audio_spectre = fft.Calculate(audio_in);
    rectH.resize(audio_spectre->size());
    for (size_t i = 0; i < audio_spectre->size(); ++i) {
        double re = (*audio_spectre)[i].real();
        double im = (*audio_spectre)[i].imag();
        rectH[i] = sqrt(re * re);

    }
}

void Spectrogram::draw(RenderWindow& window) {
    cout << rectH.size() << endl;
    //rectH.resize(1000);
    sf::Shader shader;
    shader.loadFromFile("shaders/shader.glsl", sf::Shader::Vertex);

    size_t N = rectH.size();
    double W = WIDTH / static_cast<double>(N);

    if (RowPosition == End && !ChangeStrategy) {
        ChangeStrategy = true;
        RowPosition = Start;
        End++;
        Start++;
    }

    if (End > HEIGHT) {
        End = 0;
    }
    if (Start == HEIGHT) {
        Start = 0;
    }

    for (size_t i = 0; i < N; ++i) {
        Matrix[RowPosition][i] = rectH[i];
    }

    for (size_t i = Start, k = 0; i != End, k < HEIGHT; ++i, ++k) {
        if (i == HEIGHT) {
            i = 0;
            if (i == End) {
                break;
            }
        }
        VertexArray points(Lines, N * 2);

        vector<double> newData(Matrix[i].size());
        double max_val = 0;
        double min_val = 0;

        max_val = max(max_val, *max_element(Matrix[i].begin(), Matrix[i].end()));

            for (size_t j = 0; j < WIDTH; ++j) {
                newData[j] = (Matrix[i][j] - min_val) / (max_val - min_val);
            }


        double W = WIDTH / static_cast<double>(N);
        for (size_t j = 0, l = 0; j < N, l < N * 2; ++j, l += 2) {
            Color c;
            c.a = newData[j] * 255;
            Vertex p(Vector2f(j * W, k), c);
            Vertex p1(Vector2f((j+1) * W, k), c);
            points[l] = p;
            points[l + 1] = p1;
        }
        window.draw(points, &shader);
    }

    if (!ChangeStrategy) {
        RowPosition++;
    } else {
        RowPosition = Start;
        Start++;
        End++;
    }
}
