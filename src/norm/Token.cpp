#include "Token.h"
#include <QByteArray>

Token::Token() {

}

void Token::create(const QByteArray& data) {
    deserialize(data);
}

QByteArray Token::data() const {
    return serialize();
}
