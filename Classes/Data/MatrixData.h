#pragma once

#include "Global.h"

const int MATRIX_LINE = 10;
const int MATRIX_ROW = 10;

extern const float BLOCK_WIDTH;
extern const float BLOCK_HEIGHT;

extern const Point MATRIX_CENTER;
extern const Point MATRIX_BOTTOM_LEFT_CENTER;
extern const Point MATRIX_BOTTOM_LEFT;

extern const float FALL_TIME;

extern const Rect MATRIX_RECT;

extern const string SIGN_IMG;
extern const float SIGN_SIZE;

extern const float GUIDELINE_WIDTH;
extern const Color4F GUIDELINE_COLOR;


Point getCenterByCoord(int line, int row);

#define ERGODIC_BLOCK(line, row) for(int (line)=0; (line)<MATRIX_LINE; ++(line)) for(int (row)=0; (row)<MATRIX_ROW; ++(row))