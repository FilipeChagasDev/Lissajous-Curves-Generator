#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.14159265359

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->pushButton, &QPushButton::clicked, this, &MainWindow::generate);
    connect(this->ui->scale_spinbox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeScale);
    this->ui->graphicsView->setScene(&scene);
    this->current_scale = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate()
{
    double x_center = this->ui->graphicsView->width()/2;
    double y_center = this->ui->graphicsView->height()/2;

    double x_freq = this->ui->x_freq_spinbox->value();
    double y_freq = this->ui->y_freq_spinbox->value();

    double x_amp = this->ui->x_amp_spinbox->value();
    double y_amp = this->ui->y_amp_spinbox->value();

    double x_phase = this->ui->x_phase_spinbox->value();

    scene.clear();

    double prev_x_t = x_center + (x_amp * sin(0));
    double prev_y_t = y_center + (y_amp * cos(0));
    for(int i = 0; i <= 1000; i++)
    {
        double t = (2*PI*i)/1000;
        double x_t = x_center + (x_amp * sin(t*x_freq+x_phase));
        double y_t = y_center +  (y_amp * cos(t*y_freq));
        scene.addLine(QLine(prev_x_t, prev_y_t, x_t, y_t));
        prev_x_t = x_t;
        prev_y_t = y_t;
    }
}

void MainWindow::changeScale()
{
    this->ui->graphicsView->scale(1/current_scale, 1/current_scale);
    double new_scale = this->ui->scale_spinbox->value();
    this->ui->graphicsView->scale(new_scale, new_scale);
    this->current_scale = new_scale;
}
