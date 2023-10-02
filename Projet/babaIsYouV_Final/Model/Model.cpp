#include "Model.h"
#include "Move.hpp"
#include <iostream>

// Getteur

int Model::getSizeNewBoard() const {return _loader.getSize();}

bool Model::getThereIsSave() const {return _loader.isThereSave();}

const State& Model::getState() const {return _partie.getState();}

const Board& Model::getBoard() const {return _partie.getBoard();}

const std::pair<int, int> Model::sizeBoard() const {return _partie.getBoard().getSizeRowAndCol();}

const Player& Model::getPlayer() const {return _partie.getPlayer();}

const RulesManager &Model::getRulesManager() const{return _partie.getRulesManager();}

bool Model::isEmptyUndo() const {return _commandManager.isEmptyUndo();}

bool Model::isEmptyRedo() const {return _commandManager.isEmptyRedo();}


// Méthode chargement/save

bool Model::loadSave() {
    try {
        _partie = _loader.getSave();
        _commandManager = {};
        notifyObserver();
        return true;
    } catch (...) {
        return false;
    }
}

bool Model::loadNew() {
    try {
        _partie = _loader.getBoard();
        _commandManager = {};
        notifyObserver();
        return true;
    } catch (...) {
        return false;
    }
}

bool Model::restartBoard() {
    try {
        _partie = {_loader.getBoard(_partie.getBoard().getNumBoard())};
        _commandManager = {};
        notifyObserver();
        return true;
    } catch (...) {
        return false;
    }
}

bool Model::nextBoard() {
    int index = _partie.getBoard().getNumBoard();
    if(index < getSizeNewBoard()) {
        try {
            _partie = {_loader.getBoard(++index)};
            _commandManager = {};
           notifyObserver();
            return true;
        } catch (...) {
            return false;
        }
    }
    return false;
}

bool Model::saveBoard() {
    try {
        _loader.setSave(getBoard());
        notifyObserver();
        return true;
    } catch (...) {
        return false;
    }
}

bool Model::setPartie(Partie partie) {
    try {
        _partie = partie;
        notifyObserver();
        return true;
    } catch (...) {
        return false;
    }
}


// Interaction Board

void Model::move(Direction dir) {
    _partie.movePlayer(dir);
//    std::cout << _partie.getBoard().to_StringInforamtions() << std::endl;
    notifyObserver();
}

void Model::executeMove(Direction dir) {
    _commandManager.execute(new Move(*this, _partie, dir));
}

void Model::undoMove() {_commandManager.undo();}

void Model::redoMove(){_commandManager.redo();}


// Observable interface

void Model::add(Observer* obs) {
    if (std::find(_observerList.begin(), _observerList.end(), obs) == _observerList.end()) {
        _observerList.push_back(obs);
    }}

void Model::notifyObserver() {
    for (auto& obs : _observerList) {
        obs->update();
    }
}
