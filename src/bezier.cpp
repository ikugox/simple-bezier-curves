#include <vector>

#include "../include/raylib.h"

Vector2 lerp(const Vector2& a, const Vector2& b, float t) {
    return Vector2{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

Vector2 bezierCurve(const std::vector<Vector2>& points, float t) {
    // base case
    if (points.size() == 1) {
        return points[0];
    }
    // lerp between pairs of points
    std::vector<Vector2> nextPoints;
    for (int i = 0; i < points.size() - 1; ++i) {
        nextPoints.push_back(lerp(points[i], points[i + 1], t));
    }
    return bezierCurve(nextPoints, t);
}
