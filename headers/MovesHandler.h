#pragma once
#include "ChessBoard.h"
#include "MovesCalculator.h"
#include "EventListener.h"
#include "Draw.h"

class MovesHandler {
    private:
    MovesCalculator movesCalculator;
    int selectedFirstSquare = -1;
    int selectedSecondSquare = -1;

    public:
    void handleMouseClick(ChessBoard& chessBoard, EventListener& eventListener, Draw& draw);
    bool isValidMove(ChessBoard& chessBoard, int firstSquare, int secondSquare);
    void makeMove(ChessBoard& chessBoard, int firstSquare, int secondSquare);
};