#pragma once
#include "ecs/System.h"
#include "CameraMove.h"
#include <utils/Transform.h>

class CameraSystem :
    public System
{
public:
    void onStart() override;
    void onUpdate() override;

private:
    void updateCamVectors(CameraMove& cm, Transform& t);
};

