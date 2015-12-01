#ifndef RACERESULTS_H
#define RACERESULTS_H

#include <QObject>
#include <QList>

class RaceResults : public QObject
{
    Q_OBJECT

public:
    RaceResults(QObject *parent = 0);

    Q_INVOKABLE void reset();
    Q_INVOKABLE void addRaceTime(int raceTime);
    Q_INVOKABLE int getResult();
    Q_INVOKABLE int getResult(int raceTime);

private:
    int mResult;
    QList<int> mTimes;
};

#endif // RACERESULTS_H
