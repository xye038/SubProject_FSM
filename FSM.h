#ifndef _FSM_H__
#define _FSM_H__

#include "Xin.h"

typedef void (*Fsm_CallBack) (void *); /*状态机回调函数，需要用户实现*/

typedef struct FsmTable_s
{
    uint8_t event;               /*触发事件*/
    uint8_t CurState;            /*当前状态*/
    void (*eventActFun)(void *); /*动作函数*/
    uint8_t NextState;           /*跳转状态*/
    struct FsmTable_s* next;     /*下一个状态迁移表地址*/
}FsmTable_T;

typedef struct FSM_s
{
    FsmTable_T *FsmTable;   /*状态迁移表*/
    uint8_t curState;       /*状态机当前状态*/
}FSM_T;


void FsmTable_Create(FsmTable_T *fsmtable, uint8_t event, 
                    uint8_t curstate, uint8_t nextstate);
void FsmTable_Attach(FsmTable_T *fsmtable, Fsm_CallBack fsm_callback);  
void FsmTable_Delete(FsmTable_T *fsmtable);                  
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm);
void FSM_Regist(FSM_T *pFsm, FsmTable_T *pTable, uint8_t curState);

#endif
