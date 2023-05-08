CC=g++
CFLAGS=-c -Wall -std=c++20 -g3
LDFLAGS=-laudiorw -lavformat -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfftw3 -lm -lasound -lpulse -lpulse-simple
SOURCES=main.cpp \
		visualization_modes/AbstractMode.cpp \
		visualization_modes/Amplitude.cpp \
		visualization_modes/Spectre.cpp \
		math/FFT.cpp \
		audio_processing/FileAudioProcessor.cpp \
		audio_processing/PcmAudioProcessor.cpp \
		audio_processing/PulseAudioProcessor.cpp \
		visualizer/Visualizer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=app

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o app *.a visualization_modes/*.o math/*.o audio_processing/*.o visualizer/*.o

run:
	./app
