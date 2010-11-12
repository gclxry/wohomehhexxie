
#ifndef _AKLOADPIC_H_
#define _AKLOADPIC_H_

#include <atlbase.h>

//读取JPG图片文件用
CComQIPtr<IPicture> g_spIPicture;


//取文件大小
unsigned long get_file_len(char *path_name);



//加载图片文件(bmp/jpg/gif)到ppData
bool AKLoadPic(char *pFilePath,
			   unsigned char **ppData,
			   long *pWidth,long *pHeight
			   );

#endif