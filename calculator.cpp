#include "calculator.h"
#include "ui_calculator.h"

double dTrackCurrentValue = 0.0;
double dMemoryValue = 0.0;

bool bDivideTrigger = false;
bool bMultiplyTrigger = false;
bool bAddTrigger = false;
bool bSubTrigger = false;

bool bMemGetTrigger = false;
bool bMemAddTrigger = false;
bool bMemClearTrigger = false;

bool bClearTrigger = false;

Calculator::Calculator(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    //casts double to QString and displays it
    ui->Display->setText(QString::number(dTrackCurrentValue));
    QPushButton *numButtons[10]; //holds references to push buttons
    for(int i = 0; i < 10; ++i)
    {
        QString buttonName = "Button" + QString::number(i);
        //searches for a specific widget by providing its name
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        //calls NumPressed when any of the number buttons is pressed
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    //ties the button signals with the slots
    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonSubtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonDivide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));

    connect(ui->ButtonMemGet, SIGNAL(released()), this, SLOT(MemoryButtonPressed()));
    connect(ui->ButtonMemAdd, SIGNAL(released()), this, SLOT(MemoryButtonPressed()));
    connect(ui->ButtonMemClear, SIGNAL(released()), this, SLOT(MemoryButtonPressed()));
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

void Calculator::MathButtonPressed()
{
    QString displayValue = ui->Display->text();

    //store value
    dTrackCurrentValue = displayValue.toDouble();

    //check sender to find out the button that was pressed
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    //check which of the buttons was actually pressed
    if(QString::compare(buttonValue, "÷", Qt::CaseInsensitive) == 0)
        bDivideTrigger = true;
    else if(QString::compare(buttonValue, "×", Qt::CaseInsensitive) == 0)
        bMultiplyTrigger = true;
    else if(QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0)
        bAddTrigger = true;
    else if(QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0)
        bSubTrigger = true;

    //clear display, handles if math button is pressed
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double dDisplayValue = displayValue.toDouble();

    if(bDivideTrigger || bMultiplyTrigger || bAddTrigger || bSubTrigger)
    {
        if(bAddTrigger)
            solution = dTrackCurrentValue + dDisplayValue;
        else if(bSubTrigger)
            solution = dTrackCurrentValue - dDisplayValue;
        else if(bMultiplyTrigger)
            solution = dTrackCurrentValue * dDisplayValue;
        else if(bDivideTrigger)
            solution = dTrackCurrentValue / dDisplayValue;
    }

    bAddTrigger = false;
    bSubTrigger = false;
    bMultiplyTrigger = false;
    bDivideTrigger = false;

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign()
{
    QString displayValue = ui->Display->text();

    //regex to verify that what's being displayed is actually a number
    QRegExp checkRegex("[-+]?[0-9.]*");

    if(checkRegex.exactMatch(displayValue))
    {
        double dDisplayValue = displayValue.toDouble();
        double dDisplayValueSign = -1 * dDisplayValue;
        ui->Display->setText((QString::number(dDisplayValueSign)));
    }

}

void Calculator::ClearButtonPressed()
{
    dTrackCurrentValue = 0.0;

    ui->Display->setText((QString::number(dTrackCurrentValue)));
}

void Calculator::MemoryButtonPressed()
{
    QString displayValue = ui->Display->text();

    //check sender to find out the button that was pressed
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    //check which of the buttons was actually pressed
    if(QString::compare(buttonValue, "M+", Qt::CaseInsensitive) == 0)
        bMemAddTrigger = true;
    else if(QString::compare(buttonValue, "M", Qt::CaseInsensitive) == 0)
        bMemGetTrigger = true;
    else if((QString::compare(buttonValue, "M-", Qt::CaseInsensitive) == 0))
        bMemClearTrigger = true;

    if(bMemAddTrigger || bMemGetTrigger || bMemClearTrigger)
    {
        if(bMemAddTrigger)
        dMemoryValue = displayValue.toDouble();
        else if(bMemGetTrigger)
        {
            dTrackCurrentValue = dMemoryValue;
            ui->Display->setText((QString::number(dTrackCurrentValue)));
        }
        else if(bMemClearTrigger)
            dMemoryValue = 0.0;
    }

    bMemAddTrigger = false;
    bMemGetTrigger = false;
    bMemClearTrigger = false;
}





















