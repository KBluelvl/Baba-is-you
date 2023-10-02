#include "Enume.h"

/*
Mes couleurs Matériaux, Sujet, Connecteur, Aspect:
 exemple: "\x1b[48;2;139;69;19m" << "  " << "\033[0m"
 forground \x1b[38;2;.....
 background \x1b[48;2;.....
 Rock, Text_Rock, Push->              Jaune Vomi(128;128;0)
 Wall, Text_wall ->                   Gris(80;80;80)
 Flag, Text_flag, Text_best, Win ->   jaune(255;255;0)
 Metal ->                             Gris Foncé(31;31;31)
 Grass, Stop ->                       Vert(0;128;0)
 Water, Text_water, Sink ->           Bleu(0;0;255)
 Baba, Text_baba, Is ->               Blanc(255;255;255)| Yeux rose (char) You -> Rose (252;0;252)
 Void ->                              Noir(0;0;0)
 Lava, Text_lava ->                   Oragne(255;128;0)
 Bones, Text_Bones, Kill ->           Rouge(128;0;0)

 fin couleur \033[0m
 */


//Direction

Direction convIntToDirection(int index) {
    switch(index) {
    case 0:
        return Direction::NORD;
    case 1:
        return Direction::EST;
    case 2:
        return Direction::SUD;
    case 3:
        return Direction::OUEST;
    default:
        throw std::invalid_argument("!!! Erreur de converstion entier à Direction!!!");
    }
}

int convDirectionToInt(Direction dir) {
    switch(dir) {
    case Direction::NORD:
        return 0;
    case Direction::EST:
        return 1;
    case Direction::SUD:
        return 2;
    case Direction::OUEST:
        return 3;
    }
}

Direction getOpositeDirection(Direction dir) {
    switch(dir) {
    case Direction::NORD:
        return Direction::SUD;
    case Direction::EST:
        return Direction::OUEST;
    case Direction::SUD:
        return Direction::NORD;
    case Direction::OUEST:
        return Direction::EST;
    }
}

Direction convStringToDirection(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "nord") {
        return Direction::NORD;
    } else if (st == "sud") {
        return Direction::SUD;
    } else if (st == "est") {
        return Direction::EST;
    } else if(st == "ouest") {
        return Direction::OUEST;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à Direction ("+st+")!!!");
    }
}

std::string convDirectionToString(Direction direction) {
    switch(direction) {
    case Direction::NORD:
        return "nord";
    case Direction::EST:
        return "est";
    case Direction::SUD:
        return "sud";
    case Direction::OUEST:
        return "ouest";
    }
}

//State

State convStringToState(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "win") {
        return State::WIN;
    } else if (st == "loose") {
        return State::LOOSE;
    } else if (st == "start") {
        return State::START;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à State ("+st+")!!!");
    }
}

std::string convStateToString(State state) {
    switch(state) {
    case State::LOOSE:
        return "loose";
    case State::START:
        return "start";
    case State::WIN:
        return "win";
    }
}


//Matériaux

Matériaux convStringToMatériaux(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "rock") {
        return Matériaux::ROCK;
    } else if (st == "wall") {
        return Matériaux::WALL;
    } else if (st == "flag") {
        return Matériaux::FLAG;
    } else if (st == "metal") {
        return Matériaux::METAL;
    } else if (st == "grass") {
        return Matériaux::GRASS;
    } else if (st == "water") {
        return Matériaux::WATER;
    } else if (st == "baba") {
        return Matériaux::BABA;
    } else if (st == "void") {
        return Matériaux::VOID;
    } else if (st == "lava") {
        return Matériaux::LAVA;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à matériaux ("+st+")!!!");
    }
}

std::string convMatériauxToString(Matériaux matériaux) {
    switch (matériaux) {
    case Matériaux::ROCK:
        return "rock";
    case Matériaux::WALL:
        return "wall";
    case Matériaux::FLAG:
        return "flag";
    case Matériaux::METAL:
        return "metal";
    case Matériaux::GRASS:
        return "grass";
    case Matériaux::WATER:
        return "water";
    case Matériaux::BABA:
        return "baba";
    case Matériaux::VOID:
        return "void";
    case Matériaux::LAVA:
        return "lava";
    }
}

Matériaux convSujetToMatériaux(Sujet sujet) {
    switch (sujet) {
    case Sujet::TEXT_ROCK:
        return Matériaux::ROCK;
    case Sujet::TEXT_WALL:
        return Matériaux::WALL;
    case Sujet::TEXT_FLAG:
        return Matériaux::FLAG;
    case Sujet::TEXT_METAL:
        return Matériaux::METAL;
    case Sujet::TEXT_GRASS:
        return Matériaux::GRASS;
    case Sujet::TEXT_WATER:
        return Matériaux::WATER;
    case Sujet::TEXT_BABA:
        return Matériaux::BABA;
    case Sujet::TEXT_VOID:
        return Matériaux::VOID;
    case Sujet::TEXT_BEST:
        return Matériaux::BABA;
    case Sujet::TEXT_LAVA:
        return Matériaux::LAVA;
    }
}

/*
Mes couleurs Matériaux, Sujet, Connecteur, Aspect:
 exemple: "\x1b[48;2;139;69;19m" << "  " << "\033[0m"
 forground \x1b[38;2;.....
 background \x1b[48;2;.....
 Rock, Text_Rock, Push->              Jaune Vomi(128;128;0)
 Wall, Text_wall ->                   Gris(80;80;80)
 Flag, Text_flag, Text_best, Win ->   jaune(255;255;0)
 Metal ->                             Gris Foncé(31;31;31)
 Grass, Stop ->                       Vert(0;128;0)
 Water, Text_water, Sink ->           Bleu(0;0;255)
 Baba, Text_baba, Is ->               Blanc(255;255;255)| Yeux rose (char) You -> Rose (252;0;252)
 Void ->                              Noir(0;0;0)
 Lava, Text_lava ->                   Oragne(255;128;0)
 Bones, Text_Bones, Kill ->           Rouge(128;0;0)

 fin couleur \033[0m
 */
std::string displayMatériaux(Matériaux matériaux) {
    std::stringstream  buffer;
    switch (matériaux) {
    case Matériaux::ROCK:
        buffer << "\x1b[48;2;128;128;0m  ";
        break;
    case Matériaux::WALL:
        buffer << "\x1b[48;2;80;80;80m  ";
        break;
    case Matériaux::FLAG:
        buffer << "\x1b[48;2;255;255;0m  ";
        break;
    case Matériaux::METAL:
        buffer << "\x1b[48;2;31;31;31m  ";
        break;
    case Matériaux::GRASS:
        buffer << "\x1b[48;2;0;128;0m  ";
        break;
    case Matériaux::WATER:
        buffer << "\x1b[48;2;0;0;255m  ";
        break;
    case Matériaux::BABA:
        buffer << "\x1b[48;2;255;255;255m";
        buffer << "\x1b[38;2;252;0;252m";
        buffer << "**";
        break;
    case Matériaux::VOID:
        buffer << "\x1b[48;2;0;0;0m  ";
        break;
    case Matériaux::LAVA:
        buffer << "\x1b[48;2;255;128;0m  ";
        break;
    }
    buffer << "\033[0m"; // fin de couleur
    return buffer.str();
}


//Sujet

Sujet convStringToSujet(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "text_rock") {
        return Sujet::TEXT_ROCK;
    } else if (st == "text_wall") {
        return Sujet::TEXT_WALL;
    } else if (st == "text_flag") {
        return Sujet::TEXT_FLAG;
    } else if (st == "text_metal") {
        return Sujet::TEXT_METAL;
    } else if (st == "text_grass") {
        return Sujet::TEXT_GRASS;
    } else if (st == "text_water") {
        return Sujet::TEXT_WATER;
    } else if (st == "text_baba") {
        return Sujet::TEXT_BABA;
    } else if (st == "text_void") {
        return Sujet::TEXT_VOID;
    } else if (st == "text_best") {
        return Sujet::TEXT_BEST;
    } else if (st == "text_lava") {
        return Sujet::TEXT_LAVA;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à sujet !!!");
    }
}

std::string convSujetToString(Sujet sujet) {
    switch (sujet) {
    case Sujet::TEXT_ROCK:
        return "text_rock";
    case Sujet::TEXT_WALL:
        return "text_wall";
    case Sujet::TEXT_FLAG:
        return "text_flag";
    case Sujet::TEXT_METAL:
        return "text_metal";
    case Sujet::TEXT_GRASS:
        return "text_grass";
    case Sujet::TEXT_WATER:
        return "text_water";
    case Sujet::TEXT_BABA:
        return "text_baba";
    case Sujet::TEXT_VOID:
        return "text_void";
    case Sujet::TEXT_BEST:
        return "text_best";
    case Sujet::TEXT_LAVA:
        return "text_lava";
    case Sujet::NONE:
        return "none";
    }
}

/*
Mes couleurs Matériaux, Sujet, Connecteur, Aspect:
 exemple: "\x1b[48;2;139;69;19m" << "  " << "\033[0m"
 forground \x1b[38;2;.....
 background \x1b[48;2;.....
 Rock, Text_Rock, Push->              Jaune Vomi(128;128;0)
 Wall, Text_wall ->                   Gris(80;80;80)
 Flag, Text_flag, Text_best, Win ->   jaune(255;255;0)
 Metal ->                             Gris Foncé(31;31;31)
 Grass, Stop ->                       Vert(0;128;0)
 Water, Text_water, Sink ->           Bleu(0;0;255)
 Baba, Text_baba, Is ->               Blanc(255;255;255)| Yeux rose (char) You -> Rose (252;0;252)
 Void ->                              Noir(0;0;0)
 Lava, Text_lava ->                   Oragne(255;128;0)
 Bones, Text_Bones, Kill ->           Rouge(128;0;0)

 fin couleur \033[0m
 */
std::string displaySujet(Sujet sujet) {
    std::stringstream  buffer;
    switch (sujet) {
    case Sujet::TEXT_ROCK:
        buffer << "\x1b[38;2;128;128;0m";
        buffer << "RO";
        break;
    case Sujet::TEXT_WALL:
        buffer << "\x1b[38;2;80;80;80m";
        buffer << "WA";
        break;
    case Sujet::TEXT_FLAG:
        buffer << "\x1b[38;2;255;255;0m";
        buffer << "FL";
        break;
    case Sujet::TEXT_METAL:
        buffer << "ME";
        break;
    case Sujet::TEXT_GRASS:
        buffer << "GR";
        break;
    case Sujet::TEXT_WATER:
        buffer << "\x1b[38;2;0;0;255m";
        buffer << "WA";
        break;
    case Sujet::TEXT_BABA:
        buffer << "\x1b[38;2;255;255;255m";
        buffer << "BA";
        break;
    case Sujet::TEXT_VOID:
        buffer << "VO";
        break;
    case Sujet::TEXT_BEST:
        buffer << "\x1b[38;2;255;255;0m";
        buffer << "BE";
        break;
    case Sujet::TEXT_LAVA:
        buffer << "\x1b[38;2;255;128;0m";
        buffer << "LA";
        break;
    case Sujet::NONE:
        buffer << "NONE";
        break;
    }
    buffer << "\033[0m"; // Couleur blanc fin
    return buffer.str();
}


//Aspect

Aspect convStringToAspect(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "stop") {
        return Aspect::STOP;
    } else if (st == "push") {
        return Aspect::PUSH;
    } else if (st == "win") {
        return Aspect::WIN;
    } else if (st == "kill") {
        return Aspect::KILL;
    } else if (st == "sink") {
        return Aspect::SINK;
    } else if (st == "you") {
        return Aspect::YOU;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à aspect !!!");
    }
}

std::string convAspectToString(Aspect aspect) {
    switch (aspect) {
    case Aspect::STOP:
        return "stop";
    case Aspect::PUSH:
        return "push";
    case Aspect::WIN:
        return "win";
    case Aspect::KILL:
        return "kill";
    case Aspect::SINK:
        return "sink";
    case Aspect::YOU:
        return "you";
    case Aspect::NONE:
        return "none";
    }
}

/*
Mes couleurs Matériaux, Sujet, Connecteur, Aspect:
 exemple: "\x1b[48;2;139;69;19m" << "  " << "\033[0m"
 forground \x1b[38;2;.....
 background \x1b[48;2;.....
 Rock, Text_Rock, Push->              Jaune Vomi(128;128;0)
 Wall, Text_wall ->                   Gris(80;80;80)
 Flag, Text_flag, Text_best, Win ->   jaune(255;255;0)
 Metal ->                             Gris Foncé(31;31;31)
 Grass, Stop ->                       Vert(0;128;0)
 Water, Text_water, Sink ->           Bleu(0;0;255)
 Baba, Text_baba, Is ->               Blanc(255;255;255)| Yeux rose (char) You -> Rose (252;0;252)
 Void ->                              Noir(0;0;0)
 Lava, Text_lava ->                   Oragne(255;128;0)
 Bones, Text_Bones, Kill ->           Rouge(128;0;0)

 fin couleur \033[0m
 */
std::string displayAspect(Aspect aspect) {
    std::stringstream  buffer;
    switch (aspect) {
    case Aspect::STOP:
        buffer << "\x1b[38;2;0;128;0m";
        buffer << "ST";
        break;
    case Aspect::PUSH:
        buffer << "\x1b[38;2;128;128;0m";
        buffer << "PU";
        break;
    case Aspect::WIN:
        buffer << "\x1b[38;2;255;255;0m";
        buffer << "WI";
        break;
    case Aspect::KILL:
        buffer << "\x1b[38;2;128;0;0m";
        buffer << "KI";
        break;
    case Aspect::SINK:
        buffer << "\x1b[38;2;0;0;255m";
        buffer << "SI";
        break;
    case Aspect::YOU:
        buffer << "\x1b[38;2;255;255;255m";
        buffer << "YO";
        break;
    case Aspect::NONE:
        buffer << "NONE";
        break;
    }
    buffer << "\033[0m"; // fin de Couleur blanc
    return buffer.str();
}


//Connecteur

Connecteur convStringToConnecteur(std::string st) {
    std::transform(st.begin(), st.end(), st.begin(), [](char c) { return std::tolower(c); });
    if(st == "is") {
        return Connecteur::IS;
    } else {
        throw std::invalid_argument("!!! Erreur de converstion string à connecteur !!!");
    }
}

std::string convConnecteurToString(Connecteur connecteur) {
    switch (connecteur) {
    case Connecteur::IS:
        return "is";
    }
}

std::string displayConnecteur(Connecteur connecteur) {
    std::stringstream  buffer;
    switch (connecteur) {
    case Connecteur::IS:
//        buffer << "\x1b[38;2;255;255;255m";
        buffer << "IS";
        break;
    }
//    buffer << "\033[0m"; // fin de Couleur blanc
    return buffer.str();
}
