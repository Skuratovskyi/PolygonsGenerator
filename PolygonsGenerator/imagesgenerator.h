#ifndef IMAGESGENERATOR_H
#define IMAGESGENERATOR_H

#include <QImage>
#include <QPainter>
#include <QPalette>
#include <QLinearGradient>

enum class FigureType { Star, Polygon };

class ImagesGenerator : QObject
{
    Q_OBJECT

public:
    /*!
     * \brief ImagesGenerator
     * \param rect is a destination widget rectangle (to get widget size)
     * \param elementsNum is fiqures quantity
     */
    ImagesGenerator(const QRect &rect, const int polygonsNum = 5);

    ~ImagesGenerator();

    QImage GenerateImage();

    void ChangeSize(const QRect &rect);

public slots:

    void SetVertexNumber(int vnum);

    void SetPolygonsNumber(int fnum);

    void SetGradientColor1(QColor color);

    void SetGradientColor2(QColor color);

    void SetBorderColor(QColor color);

    /*!
     * \brief SetFilledWidth
     * \param width in range [0..1]
     */
    void SetFilledWidth(double width);

    /*!
     * \brief SetRatio sets ratio between outer and inner radiuses of star type polygon
     * \param ratio outer/inner, must be > 1, best results are if  1.5 < ratio < 4
     */
    void SetRatio(double ratio);

    void SetFigureType(FigureType type);

    void SetAngle(int angle);

private:
    QPainter painter;
    QPalette palette;

    QImage *polygons;
    QImage *polygonsContour;

    QColor color1;
    QColor color2;
    QColor borderColor;

    QLinearGradient *gradient;

    QPolygonF polygon;
    int vertexNum;
    int polygonsNum;
    double filledWidth;
    double radiusRatio;
    int outerRadius;
    int innerRadius;
    FigureType figureType;
    int angle;

    /*!
     * \brief widgetWidth - width of widget
     */
    int widgetWidth;

    /*!
     * \brief widgetHeight - height of widget
     */
    int widgetHeight;

    /*!
     * \brief width - real wisth of polygon set
     * \details width = polygonWidth * polygonsNum
     */
    int width;

    /*!
     * \brief height - real height of image
     * \details height = polygonWidth
     */
    int height;
    int verticalOffset;

    /*!
     * \brief fillImage - fill QImage by generated data
     * \param img - QImage to fill
     * \param color - global color for filling
     */
    void fillImage(QImage *img, Qt::GlobalColor color);

    void generatePolygon();

    void createGradient();

    /*!
     * \brief ImagesGenerator::recalcSize sets size of polygons set.
     *  Scale if needed. Ideal case is width/height = 5
     */
    void recalcSize();
};

#endif // IMAGESGENERATOR_H
