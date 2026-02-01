# Optimization practice for UNN Winter School 2025

Репозиторий для практической работы по оптимизации алгоритмов для архитектуры RISC-V и работы с симулятором Gem5.

## Алгоритм работы над функцией:

1) Ознакомление с алгоритмом и его скалярным референсом.
2) Добавить тесты на производительность в папке [perf](perf).
3) Анализ производительности скалярной версии.
    * Запуск на RISC-V плате
    * Запуск скалярной версии на симуляторе, анализ трасс исполнения.
    * Улучшение кода и повторные замеры
4) Реализация векторной версии алгоритма.
    * Проверка корректности с помощью функциональных тестов на Qemu
5) Анализ производительности векторной версии
    * Запуск на RISC-V плате
    * Запуск векторной версии на симуляторе, анализ трасс исполнения.
    * Исследование возможности улучшения
6) Формирование выводов по исследуемому алгоритму
    * Краткое описание алгоритма. Обзор и основные сложности реализации.
    * Используемые инструкции в алгоритме и их влияние на производительность.
    * Анализ различия замеров на плате и симуляторе.
    * Выводы по анализу трасс исполнения.

## Структура репозитория

* [lib](lib) - библиотека с реализациями алгоритмов
* [perf](perf) - бенчмарки для замеров производительности алгоритмов
* [test](test) - функциональные тесты для проверки корректности алгоритмов

## Сборка проекта

Сначала нужно скачать кросс-компилятор. [Краткая инструкция](docs/InstallEnv.md)

Для сборки проекта можно использовать скрипт [build.sh](build.sh). Перед запуском необходимо установить пути для кросс-компиляторов `C_COMPILER_PATH` и `CXX_COMPILER_PATH` и выставить соответствующие параметры сборки.

Опции конфигурации проекта:
* `ENABLE_TEST` - Сборка тестов (`ON`\\`OFF`)
* `ENABLE_BENCH` -  Сборка бенчмарков (`ON`\\`OFF`)
* `BUILD_TYPE` - Режим сборки (`Release`\\`Debug`)
* `BUILD_FOLDER` - Папка для артефактов сборки
* `BUILD_STATIC` - Включить статическую линковку (`ON`\\`OFF`)

## Пример запуска с помощью QEMU

``
qemu-riscv64 -cpu rv64,v=on,vlen=256 ./_build/test/abs_rvv_test
``
где `-cpu rv64,v=on,vlen=256` нужен для поддержки RVV

В случае ошибки:\
``
qemu-riscv64: Could not open '/lib/ld-linux-riscv64-lp64d.so.1': No such file or directory
``\
необходимо сконфигурировать проект с `-DBUILD_STATIC=ON` или добавить ключ запуска `-L <path-to-toolchain>/riscv-gcc/sysroot/`

## Отладка кода на RISC-V

[Краткая инструкция](docs/How2Debug.md)

## Пример запуска с помощью Gem5

Сначала нужно скачать gem5. [Краткая инструкция](docs/InstallEnv.md)

``
<path-to-gem5>/gem5.opt --debug-flags=O3PipeView --debug-file=./pipeview.out ./gem5/configuration.py ./_build/perf/abs_scalar_perf
``

где:\
`--debug-flags=O3PipeView` нужен для генерации трасс исполнения (kanata трасс).\
`--debug-file=./trace.out` название файла с трассой исполнения.

### Проблемы с запуском Gem5
1) При любой проблеме сначала лучше установить необходимые пакеты\
    `sudo apt-get install -y gcc-10 g++-10 build-essential libncurses5 cmake curl wget git m4 scons telnet zlib1g zlib1g-dev jq \
    libgoogle-perftools-dev python3-dev python3-pip \
    python-is-python3 libboost-all-dev pkg-config graphviz \
    lsb-release software-properties-common gnupg unzip`
2) ./gem5.opt: error while loading shared libraries: libpython3.10.so.1.0: cannot open shared object file: No such file or directory
    * `sudo add-apt-repository ppa:deadsnakes/ppa`
    * `sudo apt update`
    * `sudo apt-get install libpython3.10-dev`
3) ./gem5.opt: error while loading shared libraries: libprotobuf.so.23: cannot open shared object file: No such file or directory
    * `sudo ln <path-to-repo>/gem5/bin/libprotobuf.so.23.0.4 /lib/x86_64-linux-gnu/libprotobuf.so.23`

## Установка программы для просмотра трасс исполнения

1) Скачать релизный билд https://github.com/shioyadan/Konata/releases/tag/v0.39 (konata-win32-x64.zip)
2) Распаковать, запустить konata.exe
3) Открыть трассу в программе konata (можно drug&drop)


## Поиск тестируемой функции на kanata трассе

Самый надежный способ - поиск по адресу инструкции. Чтобы его узнать, сначала нужно получить дизасемблер бенчмарка, который запускался с помощью Gem5:

`<path-to-sc-dt>/sc-dt/riscv-gcc/bin/riscv64-unknown-linux-gnu-objdump -d ./_build/perf/axpby_scalar_perf > objdump_scal.txt`

В файле с дизасеблером найти нужную функцию через поиск (напр. axpby_scalar) и взять адрес первой инструкции или функции.

Далее поиском (Cntr+F) в программе для просмотра трасс вставить этот адрес. Также поиском можно искать по названиям инструкций (если это RVV функция, то, например, vsetvli).



