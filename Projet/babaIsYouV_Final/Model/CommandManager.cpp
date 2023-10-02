#include "CommandManager.h"
#include <iostream>

void CommandManager::execute(Command* command) {
    command->execute();
    _historyUndo.push(command);
    std::stack<Command*> clearStack;
    _historyRedo.swap(clearStack);
}

void CommandManager::undo() {
    if(isEmptyUndo()) {
        throw std::invalid_argument("Aucun mouvement à annuler");
    }
    Command* toUndo = _historyUndo.top();
    _historyUndo.pop();
    toUndo->undo();
    _historyRedo.push(toUndo);
}

void CommandManager::redo() {
    if(isEmptyRedo()) {
        throw std::invalid_argument("Aucun undo à annuler");
    }
    Command* toRedo = _historyRedo.top();
    _historyRedo.pop();
    toRedo->execute();
    _historyUndo.push(toRedo);
}

bool CommandManager::isEmptyUndo() const {return _historyUndo.size() == 0;}

bool CommandManager::isEmptyRedo() const {return _historyRedo.size() == 0;}
