#include "raceresults.h"
#include <QtAlgorithms>
#include <QString>
#include <QDebug>

RaceResults::RaceResults(QObject *parent) : QObject(parent)
{
    mResult = 0;
}

void RaceResults::reset()
{
    mResult = 0;
    mTimes.clear();
}

void RaceResults::addRaceTime(int raceTime)
{
    int index = mTimes.count() - 1;
    while (index >= 0) {
        if (mTimes[index] > raceTime) {
            index--;
            continue;
        }
        else
            break;
    }
    mTimes.insert(index+1, raceTime);
}

int RaceResults::getResult()
{
    return ++mResult;
}

int RaceResults::getResult(int raceTime)
{
    return mTimes.indexOf(raceTime) + 1;
}
