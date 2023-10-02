#include "Controller.h"


Controller::Controller(Model& facade, ViewConsole& view): _facade{facade},_view{view} {}

void Controller::start() {
//    _view.clearConsol();
    _view.displayTitle();
    bool end = accueil();
//    _view.clearConsol();
//    if(!end) {_view.displayBoard();}
    while(!end) {
        end = direction();


        switch(_facade.getState()) {
            case State::WIN:
                end = win();
                break;
            case State::LOOSE:
                end = dead();
                break;
            case State::START:
                break;
        }

        if(end) {
            start();
        }
    }
}

bool Controller::accueil() {
    _view.displayChooseLoadOrSave(); // display al demande de choix de new, save ou exit
    std::vector<std::string> listRWord {"new", "save", "exit"};
    bool rightCommand = false;
    int wrongAnswer = 0;
    while (!rightCommand) {
        rightCommand = true;
        switch(getCommandPlayer(listRWord)) {
        case 1:
            _facade.loadNew();
            break;
        case 2:
            _facade.loadSave();
            break;
        case 3:
            return true;
        default:
            rightCommand = false;
            wrongAnswer ++;
            if(wrongAnswer == 10) {
                _view.displayError("!!! 10 mauvaises entrée, retour au menu !!!");
                return true;
            } else {
                _view.displayError("Veillez entrer NEW, SAVE, EXIT");
            }
        }

    }
    return false;
}

bool Controller::direction() {
    _view.displayChooseDirection();
    std::vector<std::string> listRWord {"z", "q", "s", "d", "undo", "redo", "save", "help", "exit"};
    bool rightCommand = false;
    int wrongAnswer = 0;
    while (!rightCommand) {
        rightCommand = true;
        switch(getCommandPlayer(listRWord)) {
        case 1:
            _facade.executeMove(Direction::NORD);
            break;
        case 2:
            _facade.executeMove(Direction::OUEST);
            break;
        case 3:
            _facade.executeMove(Direction::SUD);
            break;
        case 4:
            _facade.executeMove(Direction::EST);
            break;
        case 5:
            if(_facade.isEmptyUndo()) {
                _view.displayError("!!! Pas de commande à undo !!!");
                rightCommand = false;
            } else {
                _facade.undoMove();
            }
            break;
        case 6:
            if(_facade.isEmptyRedo()) {
                _view.displayError("!!! Pas de commande à redo !!!");
                rightCommand = false;
            } else {
                _facade.redoMove();
            }
            break;
        case 7:
            if(_facade.saveBoard()) {
                _view.displayError("Save réussi");
            } else {
                _view.displayError("Save pas réussi");
            }
            rightCommand = false;
            break;
        case 8:
            _view.displayRègles();
            rightCommand = false;
            break;
        case 9:
            return true;
        default:
            rightCommand = false;
            wrongAnswer ++;
            if(wrongAnswer == 10) {
                _view.displayError("!!! 10 mauvaises entrée, retour au menu !!!");
                return true;
            } else {
                _view.displayError("Veillez entrer Z, Q, S, D, UNDO, REDO ou EXIT");
            }
        }
    }
    return false; // si pas de exit = false, si exit = true
}


bool Controller::dead() {
    _view.displayDead();
    std::vector<std::string> listRWord {"exit", "undo", "restart"};
    bool rightCommand = false;
    int wrongAnswer = 0;
    while (!rightCommand) {
        switch(getCommandPlayer(listRWord)) {
        case 1:
            return true;
        case 2:
            if(_facade.isEmptyUndo()) {
                _view.displayError("!!! Pas de commande à undo !!!");
            } else {
                _view.displayError("!!! mouvement undo !!!");
                _facade.undoMove();
                return false;
            }
        case 3:
            _facade.restartBoard();
            return false;
        default:
            rightCommand = false;
            wrongAnswer ++;
            if(wrongAnswer == 10) {
                _view.displayError("!!! 10 mauvaises entrée, retour au menu !!!");
                return true;
            } else {
                _view.displayError("Veillez entrer EXIT, undo ou restart");
            }
        }
    }
    return rightCommand;
}

bool Controller::win() {
    _view.displayWin();
    std::vector<std::string> listRWord {"exit", "next"};
    bool rightCommand = false;
    int wrongAnswer = 0;
    while (!rightCommand) {
        switch(getCommandPlayer(listRWord)) {
        case 1:
            return true;
        case 2:
            if(!_facade.nextBoard()) {
                _view.displayError("!!! Plus de partie disponible, retour au menu !!!");
                return true;
            }
            return false;
        default:
            rightCommand = false;
            wrongAnswer ++;
            if(wrongAnswer == 10) {
                _view.displayError("!!! 10 mauvaises entrée, retour au menu !!!");
                return true;
            } else {
                _view.displayError("Veillez entrer EXIT ou next");
            }
        }
    }
    return rightCommand;
}

int Controller::getCommandPlayer(std::vector<std::string> listRWord) {
    std::string commande;
    std::getline(std::cin, commande);
    std::transform(commande.begin(), commande.end(), commande.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    int index = 1;
    for (const std::string& rightWord : listRWord) {
        if(commande == rightWord) {
            return index;
        }
        index ++;
    }
    return -1;
}


