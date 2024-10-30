#include <vector>

#include "../include/raylib.h"
#include "../include/settings.h"

void updateMovingPoint(std::vector<Vector2> &points, const Vector2 &mousePos,
                       int &currentlyMoving);
int  findPointUnderMouse(const std::vector<Vector2> &points,
                         const Vector2              &mousePos);

static int currentlyMoving = -1;  // initialize to -1

void handleLeftClick(std::vector<Vector2> &points) {
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        currentlyMoving = -1;  // reset when the mouse button is released
    } else {
        Vector2 mousePos = GetMousePosition();
        updateMovingPoint(points, mousePos, currentlyMoving);
    }
}

void updateMovingPoint(std::vector<Vector2> &points, const Vector2 &mousePos,
                       int &currentlyMoving) {
    if (currentlyMoving == -1) {
        currentlyMoving = findPointUnderMouse(points, mousePos);
    } else {
        points[currentlyMoving] = mousePos;
    }
}

int findPointUnderMouse(const std::vector<Vector2> &points,
                        const Vector2              &mousePos) {
    for (int i = 0; i < points.size(); i++) {
        if (CheckCollisionPointCircle(mousePos, points[i], BALL_SIZE)) {
            return i;
        }
    }
    return -1;
}
