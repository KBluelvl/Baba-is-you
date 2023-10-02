#ifndef VIEW_H
#define VIEW_H

#include "Model/Model.h"
#include <iostream>


/**
 * @brief The View class
 * Classe gérant la vue console
 */
class ViewConsole : Observer {

    Model& _facade;


public:
    ViewConsole(Model& facade);

    /**
     * @brief displayTitle
     * Affiche le titre du jeu "BABA IS YOU"
     */
    void displayTitle();

    /**
     * @brief displayLoadOrSave
     * Affiche la demande nouvelle partie ou save
     */
    void displayChooseLoadOrSave();

    /**
     * @brief displayPlayer
     * Affiche les informations sur le joueur
     * blocks contrôlé par le joueur,
     * si aucun block, afficher qu'il est mort
     */
    void displayPlayer();

    /**
     * @brief displayBoard
     * Affiche la map du jeu
     */
    void displayBoard();

    /**
     * @brief displayChooseDirection
     * Affiche la demande de direction
     */
    void displayChooseDirection();

    /**
     * @brief displayError
     * Affiche les erreurs potentiels en rouge vif
     * @param e l'erreur à afficher
     */
    void displayError(std::string e);

    /**
     * @brief displayDead
     * Affiche la mort du player et demande si il veut
     * undo, restart, ou exit
     */
    void displayDead();

    /**
     * @brief displayWin
     * Affiche que la partie est gagné
     */
    void displayWin();

    /**
     * @brief displayRègles
     * Affiche le nom des block matériaux avec leurs couleurs dans le jeu
     * ainsi que les règles qui y sont liées
     * |----------------------------------------------|
     * |  BlockMatériaux[couleur] --> règles liées    |
     * |----------------------------------------------|
     */
    void displayRègles();

    /**
     * @brief clearConsol
     * Retire tout l'affichage de la console
     */
    void clearConsol();


    // Observer interface
    void update() override;
};

#endif // VIEW_H
