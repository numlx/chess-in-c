#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PIECE_SIZE    68
#define BOARD_SIZE    80
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH  800
#define SQUARE_SIZE   68

enum Piece{
  
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

}Piece;

Rectangle PieceSource(int piece){
  if(piece == 0) return(Rectangle){0, 0, 0, 0};

  int absPiece = (piece > 0) ? piece : -piece;
  int col = absPiece - 1;
  int row = (piece > 0) ? 0 : 1;

  return(Rectangle){
    col * PIECE_SIZE,
    row * PIECE_SIZE,
    PIECE_SIZE,
    PIECE_SIZE
  };

}

int board[8][8] = {
  { -5,-4,-3,-2,-1,-3,-4,-5 },
  { -6,-6,-6,-6,-6,-6,-6,-6 },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
  {  6, 6, 6, 6, 6, 6, 6, 6 },
  {  5, 4, 3, 2, 1, 3, 4, 5 }
};

void DrawBoard(){
  int offsetX = (GetScreenWidth() - PIECE_SIZE * 8) / 2;
  int offsetY = (GetScreenHeight() - PIECE_SIZE * 8) / 2;
  for(int x = 0; x < 8; x++){
    for(int y = 0; y < 8; y++){
      if((x + y) % 2){
        DrawRectangle(x * SQUARE_SIZE + offsetX, y * SQUARE_SIZE + offsetY, SQUARE_SIZE, SQUARE_SIZE, DARKGREEN);
      } else {
        DrawRectangle(x * SQUARE_SIZE + offsetX, y * SQUARE_SIZE + offsetY, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
    }
  }
}

int main(){
  
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

  Texture2D atlas = LoadTexture("pieces.png");
  ClearBackground(BLACK);
  
  int offsetX = (GetScreenWidth() - PIECE_SIZE * 8) / 2;
  int offsetY = (GetScreenHeight() - PIECE_SIZE * 8) / 2;

  SetTargetFPS(60);

  while(!WindowShouldClose()){
    BeginDrawing();
    DrawBoard(); 

    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
          int piece = board[k][i];
          if(piece == 0) continue;
          Rectangle src = PieceSource(piece);
          Rectangle dst = {i * PIECE_SIZE + offsetX, k * PIECE_SIZE + offsetY, PIECE_SIZE, PIECE_SIZE};
          DrawTexturePro(atlas, src, dst, (Vector2){0, 0,}, 0, WHITE);
        }
      }
    //int piece = B_PAWN;
    //Rectangle source = PieceSource(piece);
    //Rectangle dst = {200, 200, PIECE_SIZE, PIECE_SIZE};
    //DrawTexturePro(atlas, source, dst, (Vector2){0, 0}, 0, WHITE);
    EndDrawing();
  }
  UnloadTexture(atlas);
  CloseWindow();

  return 0;
}
