#include <klib-macros.h>
#include <assert.h>
#include <am.h>
#include "../include/minirvEMU.h"
#define N 256
static int x, y;
static uint32_t color_buf[N * N * 2];
static uint32_t canvas[N][N];
int isVGA = 0;

void draw() {
    ioe_init(); // initialization for GUI
    int w = io_read(AM_GPU_CONFIG).width / N;
    int h = io_read(AM_GPU_CONFIG).height / N;
    int block_size = w * h;
    assert((uint32_t)block_size <= LENGTH(color_buf));

    int x, y, k;
    for (x = 0; x < N; x ++) {
        for (y = 0; y < N; y ++) {
            for (k = 0; k < block_size; k ++) {
                color_buf[k] = canvas[x][y];
            }
            io_write(AM_GPU_FBDRAW, x * w, y * h, color_buf, w, h, false);
        }
    }
    io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
}

void show_image(){
    isVGA = (swaddr > 0x20000000 && swaddr < 0x20040000);
    if(isVGA) {
        y = (swaddr >> 2) / N;
        x = (swaddr >> 2) % N;
        if(x < N && x > 0 && y < N && y > 0) {
            canvas[x][y] = rs2_o;
        }
    }

    if(cnt > 629000) {
        stop = 1;
    }

}