#ifndef MOVE_HPP
#define MOVE_HPP


#include "Command.h"
#include "Model.h"

class Move : public Command {
protected: Model& _model;
    const Partie _savePartie;
    const Direction _saveDir;

public:

    Move(Model& model, Partie partie, Direction dir):
        _model{model}, _savePartie{partie}, _saveDir{dir} {}

    // Command interface

    void execute() override{_model.move(_saveDir);}
    void undo() override{_model.setPartie(_savePartie);}
};

#endif // MOVE_HPP
