#ifndef _RAM_VIRT_FLASH_H_
#define _RAM_VIRT_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    FLASH_PARTITION_DATA = 0,
    FLASH_PARTITION_MAX,
} hal_partition_t;

typedef struct {
    const char *partition_description;
    uint32_t partition_start_addr;
    uint32_t partition_length;
    uint32_t partition_options;
} hal_logic_partition_t;

int32_t virt_flash_erase(hal_partition_t in_partition, uint32_t off_set, uint32_t size);
int32_t virt_flash_write(hal_partition_t in_partition, uint32_t *off_set,
			                        const void *in_buf, uint32_t in_buf_len);
int32_t virt_flash_erase_write(hal_partition_t in_partition, uint32_t *off_set,
			                              const void *in_buf, uint32_t in_buf_len);
int32_t virt_flash_read(hal_partition_t in_partition, uint32_t *off_set,
			                       void *out_buf, uint32_t in_buf_len);

#ifdef __cplusplus
}
#endif

#endif /* _RAM_VIRT_FLASH_H_ */
