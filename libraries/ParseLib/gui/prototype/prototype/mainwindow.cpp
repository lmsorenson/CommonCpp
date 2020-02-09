#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include "myentity.h"
#include "modelscene.h"

struct Entity
{
    QGraphicsRectItem * square;
    QGraphicsTextItem * text;
    QGraphicsLineItem * line;
    QGraphicsItemGroup *group;
    QPointF point;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "BEGIN PROGRAM";

    QGraphicsScene * scene = new QGraphicsScene(this);

    QPalette palette = scene->palette();


    scene->setPalette(palette);
    ui->graphicsView->setScene(scene);


    Entity record, cell;
    MyEntity * ent = new MyEntity("Record", QPointF(0,0));
    MyEntity * ent2 = new MyEntity("Cell", QPointF(300,0));
    MyEntity * ent3 = new MyEntity("Field", QPointF(600,0));

    QGraphicsLineItem *line = scene->addLine(QLineF(125, 62.5, 300, 62.5));
    QGraphicsLineItem *line2 = scene->addLine(QLineF(425, 62.5, 600, 62.5));


    ent->AddLine(line, true);//origin of the line.
    ent2->AddLine(line, false);

    ent2->AddLine(line2, true);//origin of the line.
    ent3->AddLine(line2, false);

    scene->addItem(ent);
    scene->addItem(ent2);
    scene->addItem(ent3);


}

MainWindow::~MainWindow()
{
    delete ui;
}

