CXX = g++
FLAGS = -std=c++11 -O2 -lgmp -lCGAL -lCGAL_Core
CVFLAGS = `pkg-config --cflags --libs opencv`
MAIN = src/main.cpp
SOURCE_DIR = src
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/demo

SOURCE_RAW = image.cpp MVCCloner.cpp
SOURCES = $(addprefix $(SOURCE_DIR)/,$(SOURCE_RAW))

demo: bin 
	$(CXX) $(MAIN) $(SOURCES) -o $(TARGET) $(FLAGS) $(CVFLAGS)


clean:
	rm -rf bin/
