
#ifndef _AKLOADPIC_H_
#define _AKLOADPIC_H_

#include <atlbase.h>

//��ȡJPGͼƬ�ļ���
CComQIPtr<IPicture> g_spIPicture;


//ȡ�ļ���С
unsigned long get_file_len(char *path_name);



//����ͼƬ�ļ�(bmp/jpg/gif)��ppData
bool AKLoadPic(char *pFilePath,
			   unsigned char **ppData,
			   long *pWidth,long *pHeight
			   );

#endif