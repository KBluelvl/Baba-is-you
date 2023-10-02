#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui {
class helpWidget;
}

/**
 * @brief The helpWidget class
 * Classe gérant la fenêtre help
 */
class helpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit helpWidget(QWidget *parent = nullptr);
    ~helpWidget();

signals:
    void backClicked();

private slots:
    /**
     * @brief on_backButton_clicked
     * Envoie un signal quand on clique sur le bouton back
     */
    void on_backButton_clicked();

private:
    Ui::helpWidget *ui;
};

#endif // HELPWIDGET_H
