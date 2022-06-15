#pragma once
#include "wrap.h"


typedef struct _WRAP_IMAGE {
	int width;
	int height;
	int channel;
} WRAP_IMAGE;

typedef struct _WRAP_GIF_IMAGE : WRAP_IMAGE
{
	int *delay;
	int frame_count;
} WRAP_GIF_IMAGE;





bool LoadImageSingle(WRAP_IMAGE *wrap_image, const char *image_path);
bool LoadImageGIF(WRAP_GIF_IMAGE *wrap_gif_image, const char *image_path);
