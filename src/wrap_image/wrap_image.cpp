#include <stdlib.h>

// ===== stb image settings ===== //
#define STB_IMAGE_IMPLEMENTATION
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

	// 파일 읽어서 처리 해야함.
#if 0
	stbi_uc* ts = stbi_load_gif_from_memory(data, (int)size, &delays, &width, &height, &cnt_frames, &channel, 0);
	// GIF 로딩에 실패한 경우
	if (!ts)
	{
		Err_("Cannot call gif from memory");
		return NULL;
	}
#endif


	return ret;
}
