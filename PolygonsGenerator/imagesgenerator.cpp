#include "imagesgenerator.h"
#include "polygongenerator.h"

/*!
 * \brief ImagesGenerator::ImagesGenerator constructor
 * \param rect
 * \param eNum
 */
ImagesGenerator::ImagesGenerator(const QRect &rect, const int eNum)
    : polygonsNum(eNum), widgetWidth(rect.width()), widgetHeight(rect.height())
{
    // Format_ARGB32_Premultiplied has max performance and alpha channel
    // do not change format
    this->polygons = new QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    this->polygonsContour = new QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);

    this->createGradient();

    // set default parameters
    this->vertexNum = 5;
    this->color1 = QColor(80, 0, 0);
    this->color2 = QColor(255, 0, 0);
    this->borderColor = QColor(127,127,127);
    this->filledWidth = 0.8;
    this->figureType = FigureType::Star;
    this->angle = 0;

    // recalculate size
    this->recalcSize();

    // set initial ratio
    this->SetRatio(1.6);
}

ImagesGenerator::~ImagesGenerator()
{
    delete this->polygons;
    delete this->polygonsContour;
}

void ImagesGenerator::recalcSize()
{
    if (this->widgetHeight * this->polygonsNum > this->widgetWidth){
        this->width = this->widgetWidth;
        this->height = this->widgetWidth/this->polygonsNum;
        this->verticalOffset = (this->widgetHeight - this->height)/2;
    }
    else {
        this->verticalOffset = 0;
        this->height = this->widgetHeight;
        this->width = this->height*this->polygonsNum;
    }
}

/*!
 * \brief ImagesGenerator::GetImage is main entry point in function.
 * \return QImage to draw in the widget
 */
QImage ImagesGenerator::GenerateImage()
{
    QImage result(this->widgetWidth, this->widgetHeight, QImage::Format_ARGB32_Premultiplied);

    this->generatePolygon();
    this->fillImage(this->polygons, Qt::red);
    this->fillImage(this->polygonsContour, Qt::transparent);

    // render composition image from three layers
    painter.begin(&result);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(*this->gradient);
    painter.drawRect(0, 0,
                     this->widgetWidth, this->widgetHeight);

    painter.setBrush(palette.background());
    painter.drawRect(width*this->filledWidth, 0,
                     this->widgetWidth, this->widgetHeight);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    painter.drawImage(0, 0, *polygons);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, *polygonsContour);
    painter.end();

    return result;
}

void ImagesGenerator::ChangeSize(const QRect &rect)
{
    this->widgetWidth = rect.width();
    this->widgetHeight = rect.height();
    this->recalcSize();

    // recreate polygons and contour images with new sizes
    delete this->polygons;
    delete this->polygonsContour;
    delete this->gradient;

    this->polygons = new QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    this->polygonsContour = new QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    this->createGradient();
}

void ImagesGenerator::SetVertexNumber(int vnum)
{
    this->vertexNum = vnum;
}

void ImagesGenerator::SetPolygonsNumber(int fnum)
{
    this->polygonsNum = fnum;
    recalcSize();
}

void ImagesGenerator::SetGradientColor1(QColor color)
{
    this->color1 = color;
}

void ImagesGenerator::SetGradientColor2(QColor color)
{
    this->color2 = color;
}

void ImagesGenerator::SetBorderColor(QColor color)
{
    this->borderColor = color;
}

void ImagesGenerator::SetFilledWidth(double width)
{
    this->filledWidth = width;
}

void ImagesGenerator::SetRatio(double ratio)
{
    this->radiusRatio = ratio;
    this->outerRadius = this->height/2;
    switch(this->figureType){
        case FigureType::Star:
            this->innerRadius = this->outerRadius/ratio;
            break;
        case FigureType::Polygon:
            this->innerRadius = 0;
            break;
    }
}

void ImagesGenerator::SetFigureType(FigureType type)
{
    this->figureType = type;
}

void ImagesGenerator::SetAngle(int angle)
{
    this->angle = angle;
}

void ImagesGenerator::fillImage(QImage *img, Qt::GlobalColor color)
{
    img->fill(QColor(0, 0, 0, 0));
    painter.begin(img);           // paint in picture
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(this->borderColor));
    QColor c(color);
    painter.setBrush(c);
    for (int i = 0; i < polygonsNum; ++i){
        painter.drawPolygon(this->polygon, Qt::WindingFill);
        painter.translate(this->height, 0);
    }
    painter.end();
}

void ImagesGenerator::generatePolygon()
{
    this->polygon = PolygonGenerator::Generate(this->vertexNum,
                                               this->outerRadius,
                                               this->innerRadius,
                                               this->angle,
                                               this->verticalOffset);
}

void ImagesGenerator::createGradient()
{
    int y1 = (this->widgetHeight - this->height)/2;
    int y2 = y1 + this->height;
    this->gradient = new QLinearGradient(0, y1, 0, y2);
    this->gradient->setColorAt(0, this->color1);
    this->gradient->setColorAt(1, this->color2);
}

