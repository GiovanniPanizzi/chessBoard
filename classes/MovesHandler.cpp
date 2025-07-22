#include "../headers/MovesHandler.h"
#include <iostream>

void MovesHandler::handleMouseClick(ChessBoard& chessBoard, EventListener& eventListener, Draw& draw) {
    if (eventListener.isLeftMousePressed()) {
        int mouseX = eventListener.getMouseX();
        int mouseY = eventListener.getMouseY();

        // Calculate the index of the square based on mouse position
        int squareIndex = (7 - mouseY / tileSize) * 8 + (7 - mouseX / tileSize);

        if (selectedFirstSquare == -1) {
            selectedFirstSquare = squareIndex;
            std::cout << "Selected first square: " << selectedFirstSquare << std::endl;
        } else {
            if(squareIndex != selectedFirstSquare) {
                selectedSecondSquare = squareIndex;
                std::cout << "Selected second square: " << selectedSecondSquare << std::endl;
                makeMove(chessBoard, selectedFirstSquare, selectedSecondSquare);
                selectedFirstSquare = -1;
                selectedSecondSquare = -1;
            }
        }
    }
}

void MovesHandler::makeMove(ChessBoard& chessBoard, int firstSquare, int secondSquare) {
    // Check if the move is valid
    if (isValidMove(chessBoard, firstSquare, secondSquare)) {
        // Update the chessboard state
        uint64_t piece = 1ULL << firstSquare;
        if (chessBoard.whitePieces & piece) {
            std::cout << "Moving white piece from " << firstSquare << " to " << secondSquare << std::endl;
            chessBoard.whitePieces &= ~piece;
            chessBoard.whitePieces |= (1ULL << secondSquare);
            // check what piece is on the first square
            if (chessBoard.whitePawns & piece) {
                chessBoard.whitePawns &= ~piece;
                chessBoard.whitePawns |= (1ULL << secondSquare);
            } else if (chessBoard.whiteKnights & piece) {
                chessBoard.whiteKnights &= ~piece;
                chessBoard.whiteKnights |= (1ULL << secondSquare);
            } else if (chessBoard.whiteBishops & piece) {
                chessBoard.whiteBishops &= ~piece;
                chessBoard.whiteBishops |= (1ULL << secondSquare);
            } else if (chessBoard.whiteRooks & piece) {
                chessBoard.whiteRooks &= ~piece;
                chessBoard.whiteRooks |= (1ULL << secondSquare);
            } else if (chessBoard.whiteQueens & piece) {
                chessBoard.whiteQueens &= ~piece;
                chessBoard.whiteQueens |= (1ULL << secondSquare);
            } else if (chessBoard.whiteKing & piece) {
                chessBoard.whiteKing &= ~piece;
                chessBoard.whiteKing |= (1ULL << secondSquare);
                //short castle
                if(secondSquare == 6){
                    chessBoard.whiteRooks &= ~(1ULL << 7);
                    chessBoard.whiteRooks |= (1ULL << 5);
                }
                //long castle
                else if(secondSquare == 1){
                    chessBoard.whiteRooks &= ~(1ULL << 0);
                    chessBoard.whiteRooks |= (1ULL << 2);
                }
            }
            movesCalculator.removeBlackPiece(chessBoard, secondSquare);
        }
        chessBoard.movesCount++;
        chessBoard.invertPieces();
    }
}

bool MovesHandler::isValidMove(ChessBoard& chessBoard, int firstSquare, int secondSquare) {
    std::vector<ChessBoard> possibleMoves = movesCalculator.allMoves(chessBoard);
    ChessBoard newBoard = chessBoard;
    newBoard.movesCount++;
    newBoard.whitePieces &= ~(1ULL << firstSquare);
    newBoard.whitePieces |= (1ULL << secondSquare);
    //check what piece is on the first square
    if (chessBoard.whitePieces & (1ULL << firstSquare)) {
        if(chessBoard.whitePawns & (1ULL << firstSquare)) {
            newBoard.whitePawns &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whitePawns |= (1ULL << secondSquare);
        }
        else if(chessBoard.whiteKnights & (1ULL << firstSquare)) {
            newBoard.whiteKnights &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whiteKnights |= (1ULL << secondSquare);
        }
        else if(chessBoard.whiteBishops & (1ULL << firstSquare)) {
            newBoard.whiteBishops &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whiteBishops |= (1ULL << secondSquare);
        }
        else if(chessBoard.whiteRooks & (1ULL << firstSquare)) {
            newBoard.whiteRooks &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whiteRooks |= (1ULL << secondSquare);
        }
        else if(chessBoard.whiteQueens & (1ULL << firstSquare)) {
            newBoard.whiteQueens &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whiteQueens |= (1ULL << secondSquare);
        }
        else if(chessBoard.whiteKing & (1ULL << firstSquare)) {
            newBoard.whiteKing &= ~(1ULL << firstSquare);
            movesCalculator.removeBlackPiece(newBoard, secondSquare);
            newBoard.whiteKing |= (1ULL << secondSquare);
            //short castle
            if(firstSquare == 4 && secondSquare == 6){
                newBoard.whiteRooks &= ~(1ULL << 7);
                newBoard.whiteRooks |= (1ULL << 5);
            }
            //long castle
            else if(firstSquare == 4 && secondSquare == 1){
                newBoard.whiteRooks &= ~(1ULL << 0);
                newBoard.whiteRooks |= (1ULL << 2);
            }
        }
    }
    for(auto& move : possibleMoves) {
        if (move == newBoard) {
            return true; 
        }
    }
    std::cout << "Move from " << firstSquare << " to " << secondSquare << " is not valid." << std::endl;
    return false;
}