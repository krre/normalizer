#pragma once
#include <QObject>

class RestApi;

namespace Qml {

class QmlController : public QObject {
    Q_OBJECT
public:
    QmlController();
    static void setRestApi(RestApi* restApi);

signals:
    void errorOccured(int status, const QString& message);

protected:
    static RestApi* restApi();

private:
    static RestApi* s_restApi;
};

}
