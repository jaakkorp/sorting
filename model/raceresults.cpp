#include "raceresults.h"

RaceResults::RaceResults(QObject *parent)
    : QObject(parent)
    , m_result(0)
{
}

void RaceResults::reset()
{
    m_result = 0;
    m_times.clear();
}

void RaceResults::addRaceTime(int raceTime)
{
    auto index = m_times.count() - 1;

    while (index >= 0 && m_times[index] > raceTime)
            --index;

    m_times.insert(index + 1, raceTime);
}

int RaceResults::getResult()
{
    return ++m_result;
}

int RaceResults::getResult(int raceTime)
{
    return m_times.indexOf(raceTime) + 1;
}
