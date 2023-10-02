#ifndef OO_H
#define OO_H

/**
 * @brief The Observable class
 * Classe interface de l'observateur
 */
class Observer{
public:

    /**
     * @brief update
     * Préviens l'observateur de rafraichir certaines informations
     */
    virtual void update() = 0;
};

/**
 * @brief The Observable class
 * Classe interface de l'observée
 */
class Observable {
public:

    /**
     * @brief add
     * Rajoute un observateur à la liste d'observateur
     * @param obs l'observateur à rajouter
     */
    virtual void add(Observer* obs) = 0;

    /**
     * @brief notifyObserver
     * Envoie une notification à tous les observateurs de la classe
     */
    virtual void notifyObserver() = 0;
};

#endif // OO_H
