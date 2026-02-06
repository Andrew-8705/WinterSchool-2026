import os
import re
import csv
import glob

# Настройки
OUTPUT_CSV = 'gemv_data.csv'

def parse_txt_files():
    parsed_data = {}
    all_labels = set()
    all_sizes = set()

    txt_files = glob.glob("*.txt")
    
    if not txt_files:
        print("Нет .txt файлов в текущей директории!")
        return

    print(f"Найдено файлов: {len(txt_files)}")

    for filepath in txt_files:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
            
            if not lines:
                continue

            # 1. Читаем название реализации из первой строки
            label = lines[0].strip()
            all_labels.add(label)
            print(f"Обработка файла '{filepath}' -> Реализация: '{label}'")

            current_m = 0
            current_n = 0
            
            # --- ИЗМЕНЕННЫЕ РЕГУЛЯРНЫЕ ВЫРАЖЕНИЯ ---
            
            # Ищет "Testing", затем любые символы (.*?), затем "GEMV", пробел и MxN
            # Это проигнорирует тот странный символ между Testing и GEMV
            size_pattern = re.compile(r"Testing.*?GEMV\s+(\d+)x(\d+)")
            
            # Ищет такты (оставляем как было)
            cycles_pattern = re.compile(r"(\d+)\s+cycles min")

            for line in lines[1:]:
                line = line.strip()
                if not line:
                    continue

                # Ищем размер матрицы
                size_match = size_pattern.search(line)
                if size_match:
                    current_m = int(size_match.group(1))
                    current_n = int(size_match.group(2))
                    continue

                # Ищем количество тактов (min)
                cycles_match = cycles_pattern.search(line)
                if cycles_match and current_m > 0 and current_n > 0:
                    cycles = int(cycles_match.group(1))
                    
                    size_key = (current_m, current_n)
                    all_sizes.add(size_key)
                    
                    if size_key not in parsed_data:
                        parsed_data[size_key] = {}
                    
                    parsed_data[size_key][label] = cycles
                    
                    # Сбрасываем, чтобы ждать следующего блока Testing
                    current_m = 0
                    current_n = 0

    # 3. Сохранение в CSV
    sorted_labels = sorted(list(all_labels))
    if 'Scalar' in sorted_labels:
        sorted_labels.remove('Scalar')
        sorted_labels.insert(0, 'Scalar')

    sorted_sizes = sorted(list(all_sizes), key=lambda x: (x[0], x[1]))

    with open(OUTPUT_CSV, 'w', newline='', encoding='utf-8') as csvfile:
        writer = csv.writer(csvfile)
        header = ['M', 'N'] + sorted_labels
        writer.writerow(header)

        for size in sorted_sizes:
            row = [size[0], size[1]]
            for label in sorted_labels:
                val = parsed_data.get(size, {}).get(label, '')
                row.append(val)
            writer.writerow(row)

    print(f"\nДанные успешно сохранены в {OUTPUT_CSV}")
    print(f"Всего уникальных размеров матриц: {len(sorted_sizes)}")
    print(f"Реализации: {sorted_labels}")

if __name__ == "__main__":
    parse_txt_files()