#include "ui/widget/RecentMenu.h"
#include <QTest>

constexpr auto part1 = "name1.1/name1.2";
constexpr auto part2 = "name2.1/name2.2";
constexpr auto part3 = "name3.1/name3.2";

class TextRecentMenu : public QObject {
    Q_OBJECT
public:
    TextRecentMenu() {
        QDir dir;
        dir.mkpath(path1());
        dir.mkpath(path2());
        dir.mkpath(path3());
    }

private slots:
    void setPathes();
    void setPathes_data();

    void addNew();
    void clear();

private:
    QString path1() const { return tmp.path() + "/" + QString(part1); }
    QString path2() const { return tmp.path() + "/" + QString(part2); }
    QString path3() const { return tmp.path() + "/" + QString(part3); }

    QTemporaryDir tmp;
};

void TextRecentMenu::setPathes() {
    QFETCH(QStringList, inPathes);
    QFETCH(QStringList, outPathes);

    RecentMenu recentMenu("");
    recentMenu.setPathes(inPathes);

    QCOMPARE(recentMenu.pathes(), outPathes);
}

void TextRecentMenu::setPathes_data() {
    QTest::addColumn<QStringList>("inPathes");
    QTest::addColumn<QStringList>("outPathes");

    QTest::newRow("empty") << QStringList() << QStringList();
    QTest::newRow("one") << QStringList(path1()) << QStringList(path1());
    QTest::newRow("two") << QStringList({ path1(), path2() }) << QStringList({ path2(), path1() });
    QTest::newRow("same") << QStringList({ path1(), path1() }) << QStringList(path1());

}

void TextRecentMenu::addNew() {
    RecentMenu recentMenu("");
    recentMenu.setPathes(QStringList({ path1(), path2() }));
    recentMenu.addPath(path3());

    QCOMPARE(recentMenu.pathes(), QStringList({ path3(), path2(), path1() }));
}

void TextRecentMenu::clear() {
    RecentMenu recentMenu("");
    recentMenu.setPathes(QStringList({ path1(), path2() }));
    recentMenu.clear();

    QCOMPARE(recentMenu.pathes().count(), 0);
}

QTEST_MAIN(TextRecentMenu)

#include "tst_recentmenu.moc"
