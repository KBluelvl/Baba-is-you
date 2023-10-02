#include "Controller/Controller.h"
#include "View/ViewConsole.h"
#include "View/ViewGraphique.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "Windows.h"


int main(int argc, char *argv[]) {

    if(true){
        QApplication a(argc, argv);
        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale : uiLanguages) {
            const QString baseName = "BabaIsYouV_Final" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
        Model model {};
        MainWindow w(model);
        ViewGraphique view{model,w};
        return a.exec();
    } else {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);

        Model model {};
        ViewConsole view{model};
        Controller controller{model, view};
        controller.start();
        return 0;
    }
}
