#include "Exception.h"

Exception::Exception(const char* error) : m_error(error) {

}

Exception::Exception(const QString& error) : m_error(error) {

}

Exception::Exception(const std::string& error) : m_error(QString::fromUtf8(error)) {

}

const QString& Exception::error() const {
    return m_error;
}
