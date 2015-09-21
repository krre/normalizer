#include "viewport.h"

Viewport::Viewport()
{
    setFlag(ItemHasContents, true);
}

QSGNode *Viewport::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    qDebug() << oldNode;
    return oldNode;
}

