all: assembler processor clean

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

assembler: Assembler.o
	g++ Assembler.o -o .\a.exe

processor: processor1.o stack3.o
	g++ processor1.o stack3.o -o .\a.exe

processor1.o: ./procces/processor1.cpp
	g++ -I ./include/ -c $(flags) ./procces/processor1.cpp

Assembler.o: ./assembler/Assembler.cpp
	g++ -I ./include/ -c $(flags) ./assembler/Assembler.cpp

stack3.o: ./stack/stack3.cpp
	g++ -I ./include/ -c $(flags) ./stack/stack3.cpp

clean:
	rm -rf *.o *.exe 


