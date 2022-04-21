#include "FSM.h"

static FsmTable_T *HeadFsmTable = NULL;

/*==================================================================
* Function    : FSM_StateTransfer
* Description : 状态转换
* Input Para  : pFsm 状态机对象，
* Return Value:
==================================================================*/
static void FSM_StateTransfer(FSM_T *pFsm, uint8_t state)
{
    pFsm->curState = state;
}

/*==================================================================
* Function    : Add_FsmTable
* Description : 使用单链表将状态迁移表连接起来
* Input Para  : 状态迁移表指针
* Return Value:
==================================================================*/
static void Add_FsmTable(FsmTable_T * fsmtable)
{
   fsmtable->next = HeadFsmTable;
   HeadFsmTable = fsmtable;
}

/*==================================================================
* Function    : FsmTable_Delete
* Description : 删除某一个节点
* Input Para  : 状态迁移表指针
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
* Description : 状态机处理函数
* Input Para  : pFsm状态机对象, event触发事件, parm动作执行参数
* Output Para :
* Return Value:
==================================================================*/
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm)
{
  struct FsmTable_s* pass_fsm;
  /*当前状态需要执行的事件函数*/
  void (*eventActFun)(void *) = NULL;
  uint8_t NextState;
  /*获取当前状态号*/
  uint8_t CurState = pFsm ->curState;
  uint8_t flag = 0;
  /*遍历状态链表*/
  for(pass_fsm = HeadFsmTable; pass_fsm != NULL; pass_fsm = pass_fsm->next)
  {
    /*当且仅当当前状态下来个对应的事件才执行*/
    if(event == pass_fsm->event && CurState == pass_fsm->CurState)
    {
      /*允许执行状态事件*/
      flag = 1;
      /*获取当前状态事件执行函数*/
      eventActFun = pass_fsm->eventActFun;
      /*获取下一个状态事件号*/
      NextState = pass_fsm->NextState;
      break;
    }
  }
  /*开始执行状态事件*/
  if(flag)
  {
    /*如果当前事件状态有需要执行的函数，就执行*/
    if(eventActFun != NULL)
    {
        eventActFun(parm);   // 执行相应动作
    }
    /*状态转换*/
    FSM_StateTransfer(pFsm, NextState);
  }
}

/*==================================================================
* Function  : FSM_Regist
* Description : 状态机注册
* Input Para  : pFsm状态机对象，pTable状态迁移表，curState当前状态
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
* Description : 状态迁移表创建
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
* Description : 将状态迁移表与回调函数映射起来
* Input Para  : 
* Output Para :
* Return Value:
==================================================================*/
void FsmTable_Attach(FsmTable_T *fsmtable, Fsm_CallBack fsm_callback)
{
  fsmtable->eventActFun = fsm_callback;
}