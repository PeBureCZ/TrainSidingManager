#include "buttonfunctions.h"


void setButtonText(QString text, QPushButton* button)
{
    button->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
    button->setText(text);
}

void freeButton(QPushButton* button)
{
    button->setText("");
    button->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
}
