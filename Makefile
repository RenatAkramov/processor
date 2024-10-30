all: compiler clean processor


fg = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp

compiler.exe: compiler1.o stack3.o
	g++ compiler1.o stack3.o -o compiler.exe

proc.exe: processor1.o stack3.o 
	g++ processor1.o stack3.o -o proc.exe

processor1.o: processor1.cpp
	g++ -c $(fg) processor1.cpp

stack3.o: stack3.cpp
	g++ -c $(fg) stack3.cpp

compiler1.o: compiler1.cpp
	g++ -c $(fg) compiler1.cpp

processor: proc.exe
	.\proc.exe

compiler: compiler.exe
	.\compiler.exe



