#include "calculator.h"
#include "ui_calculator.h"

double dTrackCurrentValue = 0.0;
bool bDivideTrigger = false;
bool bMultiplyTrigger = false;
bool bAddTrigger = false;
bool bSubTrigger = false;

Calculator::Calculator(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(dTrackCurrentValue)); //casts double to QString and displays it
    QPushButton *numButtons[10]; //holds references to push buttons
    for(int i = 0; i < 10; ++i)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName); //searches for a specific widget by providing its name
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed())); //calls NumPressed when any of the number buttons is pressed
    }
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    //returns pointer to button that was pressed via sender
    QPushButton *button = (QPushButton *)sender();
    //store button number so we can use it
    QString buttonValue = button->text();
    //sends stored value to display
    QString displayValue = ui->Display->text();
    //dangerous cast, necessary for this purpose

    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0)
        ui->Display->setText(buttonValue);
    else
    {
        QString newValue = displayValue + buttonValue;
        double dNewValue = newValue.toDouble();
        //changes the number of digits displayed before scientific notation is used
        ui->Display->setText(QString::number(dNewValue, 'g', 16));
    }
}
