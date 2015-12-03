#include "readysteadygo.h"

#include <QTimerEvent>
#include <QDateTime>

const qint64 KCountDownInterval = 1000;

ReadySteadyGo::ReadySteadyGo(QObject *parent)
    : QObject(parent)
    , m_running(false)
{
}

ReadySteadyGo::~ReadySteadyGo()
{
}

bool ReadySteadyGo::running() const
{
    return m_running;
}


qint64 ReadySteadyGo::initTime()
{
    m_startTime = QDateTime::currentMSecsSinceEpoch();
    return m_startTime;
}

void ReadySteadyGo::countDown(qint64 initTime)
{
    m_timerCallbacks = 0;

    auto timeDifference = QDateTime::currentMSecsSinceEpoch() - initTime;
    auto startInterval = (KCountDownInterval - timeDifference) % 100;
    startTimer(startInterval);
}

void ReadySteadyGo::timerEvent(QTimerEvent *event)
{
    switch (m_timerCallbacks) {
    case 0:
        emit init();

        killTimer(event->timerId());
        startTimer(KCountDownInterval);
        m_running = true;

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
        m_running = false;

        emit runningChanged();

        break;
    }

    ++m_timerCallbacks;
}




