#include <SDL.h>
#include "headers/Draw.h"
#include "headers/EventListener.h"
#include "headers/globals.h"
#include "headers/ChessBoard.h"
#include <iostream>

void mainfunction(ChessBoard& chessBoard, Draw& draw){
    draw.clearScreen(255, 255, 255, 255);
    chessBoard.draw(draw);
    draw.present();
}

int main(int argc, char *argv[]) {

    ChessBoard chessBoard;
    //event listener
    EventListener eventListener;

    //SDL initialize
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Errore nell'inizializzazione di SDL2: %s\n", SDL_GetError());
        return -1;
    }
    //create Window
    SDL_Window *window = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Errore nella creazione della finestra: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    //renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (!renderer) {
        printf("Errore nella creazione del renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    //draw
    Draw draw(*renderer);

    //timing variables
    float time = 0.0f;
    int frameCount = 0;
    int currentFPS = 0;
    const int desiredFPS = 60;
    const int frameDelay = 1000 / desiredFPS;
    Uint32 lastTick = SDL_GetTicks();
    float deltaTime;

    //main loop
    while (running) {
        Uint32 frameStart = SDL_GetTicks();
        deltaTime = (frameStart - lastTick) / 1000.0f;
        lastTick = frameStart;

        time += deltaTime;
        frameCount++;

        if (time >= 1.0f) {
            currentFPS = frameCount;
            frameCount = 0;
            time = 0.0f;
            //std::cout << currentFPS << std::endl;
        }
        eventListener.listenEvents();

        mainfunction(chessBoard, draw);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //destroy 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}