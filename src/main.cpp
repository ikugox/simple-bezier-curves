#include <vector>

#include "../include/raylib.h"
#include "../include/settings.h"
#include "../include/theme.h"

/* --------------------------- LEFT CLICK TO MOVE --------------------------- */
/* ---------------------- RIGHT CLICK TO CREATE/DELETE ---------------------- */
void handleRightClick(std::vector<Vector2> &points);
void handleLeftClick(std::vector<Vector2> &points);
void handleKeys(std::vector<Vector2> &points);

void drawPoints(std::vector<Vector2> &points);
void drawCurve(std::vector<Vector2> &points);

Vector2 bezierCurve(const std::vector<Vector2> &points, float t);

int main(void) {
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Simple Bezier Curves");
    SetTargetFPS(60);

    std::vector<Vector2> points;

    while (!WindowShouldClose()) {
        handleRightClick(points);
        handleKeys(points);
        handleLeftClick(points);

        BeginDrawing();
        {
            ClearBackground(BACKGROUND_COLOR);
            drawPoints(points);
            drawCurve(points);
            // DrawFPS(SCREEN_SIZE - 30, 5);
            DrawText("(Q)uit  (R)eset  (S)creenshot", 10, 5, 20, TEXT_COLOR);
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void drawCurve(std::vector<Vector2> &points) {
    if (points.size() > 1) {
        for (float t = 0; t <= 1; t += DOT_FREQUENCY) {
            DrawCircleV(bezierCurve(points, t), DOT_THICKNESS, DOT_COLOR);
        }
    }
}

void drawPoints(std::vector<Vector2> &points) {
    for (int i = 0; i < points.size(); i++) {
        Color c = POINT_COLOR;
        if (i == 0 || i == points.size() - 1)
            c = POINT_COLOR_ALT;
        DrawCircleV(points[i], BALL_SIZE, c);
    }
}
