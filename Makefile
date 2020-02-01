
export
BASEDIR := $(PWD)
BINDIR := $(BASEDIR)/bin
SRCDIR := $(BASEDIR)/src
LIBDIR := $(BASEDIR)/lib
INCDIR := $(BASEDIR)/include

ROMNAME := zx81.rom
BINARY_NAME := zx81

CPU := soft-float
CC := gcc
LD := ld
AS := as
AR := ar
CPY := objcopy
CCFLAGS := -no-pie -Wall -I $(PWD)/lib/libz80/ -include $(PWD)/lib/libz80/z80.h -I $(INCDIR)

SOURCES := $(shell find $(BASEDIR)/src -name '*.c')
LIBS = ./lib/libz80/libz80.o
OBJECTS := $(patsubst $(BASEDIR)/%.c, $(BINDIR)/%.o, $(SOURCES))

########################################

.PHONY: all clean distclean run
all:
	rm -f $(INCDIR)/rom.h && cd $(INCDIR) && xxd -i $(ROMNAME) > $(INCDIR)/rom.h
	$(MAKE) $(BINARY_NAME)

clean:
	rm -f $(INCDIR)/rom.h
	rm -rf $(BINDIR)/* -vf
	find ./ -maxdepth 10 -type l -delete
	cd ./lib/libz80 && make clean

run-debug: all
	$(BINDIR)/$(BINARY_NAME) -r $(INCDIR)/$(ROMNAME) -d

run: all
	$(BINDIR)/$(BINARY_NAME)

.SECONDEXPANSION:
$(OBJECTS): $$(patsubst $$(BINDIR)%.o, $$(BASEDIR)%.c, $$@)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $(patsubst $(BINDIR)%, $(BASEDIR)%, $(@:%.o=%.c)) -o $@

$(BINARY_NAME): $(OBJECTS) $(LIBS)
	$(CC) -no-pie -lGLEW -lGL -lSDL2 -lSDL2_image -lm -lc $(BINDIR)/*.o $(OBJECTS) -o $(BINDIR)/$(BINARY_NAME)

#-------------------------------------------------

.PHONY: libs-clean
$(LIBS):
	cd ./lib/libz80 && make
	cp ./lib/libz80/libz80.o $(BINDIR)
