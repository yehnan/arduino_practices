# Arduino makefile
#
# This makefile allows you to build sketches from the cygwin command line
# without the Arduino environment (or Java). And allows you to upload program
# to Arduino board from the cygwin command line.
#
# However, you still need to install Arduino software.
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
#   - Put all source files of your program in one directory.
#     Don't create sub-directory and put source files in it.
#     Put thie makefile with your program's source files.
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
#   - Modify the line containing "PROJECT" to refer to any name you
#     want. This will be the filename of final built products(.elf, .hex, .eep).
#
#   - All files(.c and .cpp) in the same directory with this makefile,
#     will be treated as source files.
#     
#   - Modify the line containg "INSTALL_PATH" to point to the directory that
#     contains the Arduino software.
#     This directory should contains arduino.exe, hardware, libraries, etc..
#
#     Modify the line containing "SKETCHBOOK" to point to the sketchbook directory.
#
#     If needed, modify "CORE". Should point to the directory that
#     contains the Arduino core source files.
#     This directory should contains Arduino.h, wiring_analog.c, Print.cpp, etc..
#
#     If needed, modify "BUILTINLIB". Should pont to the directory that
#     contains built-in libraries.
#     This directory probably contains directories EEPROM, Ethernet, LiquidCrystal, etc..
#
#     If needed, modify "THIRDPARTYLIB". Should point the third-party libraries directory.
#     This directory contains the libraries you installed.
#     This directory probably is inside the sketchbook directory.
#
#   - To use built-in libraries(e.g. EEPROM, Ethernet, LiquidCrystal, etc..),
#     add the names of libraries you want to use 
#     in the line containing "BUILTINLIB_ENABLED"
#
#   - To use third-party libraries(for example, BOUNCE),
#     put the directory containing the library inside "THIRDPARTYLIB" path.
#     add the names of libraries you want to use 
#     in the line containing "THIRDPARTYLIB_ENABLED"
#
#   - Modify the line containing "PORT" to refer to the filename
#     representing the USB or serial connection to your Arduino board
#     (e.g. \\.\COM3 on Windows, /dev/tty.USB0 on Linux). If the exact name of this file
#     changes, you can use * as a wildcard (e.g. PORT = /dev/tty.USB*).
#     Modify "UPLODA_RATE" to meet your serial port.
#
#   - Change "MCU", "ARDUINO_VERSION" to meet your need.
#     Probably don't need to change "F_CPU".
#
#   - At the command line, change to the directory containing your
#     program's file and the makefile.
#
#   - Use "make depend" to generate depencies.
#     Use "make" compile/verify your program.
#     Use "make upload", reset your Arduino board, to
#       upload your program to the Arduino board.
#     Use "make clean" to delete all intermediate files(.o, .a, etc..) and
#       all built product files(.hex, .elf, .eep).
#
# $Id$

PROJECT := BlinkMakefile

# built-in libraries
# EEPROM Ethernet Firmata LiquidCrystal SD Servo SoftwareSerial SPI Stepper Wire
BUILTINLIB_ENABLED := 

# third-party libraries
THIRDPARTYLIB_ENABLED := 

MCU := atmega328p
F_CPU := 16000000L
ARDUINO_VERSION := 100
FORMAT := ihex
UPLOAD_RATE := 115200
#PORT := /dev/tty.usbserial*
PORT := \\.\COM3

#the topmost path to the arduino software
INSTALL_PATH := D:/Arduino/arduino-1.0
#path to arduino core source files and header files
CORE := $(INSTALL_PATH)/hardware/arduino/cores/arduino
#path to arduino built-in libraries
BUILTINLIB := $(INSTALL_PATH)/libraries
#path to sketchbook
SKETCHBOOK := D:/Arduino/sketchbook
#path to third-party libraries
THIRDPARTYLIB := $(SKETCHBOOK)/libraries

# Name of this Makefile (used for "make depend").
MAKEFILE := Makefile

###source files for the project
#PROJ_SOURCE := foo.c bar.cpp BlinkMakefile.cpp
ifndef PROJ_SOURCE
PROJ_SOURCE := $(wildcard *.c) $(wildcard *.cpp)
endif

PROJSRC := $(filter %.c, $(PROJ_SOURCE))
PROJCXXSRC := $(filter %.cpp, $(PROJ_SOURCE))

#CORESOURCEFILE := WInterrupts.c wiring.c wiring_analog.c wiring_digital.c \
#  wiring_pulse.c wiring_shift.c \
#  CDC.cpp HardwareSerial.cpp HID.cpp IPAddress.cpp \
#  Print.cpp Stream.cpp Tone.cpp USBCore.cpp \
#  WMath.cpp WString.cpp main.cpp new.cpp 
ifndef CORESOURCEFILE
CORESOURCE := $(wildcard $(CORE)/*.c) $(wildcard $(CORE)/*.cpp)
else
CORESOURCE := $(foreach fp, $(CORESOURCEFILE), $(CORE)/$(fp))
endif

CORESRC := $(filter %.c, $(CORESOURCE))
CORECXXSRC := $(filter %.cpp, $(CORESOURCE))

#
BUILTINLIB_DIRS = $(foreach dir, $(BUILTINLIB_ENABLED), $(BUILTINLIB)/$(dir))
BUILTINLIB_DIRS += $(foreach dir, $(BUILTINLIB_ENABLED), $(shell test -d $(BUILTINLIB)/$(dir)/utility && echo $(BUILTINLIB)/$(dir)/utility))

BUILTINLIB_SRC = $(foreach path, $(BUILTINLIB_DIRS), $(wildcard $(path)/*.c))
BUILTINLIB_CXXSRC = $(foreach path, $(BUILTINLIB_DIRS), $(wildcard $(path)/*.cpp))

#
THIRDPARTYLIB_DIRS = $(foreach dir, $(THIRDPARTYLIB_ENABLED), $(THIRDPARTYLIB)/$(dir))
THIRDPARTYLIB_DIRS += $(foreach dir, $(THIRDPARTYLIB_ENABLED), $(shell test -d $(THIRDPARTYLIB)/$(dir)/utility && echo $(THIRDPARTYLIB)/$(dir)/utility))

THIRDPARTYLIB_SRC = $(foreach path, $(THIRDPARTYLIB_DIRS), $(wildcard $(path)/*.c))
THIRDPARTYLIB_CXXSRC = $(foreach path, $(THIRDPARTYLIB_DIRS), $(wildcard $(path)/*.cpp))

#
SRC = $(PROJSRC) $(CORESRC) $(BUILTINLIB_SRC) $(THIRDPARTYLIB_SRC)
CXXSRC = $(PROJCXXSRC) $(CORECXXSRC) $(BUILTINLIB_CXXSRC) $(THIRDPARTYLIB_CXXSRC)

#
CDEFS := -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION)
CXXDEFS := -DF_CPU=$(F_CPU) -DARDUINO=$(ARDUINO_VERSION)

# Place -I options here
COMMON_INCS =  -I. -I$(CORE) -I$(CORE)/../../variants/standard
COMMON_INCS += $(foreach path, $(BUILTINLIB_DIRS), -I$(path))
COMMON_INCS += $(foreach path, $(THIRDPARTYLIB_DIRS), -I$(path))

CINCS := $(COMMON_INCS)
CXXINCS := $(COMMON_INCS)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD := -std=gnu99
CDEBUG := -g
OPT = s
CWARN := -Wall
CEXTRA :=  -ffunction-sections -fdata-sections
CXXEXTRA := -fno-exceptions -ffunction-sections -fdata-sections

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
AVRDUDE_PROGRAMMER := arduino
AVRDUDE_PORT := $(PORT)
AVRDUDE_WRITE_FLASH := -U flash:w:$(PROJECT).hex:i
AVRDUDE_FLAGS := -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) \
  -b $(UPLOAD_RATE) -D -v

# Program settings
CC := avr-gcc
CXX := avr-g++
AR := avr-ar
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE := avr-size
NM := avr-nm
AVRDUDE := avrdude
REMOVE := rm -f
MV := mv -f

ARFLAGS = rcs

# Define all listing files.
LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Default target.
# @avr-size $(PROJECT).elf
all: build

build: elf hex eep

elf: $(PROJECT).elf
hex: $(PROJECT).hex
eep: $(PROJECT).eep
lss: $(PROJECT).lss 
sym: $(PROJECT).sym

# upload the program to the arduino board
upload: $(PROJECT).hex $(PROJECT).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 

coff: $(PROJECT).elf
	$(COFFCONVERT) -O coff-avr $(PROJECT).elf $(PROJECT).cof

extcoff: $(PROJECT).elf
	$(COFFCONVERT) -O coff-ext-avr $(PROJECT).elf $(PROJECT).cof


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
PROJOBJ = $(PROJSRC:.c=.o) $(PROJCXXSRC:.cpp=.o) $(PROJASRC:.S=.o)

COREOBJ = $(CORESRC:.c=.o) $(CORECXXSRC:.cpp=.o) $(COREASRC:.S=.o)

BUILTINLIB_OBJ = $(BUILTINLIB_SRC:.c=.o) $(BUILTINLIB_CXXSRC:.cpp=.o)

THIRDPARTYLIB_OBJ = $(THIRDPARTYLIB_SRC:.c=.o) $(THIRDPARTYLIB_CXXSRC:.cpp=.o)


CORE_A = $(CORE)/core.a
$(CORE_A): $(COREOBJ)
	$(AR) rcs $(CORE_A) $(COREOBJ)

BUILTINLIB_A = $(BUILTINLIB)/builtinlib.a
$(BUILTINLIB_A): $(BUILTINLIB_OBJ)
	$(AR) rcs $(BUILTINLIB_A) $(BUILTINLIB_OBJ)

THIRDPARTYLIB_A = $(THIRDPARTYLIB)/thirdparty.a
$(THIRDPARTYLIB_A): $(THIRDPARTYLIB_OBJ)
	$(AR) rcs $(THIRDPARTYLIB_A) $(THIRDPARTYLIB_OBJ)

# Link: create ELF output file from object files.
$(PROJECT).elf: $(PROJOBJ) $(CORE_A) $(BUILTINLIB_A) $(THIRDPARTYLIB_A)
	$(CC) $(ALL_CFLAGS) $(PROJOBJ) $(CORE_A) $(BUILTINLIB_A) $(THIRDPARTYLIB_A) -lm --output $@ $(LDFLAGS)

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
clean: mostlyclean
	@echo Cleaning Arduino core intermediate files
	@$(REMOVE) $(COREOBJ) $(CORE_A)
	@echo Cleaning Arduino built-in libraries intermediate files
	@$(REMOVE) $(BUILTINLIB_OBJ) $(BUILTINLIB_A)
	@echo Cleaning third-party libraries intermediate files
	@$(REMOVE) $(THIRDPARTYLIB_OBJ) $(THIRDPARTYLIB_A)
	@echo Cleaning LST and other files
	@$(REMOVE) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d)

mostlyclean:
	@echo Cleaning product files of the projct
	@$(REMOVE) $(PROJECT).hex $(PROJECT).eep $(PROJECT).cof $(PROJECT).elf \
	$(PROJECT).map $(PROJECT).sym $(PROJECT).lss
	@echo Cleaning intermediate files of the project
	@$(REMOVE) $(PROJOBJ) 

depend:
	if grep '^# DO NOT DELETE' $(MAKEFILE) >/dev/null; \
	then \
		sed -e '/^# DO NOT DELETE/,$$d' $(MAKEFILE) > \
			$(MAKEFILE).$$$$ && \
		$(MV) $(MAKEFILE).$$$$ $(MAKEFILE); \
	fi
	echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' >> $(MAKEFILE)
	#$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(SRC) $(ASRC) >> $(MAKEFILE)
	#$(CXX) -M -mmcu=$(MCU) $(CXXDEFS) $(CXXINCS) $(CXXSRC) $(ASRC) >> $(MAKEFILE)
	for F in $(SRC); do \
	D=`dirname $$F | sed "s/^\.\///"`; \
	echo -n "$$D/" >> $(MAKEFILE); \
	$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(ASRC) $$F \
	>> $(MAKEFILE); \
	done
	for F in $(CXXSRC); do \
	D=`dirname $$F | sed "s/^\.\///"`; \
	echo -n "$$D/" >> $(MAKEFILE); \
	$(CXX) -M -mmcu=$(MCU) $(CXXDEFS) $(CXXINCS) $(ASRC) $$F \
	>> $(MAKEFILE); \
	done

.PHONY:	all build upload elf hex eep lss sym coff extcoff clean mostlyclean depend

