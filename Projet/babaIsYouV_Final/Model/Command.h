#ifndef COMMAND_H
#define COMMAND_H

/**
 * @brief The Command class
 * Classe Interface représentant une commande du jeu
 */
class Command {
public:
    /**
     * @brief execute
     * Permet l'éxecution de la commande
     */
    virtual void execute() = 0;

    /**
     * @brief undo
     * Permet de revenir en arrière sur la commande
     */
    virtual void undo() = 0;
};

#endif // COMMAND_H
