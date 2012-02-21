# Arduino makefile
#
# This makefile allows you to build sketches from the cygwin command line
# without the Arduino environment (or Java). And allows you to upload program
# to Arduino board from the cygwin command line.
#
# My environment is Windows XP, Cygwin(version of make is 2.80), and
# Arduino 1.0.
#
# If you're using versions older than Arduion 1.0, you may need to do
# some changes.
#
# The Arduino environment does some pre-processing on a sketch before
# compiling it.  If you're using this makefile instead, you'll need to do
# a few things differently:
#
#   - Give your program's file a .cpp extension (e.g. xxx.cpp).
#
#   - At top of code: #include <Arduino.h>
#     note: Arduino.h exits in 1.0, older version may use WProgram.h
#
#   - Write prototypes for all your functions (or define them before you
#     call them).  A prototype declares the types of parameters a
#     function will take and what type of value it will return.  This
#     means that you can have a call to a function before the definition
#     of the function.  A function prototype looks like the first line of
#     the function, with a semi-colon at the end.  For example:
#     int digitalRead(int pin);
#
# How to use this makefile:
#
#  1. Copy this file into the folder with your sketch.
#
#  2. Modify the line containing "TARGET" to refer to any name you
#     want. This will be the filename of final built products(.elf, .hex, .eep).
#
#  3. Put your C source files after PROJSRC.
#     Put your C++ source files after PROJCXXSRC.
#
#  3. Modify the line containg "ARDUINO" to point the directory that
#     contains the Arduino core.
#     This directory should contains Arduino.h, wiring_digital.c, wiring_shift.c, etc..
#
#  4. Modify the line containing "PORT" to refer to the filename
#     representing the USB or serial connection to your Arduino board
#     (e.g. \\.\COM3 on Windows, /dev/tty.USB0 on Linux). If the exact name of this file
#     changes, you can use * as a wildcard (e.g. PORT = /dev/tty.USB*).
#     Modify "UPLODA_RATE" to meet your serial port.
#
#  5. Change "MCU", "ARDUINO_VERSION" to meet your need.
#     Probably don't need to change "F_CPU".
#  6. At the command line, change to the directory containing your
#     program's file and the makefile.
#
#  7. Use "make" compile/verify your program.
#     Use "make upload", reset your Arduino board, to
#     upload your program to the Arduino board.
#     Use "make clean" to delete all intermediate files(.o, .a, etc..) and
#     all built product files(.hex, .elf, .eep).
#
# $Id$

TARGET = BlinkMakefile

PROJSRC = foo.c
PROJCXXSRC = BlinkMakefile.cpp bar.cpp

MCU = atmega328p
F_CPU = 16000000L
ARDUINO_VERSION = 100
FORMAT = ihex
UPLOAD_RATE = 115200
#PORT = /dev/tty.usbserial*
PORT = \\.\COM3

# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

#core source and header files of arduino
#ARDUINO = /cygdrive/d/Arduino/arduino-1.0/hardware/arduino/cores/arduino
ARDUINO = D:/Arduino/arduino-1.0/hardware/arduino/cores/arduino

CORESRC = $(ARDUINO)/WInterrupts.c $(ARDUINO)/wiring.c $(ARDUINO)/wiring_analog.c \
  $(ARDUINO)/wiring_digital.c $(ARDUINO)/wiring_pulse.c $(ARDUINO)/wiring_shift.c

CORECXXSRC = $(ARDUINO)/CDC.cpp $(ARDUINO)/HardwareSerial.cpp \
  $(ARDUINO)/HID.cpp $(ARDUINO)/IPAddress.cpp $(ARDUINO)/main.cpp $(ARDUINO)/new.cpp \
  $(ARDUINO)/Print.cpp $(ARDUINO)/Stream.cpp $(ARDUINO)/Tone.cpp $(ARDUINO)/USBCore.cpp \
  $(ARDUINO)/WMath.cpp $(ARDUINO)/WString.cpp

SRC = $(PROJSRC) $(CORESRC)
CXXSRC = $(PROJCXXSRC) $(CORECXXSRC)

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION)
CXXDEFS = -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION)

# Place -I options here
CINCS = -I. -I$(ARDUINO) -I$(ARDUINO)/../../variants/standard
CXXINCS = -I. -I$(ARDUINO) -I$(ARDUINO)/../../variants/standard

OPT = s

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99
CDEBUG = -g
CWARN = -Wall
CEXTRA =  -ffunction-sections -fdata-sections
CXXEXTRA = -fno-exceptions -ffunction-sections -fdata-sections

CFLAGS = $(CDEFS) $(CDEBUG) -O$(OPT) $(CWARN) $(CEXTRA) $(CSTANDARD) $(CINCS)
CXXFLAGS = $(CXXDEFS) $(CDEBUG) -O$(OPT) $(CWARN) $(CXXEXTRA) $(CXXINCS)
#ASFLAGS = -I. -Wa,-adhlns=$(<:.S=.lst),-gstabs 
LDFLAGS = 

# Combine all necessary flags and optional flags.
# Add target processor to flags.
#-Wl,--gc-sections
ALL_CFLAGS = -mmcu=$(MCU) $(CFLAGS)
ALL_CXXFLAGS = -mmcu=$(MCU) $(CXXFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -x assembler-with-cpp $(ASFLAGS)

# Programming support using avrdude. Settings and variables.
#AVRDUDE_PROGRAMMER = stk500
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex:i
AVRDUDE_FLAGS = -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) \
  -b $(UPLOAD_RATE) -D -v


# Program settings
CC = avr-gcc
CXX = avr-g++
AR = avr-ar
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
MV = mv -f

ARFLAGS = rcs

# Define all listing files.
LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Default target.
all: build

build: elf hex eep

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss 
sym: $(TARGET).sym

# Program the device.  
upload: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 

coff: $(TARGET).elf
	$(COFFCONVERT) -O coff-avr $(TARGET).elf $(TARGET).cof

extcoff: $(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr $(TARGET).elf $(TARGET).cof


.SUFFIXES: .elf .eep .hex .lss .sym

.elf.eep:
	-$(OBJCOPY) -O $(FORMAT) -j .eeprom --set-section-flags=.eeprom=alloc,load \
	--no-change-warnings --change-section-lma .eeprom=0 $< $@

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
.elf.sym:
	$(NM) -n $< > $@

# Define all object files.
OBJ = $(SRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)

PROJOBJ = $(PROJSRC:.c=.o) $(PROJCXXSRC:.cpp=.o) $(PROJASRC:.S=.o)

COREOBJ = $(CORESRC:.c=.o) $(CORECXXSRC:.cpp=.o) $(COREASRC:.S=.o)
core.a: $(COREOBJ)
	$(AR) rcs core.a $(COREOBJ)

# Link: create ELF output file from object files.
$(TARGET).elf: $(PROJOBJ) core.a 
	$(CC) $(ALL_CFLAGS) $(PROJOBJ) core.a -lm --output $@ $(LDFLAGS)

# Compile: create object files from C++ source files.
.cpp.o:
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

# Compile: create object files from C source files.
.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


# Compile: create assembler files from C source files.
.c.s:
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@



# Target: clean project.
clean:
	$(REMOVE) $(TARGET).hex $(TARGET).eep $(TARGET).cof $(TARGET).elf \
	$(TARGET).map $(TARGET).sym $(TARGET).lss core.a \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d)

depend:
	if grep '^# DO NOT DELETE' $(MAKEFILE) >/dev/null; \
	then \
		sed -e '/^# DO NOT DELETE/,$$d' $(MAKEFILE) > \
			$(MAKEFILE).$$$$ && \
		$(MV) $(MAKEFILE).$$$$ $(MAKEFILE); \
	fi
	echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' \
		>> $(MAKEFILE); \
	$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(SRC) $(ASRC) >> $(MAKEFILE)

.PHONY:	all build elf hex eep lss sym program coff extcoff clean depend
