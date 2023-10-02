#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include <stdexcept>

#include "Command.h"

/**
 * @brief The CommandManager class
 * Gère la sauvegarde temporaire de la partie à chaque mouvements
 * et permet de revenir en arrière ou en avant sur les mouvements
 */
class CommandManager {

    std::stack<Command*> _historyUndo {};
    std::stack<Command*> _historyRedo {};

public:
    CommandManager() = default;

    /**
     * @brief execute
     * Execute la commande passée en paramètre et la stock de
     * la stack du undo et vide la stack de redo
     * @param command à éxecuter et à save
     */
    void execute(Command* command);

    /**
     * @brief undo
     * Permet de revenir en arrière sur un commande déjà éxecutée
     * Et la stock dans la stack Redo
     */
    void undo();

    /**
     * @brief redo
     * Permet de revenir en arrière sur une commande que l'on a undo
     * et la stock dans la stack Undo
     */
    void redo();

    /**
     * @brief isEmptyUndo
     * @return True si la stack Undo est vide et false si non
     */
    bool isEmptyUndo() const;

    /**
     * @brief isEmptyRedo
     * @return True si la stack Redo est vide et false si non
     */
    bool isEmptyRedo() const;

};

#endif // COMMANDMANAGER_H
