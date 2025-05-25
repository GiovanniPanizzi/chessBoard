#pragma once
#include <vector>
#include "objects.h"
#include "stats.h"
#include <unordered_map>
#include "Draw.h"

class ChessBoard {
    public:
    size_t index;
    std::vector<Entity> whitePawns;
    std::vector<Entity> whiteRooks;
    std::vector<Entity> whiteKnights;
    std::vector<Entity> whiteBishops;
    std::vector<Entity> whiteQueens;
    std::vector<Entity> whiteKing;

    std::vector<Entity> blackPawns;
    std::vector<Entity> blackRooks;
    std::vector<Entity> blackKnights;
    std::vector<Entity> blackBishops;
    std::vector<Entity> blackQueens;
    std::vector<Entity> blackKing;

    std::unordered_map<size_t, Position> positions;

    ChessBoard();
    void draw(Draw& draw);
};