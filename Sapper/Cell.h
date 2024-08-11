#pragma once
#include <Windows.h>
#include <atltypes.h>

#include "Coord.h"

struct Cell {
	Cell(): value(-1), marked(false) {
	}

	Cell(Coord coord, CRect rect, char value = 0)
		: coord(coord), rect(rect), value(value), marked(false) {}

	Coord coord;
	CRect rect;

    char value;
    bool marked;

    bool operator==(const Cell& other) const {
        return (coord == other.coord) && (rect == other.rect) && 
            (other.value == value) && other.marked == marked;
    }

    bool operator!=(const Cell& other) const {
        return !(*this == other);
    }

    Cell& operator=(const Cell& other) {
        if (this != &other) {
            coord = other.coord;
            rect = other.rect;
            value = other.value;
            marked = other.marked;
        }
        return *this;
    }
};