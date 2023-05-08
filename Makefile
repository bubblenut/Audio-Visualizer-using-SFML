compile:./main.cpp
	g++ -c ./main.cpp
	g++ -g3 main.cpp visualization_modes/*.cpp math/*.cpp audio_processing/*.cpp visualizer/*.cpp -o app -std=c++20 -laudiorw -lavformat -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfftw3 -lm -lasound -lpulse -lpulse-simple

run:
	./app