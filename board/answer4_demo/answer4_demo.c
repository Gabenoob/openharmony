#include "answer4_demo.h"

static void TaskF01()
{
   if (umode == update_mode_mutex)
   {
      LOS_MuxPend(mutex, LOS_WAIT_FOREVER);
      LOS_TaskDelay(10);
   }

   if (umode == update_mode_sem)
   {
      LOS_SemPend(sem, LOS_WAIT_FOREVER);
   }

   char *p = NULL;
   UINT32 size = 1000;
   p = (char *)LOS_MemAlloc((void *)LOSCFG_SYS_HEAP_ADDR, size);
   pi_digits(10000, p);

   //写入文本文件
   UINT32 ret1, ret2;

   char *x = (char *)malloc(sizeof(char) * 251);
   for (int i = 0; i < 250; i++)
   {
      x[i] = p[i + 1];
   }
   x[250] = '\0';

   if (nmode == 2 || nmode == 3)
   {
      ret1 = open("/ram/pi1-250.txt", O_CREAT | O_RDWR);
      write(ret1, x, strlen(x));
      close(ret1);
   }
   if (nmode == 1 || nmode == 3)
   {
      ret1 = open("/ram/pi1-1000.txt", O_RDWR|O_APPEND|O_CREAT);
      write(ret1, x, 250);
      close(ret1);
   }
   free(x);
   LOS_MemFree((void *)LOSCFG_SYS_HEAP_ADDR, p);

   if (umode == update_mode_event)
   {
      printf("task1 finished\n");
      LOS_EventWrite(&event_CB, 0x01);
   }

   if (umode == update_mode_queue)
   {
      printf("task1 finished\n");
      LOS_QueueWriteCopy(QueueID001, "tsk1", QUEUE_BASE_MSGSIZE, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_mutex)
   {
      printf("task1 finished\n");
      LOS_MuxPost(mutex);
   }

   if (umode == update_mode_sem)
   {
      printf("task1 finished\n");
      LOS_SemPost(sem);
   }

   return;
}

static void TaskF02()
{
   if (umode == update_mode_mutex)
   {
      LOS_MuxPend(mutex, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_sem)
   {
      LOS_SemPend(sem, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_event)
   {
      LOS_EventRead(&event_CB, 0x01, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
   }

   char *p = NULL;
   UINT32 size = 1000;
   p = (char *)LOS_MemAlloc((void *)LOSCFG_SYS_HEAP_ADDR, size);
   pi_digits(10000, p);
   char *x = (char *)malloc(sizeof(char) * 251);

   //写入文本文件
   UINT32 ret1, ret2;

   for (int i = 0; i < 250; i++)
   {
      x[i] = p[i + 251];
   }
   x[250] = '\0';

   if (nmode == 2 || nmode == 3)
   {
      ret1 = open("/ram/pi251-500.txt", O_CREAT | O_RDWR);
      write(ret1, x, strlen(x));
      close(ret1);
   }
   if (nmode == 1 || nmode == 3)
   {
      ret1 = open("/ram/pi1-1000.txt", O_RDWR|O_APPEND|O_CREAT);
      write(ret1, x, 250);
      close(ret1);
   }
   LOS_MemFree((void *)LOSCFG_SYS_HEAP_ADDR, p);
   free(x);

   if (umode == update_mode_event)
   {
      printf("task2 finished\n");
      LOS_EventWrite(&event_CB, 0x02);
   }

   if (umode == update_mode_queue)
   {
      printf("task2 finished\n");
      LOS_QueueWriteCopy(QueueID001, "tsk2", QUEUE_BASE_MSGSIZE, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_mutex)
   {
      printf("task2 finished\n");
      LOS_MuxPost(mutex);
   }

   if (umode == update_mode_sem)
   {
      printf("task2 finished\n");
      LOS_SemPost(sem);
   }

   return;
}

static void TaskF03()
{
   if (umode == update_mode_mutex)
   {
      LOS_MuxPend(mutex, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_sem)
   {
      LOS_SemPend(sem, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_event)
   {
      LOS_EventRead(&event_CB, 0x03, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
   }
   char *p = NULL;
   UINT32 size = 1000;
   p = (char *)LOS_MemAlloc((void *)LOSCFG_SYS_HEAP_ADDR, size);
   pi_digits(10000, p);
   char *x = (char *)malloc(sizeof(char) * 251);

   for (int i = 0; i < 250; i++)
   {
      x[i] = p[i + 501];
   }
   x[250] = '\0';

   UINT32 ret1, ret2;

   if (nmode == 2 || nmode == 3)
   {
      ret1 = open("/ram/pi501-750.txt", O_CREAT | O_RDWR);
      write(ret1, x, strlen(x));
      close(ret1);
   }
   if (nmode == 1 || nmode == 3)
   {
      ret1 = open("/ram/pi1-1000.txt", O_RDWR|O_APPEND|O_CREAT);
      LOS_Lseek(ret1, 500, 0);
      write(ret1, x, 250);
      close(ret1);
   }
   LOS_MemFree((void *)LOSCFG_SYS_HEAP_ADDR, p);
   free(x);

   if (umode == update_mode_event)
   {
      printf("task3 finished\n");
      LOS_EventWrite(&event_CB, 0x04);
   }

   if (umode == update_mode_queue)
   {
      printf("task3 finished\n");
      LOS_QueueWriteCopy(QueueID001, "tsk3", QUEUE_BASE_MSGSIZE, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_mutex)
   {
      printf("task3 finished\n");
      LOS_MuxPost(mutex);
   }

   if (umode == update_mode_sem)
   {
      printf("task3 finished\n");
      LOS_SemPost(sem);
   }

   return;
}

static void TaskF04()
{
   if (umode == update_mode_mutex)
   {
      LOS_MuxPend(mutex, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_sem)
   {
      LOS_SemPend(sem, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_event)
   {
      LOS_EventRead(&event_CB, 0x07, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
   }

   char *p = NULL;
   UINT32 size = 1000;
   p = (char *)LOS_MemAlloc((void *)LOSCFG_SYS_HEAP_ADDR, size);
   pi_digits(10000, p);
   char *x = (char *)malloc(sizeof(char) * 251);

   for (int i = 0; i < 250; i++)
   {
      x[i] = p[i + 751];
   }
   x[250] = '\0';

   UINT32 ret1, ret2;

   if (nmode == 2 || nmode == 3)
   {
      ret1 = open("/ram/pi751-1000.txt", O_CREAT);
      write(ret1, x, strlen(x));
      close(ret1);
   }
   if (nmode == 1 || nmode == 3)
   {
      ret1 = open("/ram/pi1-1000.txt", O_RDWR|O_APPEND|O_CREAT);
      // LOS_Lseek(ret1, 750, 0);
      write(ret1, x, 250);
      close(ret1);
   }
   LOS_MemFree((void *)LOSCFG_SYS_HEAP_ADDR, p);
   free(x);

   if (umode == update_mode_event)
   {
      printf("task4 finished\n");
      LOS_EventWrite(&event_CB, 0x08);
   }

   if (umode == update_mode_queue)
   {
      printf("task4 finished\n");
      LOS_QueueWriteCopy(QueueID001, "tsk4", QUEUE_BASE_MSGSIZE, LOS_WAIT_FOREVER);
   }

   if (umode == update_mode_mutex)
   {
      printf("task4 finished\n");
      LOS_MuxPost(mutex);
   }

   if (umode == update_mode_sem)
   {
      printf("task4 finished\n");
      LOS_SemPost(sem);
   }

   return;
}

void Answer4_Demo(UINT32 argc, const CHAR **argv)
{
   UINT32 ret;
   //检查参数是否有误
   if (argc != 3 && argc != 4)
   {
      INPUT_ERROR;
   }
   else
   {
      for (int i = 1; i < argc; i++)
         if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "-M") == 0)
         {
            umode += update_mode_mutex;
         }
         else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-S") == 0)
         {
            umode += update_mode_sem;
         }
         else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-E") == 0)
         {
            umode += update_mode_event;
         }
         else if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "-Q") == 0)
         {
            umode += update_mode_queue;
         }
         else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-A") == 0)
         {
            nmode += note_mode_all;
         }
         else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-P") == 0)
         {
            nmode += note_mode_particle;
         }
   }
   if (umode != update_mode_sem && umode != update_mode_mutex && umode != update_mode_event && umode != update_mode_queue)
   {
      INPUT_ERROR
   }
   else if (nmode != note_mode_all && nmode != note_mode_particle && nmode != note_mode_particle_and_all)
   {
      INPUT_ERROR
   }

   // //任务创建
   LOS_TaskLock();
   task1.pcName = "pi_1-250";
   task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF01;
   task1.usTaskPrio = TASK_PRIO_TEST-3;
   task1.uwStackSize = 0xF000;
   task1.uwResved = 0;

   ret = LOS_TaskCreate(&TaskID01, &task1);
   if (ret == LOS_OK)
   {
      printf("\n++++++++++wangweizhao :testTask1 created ok with ID 0x%d\n", TaskID01);
   }

   task2.pcName = "pi_251-500";
   task2.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF02;
   task2.usTaskPrio = TASK_PRIO_TEST-2;
   task2.uwStackSize = 0xF000;
   task2.uwResved = 0;

   ret = LOS_TaskCreate(&TaskID02, &task2);
   if (ret == LOS_OK)
   {
      printf("\n++++++++++wangweizhao :testTask2 created ok with ID 0x%d\n", TaskID02);
   }

   task3.pcName = "pi_501-750";
   task3.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF03;
   task3.usTaskPrio = TASK_PRIO_TEST-1;
   task3.uwStackSize = 0xF000;
   task3.uwResved = 0;

   ret = LOS_TaskCreate(&TaskID03, &task3);
   if (ret == LOS_OK)
   {
      printf("\n++++++++++wangweizhao :testTask2 created ok with ID 0x%d\n", TaskID03);
   }

   task4.pcName = "pi_751-1000";
   task4.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF04;
   task4.usTaskPrio = TASK_PRIO_TEST;
   task4.uwStackSize = 0xF000;
   task4.uwResved = 0;

   ret = LOS_TaskCreate(&TaskID04, &task4);
   if (ret == LOS_OK)
   {
      printf("\n++++++++++wangweizhao :testTask1 created ok with ID 0x%d\n", TaskID04);
   }

   if (umode == update_mode_event)
   {
      event_CB.uwEventID = 0x0;
      ret = LOS_EventInit(&event_CB);
      if (ret == LOS_OK)
      {
         printf("\neventInit ok!\n");
      }

      LOS_TaskUnlock();

      ret = LOS_EventRead(&event_CB, 0x0f, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
      printf("event all finished\n");
      ret = LOS_EventDestroy(&event_CB);
   }

   if (umode == update_mode_queue)
   {
      ret = LOS_QueueCreate("queue", 1, &QueueID001, 0, QUEUE_BASE_MSGSIZE);
      if (ret == LOS_OK)
      {
         printf("QueueCreat ok!\n");
      }
      int i = 4;
      char x[8];

      LOS_TaskUnlock();

      while (i)
      {
         LOS_QueueRead(QueueID001, &x, QUEUE_BASE_MSGSIZE, LOS_WAIT_FOREVER);
         printf("read once \n");
         i--;
      }
      printf("queue finished\n");
   }

   if (umode == update_mode_sem)
   {
      ret = LOS_SemCreate(4, &sem);
      if (ret == LOS_OK)
      {
         printf("sem creat ok!\n");
      }
      LOS_TaskUnlock();
      LOS_TaskDelay(10);
      LOS_SemPend(sem, LOS_WAIT_FOREVER);
      LOS_SemPost(sem);
      printf("sem finished\n");
      LOS_SemDelete(sem);
   }

   if (umode == update_mode_mutex)
   {

      ret = LOS_MuxCreate(&mutex);
      if (ret == LOS_OK)
      {
         printf("mutex creat ok!\n");
      }
      LOS_TaskUnlock();
      LOS_TaskDelay(10);
      LOS_MuxPend(mutex,LOS_WAIT_FOREVER);
      LOS_MuxPost(mutex);
      printf("mutex finished\n");
      LOS_MuxDelete(mutex);
   }

   umode = 0;
   nmode = 0;

//输出pi1-1000.txt的内容
   // char x[1000];
   // int fd = open("/ram/pi1-1000.txt",O_RDONLY);
   // LOS_Lseek(fd,0,0);
   // read(fd,x,1000);
   // close(fd);
   // for (int i=0;i<1000;i++){
   //    printf("%c",x[i]);
   // }
   // return;
}
void pi_digits(int digits, char *s)
{
   int pos = 0;
   int carry = 0;
   int arr[digits + 1];
   for (int i = 0; i <= digits; ++i)
      arr[i] = 2000;
   for (int i = digits; i > 0; i -= 14)
   {
      int sum = 0;
      for (int j = i; j > 0; --j)
      {
         sum = sum * j + 10000 * arr[j];
         arr[j] = sum % (j * 2 - 1);
         sum /= j * 2 - 1;
      }
      int digit = carry + sum / 10000;
      *(s + pos) = digit / 1000 + 48;
      *(s + pos + 1) = digit / 100 % 10 + 48;
      *(s + pos + 2) = digit / 10 % 10 + 48;
      *(s + pos + 3) = digit % 10 + 48;
      pos += 4;
      if (pos >= 1000)
      {
         return;
      }
      carry = sum % 10000;
   }
}