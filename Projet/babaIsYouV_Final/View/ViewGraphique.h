#ifndef VIEWGRAPHIQUE_H
#define VIEWGRAPHIQUE_H

#include "Model/Model.h"
#include "../Model/OO.h"
#include "View/mainwindow.h"

class ViewGraphique : Observer {
    Model& _facade;
    MainWindow& _mainWindow;
public:
    ViewGraphique(Model& facade, MainWindow& mainWindow);

    /**
     * @brief displayBoard
     * Affiche la map du jeu
     */
    void displayBoard();

    // Observer interface
    void update() override;
};

#endif // VIEWGRAPHIQUE_H
