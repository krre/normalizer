#pragma once
#include <Qt3DRender/QEffect>

namespace IrbisUnitBuilder {

class OnTopEffect : public Qt3DRender::QEffect {

public:
    explicit OnTopEffect(Qt3DCore::QNode* parent = 0);
};

} // IrbisUnitBuilder
