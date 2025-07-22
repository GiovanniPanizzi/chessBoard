#include "../headers/MovesCalculator.h"
#include <iostream>

//is square under attack
inline bool isSquareUnderAttack(const ChessBoard& chessBoard, int square) {
    // Check if the square is attacked by any black piece
    uint64_t blackPawns = chessBoard.blackPawns;
    uint64_t blackKnights = chessBoard.blackKnights;
    uint64_t blackBishops = chessBoard.blackBishops;
    uint64_t blackRooks = chessBoard.blackRooks;
    uint64_t blackQueens = chessBoard.blackQueens;
    uint64_t blackKing = chessBoard.blackKing;

    int x = square % 8;
    int y = square / 8;

    // Check for black pawns
    if (y > 0) {
        if (x > 0 && (blackPawns & (1ULL << (square - 9)))) return true; // Left diagonal
        if (x < 7 && (blackPawns & (1ULL << (square - 7)))) return true; // Right diagonal
    }

    // Check for black rooks and queens
    for (int i = 0; i < 64; i++) {
        if ((blackRooks | blackQueens) & (1ULL << i)) {
            int rookX = i % 8;
            int rookY = i / 8;
            if (rookX == x || rookY == y) {
                return true; // Rook or queen can attack vertically or horizontally
            }
        }
    }

    // Check for black knights
    for (int i = 0; i < 64; i++) {
        if (blackKnights & (1ULL << i)) {
            int knightX = i % 8;
            int knightY = i / 8;
            if ((abs(knightX - x) == 2 && abs(knightY - y) == 1) || 
                (abs(knightX - x) == 1 && abs(knightY - y) == 2)) {
                return true; // Knight can attack in L-shape
            }
        }
    }

    // Check for black bishops and queens
    for (int i = 0; i < 64; i++) {
        if ((blackBishops | blackQueens) & (1ULL << i)) {
            int bishopX = i % 8;
            int bishopY = i / 8;
            if (abs(bishopX - x) == abs(bishopY - y)) {
                int dx = (bishopX - x) > 0 ? 1 : -1;
                int dy = (bishopY - y) > 0 ? 1 : -1;
                int stepX = x + dx;
                int stepY = y + dy;
                bool clearPath = true;
                while (stepX != bishopX && stepY != bishopY) {
                    if ((chessBoard.allPieces & (1ULL << (stepY * 8 + stepX))) != 0) {
                        clearPath = false;
                        break;
                    }
                    stepX += dx;
                    stepY += dy;
                }
                if (clearPath) return true; // Bishop or queen can attack diagonally
            }
        }
    }
    // Check for black king
    if (blackKing) {
        int blackKingSquare = __builtin_ctzll(blackKing);
        int blackKingX = blackKingSquare % 8;
        int blackKingY = blackKingSquare / 8;
        if (abs(blackKingX - x) <= 1 && abs(blackKingY - y) <= 1) {
            return true; // Black king is adjacent to the square
        }
    }
    return false;
}

inline bool isOccupied(const ChessBoard& chessBoard, int square) {
    return (chessBoard.allPieces & (1ULL << square)) != 0;
}

inline bool isBlackOccupied(const ChessBoard& chessBoard, int square) {
    return (chessBoard.blackPieces & (1ULL << square)) != 0;
}

inline bool isWhiteOccupied(const ChessBoard& chessBoard, int square) {
    return (chessBoard.whitePieces & (1ULL << square)) != 0;
}

bool isWhiteKingHanging(const ChessBoard& chessboard){
    uint64_t whiteKing = chessboard.whiteKing;
    int kingSquare = __builtin_ctzll(whiteKing); // Get the index of the white king
    int x = kingSquare % 8;
    int y = kingSquare / 8;
    // Check if the king is attacked by any black pawn
    uint64_t blackPawns = chessboard.blackPawns;
    if (y > 0) {
        if (x > 0 && (blackPawns & (1ULL << (kingSquare - 9)))) return true; // Left diagonal
        if (x < 7 && (blackPawns & (1ULL << (kingSquare - 7)))) return true; // Right diagonal
    }
    // Check if the king is attacked by any black rook
    uint64_t blackRooks = chessboard.blackRooks;
    for (int i = 0; i < 64; i++) {
        if (blackRooks & (1ULL << i)) {
            int rookX = i % 8;
            int rookY = i / 8;
            if (rookX == x || rookY == y) {
                return true;
            }
        }
    }
    // Check if the king is attacked by any black knight
    uint64_t blackKnights = chessboard.blackKnights;
    for (int i = 0; i < 64; i++) {
        if (blackKnights & (1ULL << i)) {
            int knightX = i % 8;
            int knightY = i / 8;
            if ((abs(knightX - x) == 2 && abs(knightY - y) == 1) || 
                (abs(knightX - x) == 1 && abs(knightY - y) == 2)) {
                return true;
            }
        }
    }
    // Check if the king is attacked by any black bishop
    uint64_t blackBishops = chessboard.blackBishops;
    for (int i = 0; i < 64; i++) {
        if (blackBishops & (1ULL << i)) {
            int bishopX = i % 8;
            int bishopY = i / 8;
            if (abs(bishopX - x) == abs(bishopY - y)) {
                int dx = (bishopX - x) > 0 ? 1 : -1;
                int dy = (bishopY - y) > 0 ? 1 : -1;
                int stepX = x + dx;
                int stepY = y + dy;
                bool clearPath = true;
                while (stepX != bishopX && stepY != bishopY) {
                    if (isOccupied(chessboard, stepY * 8 + stepX)) {
                        clearPath = false;
                        break;
                    }
                    stepX += dx;
                    stepY += dy;
                }
                if (clearPath) return true;
            }
        }
    }
    // Check if the king is attacked by any black queen
    uint64_t blackQueens = chessboard.blackQueens;
    for (int i = 0; i < 64; i++) {
        if (blackQueens & (1ULL << i)) {
            int queenX = i % 8;
            int queenY = i / 8;
            if (queenX == x || queenY == y || abs(queenX - x) == abs(queenY - y)) {
                int dx = (queenX - x) > 0 ? 1 : (queenX - x) < 0 ? -1 : 0;
                int dy = (queenY - y) > 0 ? 1 : (queenY - y) < 0 ? -1 : 0;
                int stepX = x + dx;
                int stepY = y + dy;
                bool clearPath = true;
                while (stepX != queenX || stepY != queenY) {
                    if (isOccupied(chessboard, stepY * 8 + stepX)) {
                        clearPath = false;
                        break;
                    }
                    stepX += dx;
                    stepY += dy;
                }
                if (clearPath) return true;
            }
        }
    }
    // Check if the king is attacked by any black king
    uint64_t blackKing = chessboard.blackKing;
    if (blackKing) {
        int blackKingSquare = __builtin_ctzll(blackKing);
        int blackKingX = blackKingSquare % 8;
        int blackKingY = blackKingSquare / 8;
        if (abs(blackKingX - x) <= 1 && abs(blackKingY - y) <= 1) {
            return true; // Black king is adjacent to white king
        }
    }
    return false;
}

//remove black piece
void MovesCalculator::removeBlackPiece(ChessBoard& chessBoard, int square) {
    bool pieceRemoved = false;

    if (chessBoard.blackPawns & (1ULL << square)) {
        std::cout << "Removing black pawn at square: " << square << std::endl;
        chessBoard.blackPawns &= ~(1ULL << square);
        pieceRemoved = true;
    }
    if (chessBoard.blackKnights & (1ULL << square)) {
        std::cout << "Removing black knight at square: " << square << std::endl;
        chessBoard.blackKnights &= ~(1ULL << square);
        pieceRemoved = true;
    }
    if (chessBoard.blackBishops & (1ULL << square)) {
        std::cout << "Removing black bishop at square: " << square << std::endl;
        chessBoard.blackBishops &= ~(1ULL << square);
        pieceRemoved = true;
    }
    if (chessBoard.blackRooks & (1ULL << square)) {
        std::cout << "Removing black rook at square: " << square << std::endl;
        chessBoard.blackRooks &= ~(1ULL << square);
        pieceRemoved = true;
    }
    if (chessBoard.blackQueens & (1ULL << square)) {
        std::cout << "Removing black queen at square: " << square << std::endl;
        chessBoard.blackQueens &= ~(1ULL << square);
        pieceRemoved = true;
    }
    if (chessBoard.blackKing & (1ULL << square)) {
        std::cout << "Removing black king at square: " << square << std::endl;
        chessBoard.blackKing = 0;
        pieceRemoved = true;
    }

    // Update combined bitboards
    chessBoard.allPieces &= ~(1ULL << square);
    chessBoard.blackPieces &= ~(1ULL << square);

    // Reset movesWithoutCaptureOrPawnMove if a piece was removed
    if (pieceRemoved) {
        chessBoard.movesWithoutCaptureOrPawnMove = 0;
    }
}

std::vector<ChessBoard> MovesCalculator::whitePawnMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t pawns = chessBoard.whitePawns;

    for (int square = 0; square < 64; square++) {
        if (pawns & (1ULL << square)) {
            int x = square % 8;
            int y = square / 8;

            // Move forward
            if (y < 7 && !isOccupied(chessBoard, square + 8)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                if( y == 6) { // Promotion
                    ChessBoard newBoard2 = newBoard;
                    ChessBoard newBoard3 = newBoard;
                    ChessBoard newBoard4 = newBoard;
                    newBoard.whiteQueens |= (1ULL << (square + 8)); // Promote to queen
                    newBoard2.whiteRooks |= (1ULL << (square + 8)); // Promote to rook
                    newBoard3.whiteBishops |= (1ULL << (square + 8)); // Promote to bishop
                    newBoard4.whiteKnights |= (1ULL << (square + 8)); // Promote to knight
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                    if (!isWhiteKingHanging(newBoard2)) {
                        moves.push_back(newBoard2);
                    }
                    if (!isWhiteKingHanging(newBoard3)) {
                        moves.push_back(newBoard3);
                    }
                    if (!isWhiteKingHanging(newBoard4)) {
                        moves.push_back(newBoard4);
                    }
                } else { // Regular move
                    newBoard.whitePawns |= (1ULL << (square + 8));
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                }
            }

            // Capture left
            if (x > 0 && y < 7 && isBlackOccupied(chessBoard, square + 7)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                removeBlackPiece(newBoard, square + 7);
                if( y == 6) { // Promotion
                    ChessBoard newBoard2 = newBoard;
                    ChessBoard newBoard3 = newBoard;
                    ChessBoard newBoard4 = newBoard;
                    newBoard.whiteQueens |= (1ULL << (square + 7)); // Promote to queen
                    newBoard2.whiteRooks |= (1ULL << (square + 7)); // Promote to rook
                    newBoard3.whiteBishops |= (1ULL << (square + 7)); // Promote to bishop
                    newBoard4.whiteKnights |= (1ULL << (square + 7)); // Promote to knight
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                    if (!isWhiteKingHanging(newBoard2)) {
                        moves.push_back(newBoard2);
                    }
                    if (!isWhiteKingHanging(newBoard3)) {
                        moves.push_back(newBoard3);
                    }
                    if (!isWhiteKingHanging(newBoard4)) {
                        moves.push_back(newBoard4);
                    }
                } else { // Regular capture
                    newBoard.whitePawns |= (1ULL << (square + 7));
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                }
            }

            // Capture right
            if (x < 7 && y < 7 && isBlackOccupied(chessBoard, square + 9)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                removeBlackPiece(newBoard, square + 9);
                if( y == 6) { // Promotion
                    ChessBoard newBoard2 = newBoard;
                    ChessBoard newBoard3 = newBoard;
                    ChessBoard newBoard4 = newBoard;
                    newBoard.whiteQueens |= (1ULL << (square + 9)); // Promote to queen
                    newBoard2.whiteRooks |= (1ULL << (square + 9)); // Promote to rook
                    newBoard3.whiteBishops |= (1ULL << (square + 9)); // Promote to bishop
                    newBoard4.whiteKnights |= (1ULL << (square + 9)); // Promote to knight
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                    if (!isWhiteKingHanging(newBoard2)) {
                        moves.push_back(newBoard2);
                    }
                    if (!isWhiteKingHanging(newBoard3)) {
                        moves.push_back(newBoard3);
                    }
                    if (!isWhiteKingHanging(newBoard4)) {
                        moves.push_back(newBoard4);
                    }
                } else { // Regular capture
                    newBoard.whitePawns |= (1ULL << (square + 9));
                    if (!isWhiteKingHanging(newBoard)) {
                        moves.push_back(newBoard);
                    }
                }
            }

            // Double move from starting position
            if (y == 1 && !isOccupied(chessBoard, square + 16) && !isOccupied(chessBoard, square + 8)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                newBoard.whitePawns |= (1ULL << (square + 16));
                if( !isWhiteKingHanging(newBoard)) {
                    moves.push_back(newBoard);
                }
            }

            // En passant capture left
            if (x > 0 && y == 4 && isBlackOccupied(chessBoard, square + 7) &&
                (chessBoard.blackPawns & (1ULL << (square - 1))) &&
                (chessBoard.enPassantSquare == square + 7)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                newBoard.whitePawns |= (1ULL << (square + 7));
                removeBlackPiece(newBoard, square - 1);
                if( !isWhiteKingHanging(newBoard)) {
                    moves.push_back(newBoard);
                }
            }

            // En passant capture right
            if (x < 7 && y == 4 && isBlackOccupied(chessBoard, square + 9) &&
                (chessBoard.blackPawns & (1ULL << (square + 1))) &&
                (chessBoard.enPassantSquare == square + 9)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whitePawns &= ~(1ULL << square);
                newBoard.whitePawns |= (1ULL << (square + 9));
                removeBlackPiece(newBoard, square + 1);
                if( !isWhiteKingHanging(newBoard)) {
                    moves.push_back(newBoard);
                }
            }
        }
    }
    return moves;
}

std::vector<ChessBoard> MovesCalculator::whiteRookMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t rooks = chessBoard.whiteRooks;

    for (int square = 0; square < 64; square++) {
        if (rooks & (1ULL << square)) {
            int x = square % 8;
            int y = square / 8;

            // Horizontal and vertical moves
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if ((dx == 0 || dy == 0) && (dx != dy)) { // Only horizontal or vertical
                        int stepX = x + dx;
                        int stepY = y + dy;
                        while (stepX >= 0 && stepX < 8 && stepY >= 0 && stepY < 8) {
                            int newSquare = stepY * 8 + stepX;
                            if (!isOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteRooks &= ~(1ULL << square);
                                newBoard.whiteRooks |= (1ULL << newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                            } else if (isBlackOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteRooks &= ~(1ULL << square);
                                newBoard.whiteRooks |= (1ULL << newSquare);
                                removeBlackPiece(newBoard, newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                                break; // Stop at the first occupied square
                            } else {
                                break; // Stop at the first empty square
                            }
                            stepX += dx;
                            stepY += dy;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<ChessBoard> MovesCalculator::whiteKnightMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t knights = chessBoard.whiteKnights;

    for (int square = 0; square < 64; square++) {
        if (knights & (1ULL << square)) {
            int x = square % 8;
            int y = square / 8;

            // Knight moves
            int knightMoves[8][2] = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
            };

            for (const auto& move : knightMoves) {
                int newX = x + move[0];
                int newY = y + move[1];
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    int newSquare = newY * 8 + newX;
                    if (!isOccupied(chessBoard, newSquare)) {
                        ChessBoard newBoard = chessBoard;
                        newBoard.movesCount++;
                        newBoard.whiteKnights &= ~(1ULL << square);
                        newBoard.whiteKnights |= (1ULL << newSquare);
                        if (!isWhiteKingHanging(newBoard)) {
                            moves.push_back(newBoard);
                        }
                    } else if (isBlackOccupied(chessBoard, newSquare)) {
                        ChessBoard newBoard = chessBoard;
                        newBoard.movesCount++;
                        newBoard.whiteKnights &= ~(1ULL << square);
                        newBoard.whiteKnights |= (1ULL << newSquare);
                        removeBlackPiece(newBoard, newSquare);
                        if (!isWhiteKingHanging(newBoard)) {
                            moves.push_back(newBoard);
                        }
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<ChessBoard> MovesCalculator::whiteBishopMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t bishops = chessBoard.whiteBishops;

    for (int square = 0; square < 64; square++) {
        if (bishops & (1ULL << square)) {
            int x = square % 8;
            int y = square / 8;

            // Diagonal moves
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) == abs(dy) && dx != 0) { // Only diagonal
                        int stepX = x + dx;
                        int stepY = y + dy;
                        while (stepX >= 0 && stepX < 8 && stepY >= 0 && stepY < 8) {
                            int newSquare = stepY * 8 + stepX;
                            if (!isOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteBishops &= ~(1ULL << square);
                                newBoard.whiteBishops |= (1ULL << newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                            } else if (isBlackOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteBishops &= ~(1ULL << square);
                                newBoard.whiteBishops |= (1ULL << newSquare);
                                removeBlackPiece(newBoard, newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                                break; // Stop at the first occupied square
                            } else {
                                break; // Stop at the first empty square
                            }
                            stepX += dx;
                            stepY += dy;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<ChessBoard> MovesCalculator::whiteQueenMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t queens = chessBoard.whiteQueens;

    for (int square = 0; square < 64; square++) {
        if (queens & (1ULL << square)) {
            int x = square % 8;
            int y = square / 8;

            // Horizontal, vertical, and diagonal moves
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if ((dx == 0 || dy == 0 || abs(dx) == abs(dy)) && (dx != dy || dx != 0)) { // All directions
                        int stepX = x + dx;
                        int stepY = y + dy;
                        while (stepX >= 0 && stepX < 8 && stepY >= 0 && stepY < 8) {
                            int newSquare = stepY * 8 + stepX;
                            if (!isOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteQueens &= ~(1ULL << square);
                                newBoard.whiteQueens |= (1ULL << newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                            } else if (isBlackOccupied(chessBoard, newSquare)) {
                                ChessBoard newBoard = chessBoard;
                                newBoard.movesCount++;
                                newBoard.whiteQueens &= ~(1ULL << square);
                                newBoard.whiteQueens |= (1ULL << newSquare);
                                removeBlackPiece(newBoard, newSquare);
                                if (!isWhiteKingHanging(newBoard)) {
                                    moves.push_back(newBoard);
                                }
                                break; // Stop at the first occupied square
                            } else {
                                break; // Stop at the first empty square
                            }
                            stepX += dx;
                            stepY += dy;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<ChessBoard> MovesCalculator::whiteKingMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> moves;
    uint64_t king = chessBoard.whiteKing;

    if (king == 0) return moves; // No king present

    int kingSquare = __builtin_ctzll(king); // Get the index of the white king
    int x = kingSquare % 8;
    int y = kingSquare / 8;

    // King moves
    int kingMoves[8][2] = {
        {1, 0}, {1, 1}, {0, 1}, {-1, 1},
        {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
    };

    for (const auto& move : kingMoves) {
        int newX = x + move[0];
        int newY = y + move[1];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            int newSquare = newY * 8 + newX;
            if (!isOccupied(chessBoard, newSquare)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whiteKing &= ~(1ULL << kingSquare);
                newBoard.whiteKing |= (1ULL << newSquare);
                if (!isWhiteKingHanging(newBoard)) {
                    moves.push_back(newBoard);
                }
            } else if (isBlackOccupied(chessBoard, newSquare)) {
                ChessBoard newBoard = chessBoard;
                newBoard.movesCount++;
                newBoard.whiteKing &= ~(1ULL << kingSquare);
                newBoard.whiteKing |= (1ULL << newSquare);
                removeBlackPiece(newBoard, newSquare);
                if (!isWhiteKingHanging(newBoard)) {
                    moves.push_back(newBoard);
                }
            }
        }
    }

    //short castling 
    if (!chessBoard.whiteKingMoved && !chessBoard.whiteRooksMoved[0] && 
        !isOccupied(chessBoard, 5) && !isOccupied(chessBoard, 6) &&
        !isWhiteKingHanging(chessBoard)) {
        std::cout << "Trying short castling" << std::endl;
        ChessBoard newBoard = chessBoard;
        newBoard.movesCount++;
        newBoard.whiteKing &= ~(1ULL << kingSquare);
        newBoard.whiteRooks &= ~(1ULL << 7);
        newBoard.whiteKing |= (1ULL << 6);
        newBoard.whiteRooks |= (1ULL << 5);
        if (!isWhiteKingHanging(newBoard) && !isSquareUnderAttack(newBoard, 5) && !isSquareUnderAttack(newBoard, 6)) {
            std::cout << "Short castling" << std::endl;
            moves.push_back(newBoard);
        }
    }

    //long castling
    if (!chessBoard.whiteKingMoved && !chessBoard.whiteRooksMoved[1] && 
        !isOccupied(chessBoard, 3) && !isOccupied(chessBoard, 2) && !isOccupied(chessBoard, 1) &&
        !isWhiteKingHanging(chessBoard)) {
        std::cout << "Trying long castling" << std::endl;
        ChessBoard newBoard = chessBoard;
        newBoard.movesCount++;
        newBoard.whiteKing &= ~(1ULL << kingSquare);
        newBoard.whiteKing |= (1ULL << 2);
        newBoard.whiteRooks &= ~(1ULL << 0);
        newBoard.whiteRooks |= (1ULL << 3);
        if (!isWhiteKingHanging(newBoard) && !isSquareUnderAttack(newBoard, 3) && !isSquareUnderAttack(newBoard, 2) && !isSquareUnderAttack(newBoard, 1)) {
            std::cout << "Long castling" << std::endl;
            moves.push_back(newBoard);
        }
    }

    return moves;
}

std::vector<ChessBoard> MovesCalculator::allMoves(const ChessBoard& chessBoard) {
    std::vector<ChessBoard> allMoves;

    auto pawnMoves = whitePawnMoves(chessBoard);
    allMoves.insert(allMoves.end(), pawnMoves.begin(), pawnMoves.end());

    auto rookMoves = whiteRookMoves(chessBoard);
    allMoves.insert(allMoves.end(), rookMoves.begin(), rookMoves.end());

    auto knightMoves = whiteKnightMoves(chessBoard);
    allMoves.insert(allMoves.end(), knightMoves.begin(), knightMoves.end());

    auto bishopMoves = whiteBishopMoves(chessBoard);
    allMoves.insert(allMoves.end(), bishopMoves.begin(), bishopMoves.end());

    auto queenMoves = whiteQueenMoves(chessBoard);
    allMoves.insert(allMoves.end(), queenMoves.begin(), queenMoves.end());

    auto kingMoves = whiteKingMoves(chessBoard);
    allMoves.insert(allMoves.end(), kingMoves.begin(), kingMoves.end());

    return allMoves;
}