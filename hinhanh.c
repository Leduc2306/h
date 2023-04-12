#include <stdint.h>
#include <stdio.h>
#include <system_stm32f4xx.h>
#include <stm32f401re_gpio.h>
#include <timer.h>
#include <Ucglib.h>
#include "ucg.h"
#include "Image_1.h"

static ucg_t ucg;

#define ROTATE_0 0
#define ROTATE_90 1
#define ROTATE_180 2
#define ROTATE_270 3
#define SIZE_IMAGE 128

void delay(uint16_t _ms){
    uint32_t _timer = 16000;
    while(_timer > 0){
        while(_ms > 0)
            _ms--;
        _timer--;
    }
}

int main(void){
    SystemCoreClockUpdate();
    TimerInit();
    Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
    ucg_ClearScreen(&ucg);
    ucg_SetFont(&ucg, ucg_font_helvR08_tf);
    ucg_SetColor(&ucg, 0,0,0,255);
    int rotate = ROTATE_0;
    while(1){
        for(int i=0; i< SIZE_IMAGE; i++){
            for(int j=0; j< SIZE_IMAGE; j++){
                ucg_SetColor(&ucg, 0,image1[ SIZE_IMAGE*i*3 + j*3 + 2],image1[SIZE_IMAGE*i*3 + j*3+1],image1[SIZE_IMAGE*i*3 + j*3]);
                ucg_DrawPixel(&ucg, j, i);
            }
        }
        delay(3000);
        rotate++;
        if(rotate > ROTATE_270) rotate = ROTATE_0;
        switch(rotate){
            case ROTATE_0:
             ucg_UndoRotate(&ucg);
                break;
            case ROTATE_90:
                ucg_SetRotate90(&ucg);
                break;
            case ROTATE_180:
                ucg_SetRotate180(&ucg);
                break;
            case ROTATE_270:
                ucg_SetRotate270(&ucg);
                break;
        }
    }
}
