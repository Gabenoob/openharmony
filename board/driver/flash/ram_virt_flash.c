/*
 *  * Copyright (c) 2021 bestechnic (Shanghai) Technologies CO., LIMITED.
 *   * Licensed under the Apache License, Version 2.0 (the "License");
 *    * you may not use this file except in compliance with the License.
 *     * You may obtain a copy of the License at
 *      *
 *       *     http://www.apache.org/licenses/LICENSE-2.0
 *        *
 *         * Unless required by applicable law or agreed to in writing, software
 *          * distributed under the License is distributed on an "AS IS" BASIS,
 *           * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *            * See the License for the specific language governing permissions and
 *             * limitations under the License.
 *              */
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "pthread.h"
#include "ram_virt_flash.h"
#include "securec.h"
#include "los_interrupt.h"

/* Logic partition on flash devices */
hal_logic_partition_t g_halPartitions[] = {
[FLASH_PARTITION_DATA] = {
	            .partition_description = "littlefs",
	            .partition_start_addr = 0x21800000,
	            .partition_length = 0x800000, //8M
		        },
};

int32_t virt_flash_erase(hal_partition_t in_partition, uint32_t off_set, uint32_t size)
{
    uint32_t start_addr;
    uint32_t partition_end;

    start_addr = g_halPartitions[in_partition].partition_start_addr + off_set;
    partition_end = g_halPartitions[in_partition].partition_start_addr + g_halPartitions[in_partition].partition_length;
    if (start_addr >= partition_end) {
        printf("flash over write\r\n");
        return -1;
    }
    if ((start_addr + size) > partition_end) {
        size = partition_end - start_addr;
        printf("flash over write, new len is %d\r\n", size);
    }

    uint32_t intSave = LOS_IntLock();
    (void)memset_s((void *)start_addr, size, 0, size);
    LOS_IntRestore(intSave);
    return 0;
}

int32_t virt_flash_write(hal_partition_t in_partition, uint32_t *off_set, const void *in_buf, uint32_t in_buf_len)
{
    uint32_t start_addr;
    uint32_t partition_end;
    start_addr = g_halPartitions[in_partition].partition_start_addr + *off_set;
    partition_end = g_halPartitions[in_partition].partition_start_addr + g_halPartitions[in_partition].partition_length;

    if (start_addr >= partition_end) {
       printf("flash over write\r\n");
       return -1;
    }

    if ((start_addr + in_buf_len) > partition_end) {
      in_buf_len = partition_end - start_addr;
      printf("flash over write, new len is %d\r\n", in_buf_len);
    }

    uint32_t intSave = LOS_IntLock();
    (void)memcpy_s((void *)start_addr, in_buf_len, in_buf, in_buf_len);
    LOS_IntRestore(intSave);

    return 0;
}

int32_t virt_flash_erase_write(hal_partition_t in_partition, uint32_t *off_set, const void *in_buf, uint32_t in_buf_len)
{
    uint32_t start_addr;
    uint32_t partition_end;

    start_addr = g_halPartitions[in_partition].partition_start_addr + *off_set;
    partition_end = g_halPartitions[in_partition].partition_start_addr + g_halPartitions[in_partition].partition_length;

    if (start_addr >= partition_end) {
       printf("flash over erase&write\r\n");
       return -1;
    }

    if ((start_addr + in_buf_len) > partition_end) {
       in_buf_len = partition_end - start_addr;
       printf("flash over erase&write, new len is %d\r\n", in_buf_len);
    }

    uint32_t intSave = LOS_IntLock();
    (void)memset_s((void *)start_addr, in_buf_len, 0, in_buf_len);
    (void)memcpy_s((void *)start_addr, in_buf_len, in_buf, in_buf_len);
    LOS_IntRestore(intSave);

    return 0;
}

int32_t virt_flash_read(hal_partition_t in_partition, uint32_t *off_set, void *out_buf, uint32_t in_buf_len)
{
    uint32_t start_addr;
    uint32_t partition_end;

    start_addr = g_halPartitions[in_partition].partition_start_addr + *off_set;
    partition_end = g_halPartitions[in_partition].partition_start_addr + g_halPartitions[in_partition].partition_length;

    if (start_addr >= partition_end) {
       printf("flash over read\r\n");
       return -1;
    }

    if ((start_addr + in_buf_len) > partition_end) {
       in_buf_len = partition_end - start_addr;
       printf("flash over read, new len is %d\r\n", in_buf_len);
    }

    uint32_t intSave = LOS_IntLock();
    (void)memcpy_s(out_buf, in_buf_len, (void *)start_addr, in_buf_len);
    LOS_IntRestore(intSave);

    return 0;
}
