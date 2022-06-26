#include "SourceEditor.h"

SourceEditor::SourceEditor(const QString& filePath, QWidget* parent) : QWidget(parent), m_filePath(filePath) {

}

const QString& SourceEditor::filePath() const {
    return m_filePath;
}
