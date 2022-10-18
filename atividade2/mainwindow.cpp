#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectedDraw(int i){
    typeOfDraw = i;
    update();
}

void MainWindow::SelectedColor(int i){
    typeOfColor = i;
    update();
}

void MainWindow::paintEvent(QPaintEvent *){
    int x{ui->inputX->text().toInt()};
    int y{ui->inputY->text().toInt()};
    int escala{ui->inputEscala->text().toInt()};
    if(escala < 1){
        escala = 1;
        //ui->inputEscala->setText("1");
    }
    QPainter painter(this);
    QPointF points[6] = {
       QPointF(x + 10 * escala, y + 20 * escala),
       QPointF(x + 20 * escala, y),
       QPointF(x + 10 * escala, y - 20 * escala),
       QPointF(x - 10 * escala, y - 20 * escala),
       QPointF(x - 20 * escala, y),
       QPointF(x - 10 * escala, y + 20 * escala)
   };

    switch(typeOfColor){
        case 0:
            painter.setBrush(Qt::black);
            painter.setPen(Qt::black);
            break;
        case 1:
            painter.setBrush(Qt::blue);
            painter.setPen(Qt::blue);
            break;
        case 2:
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::yellow);
            break;
        case 3:
            painter.setBrush(Qt::red);
            painter.setPen(Qt::red);
            break;
        case 4:
            painter.setBrush(Qt::green);
            painter.setPen(Qt::green);
            break;
        case 5:
            painter.setBrush(Qt::cyan);
            painter.setPen(Qt::cyan);
            break;
        default:
            painter.setBrush(Qt::white);
            painter.setPen(Qt::white);
            break;
    }

    switch(typeOfDraw){
        case 0:
            break;
        case 1:
            painter.drawEllipse(x, y, 20 * escala, 20 * escala);
            break;
        case 2:
            painter.drawRect(x, y, 50 * escala, 30 * escala);
            break;
        case 3:
            painter.drawEllipse(x, y, 30 * escala,20 * escala);
            break;
        case 4:
            painter.drawRect(x, y, 30 * escala, 30 * escala);
            break;
        case 5:
            painter.drawArc(x, y, 80 * escala, 60 * escala, 30*12, 120*12);
            break;
        case 6:
            painter.drawPolygon(points, 6);
            break;
        default:
            break;
    }
}
