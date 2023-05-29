#include "AbstractMode.h"
#include "../math/FFT.h"

class Rave : public AbstractMode {
private:
    vector<double> Hz;
    FFT* fft;
public:
    Rave(double sample_rate_audio);
    void draw(sf::RenderWindow& window) override;
    void update(vector<double>& audio_in) override;
};