#ifndef IT_LOS_QUEUE_H
#define IT_LOS_QUEUE_H
#include "osTest.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define QUEUE_SHORT_BUFFER_LENGTH 12
#define QUEUE_STANDARD_BUFFER_LENGTH 50
#define QUEUE_BASE_NUM 3
#define QUEUE_BASE_MSGSIZE 8

#define PER_ADDED_VALUE 1



VOID Queue_Demo(VOID);
VOID PrintQueueInfo(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* IT_LOS_QUEUE_H */