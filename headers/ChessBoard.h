#pragma once
#include <vector>
#include "objects.h"
#include "stats.h"
#include <unordered_map>
#include "globals.h"
#include "Draw.h"

class ChessBoard {
    public:
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteRooks;
    uint64_t whiteQueens;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackRooks;
    uint64_t blackQueens;
    uint64_t blackKing;

    uint64_t whitePieces;
    uint64_t blackPieces;
    uint64_t allPieces;

    int movesWithoutCaptureOrPawnMove;
    int enPassantSquare;
    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRooksMoved[2];
    bool blackRooksMoved[2];

    unsigned int movesCount;

    ChessBoard();
    ChessBoard(const ChessBoard& other);
    bool operator==(const ChessBoard& other) const;
    std::vector<std::string> operator-(const ChessBoard& other) const;
    
    //invert chessBoard so white pieces are black and black pieces are white
    void invertPieces();
    void draw(Draw& draw);
};