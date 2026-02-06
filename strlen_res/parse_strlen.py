import os
import re
import csv
import glob

# Имя выходного файла
OUTPUT_CSV = 'strlen_data.csv'

def parse_txt_files():
    # Структура: data[length][label] = cycles
    parsed_data = {}
    all_labels = set()
    all_lengths = set()

    # Ищем txt файлы
    txt_files = glob.glob("*.txt")
    
    if not txt_files:
        print("Нет .txt файлов в текущей директории!")
        return

    print(f"Найдено файлов: {len(txt_files)}")

    for filepath in txt_files:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            if not lines:
                continue

            # 1. Читаем название реализации (первая строка)
            label = lines[0].strip()
            all_labels.add(label)
            print(f"Обработка '{filepath}' -> Реализация: '{label}'")

            # 2. Парсим файл
            current_len = -1
            
            # Регулярки
            # Ищет "Testing ... STRLEN with length 32"
            len_pattern = re.compile(r"with length (\d+)")
            # Ищет "122 cycles min"
            cycles_pattern = re.compile(r"(\d+) cycles min")

            for line in lines[1:]:
                # Ищем длину строки
                len_match = len_pattern.search(line)
                if len_match:
                    current_len = int(len_match.group(1))
                    continue

                # Ищем такты
                cycles_match = cycles_pattern.search(line)
                if cycles_match and current_len != -1:
                    cycles = int(cycles_match.group(1))
                    
                    all_lengths.add(current_len)
                    
                    if current_len not in parsed_data:
                        parsed_data[current_len] = {}
                    
                    parsed_data[current_len][label] = cycles
                    
                    # Сброс
                    current_len = -1

    # 3. Сохраняем в CSV
    # Сортируем реализации (Scalar первым)
    sorted_labels = sorted(list(all_labels))
    if 'Scalar' in sorted_labels:
        sorted_labels.remove('Scalar')
        sorted_labels.insert(0, 'Scalar')

    # Сортируем длины (числовая сортировка)
    sorted_lengths = sorted(list(all_lengths))

    with open(OUTPUT_CSV, 'w', newline='', encoding='utf-8') as csvfile:
        writer = csv.writer(csvfile)
        
        # Заголовок: Length, Label1, Label2...
        header = ['Length'] + sorted_labels
        writer.writerow(header)

        for length in sorted_lengths:
            row = [length]
            for label in sorted_labels:
                # Если данных нет, оставляем пусто
                val = parsed_data.get(length, {}).get(label, '')
                row.append(val)
            writer.writerow(row)

    print(f"\nДанные сохранены в {OUTPUT_CSV}")
    print(f"Всего уникальных длин: {len(sorted_lengths)}")

if __name__ == "__main__":
    parse_txt_files()