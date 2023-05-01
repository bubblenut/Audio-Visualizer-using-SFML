compile:./main.cpp
	g++ -c ./main.cpp
	g++ -g3 main.cpp math/FFT.h math/FFT.cpp -o app -laudiorw -lavformat -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfftw3 -lm -std=c++20 

run:
	./app