#include "Player.h"
#include <iostream>

//Player::Player(const Player &other) {
//    for (const auto& pair : other._controlBlocks) {
//        Matériaux mat = pair.first;
//        std::vector<std::shared_ptr<BlockMatériaux>> blocks;
//        for (const auto& block : pair.second) {
//            blocks.push_back(block); // Copie les pointeurs vers les mêmes blocs que dans other
//        }
//        _controlBlocks.insert({mat, blocks});
//    }
//}

//Player Player::operator=(const Player &other) {
//    if (this != &other) {
//        _controlBlocks.clear();
//        for (const auto& pair : other._controlBlocks) {
//            Matériaux mat = pair.first;
//            std::vector<std::shared_ptr<BlockMatériaux>> blocks;
//            for (const auto& block : pair.second) {
//                blocks.push_back(block); // Copie les pointeurs vers les mêmes blocs que dans other
//            }
//            _controlBlocks.insert({mat, blocks});
//        }
//    }
//    return *this;
//}



// Getteur

const std::map<Matériaux, std::vector<std::shared_ptr<BlockMatériaux> > >& Player::getPlayer() const {return _controlBlocks;}
bool Player::isAlive() const{return !_controlBlocks.empty();}


// Méthode

void Player::addMatériaux(std::pair<Matériaux, std::vector<std::shared_ptr<BlockMatériaux> > > newControl){
    _controlBlocks.insert(newControl);}

void Player::removeMatériaux(Matériaux &mat){_controlBlocks.erase(mat);}

void Player::removePtrUnused() {
    auto it_map = _controlBlocks.begin();
    while (it_map != _controlBlocks.end()) {

        for (auto it = it_map->second.begin(); it != it_map->second.end();) {
            if(it->use_count() == 2) {
                it = it_map->second.erase(it);
            } else {
                ++it;
            }
        }

        if(it_map->second.empty()) {
            it_map = _controlBlocks.erase(it_map);
        } else {
            ++it_map;
        }
    }
}

void Player::clearPlayer() {
    _controlBlocks.clear();
}


// Affichage

std::string Player::to_String() const {
    std::stringstream ss;
    ss << "player: " << std::endl;
    for(const auto& mat : _controlBlocks) {
        ss << convMatériauxToString(mat.first) << ": ";
        for(const auto& block : mat.second) {
            ss << *block << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::string Player::to_StringInforamtion() const {
    std::stringstream ss;
    ss << "player: " << std::endl;
    for(const auto& mat : _controlBlocks) {
        ss << convMatériauxToString(mat.first) << ": ";
        for(const auto& block : mat.second) {
            ss << *block <<block->getPosition() << convDirectionToString(block->getDirection()) << " " << block.use_count() << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream &os, const Player &player) {return os << player.to_String();}
