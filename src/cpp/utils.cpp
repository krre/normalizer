#include "utils.h"

QString Utils::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Utils::urlToFileName(QUrl url)
{
    return url.fileName();
}
