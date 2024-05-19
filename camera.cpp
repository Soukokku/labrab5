#include <windows.h>
#include <gl/gl.h>
#include "camera.h"
#include <iostream>
#include <math.h>

struct SCamera camera = camera={0,0,2.5, 285, 0};


void Camera_Proc() {
    glRotatef(-camera.Xrot, 1, 0, 0);// поворот вокруг оси X
    glRotatef(-camera.Zrot, 0, 0, 1);//вокруг оси Z
    glTranslatef(-camera.x, -camera.y, -camera.z); //сдвиг
}

void Camera_Rotation(float xAngle, float zAngle) {
    camera.Zrot += zAngle;
    if (camera.Zrot < 0) camera.Zrot += 360;
    if (camera.Zrot > 360) camera.Zrot -= 360;
    camera.Xrot += xAngle;
    if (camera.Xrot < 0) camera.Xrot = 0;
    if (camera.Xrot < 180) camera.Xrot = 180;
}

void Camera_AutoMoveByMouse(int centerX, int centerY, float speed) {
    POINT cur;
    POINT base = {centerX, centerY};
    GetCursorPos(&cur);
    Camera_Rotation((base.y - cur.y) / 5, (base.x - cur.x) / 5);
    SetCursorPos(base.x, base.y);
}

void Camera_MoveDirectional(int forwardMove, int rightMove, float speed) {

    float angle = -camera.Zrot / 180 * M_PI;

    if (forwardMove > 0)
        angle += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);

    if (forwardMove < 0)
        angle += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));

    if (forwardMove == 0) {
        angle += rightMove > 0 ? M_PI_2 : -M_PI_2;
        if (rightMove == 0) speed = 0;
    }

    bool coordChange = false;
    if (speed != 0) {
        float predid_x = camera.x;
        float predid_y = camera.y;
        float predid_z = camera.z;

        camera.x += sin(angle) * speed;
        camera.y += cos(angle) * speed;

        if (camera.x != predid_x || camera.y != predid_y || camera.z != predid_z) {
            coordChange = true;
        }
    }
}
