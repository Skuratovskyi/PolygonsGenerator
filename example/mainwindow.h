#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../PolygonsGenerator/imagesgenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pBColor1_clicked();

    void on_pBColor2_clicked();

    void on_pBBorder_clicked();

    void setStar();
    void setPolygon();
    void setFilled(int val);
    void setFiguresNum(int val);
    void setVertexNum(int val);
    void setRatio(double val);
    void setAngle(int val);

private:
    Ui::MainWindow *ui;

    void resizeEvent(QResizeEvent* event);

    int vertexNum;
    int figuresNum;
    double ratio;
    QColor color1;
    QColor color2;
    QColor borderColor;
    FigureType type;
    double filledWidth;
    int angle;

    ImagesGenerator *imgGen;

    void resetImage();
};

#endif // MAINWINDOW_H
