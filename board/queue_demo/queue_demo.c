#include "queue_demo.h"

UINT32 g_testTaskID001;
UINT32 g_testQueueID001;
QUEUE_INFO_S queueInfo;
CHAR send_buff[QUEUE_SHORT_BUFFER_LENGTH] = "hi task";
CHAR recv_buff[QUEUE_SHORT_BUFFER_LENGTH] = " ";
CHAR queue_send_buff[QUEUE_STANDARD_BUFFER_LENGTH] = "hi demo";
CHAR queue_recv_buff[QUEUE_SHORT_BUFFER_LENGTH] = " ";

static VOID QueueTaskF01(VOID)
{
    UINT32 ret;
    printf("\n++++++++++wangweizhao QueueTaskF01:start\n");
    LOS_QueueInfoGet(g_testQueueID001, &queueInfo);

    /***********************第一种情况***********************/
    // do{
    //     ret = LOS_QueueWriteCopy(g_testQueueID001,&send_buff,QUEUE_BASE_MSGSIZE,0);
    //     printf("\n++++++++++wangweizhao QueueTaskF01:write %s to queue\n",send_buff);
    //     LOS_QueueInfoGet(g_testQueueID001,&queueInfo);
    // }while(ret == LOS_OK);
    // PrintQueueInfo();
    // printf("\n++++++++++wangweizhao QueueTaskF01:message loss!\n");

    /***********************第二种情况***********************/
    int i =4;
    while(i--){
        ret = LOS_QueueWriteCopy(g_testQueueID001,&send_buff,QUEUE_BASE_MSGSIZE,LOS_WAIT_FOREVER);
        printf("\n++++++++++wangweizhao QueueTaskF01:write %s to queue\n",send_buff);
        LOS_QueueInfoGet(g_testQueueID001,&queueInfo);
    }
    PrintQueueInfo();

    /***********************第三种情况***********************/
    // LOS_QueueInfoGet(g_testQueueID001,&queueInfo);
    // PrintQueueInfo();
    // ret = LOS_QueueReadCopy(g_testQueueID001,&recv_buff,QUEUE_BASE_MSGSIZE,0);
    // if(ret != LOS_OK){
    //     printf("\n++++++++++wangweizhao QueueTaskF01: read failed!\n");
        
    // }

    /***********************第四种情况***********************/
    // ret = LOS_QueueRead(g_testQueueID001,&recv_buff,QUEUE_BASE_MSGSIZE,LOS_WAIT_FOREVER);
    

    /***********************实验手册运行***********************/
    /*

    ret = LOS_QueueReadCopy(g_testQueueID001,&queue_recv_buff,QUEUE_BASE_MSGSIZE,LOS_WAIT_FOREVER);
    if(ret==LOS_OK){
        printf("\n++++++++++wangweizhao QueueTaskF01:message recieved=%s\n",queue_recv_buff);
    }
    ret = LOS_QueueWriteCopy(g_testQueueID001,&queue_send_buff,QUEUE_BASE_MSGSIZE,0);
     if(ret==LOS_OK){
         printf("\n++++++++++wangweizhao QueueTaskF01:messave sent=%s\n",queue_send_buff);
     }
     return ;
     */
}

VOID PrintQueueInfo(VOID)
{
    printf("\n-------------Queue Demo:queueID =%d\n", queueInfo.queueID);
    printf("\n-------------Queue Demo:queueLen =%d\n", queueInfo.queueLen);
    printf("\n-------------Queue Demo:queueHead=%d\n", queueInfo.queueHead);
    printf("\n-------------Queue Demo:queueTail =%d\n", queueInfo.queueTail);
    printf("\n-------------Queue Demo:writeableCnr =%d\n", queueInfo.writableCnt);
    printf("\n-------------Queue Demo:readableCnt =%d\n", queueInfo.readableCnt);
    printf("\n-------------Queue Demo:wait read task =%d\n", queueInfo.waitReadTask[OS_WAIT_TASK_ARRAY_LEN]);
    printf("\n-------------Queue Demo:wait write task =%d\n", queueInfo.waitWriteTask[OS_WAIT_TASK_ARRAY_LEN]);
    printf("\n-------------Queue Demo:wait mem task =%d\n", queueInfo.waitMemTask[OS_WAIT_TASK_ARRAY_LEN]);
}

VOID Queue_Demo(VOID)
{

    UINT32 ret;
    ret = LOS_QueueCreate("Q1", 3, &g_testQueueID001, 0, QUEUE_BASE_MSGSIZE);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Queue Demo: Q1 created successfully with ID:%d\n", g_testQueueID001);
    }
    ret = LOS_QueueInfoGet(g_testQueueID001, &queueInfo);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Queue Demo: Q1 info got!\n");
    }

    TSK_INIT_PARAM_S queue_task1;
    (void)memset_s(&queue_task1, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    queue_task1.pcName = "QueueTestTask1";
    queue_task1.pfnTaskEntry = (TSK_ENTRY_FUNC)QueueTaskF01;
    queue_task1.usTaskPrio = TASK_PRIO_TEST;
    queue_task1.uwStackSize = TASK_STACK_SIZE_TEST;
    queue_task1.uwResved = LOS_TASK_STATUS_DETACHED;

    ret = LOS_TaskCreate(&g_testTaskID001, &queue_task1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Queue Demo: task created with id %d\n", g_testTaskID001);
    }
    /***********************第一种情况***********************/
    /*
    LOS_TaskDelay(20);
    ret = LOS_QueueDelete(g_testQueueID001);
    ret = LOS_TaskDelete(g_testTaskID001);
    */

    /***********************第二种情况***********************/
   /*
    LOS_TaskDelay(20);
    */

    /***********************第三种情况***********************/
    /*
    LOS_TaskDelay(20);
    ret = LOS_QueueDelete(g_testQueueID001);
    ret = LOS_TaskDelete(g_testTaskID001);
    */

    /***********************第四种情况***********************/
    LOS_TaskDelay(20);
    LOS_QueueInfoGet(g_testQueueID001,&queueInfo);
    PrintQueueInfo();

    /***********************实验手册运行***********************/
    /*
    ret = LOS_QueueWriteCopy(g_testQueueID001,&send_buff,QUEUE_BASE_MSGSIZE,0);
    if(ret==LOS_OK){
        printf("\n++++++++++wangweizhao Queue Demo: message=%s sent with address 0x%x\n",send_buff,send_buff);
    }
    LOS_TaskDelay(20);

    ret = LOS_QueueReadCopy(g_testQueueID001,&recv_buff,QUEUE_BASE_MSGSIZE,LOS_WAIT_FOREVER);
    if(ret==LOS_OK){
        printf("\n++++++++++wangweizhao Queue Demo: message received=%s\n",recv_buff);
    }
    ret = LOS_QueueDelete(g_testQueueID001);
    ret = LOS_TaskDelete(g_testTaskID001);
    */
}
