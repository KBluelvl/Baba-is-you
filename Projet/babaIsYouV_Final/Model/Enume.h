#ifndef ENUME_H
#define ENUME_H

#include <sstream>
#include <string>
#include <algorithm>

/**
 * @brief The Direction enum
 * Définit les 4 mouvements possibles
 */
enum class Direction {NORD,SUD,EST,OUEST};
extern Direction convIntToDirection(int index);     //Permet la convestion d'un entier à ça son attribut Direction
extern int convDirectionToInt(Direction dir);       //Permet la convestion d'une Direction à son entier correspondant
extern Direction getOpositeDirection(Direction dir);//Donne le direction opposé
extern Direction convStringToDirection(std::string st);     //Permet la convestion d'un string à ça son attribut State
extern std::string convDirectionToString(Direction direction);  //Permet la converstion d'un attribut du State à son string

/**
 * @brief The State enum
 * Définit les trois états de jeu possible
 */
enum class State{WIN,LOOSE,START};
extern State convStringToState(std::string st);     //Permet la convestion d'un string à ça son attribut State
extern std::string convStateToString(State state);  //Permet la converstion d'un attribut du State à son string

/**
 * @brief The Sujet enum
 * Définit le sujet d'un règle et d'un blockSujet, elle relie un sujet à son matériaux
 */
enum class Sujet {TEXT_ROCK,TEXT_WALL,TEXT_FLAG,TEXT_METAL,TEXT_GRASS,TEXT_WATER,TEXT_BABA,TEXT_VOID,TEXT_BEST,TEXT_LAVA, NONE};

extern Sujet convStringToSujet(std::string st);     //Permet la convestion d'un string à ça son attribut Sujet
extern std::string convSujetToString(Sujet sujet);  //Permet la converstion d'un attribut du Sujet à son string
extern std::string displaySujet(Sujet sujet);       //Permet l'affichage console du Sujet correspondant


/**
 * @brief The Matériaux enum
 * Définit un matériaux d'un blockMatériaux, elle pourra être lié à une règle
 */
enum class Matériaux {ROCK,WALL,FLAG,METAL,GRASS,WATER,BABA,VOID,LAVA};

extern Matériaux convStringToMatériaux(std::string st);         //Permet la convestion d'un string à ça son attribut Matériaux
extern std::string convMatériauxToString(Matériaux matériaux);  //Permet la converstion d'un attribut du Matériaux à son string
extern Matériaux convSujetToMatériaux(Sujet sujet);             //Permet de convertir un attribut Sujet à son Matériaux
extern std::string displayMatériaux(Matériaux matériaux);       //Permet l'affichage console du Matériaux correspondant


/**
 * @brief The Aspect enum
 * Définit un aspect qui est relié à une règle et un blockAspect. Elle affectera le jeu
 */
enum class Aspect {STOP, PUSH, WIN, KILL, SINK, YOU, NONE};

extern Aspect convStringToAspect(std::string st);       //Permet la convestion d'un string à ça son attribut Aspect
extern std::string convAspectToString(Aspect aspect);   //Permet la converstion d'un attribut du Aspect à son string
extern std::string displayAspect(Aspect aspect);        //Permet l'affichage console du Aspect correspondant


/**
 * @brief The Connecteur enum
 * Définit un connecteur reliant un sujet à un aspect ou sujet pour créer une règle et est un blockConnecteur
 */
enum class Connecteur {IS};

extern Connecteur convStringToConnecteur(std::string st);           //Permet la convestion d'un string à ça son attribut Connecteur
extern std::string convConnecteurToString(Connecteur connecteur);   //Permet la converstion d'un attribut du Connecteur à son string
extern std::string displayConnecteur(Connecteur connecteur);        //Permet l'affichage console du Connecteur correspondant

#endif // ENUME_H
