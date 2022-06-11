#include "Polygon.h"
#include "ColorT.h"
#include "SDL.h"
#include "SDL_opengl.h"

std::vector<Vector2> Polygon::getDrawablePoints(const Vector2& windowDimensions, const Transform& transform) {
    std::vector<Vector2> ret;
    for(auto p : points) {
        auto scaled = Vector2(transform.scale.x*p.x, transform.scale.y*p.y);
        auto rotated = scaled.Rotate(transform.rotation.getAngleDegree());
        auto displaced = rotated + transform.position;
        displaced.x = (displaced.x/windowDimensions.x)*2 - 1;
        displaced.y = (displaced.y/windowDimensions.y)*2 - 1;
        ret.push_back(displaced);
    }
    return ret;
}

void Polygon::Draw(const Vector2& windowSize, const Transform& transform, const Color32& color) {
    auto drawablePoints = getDrawablePoints(windowSize, transform);

    uint8_t c[] = {color.r, color.g, color.b, 255};
    glColor4ubv( c );
    glBegin(GL_LINE_LOOP);
    {
        for (auto & drawablePoint : drawablePoints)
            glVertex2f(drawablePoint.x, drawablePoint.y);
    }
    glEnd();

//    SDL_SetRenderDrawColor(renderer,
//                           color.r,
//                           color.g,
//                           color.b,
//                           SDL_ALPHA_OPAQUE);
//    auto drawablePoints = getDrawablePoints(transform);
//    for(int i=0; i<drawablePoints.size(); i++) {
//        int other = i + 1;
//        if (other == drawablePoints.size())
//            other = 0;
//        SDL_RenderDrawLine(renderer,
//                           (int) drawablePoints[i].x,
//                           (int) drawablePoints[i].y,
//                           (int) drawablePoints[other].x,
//                           (int) drawablePoints[other].y);
//    }
}

void Polygon::DrawLine(const Vector2& windowSize, const Vector2 &v1, const Vector2 &v2, const Color32& color) {
    uint8_t c[] = {color.r, color.g, color.b, 255};
    glColor4ubv( c );

    glBegin(GL_LINES);
    {
        glVertex2f((v1.x/windowSize.x)*2-1, (v1.y/windowSize.y)*2-1);
        glVertex2f((v2.x/windowSize.x)*2-1, (v2.y/windowSize.y)*2-1);
    }
    glEnd();

//    SDL_SetRenderDrawColor(renderer,
//                           color.r,
//                           color.g,
//                           color.b,
//                           SDL_ALPHA_OPAQUE);
//    SDL_RenderDrawLine(renderer,(int) v1.x,(int) v1.y,(int) v2.x,(int) v2.y);
}

void Polygon::Draw(const Vector2& windowSize, const Vector2 &position, const Vector2 &scale, const Vector2 &rotation,
                   const Color32 &color) {
    Transform transform = {position,scale,rotation};
//    SDL_SetRenderDrawColor(renderer,
//                           color.r,
//                           color.g,
//                           color.b,
//                           SDL_ALPHA_OPAQUE);
    auto drawablePoints = getDrawablePoints(windowSize, transform);
//    for(int i=0; i<drawablePoints.size(); i++) {
//        int other = i + 1;
//        if (other == drawablePoints.size())
//            other = 0;
//        SDL_RenderDrawLine(renderer,
//                           (int) drawablePoints[i].x,
//                           (int) drawablePoints[i].y,
//                           (int) drawablePoints[other].x,
//                           (int) drawablePoints[other].y);
//    }
    uint8_t c[] = {color.r, color.g, color.b, 255};
    glColor4ubv( c );
    glBegin(GL_LINE_LOOP);
    {
        for (auto & drawablePoint : drawablePoints)
            glVertex2f(drawablePoint.x, drawablePoint.y);
    }
    glEnd();
}

Circle::Circle(int sample) {
    for (int i = 0; i < sample; i++) {
        Vector2 point = Vector2::up().Rotate(360.f * (float) i / (float) sample);
        points.push_back(point);
    }
}

Square::Square() {
    points.push_back(Vector2::up().Rotate(45));
    points.push_back(Vector2::up().Rotate(135));
    points.push_back(Vector2::up().Rotate(225));
    points.push_back(Vector2::up().Rotate(315));
}