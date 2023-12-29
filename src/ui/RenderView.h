#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class RenderView : public QWidget {
    Q_OBJECT
public:
    RenderView(const QUrl& editorUrl, Id projectId);
};
