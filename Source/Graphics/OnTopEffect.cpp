#include "OnTopEffect.h"
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <QtCore/QUrl>

namespace IrbisUnitBuilder {

OnTopEffect::OnTopEffect(Qt3DCore::QNode* parent) : Qt3DRender::QEffect(parent) {
    Qt3DRender::QTechnique* technique = new Qt3DRender::QTechnique();
    technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::NoProfile);
    technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    technique->graphicsApiFilter()->setMajorVersion(4);
    technique->graphicsApiFilter()->setMinorVersion(3);

    Qt3DRender::QFilterKey* filterkey = new Qt3DRender::QFilterKey(this);
    filterkey->setName(QStringLiteral("renderingStyle"));
    filterkey->setValue(QStringLiteral("forward"));

    technique->addFilterKey(filterkey);

    Qt3DRender::QShaderProgram* shader = new Qt3DRender::QShaderProgram();
    shader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Graphics/Shaders/OnTopMaterial.vert"))));
    shader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Graphics/Shaders/OnTopMaterial.frag"))));

    Qt3DRender::QRenderPass* renderPass = new Qt3DRender::QRenderPass();
    renderPass->setShaderProgram(shader);
    technique->addRenderPass(renderPass);

    addTechnique(technique);
}

} // IrbisUnitBuilder
