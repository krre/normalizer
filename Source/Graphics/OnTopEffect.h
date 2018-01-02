#pragma once
#include <Qt3DRender/QEffect>

class OnTopEffect : public Qt3DRender::QEffect {

public:
    explicit OnTopEffect(Qt3DCore::QNode* parent = 0);
};
