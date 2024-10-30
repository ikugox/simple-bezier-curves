#include <vector>

#include "../include/raylib.h"
#include "../include/settings.h"

void handleExistingPoint(std::vector<Vector2>& points, int pSize);
void handleNewPoint(std::vector<Vector2>& points, const Vector2& mousePos,
                    int pSize);
bool findPoint(std::vector<Vector2>& points, Vector2 mousePos);

void handleRightClick(std::vector<Vector2>& points) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        return;
    }

    Vector2 mousePos = GetMousePosition();
    bool exists = findPoint(points, mousePos);
    const int pSize = points.size();

    if (exists) {
        handleExistingPoint(points, pSize);
    } else {
        handleNewPoint(points, mousePos, pSize);
    }
}

bool findPoint(std::vector<Vector2>& points, Vector2 mousePos) {
    bool exists = false;
    const int pSize = points.size();
    for (int i = 0; i < pSize; i++) {
        if (CheckCollisionPointCircle(mousePos, points[i], BALL_SIZE))
            exists = true;
        if (exists) points[i] = points[i + 1];
    }
    return exists;
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
        points[pSize - 1] = mousePos;
    }
}
