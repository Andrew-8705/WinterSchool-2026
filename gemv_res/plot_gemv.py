import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

INPUT_CSV = 'gemv_data.csv'

def load_data():
    sizes = []
    impls = []
    results_map = {} # (M, N) -> [val1, val2...]

    try:
        with open(INPUT_CSV, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            header = next(reader)
            
            # Первая колонка M, вторая N, остальные - названия реализаций
            impls = header[2:]
            
            for row in reader:
                if not row: continue
                m = int(row[0])
                n = int(row[1])
                
                # Читаем значения тактов
                vals = []
                for v in row[2:]:
                    try:
                        vals.append(float(v))
                    except ValueError:
                        vals.append(np.nan)
                
                size_key = (m, n)
                sizes.append(size_key)
                results_map[size_key] = vals
                
    except FileNotFoundError:
        print(f"Файл {INPUT_CSV} не найден! Сначала запустите parse_results.py")
        sys.exit(1)
        
    return impls, sizes, results_map

def plot_analysis():
    impls, all_sizes, results = load_data()
    
    plt.rcParams.update({
        'font.size': 30,           # Общий размер шрифта (базовый)
        'axes.titlesize': 20,      # Размер заголовка графика
        'axes.labelsize': 20,      # Размер подписей осей (X и Y)
        'xtick.labelsize': 20,     # Размер цифр/меток на оси X
        'ytick.labelsize': 20,     # Размер цифр/меток на оси Y
        'legend.fontsize': 20,     # Размер текста в легенде
        'figure.titlesize': 20     # Размер общего заголовка (если есть)
    })

    if not impls:
        print("Нет данных для отображения.")
        return

    # Разделяем размеры на квадратные и прямоугольные
    square_sizes = [s for s in all_sizes if s[0] == s[1]]
    square_sizes.sort(key=lambda x: x[0]) 
    
    rect_sizes = [s for s in all_sizes if s[0] != s[1]]
    rect_sizes.sort(key=lambda x: (x[0]*x[1], x[0]))

    # Настройка общих стилей
    plt.style.use('seaborn-v0_8-whitegrid')
    colors = plt.cm.tab10(np.linspace(0, 1, len(impls)))

    # ==========================================
    # ГРАФИК 1: Квадратные Матрицы (CPE)
    # ==========================================
    if square_sizes:
        plt.figure(figsize=(12, 7))
        x_labels = [f"{s[0]}" for s in square_sizes]
        x_nums = [s[0] for s in square_sizes]
        
        for idx, impl_name in enumerate(impls):
            cpe_data = []
            valid_x = []
            for i, size in enumerate(square_sizes):
                cycles = results[size][idx]
                if np.isnan(cycles): continue
                
                elements = size[0] * size[1]
                cpe_data.append(cycles / elements)
                valid_x.append(x_nums[i])
            
            if cpe_data:
                plt.plot(valid_x, cpe_data, marker='o', label=impl_name, 
                         color=colors[idx], linewidth=1.5, alpha=0.8)

        plt.title('CPE (Lower is Better) BananaPi', fontsize=18)
        plt.xlabel('Matrix Dimension N (NxN)', fontsize=18)
        plt.ylabel('CPE (Cycles / N^2)', fontsize=18)
        plt.xscale('log')
        plt.yscale('log')
        plt.xticks(x_nums, x_labels, rotation=45)
        plt.grid(True, which="both", ls="-", alpha=0.3)
        plt.legend(bbox_to_anchor=(1.02, 1), loc='upper left')
        plt.tight_layout()
        plt.savefig('gemv_square_cpe.png', dpi=300)
        print("График квадратных матриц сохранен в gemv_square_cpe.png")
        plt.close() # Закрываем текущую фигуру

    # ==========================================
    # ГРАФИК 2: Прямоугольные Матрицы (Bar Chart)
    # ==========================================
    if rect_sizes:
        plt.figure(figsize=(12, 7))
        x_pos = np.arange(len(rect_sizes))
        bar_width = 0.8 / len(impls)
        
        for idx, impl_name in enumerate(impls):
            cycles_data = []
            for size in rect_sizes:
                cycles = results[size][idx]
                cycles_data.append(cycles if not np.isnan(cycles) else 0)
            
            offset = (idx - len(impls)/2) * bar_width + bar_width/2
            plt.bar(x_pos + offset, cycles_data, width=bar_width, label=impl_name, color=colors[idx])
            plt.title('Rectangular Matrices: Total Cycles (Log Scale)', fontsize=18)
        plt.ylabel('Total Cycles', fontsize=18)
        plt.yscale('log')
        
        tick_labels = [f"{s[0]}x{s[1]}" for s in rect_sizes]
        plt.xticks(x_pos, tick_labels, fontsize=18, rotation=0)
        plt.legend(bbox_to_anchor=(1.02, 1), loc='upper left')
        plt.tight_layout()
        plt.savefig('gemv_rect_cycles.png', dpi=300)
        print("График прямоугольных матриц сохранен в gemv_rect_cycles.png")
        plt.close()

if __name__ == "__main__":
    plot_analysis()