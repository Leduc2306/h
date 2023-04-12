#include <stdint.h>
#include <system_stm32f4xx.h>

#include <stm32f401re_gpio.h>
#include <timer.h>
#include <Ucglib.h>
static ucg_t ucg;

#define DISPLAY_WIDTH 16
#define PRINT_STRING  5000
#define CLEAR_STRING_AFTER  500
static void delay(void);

void printStringFirst(void);
void printStringSecond(void);
void clearScreenStringFirst(void);
void clearScreenStringSecond(void);

/* Tren cung 1 dong
 * void printStringFirst(void) {
	ucg_DrawStringLine(&ucg, 0, 26, 0, "I love Embedded", "and I love programming");
 	TimerStart("str1", PRINT_STRING, 0, (void*) clearScreenStringFirst, NULL);
}

void printStringSecond(void) {
 	ucg_DrawStringLine(&ucg, 0, 26, 0, "Toi la hoang", "va toi rat vui");
 	TimerStart("str2", PRINT_STRING, 0, (void*) clearScreenStringSecond, NULL);
}
 */
/*  Tren hai dong khac nhau
 *void printStringFirst(void) {
    ucg_DrawString(&ucg, 0, 16, 0, "I love Embedded");
    TimerStart("str1", PRINT_STRING, 0, (void*) clearScreenStringFirst, NULL);
}

void printStringSecond(void) {
    ucg_DrawString(&ucg, 0, 32, 0, "Toi la hoang");
    TimerStart("str2", PRINT_STRING, 0, (void*) clearScreenStringSecond, NULL);
}
 *

 */
void printStringFirst(void) {
	ucg_DrawString(&ucg, 0, 26, 0, "I love Embedded");
 	TimerStart("str1", PRINT_STRING, 0, (void*) clearScreenStringFirst, NULL);
}
void clearScreenStringFirst(void) {
 	ucg_ClearScreen(&ucg);
 	TimerStart("clear screen string first", CLEAR_STRING_AFTER, 0, (void*) printStringSecond, NULL);
}
void printStringSecond(void) {
 	ucg_DrawString(&ucg, 0, 26, 0, "Toi la hoang");
 	TimerStart("str2", PRINT_STRING, 0, (void*) clearScreenStringSecond, NULL);
}
void clearScreenStringSecond(void) {
 	ucg_ClearScreen(&ucg);
 	TimerStart("clear screen string second", CLEAR_STRING_AFTER, 0, (void*) printStringFirst, NULL);

}
static void delay(void) {
 	for (uint32_t i = 0; i < 500000; i++);
}

int main(void) {
 	SystemCoreClockUpdate();
 	TimerInit();

 	Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);

 	ucg_ClearScreen(&ucg);
 	ucg_SetFont(&ucg, ucg_font_helvR08_tf);
 	ucg_SetColor(&ucg, 0, 255, 255, 255);

 	ucg_SetRotate180(&ucg);
 	printStringFirst();


 while (1) {
  	processTimerScheduler();
	}
}
