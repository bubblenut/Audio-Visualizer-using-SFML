#include "AbstractMode.h"
#include "../math/FFT.h"

using namespace sf;
class Rave : public AbstractMode {
private:
    vector<double> Hz;
    FFT fft;

    CircleShape CenterCircle;
public:
    Rave(double sample_rate_audio);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};