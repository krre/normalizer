#include "Exception.h"

Exception::Exception(const QString& error) : m_error(error) {

}

const QString& Exception::error() const {
    return m_error;
}
