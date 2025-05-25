#include "../headers/ChessBoard.h"

ChessBoard::ChessBoard() {
    index = 0;

    for (int i = 0; i < 8; i++) {
        whitePawns.push_back({index});
        positions[index++] = {i, 1};
    }

    for (int i = 0; i < 8; i++) {
        blackPawns.push_back({index});
        positions[index++] = {i, 6};
    }

    whiteRooks.push_back({index});   positions[index++] = {0, 0};
    whiteKnights.push_back({index}); positions[index++] = {1, 0};
    whiteBishops.push_back({index}); positions[index++] = {2, 0};
    whiteQueens.push_back({index});  positions[index++] = {3, 0};
    whiteKing.push_back({index});    positions[index++] = {4, 0};
    whiteBishops.push_back({index}); positions[index++] = {5, 0};
    whiteKnights.push_back({index}); positions[index++] = {6, 0};
    whiteRooks.push_back({index});   positions[index++] = {7, 0};

    blackRooks.push_back({index});   positions[index++] = {0, 7};
    blackKnights.push_back({index}); positions[index++] = {1, 7};
    blackBishops.push_back({index}); positions[index++] = {2, 7};
    blackQueens.push_back({index});  positions[index++] = {3, 7};
    blackKing.push_back({index});    positions[index++] = {4, 7};
    blackBishops.push_back({index}); positions[index++] = {5, 7};
    blackKnights.push_back({index}); positions[index++] = {6, 7};
    blackRooks.push_back({index});   positions[index++] = {7, 7};
}

void ChessBoard::draw(Draw& draw){
    int talesSize = 100;

    /*for(int i = 0; i < 8; i++){
        draw.drawLine(i * talesSize, 0, i * talesSize, talesSize * 8, 0, 0, 0, 255);
        draw.drawLine(0, i * talesSize, talesSize * 8, i* talesSize, 0, 0, 0, 255);
    }*/

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i + j) % 2 == 0){
                draw.drawRect(i * talesSize, j * talesSize, talesSize, talesSize, 0, 0, 0, 255);
            }
            else{
                draw.drawRect(i * talesSize, j * talesSize, talesSize, talesSize, 255, 255, 255, 255);
            }
        }
    }

    for(size_t i = 0; i < whitePawns.size(); i++){
        size_t pieceIndex = whitePawns[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 40;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
    }

    for(size_t i = 0; i < whiteRooks.size(); i++){
        size_t pieceIndex = whiteRooks[i].id;
        Position position = positions[pieceIndex];
        int width = 40;
        int height = 60;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
    }

    for(size_t i = 0; i < whiteBishops.size(); i++){
        size_t pieceIndex = whiteBishops[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 70;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
    }

    for(size_t i = 0; i < whiteKnights.size(); i++){
        size_t pieceIndex = whiteKnights[i].id;
        Position position = positions[pieceIndex];
        int width = 50;
        int height = 50;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
    }

    for(size_t i = 0; i < whiteQueens.size(); i++){
        size_t pieceIndex = whiteQueens[i].id;
        Position position = positions[pieceIndex];
        int width = 40;
        int height = 80;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
    }

    for(size_t i = 0; i < whiteKing.size(); i++){
        size_t pieceIndex = whiteKing[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 60;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 205, 205, 205, 255);
        draw.drawRect(position.x * talesSize + (talesSize - height) / 2, position.y * talesSize + (talesSize - width) / 2, height, width, 205, 205, 205, 255);
    }


    for(size_t i = 0; i < blackPawns.size(); i++){
        size_t pieceIndex = blackPawns[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 40;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
    }

    for(size_t i = 0; i < blackRooks.size(); i++){
        size_t pieceIndex = blackRooks[i].id;
        Position position = positions[pieceIndex];
        int width = 40;
        int height = 60;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
    }

    for(size_t i = 0; i < blackBishops.size(); i++){
        size_t pieceIndex = blackBishops[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 70;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
    }

    for(size_t i = 0; i < blackKnights.size(); i++){
        size_t pieceIndex = blackKnights[i].id;
        Position position = positions[pieceIndex];
        int width = 50;
        int height = 50;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
    }

    for(size_t i = 0; i < blackQueens.size(); i++){
        size_t pieceIndex = blackQueens[i].id;
        Position position = positions[pieceIndex];
        int width = 40;
        int height = 80;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
    }

    for(size_t i = 0; i < blackKing.size(); i++){
        size_t pieceIndex = blackKing[i].id;
        Position position = positions[pieceIndex];
        int width = 30;
        int height = 60;
        draw.drawRect(position.x * talesSize + (talesSize - width) / 2, position.y * talesSize + (talesSize - height) / 2, width, height, 50, 50, 50, 255);
        draw.drawRect(position.x * talesSize + (talesSize - height) / 2, position.y * talesSize + (talesSize - width) / 2, height, width, 50, 50, 50, 255);
    }

}