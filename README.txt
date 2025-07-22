g++ -std=c++11 -o gravity main.cpp globals.cpp \
classes/Draw.cpp classes/EventListener.cpp classes/ChessBoard.cpp classes/Phisics.cpp classes/MovesHandler.cpp \
classes/Collider.cpp classes/TextureLoader.cpp classes/MovesCalculator.cpp \
-I/opt/homebrew/opt/sdl2/include/SDL2 \
-I/opt/homebrew/opt/sdl2_image/include/SDL2 \
-L/opt/homebrew/opt/sdl2/lib \
-L/opt/homebrew/opt/sdl2_image/lib \
-lSDL2 -lSDL2_image