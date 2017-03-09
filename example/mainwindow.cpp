#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QImage>
#include <QPixmap>


const int PaintingScaleFactor = 20;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect rect(ui->label->contentsRect());
    this->type = FigureType::Star;
    this->vertexNum = ui->sBVertex->value();
    this->figuresNum = ui->sBFigures->value();
    this->ratio = ui->ratio->value();
    this->color1 = QColor(80, 0, 0);
    this->color2 = QColor(255, 0, 0);
    this->borderColor = QColor(127,127,127);
    this->angle = 0;
    ui->pBColor1->setText(color1.name());
    ui->pBColor1->setStyleSheet("background-color: "+color1.name());
    ui->pBColor2->setText(color2.name());
    ui->pBColor2->setStyleSheet("background-color: "+color2.name());
    ui->pBBorder->setText(borderColor.name());
    ui->pBBorder->setStyleSheet("background-color: "+borderColor.name());
    this->filledWidth = ui->hSFilled->value()/100.0;

    QObject::connect(ui->rBStar, &QRadioButton::clicked, this, &MainWindow::setStar);
    QObject::connect(ui->rBPolygon, &QRadioButton::clicked, this, &MainWindow::setPolygon);
    QObject::connect(ui->hSFilled, &QSlider::valueChanged, this, &MainWindow::setFilled);
    QObject::connect(ui->sBFigures, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     this, &MainWindow::setFiguresNum);
    QObject::connect(ui->sBVertex, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     this, &MainWindow::setVertexNum);
    QObject::connect(ui->sBAngle, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     this, &MainWindow::setAngle);
    QObject::connect(ui->ratio, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                     this, &MainWindow::setRatio);
    imgGen = new ImagesGenerator(rect, this->figuresNum);
    this->resetImage();
}

MainWindow::~MainWindow()
{
    delete imgGen;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   QRect rect(ui->label->contentsRect());
   imgGen->ChangeSize(rect);
   this->resetImage();
   // Your code here.
}

void MainWindow::resetImage()
{
    imgGen->SetBorderColor(this->borderColor);
    imgGen->SetPolygonsNumber(this->figuresNum);
    imgGen->SetFigureType(this->type);
    imgGen->SetFilledWidth(this->filledWidth);
    imgGen->SetGradientColor1(this->color1);
    imgGen->SetGradientColor2(this->color2);
    imgGen->SetRatio(this->ratio);
    imgGen->SetVertexNumber(this->vertexNum);
    imgGen->SetAngle(this->angle);
    QImage image = imgGen->GenerateImage();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pBColor1_clicked()
{
    QColor clr = QColorDialog::getColor(color1, this);
    if( !clr.isValid() ){
       return;
    }
    color1 = clr;
    ui->pBColor1->setText(color1.name());
    ui->pBColor1->setStyleSheet("background-color: "+color1.name());
    this->resetImage();
}

void MainWindow::on_pBColor2_clicked()
{
    QColor clr = QColorDialog::getColor(color2, this);
    if( !clr.isValid() ){
       return;
    }
    color2 = clr;
    ui->pBColor2->setText(color2.name());
    ui->pBColor2->setStyleSheet("background-color: "+color2.name());
    this->resetImage();

}

void MainWindow::on_pBBorder_clicked()
{
    QColor clr = QColorDialog::getColor(borderColor, this);
    if( !clr.isValid() ){
       return;
    }
    borderColor = clr;
    ui->pBBorder->setText(borderColor.name());
    ui->pBBorder->setStyleSheet("background-color: "+borderColor.name());
    this->resetImage();
}

void MainWindow::setStar()
{
    this->type = FigureType::Star;
    this->setRatio(this->ratio);
    this->resetImage();
}

void MainWindow::setPolygon()
{
    this->type = FigureType::Polygon;
    this->resetImage();
}

void MainWindow::setFilled(int val)
{
    this->filledWidth = val/100.0;
    this->resetImage();
}

void MainWindow::setFiguresNum(int val)
{
    this->figuresNum = val;
    this->resetImage();
}

void MainWindow::setVertexNum(int val)
{
    this->vertexNum = val;
    this->resetImage();
}

void MainWindow::setRatio(double val)
{
    this->ratio = val;
    this->resetImage();
}

void MainWindow::setAngle(int val)
{
    this->angle = val;
    this->resetImage();
}
