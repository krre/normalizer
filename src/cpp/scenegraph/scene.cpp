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
