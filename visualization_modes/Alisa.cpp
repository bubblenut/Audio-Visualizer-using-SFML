#include "Alisa.h"

using namespace sf;
using namespace std;

Alisa::Alisa(double sample_rate_audio, shared_ptr<FFT> fftPtr_)
    : AbstractMode(sample_rate_audio, fftPtr_)
{
    Vector2f qCount(6., 4.);
    qSize = {100., 100.};
    double pause = 5;

    qPositions = vector<Vector2f>(qCount.x * qCount.y, {0, 0});
    qColors = vector<int>(qCount.x * qCount.y, 0);

    float firstPosX = (WIDTH - qSize.x * qCount.x + pause * (qCount.x - 1)) / 2;
    float firstPosY = (HEIGHT - qSize.y * qCount.y + pause * (qCount.y - 1)) /2;
    Vector2f firstPos(firstPosX - pause, firstPosY - pause);


    for (size_t i = 1; i <= qCount.y; ++i) {
        for (size_t j = 1; j <= qCount.x; ++j) {
            qPositions[i] = {firstPos.x + pause * i + qSize.x, firstPos.y + qSize.y * j};
        }
    }
}


void Alisa::update(vector<double>& audio_in) {
    auto audio_spectre = fftPtr->GetResult();
    size_t step = static_cast<size_t>((WIDTH - qPositions.size()) / qPositions.size());
    for(size_t i = qPositions.size(), c = 0; i < audio_spectre->size(), c < qColors.size(); i += step, ++c) {
        qColors[c] = static_cast<int>(log10(max(0., (*audio_spectre)[i].real())));
        //qColors[c] = 200;
    }
}


void Alisa::draw(RenderWindow& window) {
    for (size_t i = 0; i < qPositions.size(); ++i) {
        RectangleShape quad({qSize.x, qSize.y});
        quad.setFillColor({255, 255, 255, qColors[i]});
        quad.setPosition({qPositions[i].x, qPositions[i].y});
        //RectangleShape quad({10, 10});
        window.draw(quad);
    }
}
