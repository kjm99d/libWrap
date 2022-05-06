#include <stdlib.h>
#include <stb_image.h>
#pragma hdrstop

#include "wrap_image.h"

bool LoadImageSingle(WRAP_IMAGE * wrap_image, const char * image_path)
{
	bool ret = false;
	 WRAP_IMAGE * const img = wrap_image;

	if (img == NULL) {
		return ret;
	}

	unsigned char * data = stbi_load(image_path, &img->width, &img->height, &img->channel, 4);
	if (data) {
		ret = true;
	}

	return ret;
}

bool LoadImageGIF(WRAP_GIF_IMAGE * wrap_gif_image, const char * image_path)
{
	bool ret = false;

	return ret;
}
