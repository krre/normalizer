#pragma once
#include <QtCore>
#include <QtQml>
#include <QtQuick>

class Node : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Node> nodes READ nodes)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_CLASSINFO("DefaultProperty", "nodes")
public:
    explicit Node(QObject *parent = 0);
    QQmlListProperty<Node> nodes() { return QQmlListProperty<Node>(this, m_nodes); }
    int count() const { return m_nodes.count(); }
    Node* node(int index) const { return m_nodes.at(index); }

    QVector3D position() const { return m_position; }
    void setPosition(QVector3D position);

    QVector3D rotation() const { return m_rotation; }
    void setRotation(QVector3D rotation);

    QVector3D scale() const { return m_scale; }
    void setScale(QVector3D scale);

signals:
    void positionChanged(QVector3D position);
    void rotationChanged(QVector3D rotation);
    void scaleChanged(QVector3D scale);

private:
    QList<Node*> m_nodes;
    QSGTransformNode transformNode;
    QMatrix4x4 matrix;
    QVector3D m_position;
    QVector3D m_rotation;
    QVector3D m_scale;
};
