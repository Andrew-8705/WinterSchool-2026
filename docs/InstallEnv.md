
## RISC-V Syntacore Development Toolkit
1) Загрузить архив по ссылке [drive.google](https://drive.google.com/file/d/1GesPVEACp5imxOwvOnd0WWRrBswmG7RB/edit)
2) Скопировать архив в Home директорию в WSL
3) Распоковать архив
```
tar -xvf sc-dt-2023.11.tar.gz -C ${HOME}
```

или

1) pip install gdown
2) gdown https://drive.google.com/uc?id=1Jo7QiknzcLnO5EyvB6uJfe5EEiln9Uzr
    * В случае `Command 'gdown' not found` попробовать указать путь `~/.local/bin/gdown`
3) Распоковать архив
```
tar -xvf sc-dt-2023.11.tar.gz -C ${HOME}
```

## Gem5
1) Загрузить архив по ссылке [drive.google](https://drive.google.com/file/d/1wp2PaDxvayvuTVkDUnmdXV7JaQ4-kP3b/view?usp=sharing)
2) Скопировать архив в директорию <path-to-repo>/UNN-WinterSchool-2025/gem5 в WSL
3) Распоковать архив
```
tar -xvf gem5.tar.gz
```

или

1) pip install gdown
2) gdown https://drive.google.com/uc?id=1wp2PaDxvayvuTVkDUnmdXV7JaQ4-kP3b
    * В случае `Command 'gdown' not found` попробовать указать путь `~/.local/bin/gdown`
3) Распоковать архив
```
tar -xvf gem5.tar.gz
```

### Сборка Gem5 из исходных файлов
Клонирование:\
``
git clone https://github.com/gem5/gem5.git && cd gem5
``\
Сборка:\
``
scons --ignore-style --without-protobuf defconfig build/RISCV build_opts/RISCV
``\
``
scons --ignore-style setconfig --without-protobuf build/RISCV USE_SYSTEMC=n RUBY_PROTOCOL_MESI_THREE_LEVEL=y
``\
``
scons --ignore-style -j 4 build/RISCV/gem5.opt
``