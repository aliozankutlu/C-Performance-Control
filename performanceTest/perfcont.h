#ifndef PERFCONT
#define PERFCONT

#define __UNIT_TEST_IS_ACTIVE

#ifdef __UNIT_TEST_IS_ACTIVE
#ifndef FALSE
  #define  FALSE  0x00u                /* Boolean value FALSE. FALSE is defined always as a zero value. */
#endif
#ifndef TRUE
  #define  TRUE   0x01u                /* Boolean value TRUE. TRUE is defined always as a non zero value. */
#endif

#ifndef NULL
  #define  NULL   0x00u
#endif

/* PE types definition */
#ifndef __cplusplus
  #ifndef bool
typedef unsigned char           bool;
  #endif
#endif
typedef unsigned char           byte;
typedef unsigned short          word;
typedef unsigned long           dword;
typedef unsigned long long      dlong;
typedef unsigned char           TPE_ErrCode;
#ifndef TPE_Float
typedef float                   TPE_Float;
#endif
#ifndef char_t
typedef char                    char_t;
#endif

/* Other basic data types */
typedef signed char             int8;
typedef signed short int        int16;
typedef signed long int         int32;

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
#endif

#define FUC_SIZE        10
#define LOOP_MES_SIZE  (FUC_SIZE*10 + 14)
#define FUNC_MES_SIZE   12

/*****************************************************/
typedef enum
{
/*--------------------------*/
    perContErr = 0,
    perContInitState,
    perContRecState,
    perContLoopStartState,
    perContSetStartState,
    perContSetStopState,
    perContLoopStopState,
/*--------------------------*/
}perContStateE;

/*****************************************************/
typedef struct
{
/*--------------------------*/
   bool minFlag;
   bool maxFlag;
/*--------------------------*/
}minMaxS;

/*****************************************************/
typedef struct
{
/*--------------------------*/
    uint32 minValue;
    uint32 maxValue;
    dlong startVal;
    dlong stopVal;
/*--------------------------*/
}perfContLoopPramS;

/*****************************************************/
typedef struct
{
/*--------------------------*/
    uint8 funcId;
    perfContLoopPramS prams;
/*--------------------------*/
}perfContPramS;

/*****************************************************/
typedef struct
{
/*--------------------------*/
      uint8 seqArr[FUC_SIZE];
      uint8 seqIndex;
      uint8 seqSize;
      uint32 seqTimeArr[FUC_SIZE];
/*--------------------------*/
}seqPramS;

/*****************************************************/
typedef struct
{
    perfContPramS contPrams[FUC_SIZE];
    seqPramS seq;
    seqPramS seqMin;
    seqPramS seqMax;
    perfContLoopPramS loopPram;
}perfContS;

/*****************************************************/
typedef struct
{
    dlong *perfContTimer;
    perContStateE perContStatus;
    perfContS perfCont;
    uint8 funcSize;
}perfContMe;

/*****************************************************/
typedef union
{
    uint8 mesArr[LOOP_MES_SIZE];
#pragma pack(push,1)
    struct
    {
        /*--------------------------*/
        uint32 loopMinVal;
        /*--------------------------*/
        uint32 loopMaxVal;
        /*--------------------------*/
        uint32 minTime[FUC_SIZE];
        /*--------------------------*/
        uint32 maxTime[FUC_SIZE];
        /*--------------------------*/
        uint8 minSeqSize;
        uint8 minSeq[FUC_SIZE];
        uint8 maxSeqSize;
        uint8 maxSeq[FUC_SIZE];
        /*--------------------------*/
        uint32 resrvd;
        /*--------------------------*/
    }loopMesPramsS;
#pragma pack(pop)
}perfContLoopMesPrams;

/*****************************************************/
typedef union
{
    uint8 mesArr[FUNC_MES_SIZE];
#pragma pack(push,1)
    struct
    {
        /*--------------------------*/
        uint8 funId;
        /*--------------------------*/
        uint32 minValue;
        /*--------------------------*/
        uint32 maxValue;
        /*--------------------------*/
        uint8 resrvd1;
        uint8 resrvd2;
        uint8 resrvd3;
        /*--------------------------*/
    }funcMesPramsS;
#pragma pack(pop)
}perfContFuncMesPrams;


extern uint8 perfCont_init(dlong *, perfContMe *);
extern uint8 perfCont_recFunc(uint8 , perfContMe *);
extern uint8 perfCont_setStartTime(uint8 , perfContMe *);
extern uint8 perfCont_setStopTime(uint8 , perfContMe *);
extern uint8 perfCont_loopMeasureStart(perfContMe *);
extern uint8 perfCont_loopMeasureStop(perfContMe *);
extern uint8 perfCont_getLoopMesPrams(perfContMe *, perfContLoopMesPrams *);
extern uint8 perfCont_getFuncMesPrams(uint8 , perfContMe *, perfContFuncMesPrams *);
extern uint8 perfCont_getFuncSize(perfContMe *);

#endif // PERFCONT

