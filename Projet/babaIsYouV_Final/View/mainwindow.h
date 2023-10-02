#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Model/Model.h"
#include "View/helpwidget.h"
#include "View/startmenu.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Classe représentant la fenêtre de l'application
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
    Model& _facade;
    QStackedWidget *_stackedWidget;
    QGridLayout *_gridLayout;
    StartMenu *_startMenu;
    helpWidget *_helpWidget;
    Board oldVec;

    QPixmap pixVoid = QPixmap(":/resources/images/void.png");
    std::map<std::string, QMovie*> images;

public:
    /**
     * @brief MainWindow
     * Construit la fenêtre en créant une pile contenant tout les widgets
     * @param facade le model
     * @param parent un objet QWidget null par défaut
     */
    MainWindow(Model& facade,QWidget *parent = nullptr);

    /**
     * @brief MainWindow
     * Contructeur par recopie
     * @param other une MainWindow donnée
     */
    MainWindow(const MainWindow& other);

    /**
     * @brief setupBoard
     * Initialise le jeu dans le _gridLayout
     * @param verif true = on fait la vérification de l'ancien board, false, sinon
     */
    void setupBoard(bool verif = true);

    /**
     * @brief keyPressEvent
     * Récupère les input de l'utilisateurs pour lancer des actions
     * @param event touche pressé par l'utilisateur
     */
    void keyPressEvent(QKeyEvent *event);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    /**
     * @brief initGridLayout
     * Initialise le _gridLayout
     * @return un pointeur de QWidget contenant le _gridLayout
     */
    QWidget* initGridLayout();
    /**
     * @brief initStartMenu
     * Initialise le _startMenu
     */
    void initStartMenu();
    /**
     * @brief initHelpWidget
     * Initialise le _helpWidget
     */
    void initHelpWidget();
    /**
     * @brief initBoard
     *
     */
    void initBoard(int x,int y);
    /**
     * @brief setStart
     * Mets la fenêtre de début
     */
    void setStart();
    /**
     * @brief setGame
     * Charge le premier niveau du jeu
     */
    void setGame();
    /**
     * @brief setSave
     * Charge un sauvegarde du jeu (si il y'en a une)
     */
    void setSave();
    /**
     * @brief setHelp
     * Mets la fenêtre d'aide
     */
    void setHelp();
    /**
     * @brief startGame
     * Mets la fenêtre de jeu
     */
    void startGame();

};
#endif // MAINWINDOW_H
