#include "ViewGraphique.h"

ViewGraphique::ViewGraphique(Model& facade,MainWindow& mainWindow): _facade{facade}, _mainWindow{mainWindow}{
    facade.add(this);
    _mainWindow.show();
}

void ViewGraphique::displayBoard() {
    _mainWindow.setupBoard();
    _mainWindow.show();
}

void ViewGraphique::update() {
    displayBoard();
}
