#include "polygongenerator.h"

PolygonGenerator::PolygonGenerator()
{

}

QPolygonF PolygonGenerator::Generate(short vertexNum,
                                     int outerRadius,
                                     int innerRadius,
                                     int angle,
                                     int verticalOffset)
{
    QPolygonF polygon;
    double innerAngle = 360.0/vertexNum;
    double innerAngleHalf = innerAngle/2;

    for(int i=0; i < vertexNum; ++i){
        polygon << QPointF(outerRadius + outerRadius * std::sin(DegreesToRadians(angle + innerAngle * i)),
                           verticalOffset + outerRadius - outerRadius * std::cos(DegreesToRadians(angle + innerAngle*i)));
        if (innerRadius > 0)
            polygon << QPointF(outerRadius + innerRadius * std::sin(DegreesToRadians(angle + innerAngle*i+innerAngleHalf)),
                            verticalOffset + outerRadius - innerRadius * std::cos(DegreesToRadians(angle + innerAngle*i + innerAngleHalf)));
    }
    return polygon;
}

double DegreesToRadians(double degree)
{
    return 3.14159265359*(degree)/180;
}
