#ifndef POLYGONGENERATOR_H
#define POLYGONGENERATOR_H

#include <QPolygonF>

class PolygonGenerator
{
public:
    PolygonGenerator();

    static QPolygonF Generate(short vertexNum,
                              int outerRadius,
                              int innerRadius = 0,
                              int angle = 0,
                              int verticalOffset = 0);

};

double DegreesToRadians(double degrees);

#endif // POLYGONGENERATOR_H
