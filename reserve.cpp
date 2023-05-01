// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <fftw3.h>
// #include <numeric>

// #include <SFML/Audio.hpp>
// #include <SFML/Graphics.hpp>

// #include <audiorw.hpp>

// #include "math/FFT.h"

// using namespace std;
// using namespace sf;

// constexpr size_t WIDTH = 1000;
// constexpr size_t HEIGHT = 800;

// const std::string FILENAME = "Ilnar";

// int main()
// {   
//     RenderWindow window(VideoMode(WIDTH, HEIGHT), FILENAME);    
//     sf::Clock clock;

//     //чтение аудиофайа  

//     //частота дискретизации
//     double sample_rate;
//     //вектор, хранящий аудиоволну
//     std::vector<std::vector<double>> audio = audiorw::read("music/" + FILENAME + ".mp3", sample_rate);


//     // проигрывание музыки

//     sf::Music music;
//     if (!music.openFromFile("music/" + FILENAME + ".ogg"))
//         return -1; // error
//     music.play();

// //ТУТ ПРОИСХОИТ ФФТ
//     // int sample_rate_pwr2 = 1;
//     // while (sample_rate_pwr2 <= sample_rate) {
//     //     sample_rate_pwr2 *= 2;
//     // }
//     // sample_rate_pwr2 /= 2;

//     float time = 0;
//     // vector<double> in;
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // if (in.size() != sample_rate_pwr2) {
//         //     int prev_idx = -1;
//         //     while (in.size() != sample_rate_pwr2) {
//         //         int ind = clock.getElapsedTime().asSeconds() * sample_rate;
//         //         if (prev_idx != ind) {
//         //             in.push_back(audio[0][ind]);
//         //             prev_idx = ind;
//         //         }
//         //     }
//         // } else {
//         //     int delta = (clock.getElapsedTime().asSeconds() - time) * sample_rate;
//         //     in.insert(in.end(), audio[0].begin() + time * sample_rate, audio[0].begin() + time * sample_rate + delta);
//         //     in.erase(in.begin(), in.begin() + delta);
//         //     time = clock.getElapsedTime().asSeconds();
//         // }
//         // vector<double> window_hann(in.size());
//         // for (int i = 0; i < in.size(); ++i) {
//         //     double multiplier = 0.5 * (1 - cos(2 * M_PI * i / (sample_rate_pwr2 - 1)));
//         //     window_hann[i] = multiplier * in[i];
//         // }

//         // fftw_complex out[in.size()];
//         // fftw_plan p = fftw_plan_dft_r2c_1d(window_hann.size(),
//         //                                     window_hann.data(),
//         //                                     out,
//         //                                     FFTW_ESTIMATE);
//         // fftw_execute(p);
//         // fftw_destroy_plan(p);        
//         // fftw_cleanup();

//         window.clear();        

//         constexpr double radius = 50;
//         constexpr int offsetX = WIDTH / 2;
//         constexpr int offsetY = HEIGHT / 2;

//         FFT my_fft;
//         my_fft.initialize(sample_rate, audio[0], clock);
//         auto window_hann = my_fft.getWindowHann();
//         auto out = my_fft.getOut();


//         VertexArray circle(Points, window_hann.size());
//         // VertexArray lines(LineStrip);
//         // for (int i = 0; i < window_hann.size(); ++i) {
//         //     Vertex point(Vector2f(cos(i) * radius + offsetX, sin(i) * radius + offsetY), Color::Green);
//         //     circle[i] = point;

//         //     auto h = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    
//         //     if (isinf(h) || h > 10000) {
//         //         continue;
//         //     }


//         //     Color c;
//         //     c.r = 255;
//         //     c.g = rand() % 50;
//         //     c.b = rand() % 60;

//         //     h = min(h, 300.);
//         //     c.a = 200;
//         //     Vertex p(Vector2f(cos(i) * (radius + h) + offsetX, sin(i) * (radius + h) + offsetY), c);
//         //     lines.append(p);

//         //     RectangleShape rect(Vector2f(2, h));
//         //     //cos(i) * (radius + h) + offsetX
//         //     rect.setFillColor(c);
//         //     rect.setRotation(i);
//         //     rect.setPosition(cos(i) * (radius) + offsetX, sin(i) * (radius) + offsetY);
//         //     //window.draw(rect);
//         // }
//         // window.draw(lines);
//         // window.draw(circle);

//         window_hann.resize(window_hann.size() * 0.30);
//         double W = static_cast<double>(WIDTH) / window_hann.size() + 1;
//         vector<double> rectH = my_fft.getHeight();
//         for (int i = 0; i < window_hann.size(); ++i) {

//             //double h = sqrt(out[0][i] * out[0][i] + out[1][i] * out[1][i]);
//             double h = rectH[i];

//             RectangleShape rect(Vector2f(10, h));
//             rect.setFillColor(Color::Red);
//             rect.setPosition(Vector2f(i * 7, HEIGHT - h));
//             window.draw(rect);

//         }
        
//         sf::CircleShape circleL, circleR;
//         double radiusL = audio[0][clock.getElapsedTime().asSeconds() * sample_rate] * 150;
//         double radiusR = audio[1][clock.getElapsedTime().asSeconds() * sample_rate] * 150;
//         circleL.setRadius(radiusL);
//         circleR.setRadius(radiusR);
//         circleL.setOutlineThickness(5);
//         circleR.setOutlineThickness(5);
//         circleL.setPosition(WIDTH / 2 - 200 - radiusL, HEIGHT / 2 - radiusL);
//         circleR.setPosition(WIDTH / 2 + 200 - radiusR, HEIGHT / 2 - radiusR);
//         circleL.setOutlineColor(sf::Color::Red);
//         circleR.setOutlineColor(sf::Color::Blue);
//         VertexArray arr(LineStrip, sample_rate);
//         for (int i = 0; i < sample_rate; ++i) {
//             Vertex point(Vector2f(audio[0][clock.getElapsedTime().asSeconds() * sample_rate] * 250 + circleL.getPosition().x + (radiusL / 2) , i / sample_rate * WIDTH), Color::Red);
//             arr[i] = point;
//         }
//         VertexArray arr1(LineStrip, sample_rate);
//         for (int i = 0; i < sample_rate; ++i) {
//             Vertex point(Vector2f(audio[1][clock.getElapsedTime().asSeconds() * sample_rate] * 250 + circleR.getPosition().x + (radiusR / 2) , i / sample_rate * WIDTH), Color::Blue);
//             arr1[i] = point;
//         }        
//         window.draw(arr);
//         window.draw(arr1);
//         window.draw(circleL);
//         window.draw(circleR);
//         window.display();
//     }    

//     return 0;
// }