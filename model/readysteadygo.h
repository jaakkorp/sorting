#ifndef READYSTEADYGO_H
#define READYSTEADYGO_H

#include <QObject>

class QTimerEvent;

class ReadySteadyGo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    ReadySteadyGo(QObject* parent = 0);
    ~ReadySteadyGo();

    bool running() const { return mRunning; }

    Q_INVOKABLE qint64 initTime();
    Q_INVOKABLE void countDown(qint64 initTime);

Q_SIGNALS:
    void init();
    void ready();
    void steady();
    void go();
    void runningChanged();

protected:
    void timerEvent(QTimerEvent * event);

private:
    qint64 mStartTime;
    int mTmerCallbacks;
    bool mRunning;
};

#endif // READYSTEADYGO_H
