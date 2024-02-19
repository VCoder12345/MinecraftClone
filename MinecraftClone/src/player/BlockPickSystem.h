#pragma once
#include "ecs/System.h"
#include <input/MouseEvent.h>

class BlockPickSystem :
    public System
{
public:
    void onStart() override;
    void onUpdate() override;

    void onMouseEvent(MouseEvent* ev);
};

