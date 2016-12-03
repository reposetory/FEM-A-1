#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "heat_equation.h"
#include "ui_heat_equation.h"
#include <QTextStream>


heat_equation::heat_equation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::heat_equation)
{
    ui->setupUi(this);
}

heat_equation::~heat_equation()
{
    delete ui;
}

void heat_equation::on_goButton_clicked()
{
    QString dimension = ui->dimension->text();
    QTextStream out(stdout);
    out<<dimension<<endl;
    QString num_scheme = ui->num_scheme->text();
    out<<num_scheme<<endl;
    QString time_step = ui->time_step->text();
    out<<time_step<<endl;
    QString space_step = ui->space_step->text();
    out<<space_step<<endl;
    QString total_time = ui->total_time->text();
    out<<total_time<<endl;
    QString output_file_name = ui->output_file_name->text();
    out<<output_file_name<<endl;
   //save a txt file containing the input parameters into lucal folder 
    QString filename="./parameters.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << dimension <<' '<<num_scheme<<' '<<time_step<<' '<<space_step<<' '<<total_time<<' '<<output_file_name<< endl;
        out<<output_file_name<<endl;
    }


}
