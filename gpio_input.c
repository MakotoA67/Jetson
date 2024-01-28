/*
 * gpio_input.c
 */
#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>
#include "gpio_test.h"

/* static関数のプロトタイプ宣言 */
static int check_key_input(void);

/* テストモード */
#define	OUTPUT_ANOTHER_PORT_WHEN_DETECTING_INPUT

int main(int argc, char **argv)
{
  const char *chipname = "gpiochip0";
  const char *appname = "jetson_gpio_input_test";
  struct gpiod_chip *chip;
  struct gpiod_line *line_in, *line_out_2;
  int val;
#ifdef OUTPUT_ANOTHER_PORT_WHEN_DETECTING_INPUT
  int prev_val = -1;
#endif

  // GPIOデバイスをオープンする
  chip = gpiod_chip_open_by_name(chipname);

  // 指定したGPIOポートのハンドラ取得
  line_in = gpiod_chip_get_line(chip, GPIO_INPUT_LINE_OFFSET);

  // ポート予約(入力設定)
  gpiod_line_request_input(line_in, appname);

#ifdef OUTPUT_ANOTHER_PORT_WHEN_DETECTING_INPUT
  // 指定されたGPIOポートのハンドラ取得
  line_out_2 = gpiod_chip_get_line(chip, GPIO_OUTPUT_LINE_OFFSET_2);

  // ポート予約(出力設定)
  gpiod_line_request_output(line_out_2, appname, 0);
#endif
  
  printf("Jetson GPIO Input Test: \nPin12: \n");

  for (;;) {
#ifndef OUTPUT_ANOTHER_PORT_WHEN_DETECTING_INPUT
    // GPIOポートの入力値取得
    val = gpiod_line_get_value(line_in);
    printf("%c", (val == 1) ? 'H' : 'L');
    fflush(stdout);

    usleep(200 * 1000);
#else
    val = gpiod_line_get_value(line_in);
    if (val != prev_val) {
      gpiod_line_set_value(line_out_2, val);
      printf("%c", (val == 1) ? 'H' : 'L');
      fflush(stdout);
    }
    prev_val = val;
#endif
    
    if (check_key_input())	// Enterキーの入力で抜ける
      break;
  }

  // ポート予約の解除
  gpiod_line_release(line_in);
#ifdef OUTPUT_ANOTHER_PORT_WHEN_DETECTING_INPUT
  // ポート予約の解除
  gpiod_line_release(line_out_2);
#endif

  // GPIOデバイスをクローズする
  gpiod_chip_close(chip);
  
  return 0;
}

/*
 * check_key_input()
 * キー入力チェック 
 * Enterキーまで入力されると検知される
 */
static int check_key_input(void)
{
  fd_set 		fds;
  struct timeval	timeout;

  FD_ZERO(&fds);
  FD_SET(0, &fds);

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  return select(0+1, &fds, NULL, NULL, &timeout);
}
