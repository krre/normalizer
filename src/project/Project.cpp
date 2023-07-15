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

    QString name = QDir(path).dirName();
    QString filePath = path + "/" + name + Const::Project::Extension;

    try {
        auto target = Norm::Target::read(filePath.toStdString());
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

void Project::createBinary(const QString& name, const QString& filePath) {
    Norm::Integer integer;
    auto x = std::make_unique<Norm::Identifier>("x", &integer);

    auto sumExpr = std::make_unique<Norm::SumOperator>();
    sumExpr->addExpression(std::make_unique<Norm::IntegerLiteral>("2"));
    sumExpr->addExpression(std::make_unique<Norm::IntegerLiteral>("3"));

    auto assign = std::make_unique<Norm::AssignStatement>();
    assign->setIdentifier(std::move(x));
    assign->setExpression(std::move(sumExpr));

    auto block = std::make_unique<Norm::BlockExpression>();
    block->addStatement(std::move(assign));

    Norm::BinaryTarget target(name.toStdString());
    target.main()->setBlock(std::move(block));
    target.write(filePath.toStdString());
}

void Project::createLibrary(const QString& name, const QString& filePath) {
    Norm::LibraryTarget target(name.toStdString());
    target.write(filePath.toStdString());
}
