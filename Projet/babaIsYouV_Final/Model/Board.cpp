#include "Board.h"
#include <iostream>


Board::Board(int sizeRow, int sizeCol, int numBoard): _sizeRow(sizeRow), _sizeCol(sizeCol), _numBoard(numBoard) {
    _carte.resize(_sizeRow); // Redimensionne le vecteur externe
    for (int row = 0; row < _sizeRow; ++row) {
        for (int col = 0; col < _sizeCol; ++col) {
            Position pos {row, col};
            _carte[row].emplace_back(pos); // Utilise la liste d'initialisation pour construire les objets Case
        }
    }
}

Board::Board(const Board &other)
    : _sizeRow(other._sizeRow), _sizeCol(other._sizeCol), _numBoard(other._numBoard) {
    _carte.reserve(_sizeRow);
    for (int row = 0; row < _sizeRow; ++row) {
        std::vector<Case> temp;
        temp.reserve(_sizeCol);
        for (int col = 0; col < _sizeCol; ++col) {
            temp.emplace_back(other._carte[row][col]);
        }
        _carte.emplace_back(std::move(temp));
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        _sizeRow = other._sizeRow;
        _sizeCol = other._sizeCol;
        _numBoard = other._numBoard;
        _carte.clear();
        _carte.reserve(_sizeRow);
        for (int row = 0; row < _sizeRow; ++row) {
            std::vector<Case> temp;
            temp.reserve(_sizeCol);
            for (int col = 0; col < _sizeCol; ++col) {
                temp.emplace_back(other._carte[row][col]);
            }
            _carte.emplace_back(std::move(temp));
        }
    }
    return *this;
}

// Getteur

std::pair<int, int> Board::getSizeRowAndCol() const {return std::make_pair(_sizeRow, _sizeCol);}
int Board::getNumBoard() const{return _numBoard;}
Carte Board::getCarte() const{return _carte;}

bool Board::isInside(Position pos) const { // Peut le mettre sur une seule ligne (row && row) && (col && col)
    if(pos.getRow() >= 0 && pos.getRow() < _sizeRow) { // Test si c'est dans la ligne (0 à taille row -1
        if(pos.getCol() >= 0 && pos.getCol() < _sizeCol) { // Test si c'est dans la col (0 à taille col -1)
            return true;
        }
    }
    return false;
}

// Méthode Board

void Board::addBlock(std::shared_ptr<Block> block) {
    if(block == nullptr) {
        throw std::invalid_argument("Board->addBlock, le block est nullptr");
    }
    if(!isInside(block->getPosition())) {
        throw std::invalid_argument("Board->addBlock, problème pos (tableau: [" + std::to_string(_sizeRow) +
                                    "," + std::to_string(_sizeCol) + "], block: " + block->getPosition().to_String() + ")");
    }
    _carte[block->getPosition().getRow()][block->getPosition().getCol()].addlast(block);
}

std::shared_ptr<Block> Board::removeBlock(const std::shared_ptr<Block>& block) {
    if(block == nullptr) {
        throw std::invalid_argument("Board->removeBlock, le block est nullptr");
    }
    if(!isInside(block->getPosition())) {
        throw std::invalid_argument("Board->removeBlock, problème pos (tableau: [" + std::to_string(_sizeRow) +
                                    "," + std::to_string(_sizeCol) + "], block: " + block->getPosition().to_String() + ")");
    }
    return _carte[block->getPosition().getRow()][block->getPosition().getCol()].removeIndex(block->getIndexCase());
}

void Board::moveBlock(const std::shared_ptr<Block> &block, Direction dir) {
    if(std::shared_ptr<Block> blockGet = removeBlock(block)) {
        blockGet->MoveBlock(dir);
        addBlock(blockGet);
    } else {
        std::cout << "le block est nullptr (moveBlock in Board)" << std::endl;
    }
}

std::shared_ptr<Block> Board::getLastBlock(Position pos) const  {
    if(!isInside(pos)) {
        throw std::invalid_argument("Board->getLastBlock, problème pos (tableau: [" + std::to_string(_sizeRow) +
                                    "," + std::to_string(_sizeCol) + "], pos: " + pos.to_String() + ")");
    }
    return _carte[pos.getRow()][pos.getCol()].getLastBlock();
}

std::string Board::to_String() const {
    std::stringstream ss;
    ss << "num: " << _numBoard << std::endl;
    ss << "taille: " << _sizeRow << "," << _sizeCol << std::endl;
    for (int row = 0; row < _sizeRow; ++row) {
        for (int col = 0; col < _sizeCol; ++col) {
            ss << _carte[col][row].to_String();
        }
        ss << std::endl;
    }
    return ss.str();
}

std::string Board::to_StringInforamtions() const {
    std::stringstream ss;
    ss << "num: " << _numBoard << std::endl;
    ss << "taille: " << _sizeRow << "," << _sizeCol << std::endl;
    for (int row = 0; row < _sizeRow; ++row) {
        for (int col = 0; col < _sizeCol; ++col) {
            ss << _carte[col][row].to_StringInFormation();
        }
        ss << std::endl;
    }
    return ss.str();
}


std::ostream& operator<<(std::ostream& os, const Board& obj) {
    return os << obj.to_String();
}
