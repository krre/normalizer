#pragma once
#include <QString>

struct HttpRequestAttributes {
    enum class Scheme {
        Http,
        Https
    };

    Scheme scheme;
    QString host;
    quint16 port = 0;
    QString token;
};
