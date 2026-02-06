#include <scalar.h>

void gemv_scalar(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
{
    const float* a_ptr = a;
    for(size_t j = 0; j < m; j++) {
        float temp = 0.0;
        for(size_t i = 0; i < n; i++) {
            temp += a_ptr[i] * x[i];
        }
        y[j] += alpha * temp;
        a_ptr += n;
    }
}

// void gemv_scalar(size_t m, size_t n, float alpha, const float* restrict a, const float* restrict x, float* restrict y)
// {
//     const float* a_ptr = a;
//     #pragma clang loop interleave_count(4)
//     for(size_t j = 0; j < m; j++) {
//         float temp = 0.0;
//         #pragma clang loop interleave_count(4)
//         for(size_t i = 0; i < n; i++) {
//             temp += a_ptr[i] * x[i];
//         }
//         y[j] += alpha * temp;
//         a_ptr += n;
//     }
// }



// void gemv_scalar(size_t m, size_t n, float alpha, const float* restrict a, const float* restrict x, float* restrict y)
// {

//     #pragma clang loop unroll_count(4)
//     for(size_t j = 0; j < m; j++) {
        
//         float temp = 0.0f;
//         const float* row_ptr = a + j * n;

//         #pragma clang loop vectorize(disable) interleave_count(4)
//         for(size_t i = 0; i < n; i++) {
//             temp = __builtin_fmaf(row_ptr[i], x[i], temp);
//         }
        
//         y[j] += alpha * temp;
//     }
// }

// void gemv_scalar(size_t m, size_t n, float alpha, const float* a, const float* x, float* y)
// {
//     for(size_t j = 0; j < m; j++) {
//         const float* row_ptr = a + j * n;
        
//         // Используем 4 независимых аккумулятора
//         float t0 = 0.0f;
//         float t1 = 0.0f;
//         float t2 = 0.0f;
//         float t3 = 0.0f;

//         size_t i = 0;

//         // Основной цикл: обрабатываем по 4 элемента за итерацию
//         for(; i + 3 < n; i += 4) {
//             t0 += row_ptr[i + 0] * x[i + 0];
//             t1 += row_ptr[i + 1] * x[i + 1];
//             t2 += row_ptr[i + 2] * x[i + 2];
//             t3 += row_ptr[i + 3] * x[i + 3];
//         }

//         // Собираем результаты из четырех аккумуляторов
//         float final_temp = (t0 + t1) + (t2 + t3);

//         // Хвост цикла: если n не делится на 4
//         for(; i < n; i++) {
//             final_temp += row_ptr[i] * x[i];
//         }

//         y[j] += alpha * final_temp;
//     }
// }