
#ifndef __SHARED_H_
#define __SHARED_H_

/* flash_mtd.c */
extern int mtd_dev_idx(const char *mtd_part);
extern int flash_mtd_read(const char *mtd_part, int offset, unsigned char *buf, size_t count);
extern int flash_mtd_write(const char *mtd_part, int offset, unsigned char *buf, size_t count);

/* files.c */
extern int file_lock(char *tag);
extern void file_unlock(int fd_lock);

#endif
