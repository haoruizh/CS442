#include "circle.h"
#include "n_elem.h"
#include "poly_line.h"
#include "wrap_cmath_inclusion.h"


void Circle::draw(void)
{
    // If the circle has not been tessellated, tessellate it.
    if (!tessellationPolyLine)
        tessellate();

    // Now draw it.
    tessellationPolyLine->render();
}


void Circle::tessellate(void)
//
// tessellates the circle
//
{
    //
    // ASSIGNMENT (PA01)
    //
    // Replace the square PolyLine code below with code that uses the
    // formula you derived to set `tessellationPolyLine` to a PolyLine
    // representing a polygon with the minimum number of sides to be
    // within a half-pixel of a circle of the given `radius`.
    //
    // PolyLine() copies `vertexPosition`, so if you use dynamic
    // storage (and you should), remember to clean up after yourself.
    //
    // 19 lines in instructor solution (YMMV)
    //

    const GLfloat PI = 3.1415926f;
    const GLfloat P = 0.00119;
    GLfloat D = P/2;
    // find side numbers for 1 degree with given D and radius
    // find radians based on one side of polygon
    GLfloat radians = acosf((this->radius-D)/this->radius);
    // find degree 
    GLfloat sidesPerDegree = radians/PI*180;
    // find sides number 
    int n = ceil(360/sidesPerDegree);
    Point2 vertexPositions[n];
    // = {
    //     Point2(-0.5, -0.5),
    //     Point2( 0.5, -0.5),
    //     Point2( 0.5,  0.5),
    //     Point2(-0.5,  0.5),
    //     Point2(0.7,0.7),
    //     Point2(0.6,0.6)
    // };
    for (int i =0; i < n; i++)
    {
        vertexPositions[i] = Point2(this->radius*cos(2*PI/n*i)+this->center.g.x, this->radius*sin(2*PI/n*i)+this->center.g.y);
    }
    tessellationPolyLine = new PolyLine(vertexPositions,
                                        N_ELEM(vertexPositions), true);
}
