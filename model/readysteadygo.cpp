#include "readysteadygo.h"

#include <QTimerEvent>
#include <QDateTime>
#include <QDebug>

const qint64 KCountDownInterval = 1000;

ReadySteadyGo::ReadySteadyGo(QObject *parent)
    : QObject(parent)
    , mRunning(false)
{
}

ReadySteadyGo::~ReadySteadyGo()
{
}

qint64 ReadySteadyGo::initTime()
{
    mStartTime = QDateTime::currentMSecsSinceEpoch();
    return mStartTime;
}

void ReadySteadyGo::countDown(qint64 initTime)
{
    mTmerCallbacks = 0;

    qint64 timeDifference = QDateTime::currentMSecsSinceEpoch() - initTime;
    qint64 startInterval = (KCountDownInterval - timeDifference) % 100;
    startTimer(startInterval);
}

void ReadySteadyGo::timerEvent(QTimerEvent* event)
{
    switch (mTmerCallbacks) {
    case 0:
        emit init();
        killTimer(event->timerId());
        startTimer(KCountDownInterval);
        mRunning = true;
        emit runningChanged();
        break;

    case 1:
        emit ready();
        break;

    case 2:
        emit steady();
        break;

    case 3:
        emit go();
        killTimer(event->timerId());
        mRunning = false;
        emit runningChanged();
        break;
    }

    mTmerCallbacks++;
}




