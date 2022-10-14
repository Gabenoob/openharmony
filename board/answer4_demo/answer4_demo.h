////////////////////////
#include "osTest.h"
#include "fcntl.h"
#include "los_memory.h"
#include "los_config.h"

#define INPUT_ERROR           \
    printf("ERROR INPUT!\n"); \
    return -1;
#define update_mode_mutex 1
#define update_mode_sem 2
#define update_mode_event 4
#define update_mode_queue 8
#define note_mode_all 1
#define note_mode_particle 2
#define note_mode_particle_and_all 3
#define QUEUE_BASE_MSGSIZE 8

TSK_INIT_PARAM_S task1;
TSK_INIT_PARAM_S task2;
TSK_INIT_PARAM_S task3;
TSK_INIT_PARAM_S task4;

EVENT_CB_S event_CB ;

UINT32 QueueID001;
UINT32 mutex;
UINT32 sem;

UINT32 TaskID01;
UINT32 TaskID02;
UINT32 TaskID03;
UINT32 TaskID04;

UINT32 umode=0;
UINT32 nmode=0;

void Answer4_Demo();
void pi_digits(int digits, char *s);
static void TaskF01();
static void TaskF02();
static void TaskF03();
static void TaskF04();