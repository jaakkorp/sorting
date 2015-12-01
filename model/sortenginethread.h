#ifndef SORTENGINETHREAD_H
#define SORTENGINETHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SortEngine;

class SortEngineThread : public QThread
{
    Q_OBJECT

public:
    SortEngineThread(QObject *parent = 0);
    ~SortEngineThread();
    Q_INVOKABLE void wait();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void sleep(int);
    SortEngine* sortEngine();

protected:
    void run() { exec(); }

private:
    QMutex lock;
    QWaitCondition mwaitCondition;
    SortEngine *mEngine;
    int mOperationInterval;
};

#endif // SORTENGINETHREAD_H

