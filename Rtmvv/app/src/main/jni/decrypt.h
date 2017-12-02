#ifndef __DECRYPT_H__
#define __DECRYPT_H__

#ifdef __cplusplus
extern "C" {
#endif

  struct mydirent
  {
    unsigned char type; // DT_DIR or DT_REG
    int level;    // type 为 DT_DIR 时，表示目录深度。type 为对联所在目录深度 
    int length;
    unsigned char name[256];
  };

  struct duilian;

  struct duilian *getduilian(void);
  int myrewinddir(struct duilian *restrict dl);
  void endn(struct duilian *dl);

  struct mydirent *myreaddir(struct duilian *restrict dl, int level);
  struct mydirent *myreadcouplet(struct duilian *restrict dl, int level);
  struct mydirent *myreaddir2(struct duilian *restrict dl, int level);

  int mygetcwd(unsigned char *restrict cwd, int size,
      struct duilian *restrict dl);

  // 返回 seek 到的级别
  int myseekdir(const unsigned char * restrict path, 
      struct duilian * restrict dl);

#ifdef __cplusplus
}
#endif

#endif

