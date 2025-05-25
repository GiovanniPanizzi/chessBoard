#pragma once
#include "ChessBoard.h"

class MovesCalculator {
    public:
    ChessBoard blackPawnMoves(ChessBoard chessBoard);
    ChessBoard blackRookMoves(ChessBoard chessBoard);
    ChessBoard blackKnightMoves(ChessBoard chessBoard);
    ChessBoard blackBishopMoves(ChessBoard chessBoard);
    ChessBoard blackQueenMoves(ChessBoard chessBoard);
    ChessBoard blackKingMoves(ChessBoard chessBoard);

    ChessBoard whitePawnMoves(ChessBoard chessBoard);
    ChessBoard whiteRockMoves(ChessBoard chessBoard);
    ChessBoard whiteKnightMoves(ChessBoard chessBoard);
    ChessBoard whiteBishopMoves(ChessBoard chessBoard);
    ChessBoard whiteQueenMoves(ChessBoard chessBoard);
    ChessBoard whiteKingMoves(ChessBoard chessBoard);

    ChessBoard allMoves(ChessBoard chessBoard);
};