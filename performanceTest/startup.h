#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>
#include <qtimer.h>

class startup : public QObject
{
    Q_OBJECT
public:
    explicit startup(QObject *parent = 0);

    ~startup();

signals:

public slots:
   void run();
   void timeout();
private:
   QTimer m_timer;
   QTimer t_timer;
};

#endif // STARTUP_H
