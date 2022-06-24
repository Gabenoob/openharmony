#include <sys/mount.h>
#include "littlefs.h"
#include "los_config.h"
#include "ram_virt_flash.h"
#include "fs_init.h"
#include "pthread.h"
#include "errno.h"

struct fs_cfg {
	char *mount_point;
	struct lfs_config lfs_cfg;
};

static struct fs_cfg fs[LOSCFG_LFS_MAX_MOUNT_SIZE] = {0};
pthread_mutex_t g_flashMux = {0};

int32_t LFSInit() 
{
	fs[0].mount_point = "/ram";
	fs[0].lfs_cfg.block_size = 4096;
	fs[0].lfs_cfg.block_count = 2048;
	fs[0].lfs_cfg.context = FLASH_PARTITION_DATA;
	fs[0].lfs_cfg.read = littlefs_block_read;
	fs[0].lfs_cfg.prog = littlefs_block_write;
	fs[0].lfs_cfg.erase = littlefs_block_erase;
	fs[0].lfs_cfg.sync = littlefs_block_sync;

	fs[0].lfs_cfg.read_size = 256;
	fs[0].lfs_cfg.prog_size = 256;
	fs[0].lfs_cfg.cache_size = 256;
	fs[0].lfs_cfg.lookahead_size = 16;
	fs[0].lfs_cfg.block_cycles = 1000;

	pthread_mutex_init(&g_flashMux, NULL);
	SetDefaultMountPath(0, fs[0].mount_point);
	int ret = mount(NULL, fs[0].mount_point, "littlefs", 0, &fs[0].lfs_cfg);
	printf("%s: mount fs on '%s' %s\n", __func__, fs[0].mount_point, (ret == 0) ? "succeed" : "failed");
	if (ret != 0) {
		return -1;
	}
	ret = mkdir(fs[0].mount_point);
	printf("%s: mkdir '%s' %s\n", __func__, fs[0].mount_point, (ret == 0) ? "succeed" : "failed");
	if (ret != 0) {
		return -1;
	}
	return 0;
}
