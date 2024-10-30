#include <vector>

#include "../include/raylib.h"

void handleKeys(std::vector<Vector2> &points) {
    if (IsKeyPressed(KEY_Q)) {
        CloseWindow();
    }
    if (IsKeyPressed(KEY_S)) {
        TakeScreenshot("./ss.png");
    }
    if (IsKeyPressed(KEY_R)) {
        points.clear();
    }
}
