#include "mutex_demo.h"

extern TSK_INIT_PARAM_S task1;
extern TSK_INIT_PARAM_S task2;

static VOID TaskF01(void)
{
    UINT32 ret;
    printf("\n++++++++++wangweizhaoTaskF01 (1) :before MUX pend success,Count = %d,it should be 2\n", Count);
    ret = LOS_MuxPend(g_mutexTest1, LOS_WAIT_FOREVER);
    Count++;
    // LOS_TaskDelay(50);
    ret = LOS_MuxPost(g_mutexTest1);
    printf("\n++++++++++wangweizhaoTaskF01 (2):after MUX post success,Count = %d,it should be 3\n", Count);
}

static VOID TaskF02(void)
{
    UINT32 ret;

    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (1) :before MUX pend success,Count = %d,it should be 1\n", Count);
    ret = LOS_MuxPend(g_mutexTest1, LOS_WAIT_FOREVER);
    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (2) :after MUX pend success,Count = %d,it should be 2\n", Count);
    printf("\n++++++++++wangweizhaoTaskF02 (3) :hold MUX for 50 ticks,task1 should be scheduled\n");
    LOS_TaskDelay(50);
    printf("\n++++++++++wangweizhaoTaskF02 (4) :MUX post,in the next 10 ticks task1 should be continued\n");
    ret = LOS_MuxPost(g_mutexTest1);
    LOS_TaskDelay(10);
    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (5):after MUX post check,Count = %d,it should be 4\n", Count);
}

VOID  Mutex_Demo(VOID)
{
   UINT32 ret;
    ret = LOS_MuxCreate(&g_mutexTest1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Mux Demo : MUX created ok with handler 0x%x\n", Count);
    }

    LOS_TaskLock();
    task1.pcName = "VMuteB2_1";
    task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF01;
    task1.usTaskPrio = TASK_PRIO_TEST;
    task1.uwStackSize = 0x900;
    task1.uwResved = 0;

    ret = LOS_TaskCreate(&g_testTaskID01, &task1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Mux Demo:testTask1 created ok with ID 0x%d\n", g_testTaskID01);
    }

    task2.pcName = "VMute2_2";
    task2.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF02;
    task2.usTaskPrio = TASK_PRIO_TEST-2;
    task2.uwStackSize = 0x900;
    task2.uwResved = 0;

    ret = LOS_TaskCreate(&g_testTaskID02, &task2);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Mux Demo:testTask2 created ok with ID 0x%d\n", g_testTaskID02);
    }
    LOS_TaskUnlock();

    printf("\n++++++++++wangweizhao Mux Demo:Mutex_demo will delay for 90 ticks\n");
    LOS_TaskDelay(90);

    printf("\n++++++++++wangweizhao Mux Demo:after 90 ticks ,the final Count = %d\n", Count);
    ret = LOS_MuxDelete(g_mutexTest1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Mux Demo:g_mutexTest1 deleted ok\n");
    }

    return ;
}


