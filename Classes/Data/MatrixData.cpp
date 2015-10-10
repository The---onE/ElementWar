#include "MatrixData.h"

const float BLOCK_WIDTH = 50;
const float BLOCK_HEIGHT = 50;

const Point MATRIX_CENTER = visibleSize / 2;
const Point MATRIX_BOTTOM_LEFT_CENTER = MATRIX_CENTER - Point(BLOCK_WIDTH*(float(MATRIX_ROW) / 2 - 0.5), BLOCK_HEIGHT*(float(MATRIX_LINE) / 2 - 0.5));
const Point MATRIX_BOTTOM_LEFT = MATRIX_CENTER - Point(BLOCK_WIDTH*(float(MATRIX_ROW) / 2), BLOCK_HEIGHT*(float(MATRIX_LINE) / 2));

const float FALL_TIME = 0.16f;

const Rect MATRIX_RECT = Rect(MATRIX_BOTTOM_LEFT.x, MATRIX_BOTTOM_LEFT.y, BLOCK_WIDTH*MATRIX_ROW, BLOCK_HEIGHT*MATRIX_LINE);

const string SIGN_IMG = "sign.png";
const float SIGN_SIZE = 0.07f;

const float GUIDELINE_WIDTH = 2.5f;
const Color4F GUIDELINE_COLOR = Color4F(0, 255, 0, 0.16f);


Point getCenterByCoord(int line, int row)
{
	Point center = MATRIX_BOTTOM_LEFT_CENTER;
	center += Point(BLOCK_WIDTH*row, BLOCK_HEIGHT*line);
	return center;
}