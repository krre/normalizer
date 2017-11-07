#pragma once
#include <QWidget>
#include <QString>

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave();
    ~Cave();
    void setFilePath(const QString& path);
    QString filePath() const;

private:
    QString m_filePath;
};
