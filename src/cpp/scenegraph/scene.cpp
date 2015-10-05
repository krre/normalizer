#include "scene.h"

Scene::Scene()
{

}

void Scene::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

QSGNode* Scene::rootNode() {
    if (m_rootNode != nullptr) {
        delete m_rootNode;
    }

    m_rootNode = new QSGNode;
    for (int i = 0; i < m_nodes.count(); i++) {
        m_rootNode->appendChildNode(m_nodes.at(i)->transformNode());
    }

    return m_rootNode;
}
