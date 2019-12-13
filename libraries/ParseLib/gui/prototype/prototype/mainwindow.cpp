#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QGraphicsScene * scene = new QGraphicsScene(this);
    QGraphicsView view(scene);
    QPalette palette = scene->palette();


    scene->setPalette(palette);
    ui->graphicsView->setScene(scene);





    QGraphicsRectItem * square = scene->addRect(QRectF(QPointF(0,0),QPointF(100,100)));
    QGraphicsTextItem * text= scene->addText("ExampleText", QFont("Arial", 20));

    text->setDefaultTextColor(Qt::black);

    square->setFlag(QGraphicsItem::ItemIsMovable);

    view.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

