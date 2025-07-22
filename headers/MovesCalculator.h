#pragma once
#include "ChessBoard.h"

class MovesCalculator {
public:
    void removeBlackPiece(ChessBoard& chessBoard, int square);
    std::vector<ChessBoard> whitePawnMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> whiteRookMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> whiteKnightMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> whiteBishopMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> whiteQueenMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> whiteKingMoves(const ChessBoard& chessBoard);
    std::vector<ChessBoard> allMoves(const ChessBoard& chessBoard);
};