# Отладка кода на RISC-V

## Отладка QEMU + GDB

1) В первой консоли запустить QEMU \
``
qemu-riscv64 -g 1234 -cpu c910v ./_build/perf/dft_perf
``
2) Во второй консоли запустить cross GDB \
``
riscv64-unknown-linux-gnu-gdb ./_build/perf/dft_perf
``
3) В консоли GDB подключиться к QEMU \
``
target remote localhost:1234
``
4) Продолжить работу как с обычным GDB
    * Moжно включить Text User Interface (TUI)\
    ``
    tui enable
    ``
    * При ошибке ``Cannot enable the TUI: error opening terminal [TERM=xterm-256color]`` может помочь:
        ```
        export TERMINFO=/usr/share/terminfo
        export TERM=xterm-basic
        sudo apt-get install  ncurses-term
        ```

## Интеграция в VSCode

1) Открыть конфигурации дебагера в VSCode \
<img src="images/VScode_debug_conf.png" width="250" height="200" />

2) Добавить конфигурацию из файла [launch.json](launch.json)
    * В файле конфигурации необходимо выставить:
        * `program` - путь до отлаживаемой программы
        * `cwd` - путь до проекта
        * `miDebuggerPath` - путь до Cross GDB
        * `miDebuggerServerAddress` - адрес и порт соеденения.
        * И свои флаги на усмотрение. [Документация](https://code.visualstudio.com/docs/cpp/launch-json-reference).

3) Запустить QEMU \
``
qemu-riscv64 -g 1234 -cpu c910v ./_build/perf/dft_perf
``

4) Запустить Cross GDB через оболочку VSCode

## Удаленная отладка на RISC-V плате

Алгоритм аналогичен отладке с помощью QEMU, только в первом шаге нужно запустить gdbserver\
``
gdbserver :1234 ./dft_perf
``\
При подключении в консоли GDB на хосте localhost заменить на IP платы.