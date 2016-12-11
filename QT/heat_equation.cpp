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
    QTextStream out(stdout);
    QString dimension = ui->comboBox_dim->currentText();
    out<<"dimension out: "<<dimension<<endl;

    QString num_scheme = ui->comboBox_num_scheme->currentText();
    out<<"numerical scheme: "<<num_scheme<<endl;
    QString time_step = ui->time_step->text();
    out<<time_step<<endl;
    QString space_step = ui->space_step->text();
    out<<space_step<<endl;
    //QString space_step_y = ui->space_step_y->text();
    //out<<space_step_y<<endl;
    QString total_time = ui->total_time->text();
    out<<total_time<<endl;
    QString output_file_name = ui->output_file_name->text();
    out<<output_file_name<<endl;

    QString filename="./parameters.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << dimension<<' '<<num_scheme<<' '<<time_step<<' '<<space_step<<' '<<total_time<<' '<<output_file_name<<' '<< endl;
        //stream << dimension <<' '<<num_scheme<<' '<<time_step<<' '<<space_step_x<<' '<<space_step_y<<' '<<total_time<<' '<<output_file_name<< endl;
        //out<<output_file_name<<endl;
    }


    QString num_threads = ui->num_threads->text();
    QString filename1="./num_threads.txt";
    QFile file1( filename1 );
    if ( file1.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file1);
        stream <<num_threads<<' ';
        //stream << dimension<<' '<<num_scheme<<' '<<time_step<<' '<<space_step<<' '<<total_time<<' '<<output_file_name<<' '<< endl;
        //stream << dimension <<' '<<num_scheme<<' '<<time_step<<' '<<space_step_x<<' '<<space_step_y<<' '<<total_time<<' '<<output_file_name<< endl;
        //out<<output_file_name<<endl;
    }

}

void heat_equation::on_comboBox_dim_activated(const QString &arg1)
{
    //QTextStream out(stdout);
    //out<<"dimension: "<<arg1<<endl;
    ui->comboBox_num_scheme->clear();
    if(arg1 =="3"){
        ui->comboBox_num_scheme->addItem("Euler");
        ui->time_step->setText("0.1");
        ui->space_step->setText("0.5");
        ui->total_time->setText("1");
        ui->num_threads->setText("1");
        ui->output_file_name->setText("file_out");
    }
    else if(arg1 == "1" || arg1 == "2"){
        ui->comboBox_num_scheme->addItem("Euler");
        ui->comboBox_num_scheme->addItem("Backward-Euler");
        ui->comboBox_num_scheme->addItem("Crank-Nicolson");
        ui->comboBox_num_scheme->addItem("DuFort-Frankel");
        ui->comboBox_num_scheme->addItem("Finite-Element");
        //ui->comboBox_num_scheme->addItem("Euler");
        ui->time_step->setText("0.1");
        ui->space_step->setText("0.4");
        ui->total_time->setText("1");
        ui->num_threads->setText("1");
        ui->output_file_name->setText("file_out");
    }

}

