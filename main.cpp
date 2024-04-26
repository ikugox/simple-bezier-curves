#include "raylib.h"
#include <vector>
/* --------------------------- LEFT CLICK TO MOVE --------------------------- */
/* ---------------------- RIGHT CLICK TO CREATE/DELETE ---------------------- */
constexpr float ballSize = 20;
constexpr float dotFrequency = 0.002;
constexpr float dotThickness = 3;
constexpr Color dotColor = DARKGREEN;

void mouseMovement(std::vector<Vector2> &points);


Vector2 lerp(Vector2 &a, Vector2 &b, float t) {
    return Vector2{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}
Vector2 quadCurve(Vector2 &a, Vector2 &b, Vector2 &c, float t) {
    Vector2 startPos = lerp(a, b, t);
    Vector2 endPos = lerp(b, c, t);
    return lerp(startPos, endPos, t);
}

Vector2 cubeCurve(Vector2 &a, Vector2 &b, Vector2 &c, Vector2 &d, float t) {
    Vector2 startPos = quadCurve(a, b, c, t);
    Vector2 endPos = quadCurve(b, c, d, t);
    return lerp(startPos, endPos, t);
}

Vector2 fourthCurve(Vector2 &a, Vector2 &b, Vector2 &c, Vector2 &d,
                    Vector2 &e, float t) {
    Vector2 startPos = cubeCurve(a, b, c, d, t);
    Vector2 endPos = cubeCurve(b, c, d, e, t);
    return lerp(startPos, endPos, t);
}
//too lazy to write the rest...
//too lazy to think of a veradict template solution...

int main(void)
{
    const int screenSize = 800;
    InitWindow(screenSize, screenSize, "WINDOW");
    // SetTargetFPS(60);

    Vector2 mousePos;
    std::vector<Vector2> points;
    
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mousePos = GetMousePosition();
            bool found = false;
            for (int i = 0; i < points.size(); i++) {
                if (CheckCollisionPointCircle(mousePos, points[i], ballSize))
                    found = true;
                if (found)
                    points[i] = points[i+1];
            }
            if (found)
                points.pop_back();
            else
                points.push_back(mousePos);
        }

        BeginDrawing();

        ClearBackground(BEIGE);
        DrawFPS(screenSize - 30, 5);
        mouseMovement(points);

        for (int i = 0; i < points.size(); i++) {
            Color c = i < 2 ? DARKBROWN : BROWN;
            DrawCircleV(points[i], ballSize, c);
        }
    
        switch (points.size()) {
        case 2:
            for (float i = 0; i <= 1; i+= dotFrequency)
                DrawCircleV(lerp(points[0], points[1], i),
                            dotThickness, dotColor);
            break;
        case 3:
            for (float i = 0; i <= 1; i+= dotFrequency)
                DrawCircleV(quadCurve(points[0], points[2], points[1], i),
                            dotThickness, dotColor);
            break;
        case 4:
            for (float i = 0; i <= 1; i+= dotFrequency)
                DrawCircleV(cubeCurve(points[0], points[2], points[3],
                            points[1], i), dotThickness, dotColor);
            break;
        case 5:
            for (float i = 0; i <= 1; i+= dotFrequency)
                DrawCircleV(fourthCurve(points[0], points[2], points[3],
                            points[4], points[1], i), dotThickness, dotColor);
            break;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void mouseMovement(std::vector<Vector2> &points) {
    Vector2 mousePos = GetMousePosition();
    static int currentlyMoving;
    
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (currentlyMoving == -1) 
            for (int i = 0; i < points.size(); i++) 
                if (CheckCollisionPointCircle(mousePos, points[i], ballSize)) {
                    currentlyMoving = i;
                    break;
                }
        if (currentlyMoving != -1)
            points[currentlyMoving] = mousePos;
    }
    else {
        currentlyMoving = -1;
    }
}