#pragma once

#include "global.h"
#include "sdcard.h"
#include <AnimatedGIF.h>

AnimatedGIF gif;
File gif_f;
TaskHandle_t gifTaskHandle = NULL;

struct GifTaskParams {
    const char* path;
    int x;
    int y;
};

#define SWAP(a, b) { int temp = a; a = b; b = temp; }

void* GIFOpenFile(const char* fname, int32_t* pSize)
{
    gif_f = SD.open(fname);
    if (gif_f)
    {
        *pSize = gif_f.size();
        return (void*)&gif_f;
    }
    return NULL;
}

void GIFCloseFile(void* pHandle)
{
    File* f = static_cast<File*>(pHandle);
    if (f) f->close();
}

int32_t GIFReadFile(GIFFILE* pFile, uint8_t* pBuf, int32_t iLen)
{
    File* f = static_cast<File*>(pFile->fHandle);
    int32_t remaining = pFile->iSize - pFile->iPos;
    if (remaining < iLen) iLen = remaining;
    if (iLen <= 0) return 0;
    int32_t readBytes = f->read(pBuf, iLen);
    pFile->iPos = f->position();
    return readBytes;
}

int32_t GIFSeekFile(GIFFILE* pFile, int32_t iPosition)
{
    File* f = static_cast<File*>(pFile->fHandle);
    f->seek(iPosition);
    pFile->iPos = f->position();
    return pFile->iPos;
}

void GIFDraw(GIFDRAW* pDraw)
{
    int frameWidth = pDraw->iWidth;
    if (pDraw->iX + frameWidth > TFT_WIDTH)
        frameWidth = TFT_WIDTH - pDraw->iX;
    if (frameWidth < 1 || pDraw->iY + pDraw->y >= TFT_HEIGHT)
        return;

    sprite.startWrite();

    for (int x = 0; x < frameWidth; x++)
    {
        uint8_t c = pDraw->pPixels[x];
        if (pDraw->ucHasTransparency && c == pDraw->ucTransparent) continue;

        uint16_t color = pDraw->pPalette[c];
        int tftX = pDraw->iX + x;
        int tftY = pDraw->iY + pDraw->y;

        switch (sprite.getRotation())
        {
            case 1:
                SWAP(tftX, tftY);
                tftX = TFT_WIDTH - tftX - 1;
                break;
            case 2:
                tftX = TFT_WIDTH - tftX - 1;
                tftY = TFT_HEIGHT - tftY - 1;
                break;
            case 3:
                SWAP(tftX, tftY);
                tftY = TFT_HEIGHT - tftY - 1;
                break;
        }

        sprite.drawPixel(tftX, tftY, color);
    }

    sprite.endWrite();
}

void gifTask(void* pvParameters)
{
    GifTaskParams* params = (GifTaskParams*)pvParameters;

    gif.begin(LITTLE_ENDIAN_PIXELS);
    if (gif.open(params->path, GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw))
    {
        while (gif.playFrame(true, NULL))
        {
            sprite.pushSprite(params->x, params->y);
        }
        gif.close();
        sprite.fillSprite(TFT_BLACK);
        sprite.pushSprite(params->x, params->y);
    }

    delete params;
    gifTaskHandle = NULL;
    vTaskDelete(NULL);
}

void gif_playback_play_async(const char* path, int x = 0, int y = 0)
{
    if (gifTaskHandle != NULL) return;

    GifTaskParams* params = new GifTaskParams{ path, x, y };
    xTaskCreatePinnedToCore(
        gifTask,
        "GIF_Playback",
        8192,
        params,
        1,
        &gifTaskHandle,
        1
    );
}

void gif_playback_stop()
{
    if (gifTaskHandle != NULL)
    {
        vTaskDelete(gifTaskHandle);
        gifTaskHandle = NULL;
        sprite.fillSprite(TFT_BLACK);
    }
}

int gif_playback_get_framecount(const char* path)
{
    AnimatedGIF tempGif;
    File f = SD.open(path);
    if (!f) return 0;

    int32_t size = f.size();
    GIFFILE gifFile;
    gifFile.fHandle = &f;
    gifFile.iSize = size;
    gifFile.iPos = 0;

    int frameCount = 0;
    tempGif.begin(LITTLE_ENDIAN_PIXELS);
    if (tempGif.open(path, GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw))
    {
        while (tempGif.playFrame(false, NULL))
        {
            frameCount++;
        }
        tempGif.close();
    }

    f.close();
    return frameCount;
}

class Gif
{
private:
    const char* path;
    int x;
    int y;

public:
    Gif(const char* path_, int x_ = 0, int y_ = 0)
        : path(path_), x(x_), y(y_) {}

    void PlayAsync()
    {
        gif_playback_play_async(path, x, y);
    }

    void Stop()
    {
        gif_playback_stop();
    }

    int GetFrameCount()
    {
        return gif_playback_get_framecount(path);
    }
};
