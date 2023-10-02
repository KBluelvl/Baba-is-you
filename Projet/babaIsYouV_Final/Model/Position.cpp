#include "Position.h"



Position::Position(int row, int col): _row{row}, _col{col} {}

Position::Position(const Position &other): _row{other._row}, _col{other._col} {}

Position &Position::operator =(const Position &other) {
    if (this != &other) {
        _row = other._row;
        _col = other._col;
    }
    return *this;
}

Position Position::move(Direction dir) const {
    switch (dir) {
        case Direction::NORD:
        return {_row,(_col-1)};
        case Direction::SUD:
        return {_row,(_col+1)};
        case Direction::OUEST:
        return {(_row-1),_col};
        case Direction::EST:
        return {(_row+1),_col};
    }
}

int Position::getRow() const {
    return _row;
}

int Position::getCol() const{
    return _col;
}

std::string Position::to_String() const {
    return "[" + std::to_string(_row) + "," + std::to_string(_col) + "]";
}

bool Position::operator==(const Position& other) const {
    return _row == other._row && _col == other._col;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    return os << pos.to_String();
}


