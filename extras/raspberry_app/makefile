TARGET = raspberry_app
SERIAL_PROTOCOL_DIR = ../../src/SerialProtocol

CPP_SOURCES = $(SERIAL_PROTOCOL_DIR)/*.cpp $(TARGET).cpp

all: build

build: $(TARGET)

clean: 
	rm $(TARGET)

$(TARGET): 
g++ -I$(SERIAL_PROTOCOL_DIR) $(CPP_SOURCES) -o $(TARGET)
