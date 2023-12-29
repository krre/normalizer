#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class RenderView : public QWidget {
public:
    RenderView(const QUrl& editorUrl, Id projectId);

private:
    Id m_projectId;
};
