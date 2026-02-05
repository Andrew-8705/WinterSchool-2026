import matplotlib.pyplot as plt
import numpy as np

# ==========================================
# 1. ВВОД ДАННЫХ
# ==========================================

# Список ваших реализаций
impls = ['Scalar', 'm8', 'm4', 'm2', 'm1', 'Unroll (4 x m2)', 'Unroll (2 x m4)']

# Размеры матриц (M, N)
# Квадратные
square_sizes = [
    (2,2), (3,3), (4,4), (5,5), (7,7), 
    (16,16), (31,31), (32,32), (33,33), 
    (64,64), (127,127), (128,128), 
    (256,256), (257,257), 
    (512,512), (1023,1023), (1024,1024), 
    (2048,2048), (2049,2049), (2053,2053)
]

# Прямоугольные
rect_sizes = [
    (2048, 32), (32, 2048), 
    (2048, 256), (256, 2048)
]

# СЛОВАРЬ РЕЗУЛЬТАТОВ
# Ключ: (M, N) кортеж
# Значение: Список тактов [Scalar, m8, m4, m2, m1, Unroll_4xm2, Unroll_2xm4]
# Порядок в списке должен совпадать со списком impls выше
results = {
    # --- Квадратные ---
    (2, 2):       [179, 384, 256, 215, 194, 394, 278],
    (3, 3):       [217, 462, 312, 248, 222, 490, 394],  
    (4, 4):       [263, 594, 374, 280, 238, 303, 395],
    (5, 5):       [323, 656, 430, 315, 271, 436, 524],  
    (7, 7):       [467, 923, 941, 382, 326, 665, 639],  
    (16, 16):     [1592, 1732, 1058, 689, 691, 730, 1091],
    (31, 31):     [5388, 3166, 1926, 1525, 1785, 1717, 2032],  
    (32, 32):     [5621, 3261, 1977, 1578, 1762, 1534, 2020],
    (33, 33):     [5990, 3363, 2675, 1970, 2193, 1948, 2652],  
    (64, 64):     [21333, 6315, 5001, 4255, 5450, 3840, 4888],
    (127, 127):   [84303, 25632, 21602, 20996, 25823, 25621, 28293],  
    (128, 128):   [84923, 25636, 21200, 20292, 24842, 25316, 26918],
    (256, 256):   [336433, 86665, 78223, 77110, 97235, 87678, 100694],
    (257, 257):   [339475, 98398, 87238, 85664, 106221, 92623, 112637],  
    (512, 512):   [1359824, 371567, 332941, 342681, 410954, 1340786, 708974],
    (1023, 1023): [5599972, 1637417, 1581560, 1586592, 1897887, 14574771, 2391153],  
    (1024, 1024): [5591504, 1581128, 1516795, 1530960, 1818081, 10035167, 2176783],
    (2048, 2048): [23810131, 7531349, 7642177, 7770579, 8688861, 13496967, 8095951],
    (2049, 2049): [23865797, 7788941, 7529628, 7786084, 8801972, 14896799, 8080604],
    (2053, 2053): [23971776, 7812389, 7602116, 7768586, 8790390, 12009635, 8444070],
    
    # --- Прямоугольные ---
    (2048, 32):   [354359, 223112, 119472, 102853, 115131, 112290, 121459],  
    (32, 2048):   [356818, 92737, 93008, 92651, 115133, 210499, 77017],  
    (2048, 256):  [2690216, 771670, 687237, 685623, 822274, 2464470, 3423430],  
    (256, 2048):  [2925474, 866682, 856589, 865341, 984992, 1980672, 955166]  
}

# ==========================================
# 2. ПОСТРОЕНИЕ ГРАФИКОВ
# ==========================================

def plot_analysis():
    # Настройка стилей
    plt.style.use('seaborn-v0_8-whitegrid')
    colors = plt.cm.tab10(np.linspace(0, 1, len(impls)))
    
    # --- ГРАФИК 1: CPE для Квадратных Матриц ---
    # Сортируем размеры по N
    sq_sorted = sorted(square_sizes, key=lambda x: x[0])
    x_labels = [f"{s[0]}" for s in sq_sorted]
    x_nums = [s[0] for s in sq_sorted]
    
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(14, 12))
    plt.subplots_adjust(hspace=0.4)

    # Рисуем линии
    for idx, impl in enumerate(impls):
        cpe_data = []
        for size in sq_sorted:
            cycles = results[size][idx]
            elements = size[0] * size[1]
            cpe_data.append(cycles / elements)
        
        # Маркеры: круг для степеней 2, звезда для остальных
        ax1.plot(x_nums, cpe_data, marker='o', label=impl, color=colors[idx], linewidth=1.5, alpha=0.8)

    ax1.set_title('Square Matrices: Cycles Per Element (Lower is Better)', fontsize=14)
    ax1.set_xlabel('Matrix Dimension N (NxN)', fontsize=12)
    ax1.set_ylabel('CPE (Cycles / N^2)', fontsize=12)
    ax1.set_xscale('log')
    ax1.set_xticks(x_nums)
    ax1.set_xticklabels(x_labels, rotation=45)
    ax1.grid(True, which="both", ls="-", alpha=0.3)
    ax1.legend(bbox_to_anchor=(1.02, 1), loc='upper left')

    # --- ГРАФИК 2: Прямоугольные Матрицы (Bar Chart) ---
    # Группируем по парам (Tall vs Wide)
    bar_width = 0.1
    x_pos = np.arange(len(rect_sizes))
    
    for idx, impl in enumerate(impls):
        cycles_data = []
        for size in rect_sizes:
            cycles = results[size][idx]
            cycles_data.append(cycles)
        
        # Сдвигаем бары
        ax2.bar(x_pos + idx * bar_width, cycles_data, width=bar_width, label=impl, color=colors[idx])

    ax2.set_title('Rectangular Matrices: Shape Analysis (Total Cycles)', fontsize=14)
    ax2.set_ylabel('Total Cycles (Log Scale)', fontsize=12)
    ax2.set_yscale('log')
    
    # Подписи оси X
    tick_labels = [f"{s[0]}x{s[1]}\n{'Tall' if s[0]>s[1] else 'Wide'}" for s in rect_sizes]
    ax2.set_xticks(x_pos + bar_width * (len(impls) - 1) / 2)
    ax2.set_xticklabels(tick_labels, fontsize=11)
    ax2.legend(bbox_to_anchor=(1.02, 1), loc='upper left')

    print("Графики построены.")
    plt.tight_layout()
    plt.show()
    #plt.savefig('gemv_res.png', dpi=300)

if __name__ == "__main__":
    plot_analysis()