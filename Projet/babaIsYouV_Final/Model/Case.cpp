#include "Case.h"
#include <iostream>

// Constructeur

Case::Case(Position pos) {
    _stackBlock.emplace_back(std::make_shared<BlockMatériaux>("void", pos, Direction::NORD));
    _stackBlock.at(size())->setIndexCase(size());
}

Case::Case(const Case &other) {
    for (int index = 0; index <= other.size(); ++index) {
        _stackBlock.emplace_back(other._stackBlock.at(index)->clone());
    }
}

Case &Case::operator =(const Case &other) {
    if(this != &other) {
        for (int index = 0; index <= other.size(); ++index) {
            _stackBlock.emplace_back(other._stackBlock.at(index)->clone());
        }
    }
    return *this;
}

bool Case::operator==(const Case &other) {
    if(size() != other.size()) {return false;}
    for (int index = 0; index <= size(); ++index) {
        if(_stackBlock.at(index)->getName() != other._stackBlock.at(index)->getName()) {
            return false;
        }
    }
    return true;
}

// Getteur

const std::shared_ptr<Block> Case::getLastBlock() const {return (isEmpty())? nullptr :_stackBlock.back();}

const std::vector<std::shared_ptr<Block> > Case::getAllBlock() const {
    std::vector<std::shared_ptr<Block>> result;
    for (int index = 1; index < _stackBlock.size(); ++index) { // Ne prend pas en compte le block Iummable
        result.emplace_back(_stackBlock.at(index));
    }
    return result;
}

int Case::size() const {return _stackBlock.size()-1;}

bool Case::isEmpty() const {return size() == 0;}

// Méthode

std::shared_ptr<Block> Case::removeLast() {
    if (isEmpty()) {
        return nullptr;
    }
    std::shared_ptr<Block> lastBlock = _stackBlock.back();
    _stackBlock.pop_back();
    return lastBlock;
}

std::shared_ptr<Block> Case::removeIndex(int index) {
    if(index > size()) {
        throw std::invalid_argument("Le block n'est pas présent dans cette case");
    }
    if (index == 0) {
        return nullptr;
    }
    std::shared_ptr<Block> lastBlock = _stackBlock.at(index);
    _stackBlock.erase(_stackBlock.begin()+index);
    for(int par = index; par <= size(); par++) {
        _stackBlock.at(par)->setIndexCase(par);
    }
    return lastBlock;
}


void Case::addlast(std::shared_ptr<Block> block) {
    block->setIndexCase(size()+1);
    _stackBlock.emplace_back(block);
}

// Affichage

std::string Case::to_String() const {
    return _stackBlock.at(size())->to_String();
}

std::string Case::to_StringInFormation() const {
    std::stringstream ss;
    for(const auto& block : _stackBlock) {
        ss << block->to_String() << block->getPosition();
        if(auto bm = std::dynamic_pointer_cast<BlockMatériaux>(block)) {
            ss << convDirectionToString(bm->getDirection());
        }
        ss  << " " << block->getIndexCase() << "|" << block.use_count() << " ";
    }
    ss << std::endl;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Case& obj) {
    return os << obj.to_String();
}
