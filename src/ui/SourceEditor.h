#pragma once
#include <QWidget>

class SourceEditor : public QWidget {
    Q_OBJECT
public:
    explicit SourceEditor(const QString& filePath, QWidget* parent = nullptr);
    const QString& filePath() const;

private:
    QString m_filePath;
};
