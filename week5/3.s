#include <malloc.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <xmmintrin.h>

float dot_product(int N, const float* A, const float* B)
{
    __m128 res = _mm_setzero_ps();
    int i;
    for (i = 0; i < N; i += 4) {
        if (N - i < 4) {
            break;
        }
        __m128 a = _mm_load_ps(&A[i]);
        __m128 b = _mm_load_ps(&B[i]);
        a = _mm_mul_ps(a, b);
        res = _mm_add_ps(res, a);
    }
    for (; i < N; ++i) {
        __m128 a = _mm_load_ss(&A[i]);
        __m128 b = _mm_load_ss(&B[i]);
        a = _mm_mul_ss(a, b);
        res = _mm_add_ps(res, a);
    }
    res = _mm_hadd_ps(res, res);
    res = _mm_hadd_ps(res, res);
    return _mm_cvtss_f32(res);
}

int main()
{
    int M;
    int N;
    scanf("%d %d", &M, &N);
    float** A;
    float** B;
    float** result;
    A = (float**)malloc(M * sizeof(float*));
    B = (float**)malloc(M * sizeof(float*));
    result = (float**)malloc(M * sizeof(float*));
    for (int i = 0; i < M; ++i) {
        A[i] = (float*)aligned_alloc(16, N * sizeof(float));
        B[i] = (float*)aligned_alloc(16, N * sizeof(float));
        result[i] = (float*)aligned_alloc(16, M * sizeof(float));
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%f", &A[i][j]);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%f", &B[j][i]);
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            float value = dot_product(N, A[i], B[j]);
            result[i][j] = value;
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%.4f ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < M; ++i) {
        free(A[i]);
        free(B[i]);
        free(result[i]);
    }
    free(A);
    free(B);
    free(result);

    return 0;
}
