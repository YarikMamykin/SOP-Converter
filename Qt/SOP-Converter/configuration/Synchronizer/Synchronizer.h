#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QObject>
#include <functional>
#include <memory>
#include <QThread>

// Retreives data from Ui component
// and syncs it to appropriate map in Parser --> and so on appropriate file

// For synchronizing use array of lambda functions
// and ParserId to detect function needed

namespace configuration
{

/* ---------------------------------------------------------------------- */
/* -- Synchronizer -- */
/* ---------------------------------------------------------------------- */

class Synchronizer final : public QObject
{
    Q_OBJECT

public:
    explicit Synchronizer(std::function<void()> runner, int _id, QObject* parent = 0);
    virtual ~Synchronizer();
signals:
    void finished();
    void end(int, bool);
public slots:
    void execute();
private:
    std::function<void()> startRunner;
    int id;
};


/* ---------------------------------------------------------------------- */
/* -- SynchronizerThread -- */
/* ---------------------------------------------------------------------- */

class SynchronizerThread : public QObject
{
    Q_OBJECT
public:
    explicit SynchronizerThread(Synchronizer* _syncer);
    virtual ~SynchronizerThread();
signals:
    void start();
private:
    QThread* thread;
    Synchronizer* syncer;
    static std::vector<SynchronizerThread*> sthreads;
};

}
#endif // SYNCHRONIZER_H
