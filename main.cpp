#include <vector>

#include "raylib.h"
/* --------------------------- LEFT CLICK TO MOVE --------------------------- */
/* ---------------------- RIGHT CLICK TO CREATE/DELETE ---------------------- */
constexpr float BALL_SIZE = 20;
constexpr float DOT_FREQUENCY = 0.002;
constexpr float DOT_THICKNESS = 3;
constexpr Color DOT_COLOR = DARKGREEN;
constexpr int SCREEN_SIZE = 800;

void handleExistingPoint(std::vector<Vector2>& points, int pSize);
void handleNewPoint(std::vector<Vector2>& points, const Vector2& mousePos,
                    int pSize);

void mouseMovement(std::vector<Vector2>& points);

Vector2 lerp(const Vector2& a, const Vector2& b, float t) {
    return Vector2{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

// Recursive function for Bezier interpolation with any number of points
Vector2 bezierCurve(const std::vector<Vector2>& points, float t) {
    // Base case: if there's only one point, return it
    if (points.size() == 1) {
        return points[0];
    }

    // Interpolate between each consecutive pair of points
    std::vector<Vector2> nextPoints;
    for (int i = 0; i < points.size() - 1; ++i) {
        nextPoints.push_back(lerp(points[i], points[i + 1], t));
    }

    // Recurse with the reduced set of points
    return bezierCurve(nextPoints, t);
}

void handleMouseClick(std::vector<Vector2>& points, const Vector2& mousePos,
                      bool exists) {
    const int pSize = points.size();

    if (exists) {
        handleExistingPoint(points, pSize);
    } else {
        handleNewPoint(points, mousePos, pSize);
    }
}

void handleExistingPoint(std::vector<Vector2>& points, int pSize) {
    if (pSize >= 2) {
        points[pSize - 1] = points[pSize - 2];
    }
    points.pop_back();
}

void handleNewPoint(std::vector<Vector2>& points, const Vector2& mousePos,
                    int pSize) {
    if (pSize == 0) {
        points.push_back(mousePos);
    } else {
        points.push_back(points[pSize - 1]);
        points[pSize - 1] =
            mousePos;  // Update the last point to the new mouse position
    }
}

int main(void) {
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "WINDOW");
    SetTargetFPS(60);

    std::vector<Vector2> points;

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mousePos = GetMousePosition();
            bool exists = false;
            const int pSize = points.size();
            for (int i = 0; i < pSize; i++) {
                if (CheckCollisionPointCircle(mousePos, points[i], BALL_SIZE))
                    exists = true;
                if (exists) points[i] = points[i + 1];
            }
            handleMouseClick(points, mousePos, exists);
        }

        // if (IsKeyPressed(KEY_S)) {
        //     TakeScreenshot("./ss.png");
        // }

        BeginDrawing();

        ClearBackground(BEIGE);
        DrawFPS(SCREEN_SIZE - 30, 5);
        mouseMovement(points);

        for (int i = 0; i < points.size(); i++) {
            Color c = BROWN;
            if (i == 0 || i == points.size() - 1) c = DARKBROWN;
            DrawCircleV(points[i], BALL_SIZE, c);
        }

        if (points.size() > 1) {
            for (float t = 0; t <= 1; t += DOT_FREQUENCY) {
                DrawCircleV(bezierCurve(points, t), DOT_THICKNESS, DOT_COLOR);
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void mouseMovement(std::vector<Vector2>& points) {
    Vector2 mousePos = GetMousePosition();
    static int currentlyMoving;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (currentlyMoving == -1)
            for (int i = 0; i < points.size(); i++)
                if (CheckCollisionPointCircle(mousePos, points[i], BALL_SIZE)) {
                    currentlyMoving = i;
                    break;
                }
        if (currentlyMoving != -1) points[currentlyMoving] = mousePos;
    } else {
        currentlyMoving = -1;
    }
}
