#include "startup.h"

typedef unsigned long long      dlong;
extern dlong time;
extern void testMain();
startup::startup(QObject *parent) : QObject(parent)
{
    connect(&m_timer, SIGNAL(timeout()),this,SLOT(run()));
    m_timer.start(1000);

    connect(&t_timer, SIGNAL(timeout()),this,SLOT(timeout()));
    t_timer.start(10);
}

startup::~startup()
{
    m_timer.stop();
}

void startup::run()
{
    printf("run");
    testMain();
}

void startup::timeout()
{
    printf("tic");
    time++;
}
