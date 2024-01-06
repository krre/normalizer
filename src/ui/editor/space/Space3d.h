#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class Space3d : public QWidget {
public:
    Space3d(const QUrl& webUrl, Id projectId);

private:
    Id m_projectId;
};
