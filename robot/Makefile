# @author: lintang, vektor
# REF: http://www.ashleymills.com/node/327
# For board-specific setting see: https://github.com/arduino/Arduino/blob/master/hardware/arduino/boards.txt
CC=avr-gcc
CXX=avr-g++

MASTER_MCU=-mmcu=atmega2560 #: atmega2560, atmega328p
MASTER_MCU_TAG=m2560 #: m2560, m328p
MASTER_UPLOAD_PROTOCOL=wiring #: arduino (for atmega328p), wiring (for atmega2560), avr109
MASTER_BOARD=arduino
MASTER_CPU_SPEED=-DF_CPU=16000000UL
MASTER_CFLAGS=$(MASTER_MCU) $(MASTER_CPU_SPEED) -Os -w -Wl,--gc-sections -ffunction-sections -fdata-sections
MASTER_LIBNAME=lib$(MASTER_BOARD)-master.a
MASTER_UPLOAD_BAUDRATE=115200 #(for promini m328p), 115200 (for mega m2560, uno m328p)
MASTER_PORT=/dev/ttyACM0

SLAVE_MCU=-mmcu=atmega328p #: atmega328p, #atmega2560
SLAVE_MCU_TAG=m328p #: m2560, m328p
SLAVE_UPLOAD_PROTOCOL=arduino #: arduino (for atmega328p), wiring (for atmega2560), avr109
SLAVE_BOARD=arduino
SLAVE_CPU_SPEED=-DF_CPU=16000000UL
SLAVE_CFLAGS=$(SLAVE_MCU) $(SLAVE_CPU_SPEED) -Os -w -Wl,--gc-sections -ffunction-sections -fdata-sections
SLAVE_LIBNAME=lib$(SLAVE_BOARD)-slave.a
SLAVE_UPLOAD_BAUDRATE=115200 #: 57600 (for promini m328p), 115200 (for mega m2560, uno m328p)
SLAVE_PORT=/dev/ttyUSB0

CONTROL_MCU=-mmcu=atmega328p
CONTROL_MCU_TAG=m328p
CONTROL_UPLOAD_PROTOCOL=arduino #: arduino (for atmega328p), wiring (for atmega2560), avr109
CONTROL_BOARD=arduino
CONTROL_CPU_SPEED=-DF_CPU=16000000UL
CONTROL_CFLAGS=$(CONTROL_MCU) $(CONTROL_CPU_SPEED) -Os -w -Wl,--gc-sections -ffunction-sections -fdata-sections
CONTROL_LIBNAME=lib$(CONTROL_BOARD)-control.a
CONTROL_PORT= /dev/ttyUSB0
CONTROL_UPLOAD_BAUDRATE=115200

TARGET_INCDIR=./include
TARGET_LIBDIR=./lib
TARGET_BUILDDIR=./build

# the word ARDUINO refers to the core arduino library and/or anything related to building it
ARDUINO_SRC= ./src/arduino/
ARDUINO_INC=-I $(ARDUINO_SRC)
ARDUINO_OBJ=$(ARDUINO_SRC)pins_arduino.o $(ARDUINO_SRC)wiring.o $(ARDUINO_SRC)wiring_analog.o $(ARDUINO_SRC)wiring_digital.o \
			$(ARDUINO_SRC)wiring_pulse.o $(ARDUINO_SRC)wiring_shift.o $(ARDUINO_SRC)Stream.h $(ARDUINO_SRC)HardwareSerial.o  $(ARDUINO_SRC)Print.o   \
			$(ARDUINO_SRC)Tone.o $(ARDUINO_SRC)WMath.o $(ARDUINO_SRC)WString.o $(ARDUINO_SRC)WInterrupts.o $(ARDUINO_SRC)new.o \
			$(ARDUINO_SRC)twi.o $(ARDUINO_SRC)Wire.o 

# NOTICE: the library linking order does matter 
# see: http://stackoverflow.com/questions/11111966/eclipse-arduino-linker-trouble
MASTER_OBJ= ./main/master.cc ./src/ros_lib/time.cpp ./src/ros_lib/duration.cpp
#./src/comm/arduino_mavlink_packet_handler.cpp 
MASTER_LIBS= $(TARGET_LIBDIR) -larduino-master -lm
#MASTER_INCDIR= /opt/ros/indigo/include
MASTER_INCFLAGS =  -I $(TARGET_INCDIR) -I $(TARGET_INCDIR)/arduino

SLAVE_OBJ= ./main/slave.cc ./src/sensor/two_phase_incremental_encoder.cpp ./src/sensor/encoder_hctl.cpp  ./src/actuator/motor.cpp ./src/actuator/sc.cpp ./src/pid/pid.c ./src/DynamixelSerial/DynamixelSerial.cpp
#./src/comm/arduino_mavlink_packet_handler.cpp
SLAVE_LIBS= -L $(TARGET_LIBDIR) -larduino-slave -lm
SLAVE_INCFLAGS= -I $(TARGET_INCDIR) -I $(TARGET_INCDIR)/arduino 

CONTROL_OBJ= ./main/control.cc ./src/ros_lib/time.cpp ./src/ros_lib/duration.cpp ./src/PS2X_lib/PS2X_lib.cpp
CONTROL_LIBS= -L $(TARGET_LIBDIR) -larduino-control -lm
CONTROL_INCFLAGS = -I $(TARGET_INCDIR) -I $(TARGET_INCDIR)/arduino

default: master_main

master_main: 
	mkdir -p $(TARGET_BUILDDIR)
	mkdir -p $(TARGET_INCDIR)/comm
	mkdir -p $(TARGET_INCDIR)/sensor
	mkdir -p $(TARGET_INCDIR)/ros_lib
	cp ./src/comm/*.hpp $(TARGET_INCDIR)/comm
	cp ./src/comm/*.h $(TARGET_INCDIR)/comm
	cp ./src/sensor/*.hpp $(TARGET_INCDIR)/sensor
	cp ./src/sensor/*.h $(TARGET_INCDIR)/sensor
	cp -rf ./src/ros_lib/* $(TARGET_INCDIR)/ros_lib 
	rm -rf $(TARGET_INCDIR)/ros_lib/examples/ 
	rm $(TARGET_INCDIR)/ros_lib/*.cpp
	$(CC) $(MASTER_CFLAGS) $(MASTER_INCFLAGS) $^ -o $(TARGET_BUILDDIR)/main.elf $(MASTER_OBJ) -L $(MASTER_LIBS)
	avr-objcopy -O ihex $(TARGET_BUILDDIR)/main.elf $(TARGET_BUILDDIR)/main.hex

slave_main:
	mkdir -p $(TARGET_BUILDDIR)
	mkdir -p $(TARGET_INCDIR)/comm
	mkdir -p $(TARGET_INCDIR)/sensor
	mkdir -p $(TARGET_INCDIR)/actuator
	mkdir -p $(TARGET_INCDIR)/pid
	mkdir -p $(TARGET_INCDIR)/DynamixelSerial
	cp ./src/comm/*.hpp $(TARGET_INCDIR)/comm
	cp ./src/comm/*.h $(TARGET_INCDIR)/comm
	cp ./src/actuator/*.h $(TARGET_INCDIR)/actuator
	cp ./src/sensor/*.hpp $(TARGET_INCDIR)/sensor
	cp ./src/sensor/*.h $(TARGET_INCDIR)/sensor
	cp ./src/pid/*.h $(TARGET_INCDIR)/pid
	cp ./src/DynamixelSerial/*.h $(TARGET_INCDIR)/DynamixelSerial
	$(CC) $(SLAVE_CFLAGS) $(SLAVE_INCFLAGS) $^ -o $(TARGET_BUILDDIR)/main.elf $(SLAVE_OBJ) $(SLAVE_LIBS)
	avr-objcopy -O ihex $(TARGET_BUILDDIR)/main.elf $(TARGET_BUILDDIR)/main.hex

control_main:
	mkdir -p $(TARGET_BUILDDIR)
	mkdir -p $(TARGET_INCDIR)/PS2X_lib
	mkdir -p $(TARGET_INCDIR)/ros_lib
	cp ./src/PS2X_lib/*.h $(TARGET_INCDIR)/PS2X_lib
	cp -rf ./src/ros_lib/* $(TARGET_INCDIR)/ros_lib 
	rm -rf $(TARGET_INCDIR)/ros_lib/examples/ 
	rm $(TARGET_INCDIR)/ros_lib/*.cpp
	$(CC) $(CONTROL_CFLAGS) $(CONTROL_INCFLAGS) $^ -o $(TARGET_BUILDDIR)/main.elf $(CONTROL_OBJ) $(CONTROL_LIBS)
	avr-objcopy -O ihex $(TARGET_BUILDDIR)/main.elf $(TARGET_BUILDDIR)/main.hex

master_arduino: ARDUINO_CFLAGS=$(MASTER_MCU) $(MASTER_CPU_SPEED) -Os -w
master_arduino: $(ARDUINO_OBJ) 
	mkdir -p $(TARGET_BUILDDIR)
	avr-ar rcs $(TARGET_BUILDDIR)/$(MASTER_LIBNAME) $^
	mkdir -p $(TARGET_INCDIR)/arduino
	mkdir -p $(TARGET_LIBDIR)
	cp $(ARDUINO_SRC)*.h $(TARGET_INCDIR)/arduino
	cp $(TARGET_BUILDDIR)/$(MASTER_LIBNAME) $(TARGET_LIBDIR)
	rm $(ARDUINO_SRC)*.o

slave_arduino: ARDUINO_CFLAGS=$(SLAVE_MCU) $(SLAVE_CPU_SPEED) -Os -w
slave_arduino: $(ARDUINO_OBJ)
	mkdir -p $(TARGET_BUILDDIR)
	avr-ar rcs $(TARGET_BUILDDIR)/$(SLAVE_LIBNAME) $^
	mkdir -p $(TARGET_INCDIR)/arduino
	mkdir -p $(TARGET_LIBDIR)
	cp $(ARDUINO_SRC)*.h $(TARGET_INCDIR)/arduino
	cp $(TARGET_BUILDDIR)/$(SLAVE_LIBNAME) $(TARGET_LIBDIR)
	rm $(ARDUINO_SRC)*.o
	
control_arduino: ARDUINO_CFLAGS=$(CONTROL_MCU) $(CONTROL_CPU_SPEED) -Os -w
control_arduino: $(ARDUINO_OBJ)
	mkdir -p $(TARGET_BUILDDIR)
	avr-ar rcs $(TARGET_BUILDDIR)/$(CONTROL_LIBNAME) $^
	mkdir -p $(TARGET_INCDIR)/arduino
	mkdir -p $(TARGET_LIBDIR)
	cp $(ARDUINO_SRC)*.h $(TARGET_INCDIR)/arduino
	cp $(TARGET_BUILDDIR)/$(CONTROL_LIBNAME) $(TARGET_LIBDIR)
	rm $(ARDUINO_SRC)*.o
	
.PHONY: master_upload
master_upload:
	avrdude -V -F -D -p $(MASTER_MCU_TAG) -c $(MASTER_UPLOAD_PROTOCOL) -b $(MASTER_UPLOAD_BAUDRATE) -Uflash:w:$(TARGET_BUILDDIR)/main.hex -P$(MASTER_PORT)

.PHONY: slave_upload
slave_upload:
	avrdude -V -F -D -p $(SLAVE_MCU_TAG) -c $(SLAVE_UPLOAD_PROTOCOL) -b $(SLAVE_UPLOAD_BAUDRATE) -Uflash:w:$(TARGET_BUILDDIR)/main.hex -P$(SLAVE_PORT)

.PHONY: control_upload
control_upload:
	avrdude -V -F -D -p $(CONTROL_MCU_TAG) -c $(CONTROL_UPLOAD_PROTOCOL) -b $(CONTROL_UPLOAD_BAUDRATE) -Uflash:w:$(TARGET_BUILDDIR)/main.hex -P$(CONTROL_PORT)

.PHONY: clean
clean:
	# $(shell rm $(TARGET_INCDIR)/*.h 2> /dev/null)
	rm -rf $(TARGET_INCDIR)
	rm -rf $(TARGET_LIBDIR)
	rm -rf $(TARGET_BUILDDIR)

%.o : %.c
	$(CC) $< $(ARDUINO_CFLAGS) $(ARDUINO_INC) -c -o $@
    
%.o : %.cpp
	$(CXX) $< $(ARDUINO_CFLAGS) $(ARDUINO_INC) -c -o $@

