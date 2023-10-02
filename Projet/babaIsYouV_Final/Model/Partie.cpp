#include "Partie.h"
#include <iostream>


Partie::Partie(Board board): _board{board}, _player{}, _rulesManager{_board, _player}, _state{State::START} {
//    _player.clearPlayer();
//    _rulesManager.checkRuleConnecteur(_board, _player);
}


Partie::Partie(const Partie &other): _board{other._board}, _player{}, _rulesManager{_board, _player}, _state{other._state} {
//    _player.clearPlayer();
//    _rulesManager.checkRuleConnecteur(_board, _player);
}

Partie &Partie::operator=(const Partie &other) {
    if (this != &other) {
        _board = other._board;
        _player.clearPlayer();
//        _player = other._player;
        _rulesManager = RulesManager(_board, _player); // Création d'une nouvelle instance
//        _rulesManager.checkRuleConnecteur(_board, _player);
//        for(auto& mat : other._player.getPlayer()) {
//            addMatériauxToPlayer(mat.first);
//        }
        _state = other._state;
    }
    return *this;
}


// Getteur

const Player& Partie::getPlayer() const {return _player;}

const Board& Partie::getBoard() const {return _board;}

const State& Partie::getState() const {return _state;}

void Partie::setState(State state) {_state = state;}

const RulesManager &Partie::getRulesManager() const{return _rulesManager;}

// Méthode

void Partie::movePlayer(Direction dir) {
    for(const auto& mat : _player.getPlayer()) {
        for(const auto& block : mat.second) {
            moveBlock(block, dir, true);
            //Tester si le block à encore un pointeur > 2, si non, le sup de la liste
        }
    }
}

bool Partie::moveBlock(const std::shared_ptr<Block> &block, Direction dir, bool isPlayer) {
    Position posToMove = block->getPosition().move(dir);
    bool validMove = true;
    bool btMove = false;
    if(_board.isInside(posToMove)) {
        for(const auto& b : _board.getBlocksTypeAndSameNameInsidePos<Block>(posToMove)) {
            if(const std::shared_ptr<BlockMatériaux>& bm = std::dynamic_pointer_cast<BlockMatériaux>(b)) {
                const auto& rules = _rulesManager.getAspectToMat(bm->getMatériaux());
                for(const auto rule : rules) {
                    validMove = applyRule(rule.second, block, dir, isPlayer);
                    if(!validMove){break;}
                }
            } else if (const std::shared_ptr<BlockText>& bt = std::dynamic_pointer_cast<BlockText>(b)) {
                validMove = applyRule(Aspect::PUSH, block, dir, isPlayer);
                btMove = true;
            }
            if(!validMove){break;}
        }
        if(validMove) {
            _board.moveBlock(block, dir);
            if(btMove) {
                _rulesManager.checkRuleConnecteur(_board, _player);
            }

        }
        if(!_player.isAlive()){_state = State::LOOSE;}
    } else {
        std::cout << "PosToMove en dehors du board" << std::endl;
    }
    return validMove;
}

bool Partie::applyRule(Aspect asp, const std::shared_ptr<Block>& block, Direction dir, bool isPlayer) {
    bool isBlockText = false;
    if(std::dynamic_pointer_cast<BlockText>(block)) {
        isBlockText = true;
    }

    switch(asp) {
    case Aspect::STOP:
        return false;
    case Aspect::PUSH:
        if(moveBlock(_board.getLastBlock(block->getPosition().move(dir)), dir, false)) {
            return true;
        } else {
            return false;
        }
    case Aspect::WIN:
        if(isPlayer) {_state = State::WIN;}
        return true;
    case Aspect::KILL:
        if(isBlockText || !isPlayer) {
            return true;
        } else {
            _board.removeBlock(block);
            _player.removePtrUnused();
            return false;
        }
    case Aspect::SINK:
        if(isBlockText) {
            return true;
        } else if(!isPlayer) {
            _board.removeBlock(_board.getLastBlock(block->getPosition().move(dir)));
            _board.removeBlock(block);
            _player.removePtrUnused();
            return false;
        } else {
            _board.removeBlock(_board.getLastBlock(block->getPosition().move(dir)));
            _board.removeBlock(block);
            _player.removePtrUnused();
            return false;
        }
    default:
        return true;
    }
    return true;
}

// Méthode player

void Partie::addMatériauxToPlayer(Matériaux mat) {
    _player.addMatériaux(std::make_pair(mat, _board.getBlocksTypeAndSameNameInsideAllBoard<BlockMatériaux>(convMatériauxToString(mat))));
}

void Partie::removeMatériauxToPlayer(Matériaux mat) {
    _player.removeMatériaux(mat);
}

// Affichage

std::string Partie::to_String() const {
    std::stringstream ss;
    ss << "état du jeu: " << convStateToString(_state) << std::endl;
    ss << "joueur en vie: " << _player.isAlive() << std::endl;
    if(_player.isAlive()) {
        ss << _player.to_String() << std::endl;
    }
    ss << _board.to_String() << std::endl;
    return ss.str();
}

std::string Partie::to_StringInformations() const {
    std::stringstream ss;
    ss << "état du jeu: " << convStateToString(_state) << std::endl;
    ss << "joueur en vie: " << _player.isAlive() << std::endl;
    if(_player.isAlive()) {
        ss << _player.to_StringInforamtion() << std::endl;
    }
    ss << _board.to_StringInforamtions() << std::endl;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Partie& obj) {
    return os << obj.to_String();
}


