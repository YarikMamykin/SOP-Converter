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

class Synchronizer final : public QObject
{
    Q_OBJECT

public:
    explicit Synchronizer(std::function<void()> _runner, int _id, QObject* parent = 0);
    virtual ~Synchronizer();
signals:
    void finished();
    void end(int, bool);
public slots:
    void executor();
private:
    std::function<void()> runner;
    int id;
};

class SynchronizerThread : public QObject
{
public:
    explicit SynchronizerThread(std::unique_ptr<Synchronizer> _syncer);
    virtual ~SynchronizerThread();
private:
    std::unique_ptr<QThread> thread;
    std::unique_ptr<Synchronizer> syncer;
};

}
#endif // SYNCHRONIZER_H
