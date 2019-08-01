#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui
{
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT //base class for objects, handles events as well

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots: //slots are excuted when signal is submitted
    void NumPressed();
    //void MathButtonPressed();
    //void EqualButton();
    //void ChangeNumberSign();
};

#endif // CALCULATOR_H
