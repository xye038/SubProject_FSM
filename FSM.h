#ifndef _FSM_H__
#define _FSM_H__

#include "Xin.h"

typedef void (*Fsm_CallBack) (void *); /*״̬���ص���������Ҫ�û�ʵ��*/

typedef struct FsmTable_s
{
    uint8_t event;               /*�����¼�*/
    uint8_t CurState;            /*��ǰ״̬*/
    void (*eventActFun)(void *); /*��������*/
    uint8_t NextState;           /*��ת״̬*/
    struct FsmTable_s* next;     /*��һ��״̬Ǩ�Ʊ��ַ*/
}FsmTable_T;

typedef struct FSM_s
{
    FsmTable_T *FsmTable;   /*״̬Ǩ�Ʊ�*/
    uint8_t curState;       /*״̬����ǰ״̬*/
}FSM_T;


void FsmTable_Create(FsmTable_T *fsmtable, uint8_t event, 
                    uint8_t curstate, uint8_t nextstate);
void FsmTable_Attach(FsmTable_T *fsmtable, Fsm_CallBack fsm_callback);  
void FsmTable_Delete(FsmTable_T *fsmtable);                  
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm);
void FSM_Regist(FSM_T *pFsm, FsmTable_T *pTable, uint8_t curState);

#endif
