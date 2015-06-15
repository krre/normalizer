#include "interpretator.h"

Interpretator::Interpretator()
{

}

void Interpretator::run(const QString filePath)
{
    emit consoleMessage("Starting " + filePath + "...");
}

