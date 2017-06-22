#pragma once

#include <QTest>
#include <QObject>
#include <QVector>

#include <string>

// This is the based class for all unit testing suites
class QTestSuite : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTestSuite)
protected:
    int argc;
    char** argv;

    QVector<std::string> args;

public:
    explicit QTestSuite()
        : QObject()
    {
        AllSuites().push_back(this);
    }
    virtual ~QTestSuite()
    {
    }

public:
    void SetConsoleArgs(int _argc, char* _argv[])
    {
        argc = _argc;
        argv = _argv;
    }

    void SetArgs(QVector<std::string> _args)
    {
        args = std::move(_args);
    }

public:
    static QVector<QObject*>& AllSuites()
    {
        static QVector<QObject*> testSuites;
        return testSuites;
    }

    template<typename Action>
    static int RunAllTests(Action action)
    {
        int failedSuitesCount = 0;
        for(auto suite : AllSuites())
        {
            action(dynamic_cast<QTestSuite*>(suite));
            if(QTest::qExec(suite)) {
                ++failedSuitesCount;
            }
        }
        return failedSuitesCount;
    }

    static int RunAllTests(int _argc, char* _argv[])
    {
        return RunAllTests([&] (QTestSuite* suite) {
            suite->SetConsoleArgs(_argc, _argv);
        });
    }

    static int RunAllTests(std::initializer_list<std::string> _args)
    {
        return RunAllTests([&] (QTestSuite* suite) {
            suite->SetArgs(_args);
        });
    }
};

