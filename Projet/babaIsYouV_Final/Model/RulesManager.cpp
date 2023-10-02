#include "RulesManager.h"
#include "Player.h"
#include <iostream>


RulesManager::RulesManager(Board &board, Player& player) {
    initCheckerRules(board);
    initRulesToMat();
    checkRuleConnecteur(board, player);
}

void RulesManager::checkRuleConnecteur(Board& board,  Player& player, std::shared_ptr<BlockConnecteur> bc) {
    for(auto it = _checkerRules.begin(); it != _checkerRules.end(); ++it) {
        if(bc != nullptr) {
            if(bc == it->first.first) {
                // vérifie ce connecteur
                creatAndCheckRuleToKeyConnecteur(it, board, player);
            }
        } else {
            // Si bc est nul, vérifie tous les BlockConnecteur
            creatAndCheckRuleToKeyConnecteur(it, board, player);
        }
    }
}

std::map<int, Aspect>& RulesManager::getAspectToMat(Matériaux mat) {
    return _rulesToMat.at(mat);
}


// Affichage

std::string RulesManager::to_String() const {
    std::stringstream ss;
    ss << "Checker de règles: " << std::endl;
    for(auto& check : _checkerRules) {
        ss << check.first.first->getPosition();
        ss << " " << convDirectionToString(check.first.second);
        ss << " -> ";
        if(check.second.first == nullptr) {
            ss << "NONE";
        } else {
            ss << check.second.first->to_String();
        }
        ss << ">";
        if(check.second.second == nullptr) {
            ss << "NONE";
        } else {
            ss << check.second.second->to_String();
        }
        ss << std::endl;
    }
    ss << std::endl;
    ss << "règles associés au matériaux: " << std::endl;
    for(auto& mat : _rulesToMat) {
        ss << displayMatériaux(mat.first);
        for(auto& rule : mat.second) {
            ss << displayAspect(rule.second) << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::string RulesManager::to_StringInformations() const {
    std::stringstream ss;
    ss << "Checker de règles: " << std::endl;
    for(auto& check : _checkerRules) {
        ss << check.first.first->getPosition() << " " << check.first.first.use_count();
        ss << " " << convDirectionToString(check.first.second);
        ss << " -> ";
        if(check.second.first == nullptr) {
            ss << "NONE";
        } else {
            ss << check.second.first->to_String();
        }
        ss << ">";
        if(check.second.second == nullptr) {
            ss << "NONE";
        } else {
            ss << check.second.second->to_String();
        }
        ss << std::endl;
    }
    ss << std::endl;
    ss << "règles associés au matériaux: " << std::endl;
    for(auto& mat : _rulesToMat) {
        ss << displayMatériaux(mat.first) << " -> ";
        for(auto& rule : mat.second) {
            ss << displayAspect(rule.second) << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream &os, const RulesManager &obj) { return os << obj.to_String();}

// private méthode

void RulesManager::initCheckerRules(Board &board) {
    for(auto block : board.getBlocksTypeAndSameNameInsideAllBoard<BlockConnecteur>("is")) {
        _checkerRules.insert({{block, Direction::NORD}, {}});
        _checkerRules.insert({{block, Direction::OUEST}, {}});
    }
}

void RulesManager::initRulesToMat() {
    for (int i = 0; i < static_cast<int>(Matériaux::LAVA) + 1; ++i) { // A changer par le dernière élément de l'énum Mat
        Matériaux matToInsert = static_cast<Matériaux>(i);
        _rulesToMat[matToInsert];
    }
}

void RulesManager::creatAndCheckRuleToKeyConnecteur(std::map<keyConnecteur, rule>::iterator& it, Board &board, Player &player) {
    auto& règleToConnecteur = it->second;
    std::shared_ptr<BlockSujet>& ruleBS = règleToConnecteur.first;
    std::shared_ptr<BlockAspect>& ruleBA = règleToConnecteur.second;
    if(ruleBS != nullptr || ruleBA != nullptr ) { // Suppression de la règle si elle existe
        removeRule(ruleBS->getMatériaux(), ruleBA->getAspect(), player);
        ruleBS = nullptr;
        ruleBA = nullptr;
    }

    Position posSujet = it->first.first->getPosition().move(it->first.second); // Position du sujet (théorique)
    Position posOposite = it->first.first->getPosition().move(getOpositeDirection(it->first.second)); // Position du sujet ou aspect (théorique)

    if(!board.isInside(posSujet) || !board.isInside(posOposite)) {return;} // Vérifie si c'est dans le plateau

    std::vector<std::shared_ptr<BlockSujet>> bs = board.getBlocksTypeAndSameNameInsidePos<BlockSujet>(posSujet);
    std::vector<std::shared_ptr<BlockSujet>> bsOposite = board.getBlocksTypeAndSameNameInsidePos<BlockSujet>(posOposite);
    std::vector<std::shared_ptr<BlockAspect>> baOposite = board.getBlocksTypeAndSameNameInsidePos<BlockAspect>(posOposite);

    if(bs.size() == 1) {
         if(bsOposite.size() == 1) {
            for(const auto& block : board.getBlocksTypeAndSameNameInsideAllBoard<BlockMatériaux>(convMatériauxToString(bs.at(0)->getMatériaux()))){
                block->setMatériaux(bsOposite.at(0)->getMatériaux());
            }
        } else {
             if(baOposite.size() == 1) {
                creatRule(bs.at(0)->getMatériaux(), baOposite.at(0)->getAspect(), board, player);
                ruleBS = bs.at(0);
                ruleBA = baOposite.at(0);
            }
        }
    }
}

void RulesManager::creatRule(Matériaux mat, Aspect asp, Board& board, Player& player) {
    if (asp == Aspect::YOU) {
        player.addMatériaux(std::make_pair(mat, board.getBlocksTypeAndSameNameInsideAllBoard<BlockMatériaux>(convMatériauxToString(mat))));
    }
    _rulesToMat[mat].insert(std::make_pair(static_cast<int>(asp), asp));
}

void RulesManager::removeRule(Matériaux mat, Aspect asp, Player& player) {
    if(asp == Aspect::YOU) {
        player.removeMatériaux(mat);
    }
    auto itMat = _rulesToMat.find(mat);
    if (itMat != _rulesToMat.end()) {
        auto& mapToModify = itMat->second;
        mapToModify.erase(static_cast<int>(asp));
    }
}
