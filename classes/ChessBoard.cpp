#include "../headers/ChessBoard.h"

// Set the bit at the specified square
#define SET_BIT(board, square) (board |= (1ULL << square))

// Clear the bit at the specified square
#define CLEAR_BIT(board, square) (board &= ~(1ULL << square))

// Map (x, y) to a bitboard square index (0-63)
inline int toSquareIndex(int x, int y) {
    return y * 8 + x;
}

// Constructor
ChessBoard::ChessBoard() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            CLEAR_BIT(whitePawns, toSquareIndex(i, j));
            CLEAR_BIT(whiteKnights, toSquareIndex(i, j));
            CLEAR_BIT(whiteBishops, toSquareIndex(i, j));
            CLEAR_BIT(whiteRooks, toSquareIndex(i, j));
            CLEAR_BIT(whiteQueens, toSquareIndex(i, j));
            CLEAR_BIT(whiteKing, toSquareIndex(i, j));

            CLEAR_BIT(blackPawns, toSquareIndex(i, j));
            CLEAR_BIT(blackKnights, toSquareIndex(i, j));
            CLEAR_BIT(blackBishops, toSquareIndex(i, j));
            CLEAR_BIT(blackRooks, toSquareIndex(i, j));
            CLEAR_BIT(blackQueens, toSquareIndex(i, j));
            CLEAR_BIT(blackKing, toSquareIndex(i, j));
        }
    }
    // Initialize white pawns
    for (int i = 0; i < 8; i++) {
        SET_BIT(whitePawns, toSquareIndex(i, 1));
    }

    // Initialize black pawns
    for (int i = 0; i < 8; i++) {
        SET_BIT(blackPawns, toSquareIndex(i, 6));
    }

    // Initialize white pieces
    SET_BIT(whiteRooks, toSquareIndex(0, 0));
    SET_BIT(whiteRooks, toSquareIndex(7, 0));
    SET_BIT(whiteKnights, toSquareIndex(1, 0));
    SET_BIT(whiteKnights, toSquareIndex(6, 0));
    SET_BIT(whiteBishops, toSquareIndex(2, 0));
    SET_BIT(whiteBishops, toSquareIndex(5, 0));
    SET_BIT(whiteQueens, toSquareIndex(3, 0));
    SET_BIT(whiteKing, toSquareIndex(4, 0));

    // Initialize black pieces
    SET_BIT(blackRooks, toSquareIndex(0, 7));
    SET_BIT(blackRooks, toSquareIndex(7, 7));
    SET_BIT(blackKnights, toSquareIndex(1, 7));
    SET_BIT(blackKnights, toSquareIndex(6, 7));
    SET_BIT(blackBishops, toSquareIndex(2, 7));
    SET_BIT(blackBishops, toSquareIndex(5, 7));
    SET_BIT(blackQueens, toSquareIndex(3, 7));
    SET_BIT(blackKing, toSquareIndex(4, 7)); 

    // Initialize combined pieces bitboards
    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    allPieces = whitePieces | blackPieces;

    // Initialize game state
    movesWithoutCaptureOrPawnMove = 0;
    enPassantSquare = -1;
    whiteKingMoved = false;
    blackKingMoved = false;
    whiteRooksMoved[0] = false; // Left rook
    whiteRooksMoved[1] = false; // Right rook
    blackRooksMoved[0] = false; // Left rook
    blackRooksMoved[1] = false; // Right rook

    movesCount = 0;
}

// Copy constructor
ChessBoard::ChessBoard(const ChessBoard& other) {
    whitePawns = other.whitePawns;
    whiteKnights = other.whiteKnights;
    whiteBishops = other.whiteBishops;
    whiteRooks = other.whiteRooks;
    whiteQueens = other.whiteQueens;
    whiteKing = other.whiteKing;

    blackPawns = other.blackPawns;
    blackKnights = other.blackKnights;
    blackBishops = other.blackBishops;
    blackRooks = other.blackRooks;
    blackQueens = other.blackQueens;
    blackKing = other.blackKing;

    movesWithoutCaptureOrPawnMove = other.movesWithoutCaptureOrPawnMove;
    enPassantSquare = other.enPassantSquare;
    whiteKingMoved = other.whiteKingMoved;
    blackKingMoved = other.blackKingMoved;
    whiteRooksMoved[0] = other.whiteRooksMoved[0];
    whiteRooksMoved[1] = other.whiteRooksMoved[1];
    blackRooksMoved[0] = other.blackRooksMoved[0];
    blackRooksMoved[1] = other.blackRooksMoved[1];

    movesCount = other.movesCount;
}

bool ChessBoard::operator==(const ChessBoard& other) const {
    return whitePawns == other.whitePawns &&
            whiteKnights == other.whiteKnights &&
            whiteBishops == other.whiteBishops &&
            whiteRooks == other.whiteRooks &&
            whiteQueens == other.whiteQueens &&
            whiteKing == other.whiteKing &&
            blackPawns == other.blackPawns &&
            blackKnights == other.blackKnights &&
            blackBishops == other.blackBishops &&
            blackRooks == other.blackRooks &&
            blackQueens == other.blackQueens &&
            blackKing == other.blackKing &&
            movesWithoutCaptureOrPawnMove == other.movesWithoutCaptureOrPawnMove &&
            enPassantSquare == other.enPassantSquare &&
            whiteKingMoved == other.whiteKingMoved &&
            blackKingMoved == other.blackKingMoved &&
            whiteRooksMoved[0] == other.whiteRooksMoved[0] &&
            whiteRooksMoved[1] == other.whiteRooksMoved[1] &&
            blackRooksMoved[0] == other.blackRooksMoved[0] &&
            blackRooksMoved[1] == other.blackRooksMoved[1] &&
            movesCount == other.movesCount;
}

void ChessBoard::invertPieces() {
    // Temporarily store the original white bitboards
    uint64_t tempWhitePawns = whitePawns;
    uint64_t tempWhiteKnights = whiteKnights;
    uint64_t tempWhiteBishops = whiteBishops;
    uint64_t tempWhiteRooks = whiteRooks;
    uint64_t tempWhiteQueens = whiteQueens;
    uint64_t tempWhiteKing = whiteKing;

    // Swap and invert the bitboards for each piece type
    whitePawns = __builtin_bswap64(blackPawns);
    blackPawns = __builtin_bswap64(tempWhitePawns);

    whiteKnights = __builtin_bswap64(blackKnights);
    blackKnights = __builtin_bswap64(tempWhiteKnights);

    whiteBishops = __builtin_bswap64(blackBishops);
    blackBishops = __builtin_bswap64(tempWhiteBishops);

    whiteRooks = __builtin_bswap64(blackRooks);
    blackRooks = __builtin_bswap64(tempWhiteRooks);

    whiteQueens = __builtin_bswap64(blackQueens);
    blackQueens = __builtin_bswap64(tempWhiteQueens);

    whiteKing = __builtin_bswap64(blackKing);
    blackKing = __builtin_bswap64(tempWhiteKing);

    // Swap king and rook movement flags
    std::swap(whiteKingMoved, blackKingMoved);
    std::swap(whiteRooksMoved[0], blackRooksMoved[0]);
    std::swap(whiteRooksMoved[1], blackRooksMoved[1]);

    // Invert the en passant square if it exists
    if (enPassantSquare != -1) {
        enPassantSquare = 63 - enPassantSquare;
    }

    // Recalculate combined bitboards
    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    allPieces = whitePieces | blackPieces;
}

std::vector<std::string> ChessBoard::operator-(const ChessBoard& other) const {

    std::vector<std::string> differences;

    if (whitePawns != other.whitePawns) differences.push_back("White Pawns");
    if (whiteKnights != other.whiteKnights) differences.push_back("White Knights");
    if (whiteBishops != other.whiteBishops) differences.push_back("White Bishops");
    if (whiteRooks != other.whiteRooks) differences.push_back("White Rooks");
    if (whiteQueens != other.whiteQueens) differences.push_back("White Queens");
    if (whiteKing != other.whiteKing) differences.push_back("White King");

    if (blackPawns != other.blackPawns) differences.push_back("Black Pawns");
    if (blackKnights != other.blackKnights) differences.push_back("Black Knights");
    if (blackBishops != other.blackBishops) differences.push_back("Black Bishops");
    if (blackRooks != other.blackRooks) differences.push_back("Black Rooks");
    if (blackQueens != other.blackQueens) differences.push_back("Black Queens");
    if (blackKing != other.blackKing) differences.push_back("Black King");

    return differences;
}

void drawPieces(uint64_t bitboard, int r, int g, int b, int width, int height, Draw& draw) {
    for (int square = 0; square < 64; square++) {
        if (bitboard & (1ULL << square)) {
            int x = 7 - square % 8;
            int y = 7 - square / 8;
            draw.drawRect(x * tileSize + (tileSize - width) / 2, y * tileSize + (tileSize - height) / 2, width, height, r, g, b, 255);
        }
    }
};

void drawKing(uint64_t bitboard, int r, int g, int b, int thickness, Draw& draw) {
    for (int square = 0; square < 64; square++) {
        if (bitboard & (1ULL << square)) {
            int x = 7 - square % 8;
            int y = 7 - square / 8;

            draw.drawRect(x * tileSize + (tileSize - thickness) / 2, y * tileSize + 15, thickness, 70, r, g, b, 255);

            draw.drawRect(x * tileSize + 15, y * tileSize + (tileSize - thickness) / 2, 70, thickness, r, g, b, 255);
        }
    }
};

void ChessBoard::draw(Draw& draw) {

    // Draw the chessboard tiles
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                draw.drawRect(i * tileSize, j * tileSize, tileSize, tileSize, 0, 0, 0, 255); // Black tile
            } else {
                draw.drawRect(i * tileSize, j * tileSize, tileSize, tileSize, 255, 255, 255, 255); // White tile
            }
        }
    }

    // Draw white pieces white if numMoves is even
    if( movesCount % 2 == 0) {
        drawPieces(whitePawns, 205, 205, 205, 30, 40, draw);
        drawPieces(whiteRooks, 205, 205, 205, 40, 60, draw);
        drawPieces(whiteKnights, 205, 205, 205, 50, 50, draw);
        drawPieces(whiteBishops, 205, 205, 205, 30, 70, draw);
        drawPieces(whiteQueens, 205, 205, 205, 40, 80, draw);
        drawKing(whiteKing, 205, 205, 205, 20, draw);

        drawPieces(blackPawns, 50, 50, 50, 30, 40, draw);
        drawPieces(blackRooks, 50, 50, 50, 40, 60, draw);
        drawPieces(blackKnights, 50, 50, 50, 50, 50, draw);
        drawPieces(blackBishops, 50, 50, 50, 30, 70, draw);
        drawPieces(blackQueens, 50, 50, 50, 40, 80, draw);
        drawKing(blackKing, 50, 50, 50, 20, draw);
    } else {
        drawPieces(whitePawns, 50, 50, 50, 30, 40, draw);
        drawPieces(whiteRooks, 50, 50, 50, 40, 60, draw);
        drawPieces(whiteKnights, 50, 50, 50, 50, 50, draw);
        drawPieces(whiteBishops, 50, 50, 50, 30, 70, draw);
        drawPieces(whiteQueens, 50, 50, 50, 40, 80, draw);
        drawKing(whiteKing, 50, 50, 50, 20, draw);

        drawPieces(blackPawns, 205, 205, 205, 30, 40, draw);
        drawPieces(blackRooks, 205, 205, 205, 40, 60, draw);
        drawPieces(blackKnights, 205, 205, 205, 50, 50, draw);
        drawPieces(blackBishops, 205, 205, 205, 30, 70, draw);
        drawPieces(blackQueens, 205, 205, 205, 40, 80, draw);
        drawKing(blackKing, 205, 205, 205, 20, draw);
    } 
}