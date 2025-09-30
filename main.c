#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PIECE_SIZE    68
#define BOARD_SIZE    8
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH  800
#define SQUARE_SIZE   68
#define BACKGROUND_COLOR (Color){48, 46, 43, 255}

enum Piece {
    EMPTY    = 0,
    W_KING   = 1,
    W_QUEEN  = 2,
    W_BISHOP = 3,
    W_KNIGHT = 4,
    W_ROOK   = 5,
    W_PAWN   = 6,
    B_KING   = -1,
    B_QUEEN  = -2,
    B_BISHOP = -3,
    B_KNIGHT = -4,
    B_ROOK   = -5,
    B_PAWN   = -6
};

Rectangle PieceSource(int piece) {
  if(piece == 0) return (Rectangle){0, 0, 0, 0};

  int absPiece = (piece > 0) ? piece : -piece;
  int col = absPiece - 1;
  int row = (piece > 0) ? 0 : 1;

  return (Rectangle){ col * PIECE_SIZE, row * PIECE_SIZE, PIECE_SIZE, PIECE_SIZE };
}

int board[8][8] = {
  {-5,-4,-3,-2, -1,-3,-4,-5},
  {-6,-6,-6,-6, -6,-6,-6,-6},
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 6, 6, 6, 6, 6, 6, 6, 6 },
  { 5, 4, 3, 2, 1, 3, 4, 5 }
};

void DrawBoard(int offsetX, int offsetY) {
  for(int row = 0; row < 8; row++) {
    for(int col = 0; col < 8; col++) {
      Color color = ((row + col) % 2) ? DARKGREEN : WHITE;
      DrawRectangle(col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY, SQUARE_SIZE, SQUARE_SIZE, color);
      }
  }
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

  Texture2D atlas = LoadTexture("pieces.png");

  int offsetX = (GetScreenWidth() - SQUARE_SIZE * 8) / 2;
  int offsetY = (GetScreenHeight() - SQUARE_SIZE * 8) / 2;

  bool dragging = false;
  Vector2 mousePosition;
  Vector2 dragOffset = {0, 0};
  int dragPiece = 0;
  int dragRow = -1;
  int dragCol = -1;

  SetTargetFPS(60);

while(!WindowShouldClose()) {
  mousePosition = GetMousePosition();

  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
  int col = (mousePosition.x - offsetX) / SQUARE_SIZE;
  int row = (mousePosition.y - offsetY) / SQUARE_SIZE;

    if(col >= 0 && col < 8 && row >= 0 && row < 8 && board[row][col] != 0) {
      dragging = true;
      dragPiece = board[row][col];
      dragRow = row;
      dragCol = col;
      dragOffset.x = mousePosition.x - (offsetX + col * SQUARE_SIZE);
      dragOffset.y = mousePosition.y - (offsetY + row * SQUARE_SIZE);

      board[row][col] = 0;
    }
  }

  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && dragging) {
    int newCol = (mousePosition.x - offsetX) / SQUARE_SIZE;
    int newRow = (mousePosition.y - offsetY) / SQUARE_SIZE;

    if(newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {
      board[newRow][newCol] = dragPiece;
    } else {
      board[dragRow][dragCol] = dragPiece;
    }

      dragging = false;
      dragPiece = 0;
    }

    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);

    DrawBoard(offsetX, offsetY);

    for(int row = 0; row < 8; row++) {
      for(int col = 0; col < 8; col++) {
        int piece = board[row][col];
          if(piece == 0) continue;
            if(dragging && row == dragRow && col == dragCol) continue;

              Rectangle src = PieceSource(piece);
              Rectangle dst = { col * SQUARE_SIZE + offsetX, row * SQUARE_SIZE + offsetY, PIECE_SIZE, PIECE_SIZE };
              DrawTexturePro(atlas, src, dst, (Vector2){0,0}, 0, WHITE);
      }
    }

    if(dragging) {
      Rectangle dst = { mousePosition.x - dragOffset.x, mousePosition.y - dragOffset.y, PIECE_SIZE, PIECE_SIZE };
      DrawTexturePro(atlas, PieceSource(dragPiece), dst, (Vector2){0,0}, 0, WHITE);
    }

      EndDrawing();
    }

    UnloadTexture(atlas);
    CloseWindow();
    return 0;
}

