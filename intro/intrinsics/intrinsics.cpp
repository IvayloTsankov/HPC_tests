#include <xmmintrin.h>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <cmath>

static long long int SLOG_get_utc_millisec()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void calculateSSE(int start, int end)
{
    int size = end - start + 1;

    // we use aligned memory, because SSE instructions are really slow
    // working on unaligned memory
    float* result = (float*)_aligned_malloc(size * sizeof(float), 16);

    __m128 x;
    __m128 delta_x = _mm_set_ps1(4.0f);
    __m128 y = _mm_set_ps1(1.0f);
    __m128* sse_result = (__m128*)result;

    const int sse_length = size / 4;
    x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
    for (int loop = 0; loop < 100000; ++loop)
    {
        for (int i = 0; i < sse_length; ++i)
        {
            __m128 sqrt_result = _mm_sqrt_ps(x);
            sse_result[i] = _mm_div_ps(sqrt_result, x);
            //sse_result[i] = _mm_add_ps(x, y);

            // move x value to next 4 numbers
            x = _mm_add_ps(x, delta_x);
        }        
    }
}

void calculate(int start, int end)
{
    int size = end - start + 1;
    float* result = (float*)_aligned_malloc(size * sizeof(float), 16);

    for (int loop = 0; loop < 100000; ++loop)
    {
        float x = 1.0f;
        for (int i = 0; i < size; ++i)
        {
            result[i] = sqrt(x) / x;
            x += 1.0f;
        }
    }
}

int main()
{
    long long start = SLOG_get_utc_millisec();

    //calculate(1, 64000);
    calculateSSE(1, 64000);
    printf("Time taken: %d\n", SLOG_get_utc_millisec() - start);
    printf("Hello SSE\n");
    return 0;
}

