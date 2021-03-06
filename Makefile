OUT=ChannelRouter.bin
FLAGS=-DTEXT_RENDER
SRCS=src/main.cpp src/graph.cpp

ifeq ($(USER),levons)
	LIBS=-L ~/levi/downloads/SDL2-2.0.5/build/.libs -lSDL2 -lfreetype -ldl -lrt
	INCLS=-I ~/levi/downloads/SDL2-2.0.5/include 
else
	LIBS=./deps/linux64/SDL2/libSDL2.a ./deps/linux64/SDL2_ttf/libSDL2_ttf.a -lfreetype -ldl -lrt
	INCLS=-I ./deps/linux64/SDL2/include -I ./deps/linux64/SDL2_ttf
endif

ifeq ($(OS),Windows_NT)
	OUT=ChannelRouter.exe
	FLAGS=-static-libstdc++ -DOS_WINDOWS -lmingw32
	LIBS=-L ./deps/win/SDL2/lib/win32 -lSDL2 ./deps/win/SDL2/lib/win32/SDL2.lib ./deps/win/SDL2/lib/win32/SDL2main.lib ./deps/win/SDL2/lib/win32/SDL2test.lib
	#LIBS=./deps/win/SDL2/lib/win32/SDL2.lib 
	INCLS=-I ./deps/win/SDL2/include
	#cp ./deps/win/SDL2/lib/win32/SDL2.dll ./bin
endif



default:
	#cd ./src
	clear
	rm -f ./bin/$(OUT) 
    # g++  -DOS_WINDOWS $(SRCS) -o ./bin/$(OUT) -I ./deps/win/SDL2/include -L ./deps/win/SDL2/lib/win32  -lmingw32 -lSDl2 -static-libgcc -static-libstdc++
	# g++ -Wfatal-errors -g $(SRCS) $(FLAGS) $(INCLS) $(LIBS) -o ./bin/$(OUT)
	g++ -std=c++0x -Wfatal-errors -g $(SRCS) -o ./bin/$(OUT)