#include <QCoreApplication>
#include "startup.h"
#include "perfcont.h"

dlong time=0;
perfContMe me;

void func1()
{
    uint32 val=(qrand()%100);
    printf("\n func1: %d",val);
    time +=val;
}

void func2()
{
     uint32 val=(qrand()%500);
     printf("\n func2: %d",val);
     time += val;
}

void func3()
{
     uint32 val=(qrand()%1000);
     printf("\n func3: %d",val);
     time += val;
}

typedef enum
{
    func0Id=0,
    func1Id,
    func2Id
}funcIdEnum;

void testStart()
{
    perfCont_init(&time,&me);
    perfCont_recFunc(func0Id,&me);
    perfCont_recFunc(func1Id,&me);
    perfCont_recFunc(func2Id,&me);
}

void printLoopPrams()
{
    uint8 i;
    perfContLoopMesPrams mesPram;
    perfCont_getLoopMesPrams(&me,&mesPram);
    printf("\n loopMinVal: %d",mesPram.loopMesPramsS.loopMinVal);
    printf("\n loopMaxVal: %d",mesPram.loopMesPramsS.loopMaxVal);

    printf("\n minSeq:");
    for(i=0;i<mesPram.loopMesPramsS.minSeqSize;i++)
    {
         printf(" %d ",mesPram.loopMesPramsS.minSeq[i]);
    }

    printf("\n minTime:");
    for(i=0;i<mesPram.loopMesPramsS.minSeqSize;i++)
    {
         printf(" %d ",mesPram.loopMesPramsS.minTime[i]);
    }

    printf("\n maxSeq:");
    for(i=0;i<mesPram.loopMesPramsS.maxSeqSize;i++)
    {
         printf(" %d ",mesPram.loopMesPramsS.maxSeq[i]);
    }

    printf("\n maxTime:");
    for(i=0;i<mesPram.loopMesPramsS.maxSeqSize;i++)
    {
         printf(" %d ",mesPram.loopMesPramsS.maxTime[i]);
    }
}

void printFunctionPrams()
{
    uint8 i;
    perfContFuncMesPrams mesPram;
    for(i=0;i<perfCont_getFuncSize(&me);i++)
    {
        perfCont_getFuncMesPrams(i,&me,&mesPram);
        printf("\n funId: %d",mesPram.funcMesPramsS.funId);
        printf("\n minValue: %d",mesPram.funcMesPramsS.minValue);
        printf("\n maxValue: %d",mesPram.funcMesPramsS.maxValue);
    }
}

void testMain()
{
   perfCont_loopMeasureStart(&me);

   perfCont_setStartTime(func0Id,&me);
   func1();
   perfCont_setStopTime(func0Id,&me);

   perfCont_setStartTime(func1Id,&me);
   func2();
   perfCont_setStopTime(func1Id,&me);

   perfCont_setStartTime(func2Id,&me);
   func3();
   perfCont_setStopTime(func2Id,&me);

   perfCont_loopMeasureStop(&me);
   printLoopPrams();
   printFunctionPrams();
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testStart();
    startup mainTask;

    return a.exec();
}
