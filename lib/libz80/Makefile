SOURCES = z80.c
FLAGS = -fPIC -Wall -ansi -g

force: clean all

all: libz80.so

libz80.so: z80.h $(OBJS)
	cd codegen && make opcodes
	gcc $(FLAGS) -c -o libz80.o $(SOURCES)

install:
	install -m 666 libz80.so /usr/lib
	install -m 666 z80.h /usr/include

clean:
	rm -f *.o *.so core
	cd codegen && make clean

realclean: clean
	rm -rf doc

doc:	*.h *.c
	doxygen

