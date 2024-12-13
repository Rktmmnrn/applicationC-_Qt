#include "stylesheet.h"

stylesheet::stylesheet()
{
    one = "QPushButton {"
          "background-color: black;"
          "color: white;"
          "font-weight: bold;"
          "}"
          "QPushButton:hover {"
          "color: Black;"
          "background-color: white;"
          "}";
    labelModif = "QLabel {"
                 "font-weight: bold;"
                 "align-items: center;"
                 "}";
    BttnEntretient0 = "QPushButton {"
                      "background-color: #f4b6b6;"
                      "font-weight: bold;"
                      "}";
    BttnEntretient1 = "QPushButton {"
                      "background-color: #eb8585;"
                      "font-weight: bold;"
                      "}";
    BttnEntretient2 = "QPushButton {"
                      "background-color: red;"
                      "font-weight: bold;"
                      "}";
    Bttnnone = "QPushButton {"
               "background-color: white;"
               "color: gray;"
               "}";
    zoneRecherche = "QLineEdit {"
                    "border-radius: 8px;"
                    "border: 1px solid gray;"
                    "}";
    BttnGauche = "QPushButton {"
                 "border-radius: 5px;"
                 "border: 1px solid gray;"
                 ""
                 "}"
                 "QPushButton:hover {"
                 "background-color: gray;"
                 ""
                 "}";
    changeUtil = "QPushButton {"
                 "border-radius: 10px;"
                 "border: 1px solid black;"
                 "}"
                 "QPushButton:hover {"
                 "background-color: green;"
                 "}";
    quitUtil = "QPushButton:hover {"
               "background: red;"
               "}";
    quitU = "QPushButton {"
            "border-radius: 10px;"
            "border: 2px solid red;"
            "}";
}
