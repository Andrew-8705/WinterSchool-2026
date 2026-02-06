import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

INPUT_CSV = 'strlen_data.csv'

def load_data():
    lengths = []
    impls = []
    results_map = {} # length -> [val1, val2...]

    try:
        with open(INPUT_CSV, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            header = next(reader)
            
            # Первая колонка Length, остальные - названия реализаций
            impls = header[1:]
            
            for row in reader:
                if not row: continue
                length = int(row[0])
                
                vals = []
                for v in row[1:]:
                    try:
                        vals.append(float(v))
                    except ValueError:
                        vals.append(np.nan)
                
                lengths.append(length)
                results_map[length] = vals
                
    except FileNotFoundError:
        print(f"Файл {INPUT_CSV} не найден! Запустите parse_strlen.py")
        sys.exit(1)
        
    return impls, lengths, results_map

def plot_strlen():
    impls, lengths, results_map = load_data()
    
    if not impls:
        print("Нет данных для отображения.")
        return

    # Подготовка данных для plot (массивы numpy)
    # Преобразуем словарь results_map в список списков по реализациям
    # data_by_impl[idx] = [cycle_len1, cycle_len2, ...]
    data_by_impl = [[] for _ in impls]
    
    for length in lengths:
        row_vals = results_map[length]
        for idx, val in enumerate(row_vals):
            data_by_impl[idx].append(val)

    lengths_np = np.array(lengths)

    # Настройка графиков
    plt.style.use('seaborn-v0_8-whitegrid')
    colors = plt.cm.tab10(np.linspace(0, 1, len(impls)))
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

    # --- ГРАФИК 1: Total Cycles (Log-Log) ---
    for idx, impl_name in enumerate(impls):
        cycles = np.array(data_by_impl[idx])
        
        # Фильтруем NaN (если для какой-то длины нет данных)
        mask = ~np.isnan(cycles)
        if not np.any(mask): continue
        
        ax1.loglog(lengths_np[mask], cycles[mask], '-o', label=impl_name, color=colors[idx], markersize=5)
    
    ax1.set_title('Strlen: Execution Time (Log-Log)', fontsize=14)
    ax1.set_xlabel('String Length (chars)', fontsize=12)
    ax1.set_ylabel('Total Cycles', fontsize=12)
    ax1.legend()
    ax1.grid(True, which="both", ls="-", alpha=0.3)

    # --- ГРАФИК 2: CPE (Cycles Per Element) ---
    for idx, impl_name in enumerate(impls):
        cycles = np.array(data_by_impl[idx])
        mask = ~np.isnan(cycles)
        if not np.any(mask): continue
        
        # CPE = Cycles / Length. 
        # Используем np.maximum(..., 1) чтобы не делить на 0, если длина строки 0
        cpe = cycles[mask] / np.maximum(lengths_np[mask], 1)
        
        ax2.plot(lengths_np[mask], cpe, '-o', label=impl_name, color=colors[idx], markersize=5)
    
    ax2.set_xscale('log')
    
    # Настройка оси Y для CPE
    # Обычно CPE < 10. Если Scalar очень медленный, можно увеличить до 20 или 50
    ax2.set_ylim(0, 10) 
    
    ax2.set_title('Cycles Per Character (CPE)', fontsize=14)
    ax2.set_xlabel('String Length (chars)', fontsize=12)
    ax2.set_ylabel('Cycles / Char', fontsize=12)
    ax2.legend()
    ax2.grid(True, which="both", ls="-", alpha=0.3)

    print("Графики построены.")
    plt.tight_layout()
    #plt.show()
    plt.savefig('strlen_res.png')

if __name__ == "__main__":
    plot_strlen()