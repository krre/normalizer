#include "scene.h"

Scene::Scene(QObject *parent) : QObject(parent)
{

}

QQmlListProperty<Node> Scene::nodes()
{
    return QQmlListProperty<Node>(this, m_nodes);
}

