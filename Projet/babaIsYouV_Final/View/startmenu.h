#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

namespace Ui {
class StartMenu;
}

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

signals:
    void playClicked();
    void exitClicked();
    void saveClicked();
    void helpClicked();

private slots:
    /**
     * @brief on_playButton_clicked
     * Envoie un signal quand on clique sur le bouton play
     */
    void on_playButton_clicked();
    /**
     * @brief on_exitButton_clicked
     * Envoie un signal quand on clique sur le bouton exit
     */
    void on_exitButton_clicked();
    /**
     * @brief on_saveButton_clicked
     * Envoie un signal quand on clique sur le bouton save
     */
    void on_saveButton_clicked();
    /**
     * @brief on_helpButton_clicked
     * Envoie un signal quand on clique sur le bouton p
     */
    void on_helpButton_clicked();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
