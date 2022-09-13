#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Vector2.h"
#include "Transform.h"
#include "Vector3.h"
#include "ColorT.h"

// naive approach to represent a polygon
struct Polygon {
public:
    Polygon() = default;
    explicit Polygon(std::vector<Vector2> points):points(std::move(points)){};
    std::vector<Vector2> points;

    // polygon points to be used in the draw functions
    std::vector<Vector2> getDrawablePoints(const Vector2& windowSize, const Transform& transform);

    void Draw(const Vector2& windowSize, const Transform& transform, const Color32& color);
    void Draw(const Vector2& windowSize, const Vector2& position, const Vector2& scale, const Vector2& rotation, const Color32& color);

    static void DrawLine(const Vector2& windowSize, const Vector2& v1, const Vector2& v2, const Color32& color);
};

struct Circle: Polygon{
    explicit Circle(int sample);
};

struct Square: Polygon{
    explicit Square();
};

#endif //POLYGON_H
