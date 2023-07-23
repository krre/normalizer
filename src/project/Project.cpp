#include "Project.h"
#include "Session.h"
#include "ui/RenderView.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <norm/token/target/BinaryTarget.h>
#include <norm/token/target/LibraryTarget.h>
#include <norm/token/item/Function.h>
#include <norm/token/expression/BlockExpression.h>
#include <norm/token/statement/AssignStatement.h>
#include <norm/token/Identifier.h>
#include <norm/token/type/Integer.h>
#include <norm/token/expression/OperatorExpression.h>
#include <norm/token/expression/LiteralExpression.h>
#include <norm/io/FileReader.h>
#include <norm/io/FileWriter.h>
#include <QDir>

Project::Project(RenderView* renderView, QObject* parent) : QObject(parent), m_renderView(renderView) {
    m_session = new Session(this);
    m_opened.setBinding([&] { return !m_path.value().isEmpty(); });
}

void Project::create(const QString& name, const QString& directory, Template projectTemplate) {
    QString path = directory + "/" + name;

    if (QDir(path).exists()) {
        throw ProjectExists();
    }

    close();

    QDir().mkpath(path);
    m_session->create(path);

    QString filePath = path + "/" + name + Const::Project::Extension;

    if (projectTemplate == Template::Binary) {
        createBinary(name, filePath);
    } else {
        createLibrary(name, filePath);
    }

    open(path);
}

void Project::open(const QString& path) {
    if (path == m_path.value()) return;

    if (!QDir(path).exists()) {
        return;
    }

    close();
    setPath(path);

    try {
        Norm::FileReader reader;
        auto token = reader.read(filePath().toStdString());
        Norm::Target* target = dynamic_cast<Norm::Target*>(token);
        m_target.reset(target);
    } catch (std::exception& e) {
        qDebug() << e.what();
    }
}

void Project::save() {

}

void Project::close() {
    setPath("");
}

void Project::setPath(const QString& path) {
    m_path = path;
    m_renderView->setVisible(!path.isEmpty());
    Settings::setValue<General::LastProject>(m_path);
}

QString Project::filePath() const {
    QString name = QDir(m_path).dirName();
    return m_path + "/" + name + Const::Project::Extension;
}

void Project::createBinary(const QString& name, const QString& filePath) {
    using namespace Norm;

    auto sumExpr = new SumOperator;
    sumExpr->addExpression(new IntegerLiteral("2"));
    sumExpr->addExpression(new IntegerLiteral("3"));

    auto assign = new AssignStatement;
    assign->setIdentifier(new Identifier("x", new Integer));
    assign->setExpression(sumExpr);

    auto block = new BlockExpression;
    block->addStatement(assign);

    BinaryTarget target(name.toStdString());
    target.main()->setBlock(block);

    Norm::FileWriter writer;
    writer.write(filePath.toStdString(), &target);
}

void Project::createLibrary(const QString& name, const QString& filePath) {
    Norm::LibraryTarget target(name.toStdString());
    Norm::FileWriter writer;
    writer.write(filePath.toStdString(), &target);
}
