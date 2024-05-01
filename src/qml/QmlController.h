#pragma once
#include <QObject>

class RestApi;

namespace Qml {

class QmlController : public QObject {
public:
    QmlController();
    static void setRestApi(RestApi* restApi);

protected:
    static RestApi* restApi();

private:
    static RestApi* s_restApi;
};

}
