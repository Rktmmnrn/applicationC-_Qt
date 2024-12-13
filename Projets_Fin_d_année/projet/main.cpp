#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    // Charge le logo avant l'affichage de l'app
//    QPixmap logo(":/images/Images/Logo_ENI.jpg");
//    // Crée le splash screen
//    QSplashScreen splash(logo);
//    splash.show();
//    // Temps d'affichage du splash screen (en millisecondes)
//    QTimer::singleShot(3000, &splash, &QSplashScreen::close);
//    // Charge la fenêtre principale après le splash screen
//    MainWindow w;
//    QTimer::singleShot(3000, &w, &MainWindow::show);
    MainWindow w;

    w.show();
    return a.exec();
}
