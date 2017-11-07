#pragma once
#include <QWidget>
#include <QString>

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave();
    ~Cave();

    void newIrbis(const QString& path);
    void openIrbis(const QString& path);
    void copyIrbis(const QString& path);
    void closeIrbis();

    QString filePath() const;

private:
    QString m_filePath;
};
