# Jetson

NVIDIA Jetsonシリーズ向けのコードを置く

# Installation

libgpiodを使用する。確か、パッケージgpiodだけインストールすればよかったような気がする。

インストール方法:

```
$ sudo apt install gpiod
```

# Usage

NVIDIA Jetsonシリーズにて使用する。
ターミナルを2つ開き、1つでgpio_inputを、もう1つでgpio_outputを、それぞれで実行する

gpio_inputの実行:

```
$ ./gpio_input
```

gpio_outputの実行:

```
$ ./gpio_output
```


