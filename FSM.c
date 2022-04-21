#include "FSM.h"

static FsmTable_T *HeadFsmTable = NULL;

/*==================================================================
* Function    : FSM_StateTransfer
* Description : ״̬ת��
* Input Para  : pFsm ״̬������
* Return Value:
==================================================================*/
static void FSM_StateTransfer(FSM_T *pFsm, uint8_t state)
{
    pFsm->curState = state;
}

/*==================================================================
* Function    : Add_FsmTable
* Description : ʹ�õ�����״̬Ǩ�Ʊ���������
* Input Para  : ״̬Ǩ�Ʊ�ָ��
* Return Value:
==================================================================*/
static void Add_FsmTable(FsmTable_T * fsmtable)
{
   fsmtable->next = HeadFsmTable;
   HeadFsmTable = fsmtable;
}

/*==================================================================
* Function    : FsmTable_Delete
* Description : ɾ��ĳһ���ڵ�
* Input Para  : ״̬Ǩ�Ʊ�ָ��
* Return Value:
==================================================================*/
void FsmTable_Delete(FsmTable_T *fsmtable)
{
  struct FsmTable_s* curr;
  if(fsmtable == HeadFsmTable)
  {
    HeadFsmTable = fsmtable->next;
    return;
  }

  for(curr = HeadFsmTable; curr!=NULL; curr=curr->next)
  {
    if(curr->next == fsmtable)
    {
      curr->next = fsmtable->next;
     return;
    }
  }
}

/*==================================================================
* Function  : FSM_EventHandle
* Description : ״̬��������
* Input Para  : pFsm״̬������, event�����¼�, parm����ִ�в���
* Output Para :
* Return Value:
==================================================================*/
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm)
{
  struct FsmTable_s* pass_fsm;
  /*��ǰ״̬��Ҫִ�е��¼�����*/
  void (*eventActFun)(void *) = NULL;
  uint8_t NextState;
  /*��ȡ��ǰ״̬��*/
  uint8_t CurState = pFsm ->curState;
  uint8_t flag = 0;
  /*����״̬����*/
  for(pass_fsm = HeadFsmTable; pass_fsm != NULL; pass_fsm = pass_fsm->next)
  {
    /*���ҽ�����ǰ״̬��������Ӧ���¼���ִ��*/
    if(event == pass_fsm->event && CurState == pass_fsm->CurState)
    {
      /*����ִ��״̬�¼�*/
      flag = 1;
      /*��ȡ��ǰ״̬�¼�ִ�к���*/
      eventActFun = pass_fsm->eventActFun;
      /*��ȡ��һ��״̬�¼���*/
      NextState = pass_fsm->NextState;
      break;
    }
  }
  /*��ʼִ��״̬�¼�*/
  if(flag)
  {
    /*�����ǰ�¼�״̬����Ҫִ�еĺ�������ִ��*/
    if(eventActFun != NULL)
    {
        eventActFun(parm);   // ִ����Ӧ����
    }
    /*״̬ת��*/
    FSM_StateTransfer(pFsm, NextState);
  }
}

/*==================================================================
* Function  : FSM_Regist
* Description : ״̬��ע��
* Input Para  : pFsm״̬������pTable״̬Ǩ�Ʊ�curState��ǰ״̬
* Output Para :
* Return Value:
==================================================================*/
void FSM_Regist(FSM_T *pFsm, FsmTable_T *pTable, uint8_t curState)
{
  pFsm->FsmTable = pTable;
  pFsm->curState = curState;
}

/*==================================================================
* Function  : FsmTable_Create
* Description : ״̬Ǩ�Ʊ���
* Input Para  : 
* Output Para :
* Return Value:
==================================================================*/
void FsmTable_Create(FsmTable_T *fsmtable, uint8_t event, 
                    uint8_t curstate, uint8_t nextstate)
{
  fsmtable->event = event;
  fsmtable->CurState = curstate;
  fsmtable->NextState = nextstate;
  Add_FsmTable(fsmtable);
}

/*==================================================================
* Function  : FsmTable_Attach
* Description : ��״̬Ǩ�Ʊ���ص�����ӳ������
* Input Para  : 
* Output Para :
* Return Value:
==================================================================*/
void FsmTable_Attach(FsmTable_T *fsmtable, Fsm_CallBack fsm_callback)
{
  fsmtable->eventActFun = fsm_callback;
}