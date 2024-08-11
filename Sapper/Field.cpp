#include "pch.h"
#include "Field.h"

void Field::GenetateField()
{
    cells = new Cell * [height];
    revealed = new bool * [height];

    for (int i = 0; i < height; i++)
    {
        cells[i] = new Cell[width];
        revealed[i] = new bool [width];

        for (int j = 0; j < width; j++)
        {
            int left = startX + j * (cellSize + spacing);
            int top = startY + i * (cellSize + spacing);
            int right = left + cellSize;
            int bottom = top + cellSize;

            revealed[i][j] = false;
            cells[i][j] = Cell(Coord(j, i), CRect(left, top, right, bottom), '.');
        }
    }

    int placedMines = 0;
    while (placedMines < mines)
    {
        int y = rand() % height;
        int x = rand() % width;

        if (cells[y][x].value != '*')
        {
            cells[y][x].value = '*';
            placedMines++;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (cells[i][j].value == '*') {
                continue;
            }

            int mineCount = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int newRow = i + x;
                    int newCol = j + y;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && 
                        newCol < width && cells[newRow][newCol].value == '*')
                    {
                        mineCount++;
                    }
                }
            }

            if (!mineCount) {
                cells[i][j].value = '.';
                continue;
            }

            char value = mineCount + '0';
            cells[i][j].value = value;
        }
    }
}

void Field::RevealCell(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height || revealed[y][x]) {
        return;
    }

    revealed[y][x] = true;

    if (cells[y][x].value != '.'  && revealed[y][x] != '0')
    {
        return;
    }

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0)
            {
                RevealCell(x + dx, y + dy);
            }
        }
    }
}

Coord Field::GetCellCoordByPoint(CPoint& point)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cells[i][j].rect.PtInRect(point)) {
                return Coord(j, i);
            }
        }
    }
    return Coord();
}

Field::Field()
{
	cells = nullptr;
	revealed = nullptr;

	width = height = mines = 0;
}

Field::Field(int width, int height, int mines):
	width(width), height(height), mines(mines)
{
    GenetateField();
}

Field::Field(const Field& other):
    width(other.width), height(other.height), mines(other.mines)
{
    cells = new Cell * [height];
    revealed = new bool* [height];

    for (int i = 0; i < height; i++) {
        cells[i] = new Cell[width];
        revealed[i] = new bool[width];

        for (int j = 0; j < width; j++) {
            cells[i][j] = other.cells[i][j];
            revealed[i][j] = other.revealed[i][j];
        }
    }
}

void Field::Draw(CPaintDC& dc)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char str = cells[i][j].value;
            _cwprintf(L"%c ", str);
            if (revealed == nullptr || revealed[i][j])
            {
                dc.Rectangle(cells[i][j].rect);

                dc.SetTextColor(0);
                dc.SetBkMode(TRANSPARENT);

                CFont font;
                font.CreatePointFont(100, _T("Arial"));
                CFont* pOldFont = dc.SelectObject(&font);

                CString text(cells[i][j].value);

                dc.DrawText(text, cells[i][j].rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                dc.SelectObject(pOldFont);
                continue;
            }

            dc.Rectangle(cells[i][j].rect);
            dc.FillSolidRect(cells[i][j].rect, cells[i][j].marked ? RGB(255, 0, 0): RGB(188, 188, 231));
        }
        _cwprintf(L"\n");
    }
    _cwprintf(L"\n\n\n");
}

bool Field::Set(CPoint& point, bool& end)
{
    Coord coord = GetCellCoordByPoint(point);

    if (coord.X <= -1 || coord.Y <= -1) {
        return false;
    }

    RevealCell(coord.X, coord.Y);
    end = cells[coord.Y][coord.X].value == '*';

    return true;
}

bool Field::SetMarker(CPoint& point)
{
    Coord coord = GetCellCoordByPoint(point);

    if (coord.X <= -1 || coord.Y <= -1 || cells[coord.Y][coord.X].marked) {
        return false;
    }

    cells[coord.Y][coord.X].marked = true;
    return true;
}

bool Field::Win()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!revealed[i][j] && cells[i][j].value != '*') {
                return false;
            }
        }
    }
    return true;
}

Field& Field::operator=(const Field& other)
{
    if (this == &other) {
        return *this; // самоприсваивание
    }

    width = other.width;
    height = other.height;
    mines = other.mines;

    cells = new Cell * [height];
    revealed = new bool* [height];

    for (int i = 0; i < height; i++) {
        cells[i] = new Cell[width];
        revealed[i] = new bool[width];

        for (int j = 0; j < width; j++) {
            cells[i][j] = other.cells[i][j];
            revealed[i][j] = other.revealed[i][j];
        }
    }

    return *this;
}
