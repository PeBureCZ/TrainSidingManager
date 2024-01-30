#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TEST : public QObject
{
    Q_OBJECT

public:
    TEST();
    ~TEST();

private slots:
    void test_case1();

};

TEST::TEST()
{

}

TEST::~TEST()
{

}

void TEST::test_case1()
{

}

QTEST_MAIN(TEST)

#include "tst_test.moc"
