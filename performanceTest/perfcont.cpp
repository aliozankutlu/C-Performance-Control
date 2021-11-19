#include "perfCont.h"

/**
 * perfCont_initPerfCont
 * @param timeCnt Zamanlayıcı sayacı
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_init(dlong *timeCnt, perfContMe *me)
{
    uint8 i;
    me->perfContTimer = timeCnt;
    me->perfCont.loopPram.minValue = 0xFFFFFFFF;
    me->perfCont.loopPram.maxValue = 0;
    me->perContStatus = perContInitState;
    me->perfCont.seqMax.seqSize = 0;
    me->perfCont.seqMin.seqSize = 0;
    me->funcSize = 0;
    for(i=0;i<FUC_SIZE;i++)
    {
        me->perfCont.contPrams[i].funcId = 0;
        me->perfCont.contPrams[i].prams.minValue = 0;
        me->perfCont.contPrams[i].prams.maxValue = 0;
        me->perfCont.seq.seqArr[i] = 0;
        me->perfCont.seqMax.seqArr[i] = 0;
        me->perfCont.seqMax.seqTimeArr[i] = 0;
        me->perfCont.seqMin.seqArr[i] = 0;
        me->perfCont.seqMin.seqTimeArr[i] = 0;
    }
    return  me->perContStatus;
}

/**
 * perfCont_recFunction
 * @param funcId Kayıt edilecek funksiyon numarası
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_recFunc(uint8 funcId, perfContMe *me)
{
    if(me->perContStatus >=  perContInitState)
    {
        if(funcId < FUC_SIZE)
        {
            me->funcSize++;
            me->perfCont.contPrams[funcId].funcId = funcId;
            me->perfCont.contPrams[funcId].prams.minValue = 0xFFFFFFFF;
            me->perfCont.contPrams[funcId].prams.maxValue = 0;
            me->perContStatus = perContRecState;
        }
        else
        {
             me->perContStatus = perContErr;
        }
    }
    else
    {
        me->perContStatus = perContErr;
    }
    return me->perContStatus;
}

/**
 * perfCont_setStartTime
 * @param funcId Kayıt edilecek funksiyon numarası
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_setStartTime(uint8 funcId, perfContMe *me)
{
    if(me->perContStatus != perContErr)
    {
        me->perfCont.seq.seqArr[me->perfCont.seq.seqIndex++] = funcId;
        me->perfCont.contPrams[funcId].prams.startVal = *(me->perfContTimer);
        me->perContStatus = perContSetStartState;
    }
    return me->perContStatus;
}

/**
 * perfCont_setStopTime
 * @param funcId Kayıt edilecek funksiyon numarası
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_setStopTime(uint8 funcId, perfContMe *me)
{
    if(me->perContStatus == perContSetStartState)
    {
        me->perfCont.contPrams[funcId].prams.stopVal = *(me->perfContTimer);
        me->perContStatus = perContSetStopState;
    }
    return  me->perContStatus;
}

/**
 * perfCont_calculateMinMax
 * @param pram  Performans kontrol döngü parametreleri yapı göstericisi
 * @return retVal Min max durum bildirimi
 */
minMaxS perfCont_calculateMinMax(perfContLoopPramS *pram)
{
    minMaxS retVal;
    dlong difference = pram->stopVal - pram->startVal;

    retVal.minFlag = FALSE;
    retVal.maxFlag = FALSE;

    if(pram->minValue > difference)
    {
        pram->minValue = difference;
        retVal.minFlag = TRUE;
    }

    if(difference > pram->maxValue)
    {
        pram->maxValue = difference;
        retVal.maxFlag = TRUE;
    }

    return retVal;
}

/**
 * perfCont_seqUpdate
 * @param control Min Max değerler yapı göstericisi
 * @param perfCont  Performans kontrol döngü parametreleri yapı göstericisi
 * @return retVal Min max durum bildirimi
 */
void perfCont_seqUpdate(minMaxS *control, perfContS *perfCont)
{
    uint8 i;
    if(control->maxFlag)
    {
        for(i=0;i<perfCont->seq.seqIndex;i++)
        {
            perfCont->seqMax.seqArr[i] = perfCont->seq.seqArr[i];
            perfCont->seqMax.seqTimeArr[i] = perfCont->contPrams[perfCont->seqMax.seqArr[i]].prams.stopVal - perfCont->contPrams[perfCont->seqMax.seqArr[i]].prams.startVal;
        }
         perfCont->seqMax.seqSize = perfCont->seq.seqIndex;
    }

    if(control->minFlag)
    {
        for(i=0;i<perfCont->seq.seqIndex;i++)
        {
            perfCont->seqMin.seqArr[i] = perfCont->seq.seqArr[i];
            perfCont->seqMin.seqTimeArr[i] = perfCont->contPrams[perfCont->seqMin.seqArr[i]].prams.stopVal - perfCont->contPrams[perfCont->seqMin.seqArr[i]].prams.startVal;
        }
         perfCont->seqMin.seqSize = perfCont->seq.seqIndex;
    }
}

/**
 * perfCont_updateFuncMinMaxVal
 * @param perfCont  Performans kontrol parametreleri yapı göstericisi
 */
void perfCont_updateFuncMinMaxVal(perfContS *perfCont)
{
    uint8 i;
    for(i=0;i<FUC_SIZE;i++)
    {
        perfCont_calculateMinMax(&perfCont->contPrams[i].prams);
    }
}

/**
 * perfCont_loopMeasureStart
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_loopMeasureStart(perfContMe *me)
{
    if(me->perContStatus != perContErr)
    {
        me->perfCont.seq.seqIndex = 0;
        me->perfCont.loopPram.startVal = *(me->perfContTimer);
        me->perContStatus = perContLoopStartState;
    }
    return me->perContStatus;
}

/**
 * perfCont_loopMeasureStop
 * @param me Performans kontrol yapı göstericisi
 * @return perContStatus Durum bildirimi
 */
uint8 perfCont_loopMeasureStop(perfContMe *me)
{
   minMaxS control;
   if(me->perContStatus >= perContLoopStartState)
   {
       me->perfCont.loopPram.stopVal = *(me->perfContTimer);
       perfCont_updateFuncMinMaxVal(&me->perfCont);
       control = perfCont_calculateMinMax(&me->perfCont.loopPram);
       perfCont_seqUpdate(&control, &me->perfCont);
       me->perContStatus = perContLoopStopState;
   }
   return me->perContStatus;
}

/**
 * perfCont_getLoopMesPrams
 * @param me Performans kontrol yapı göstericisi
 * @param mesStruct Performans kontrol döngü mesaj içeriği yapı göstericisi
 * @return size Performans kontrol döngü mesaj içeriği boyutu
 */
uint8 perfCont_getLoopMesPrams(perfContMe *me, perfContLoopMesPrams *mesStruct)
{
    uint8 i;

    mesStruct->loopMesPramsS.loopMaxVal = me->perfCont.loopPram.maxValue;
    mesStruct->loopMesPramsS.loopMinVal = me->perfCont.loopPram.minValue;
    mesStruct->loopMesPramsS.minSeqSize = me->perfCont.seqMin.seqSize;
    for(i=0;i<mesStruct->loopMesPramsS.minSeqSize;i++)
    {
         mesStruct->loopMesPramsS.minSeq[i] = me->perfCont.seqMin.seqArr[i];
         mesStruct->loopMesPramsS.minTime[i] = me->perfCont.seqMin.seqTimeArr[i];
    }
    mesStruct->loopMesPramsS.maxSeqSize = me->perfCont.seqMax.seqSize;
    for(i=0;i<mesStruct->loopMesPramsS.maxSeqSize;i++)
    {
         mesStruct->loopMesPramsS.maxSeq[i] = me->perfCont.seqMax.seqArr[i];
         mesStruct->loopMesPramsS.maxTime[i] = me->perfCont.seqMax.seqTimeArr[i];
    }
    return sizeof(mesStruct->mesArr);
}

/**
 * perfCont_getFuncMesPrams
 * @param funcId Talep edilen fonksiyon numarası
 * @param me Performans kontrol yapı göstericisi
 * @param mesStruct Performans kontrol fonksiyon mesaj içeriği yapı göstericisi
 * @return size Performans kontrol fonksiyon mesaj içeriği boyutu
 */
uint8 perfCont_getFuncMesPrams(uint8 funcId, perfContMe *me, perfContFuncMesPrams *mesStruct)
{
   mesStruct->funcMesPramsS.funId = me->perfCont.contPrams[funcId].funcId;
   mesStruct->funcMesPramsS.maxValue = me->perfCont.contPrams[funcId].prams.maxValue;
   mesStruct->funcMesPramsS.minValue = me->perfCont.contPrams[funcId].prams.minValue;
   return sizeof(mesStruct->mesArr);
}

/**
 * perfCont_getFuncIdSize
 * @param me Performans kontrol yapı göstericisi
 * @return funcSize Kayıt edilen funksiyon sayısı
 */
uint8 perfCont_getFuncSize(perfContMe *me)
{
    return  me->funcSize;
}
