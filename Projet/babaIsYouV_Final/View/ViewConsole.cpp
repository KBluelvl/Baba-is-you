#include "ViewConsole.h"

using namespace std;

ViewConsole::ViewConsole(Model& facade): _facade{facade}{
    facade.add(this);
}

void ViewConsole::displayTitle() {
    cout << endl;
    cout << endl;
    cout << "|-----------------|" << endl;
    cout << "|   " <<   "\x1b[38;2;255;0;255m"<< "BABA" << " \033[0m";
    cout <<             "\x1b[38;2;255;255;255m"<< "IS" << " \033[0m";
    cout <<             "\x1b[38;2;255;0;255m"<< "YOU" << "\033[0m" << "   |" << endl;
    cout << "|-----------------|" << endl;
    cout << endl;
    cout << endl;
}

void ViewConsole::displayChooseLoadOrSave() {
    cout << "Rentrer new ou save ou exit" << endl;
    cout << "new  --> Recommence le jeu depuis le zéro" << endl;
    cout << "save --> Reprend une partie sauvegarder" << endl;
    cout << "exit --> Quitte le le jeu" << endl;
}

void ViewConsole::displayPlayer() {
//    std::stringstream ss;
//    ss << "player: " << std::endl;
//    for(const auto& mat : _facade.getPlayer().getPlayer()) {
//        ss << convMatériauxToString(mat.first) << ": ";
//        for(const auto& block : mat.second) {
//            ss << *block << " ";
//        }
//        ss << std::endl;
//    }
//    std::cout << ss.str() << std::endl;
    std::cout << _facade.getPlayer().to_StringInforamtion() << std::endl;
}

void ViewConsole::displayBoard() {
    std::pair<int, int> sizeBoard = _facade.getBoard().getSizeRowAndCol();
    for (int x = 0; x < sizeBoard.first; ++x) {
        for (int y = 0; y < sizeBoard.second; ++y) {
            cout << _facade.getBoard().getCarte()[y][x];
        }
        cout << endl;
    }
    cout << endl;
}

void ViewConsole::displayChooseDirection() {
    cout << "Touches: Z, Q, S, D, undo, redo, save, help ou exit" << endl;
}

void ViewConsole::displayError(string e) {
    cout << "\x1b[38;2;255;0;0m"<< e << " \033[0m" <<  endl;
}

void ViewConsole::displayDead() {
    cout << "\x1b[38;2;255;0;0m" << endl;
    cout << endl;
    cout << "|-----------------|" << endl;
    cout << "| VOUS ETES MORT! |" << endl;
    cout << "|-----------------|" << endl;
    cout << endl;
    cout << " \033[0m" <<  endl;
    cout << "Enrer exit, undo ou restart" << endl;
}

void ViewConsole::displayWin() {
    cout << "\x1b[38;2;255;0;0m" << endl; //couleur verte
    cout << endl;
    cout << "|-------------------|" << endl;
    cout << "| VOUS AVEZ GAGNER! |" << endl;
    cout << "|-------------------|" << endl;
    cout << endl;
    cout << " \033[0m" <<  endl;
    cout << "entrer exit ou next" << endl;
}

void ViewConsole::displayRègles() {
    cout << _facade.getRulesManager().to_StringInformations() << endl;
}

void ViewConsole::clearConsol(){std::system("cls");}

void ViewConsole::update() {
//    clearConsol();
    displayPlayer();
    displayBoard();
}
