/*
 * gpio_output.c
 */
#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>
#include "gpio_test.h"

/* static関数のプロトタイプ宣言 */
static int check_key_input(void);

int main(int argc, char **argv)
{
#if !defined(TEST_FOR_JETSON_TX2_NX)
  const char *chipname = "gpiochip0";
#else
  const char *chipname = "gpiochip1";
#endif
  const char *appname = "jetson_gpio_output_test";
  struct gpiod_chip *chip;
  struct gpiod_line *line_out;
  int val = 0;

  // GPIOデバイスをオープンする
  chip = gpiod_chip_open_by_name(chipname);

  // 指定したGPIOポートのハンドラ取得
  line_out = gpiod_chip_get_line(chip, GPIO_OUTPUT_LINE_OFFSET);

  // ポート予約(出力設定)
  gpiod_line_request_output(line_out, appname, 0);

  printf("Jetson GPIO Output Test: \nPin31: \n");

  for (;;) {
    val ^= 0x1;
    // GPIOポートへの出力値設定
    gpiod_line_set_value(line_out, val);
    printf("%c", (val == 1) ? 'H' : 'L');
    fflush(stdout);

    //usleep(500 * 1000);
    usleep(1000 * 1000);
    
    if (check_key_input())	// Enterキーの入力で抜ける
      break;
  }

  // ポート予約の解除
  gpiod_line_release(line_out);

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
