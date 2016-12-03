#ifndef HEAT_EQUATION_H
#define HEAT_EQUATION_H

#include <QWidget>

namespace Ui {
class heat_equation;
}

class heat_equation : public QWidget
{
    Q_OBJECT

public:
    explicit heat_equation(QWidget *parent = 0);
    ~heat_equation();

private slots:
    void on_goButton_clicked();

private:
    Ui::heat_equation *ui;
};

#endif // HEAT_EQUATION_H
