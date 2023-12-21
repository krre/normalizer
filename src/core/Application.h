#pragma once
#include <QApplication>

class QMainWindow;
class MainWindow;

class Application : public QApplication {
public:
    Application(int& argc, char* argv[]);
    bool notify(QObject* receiver, QEvent* event) override;

private:
    void showErrorMessage(const QString& message) const;
};
