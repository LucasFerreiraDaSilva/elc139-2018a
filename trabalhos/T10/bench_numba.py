import numpy as np
import numba
import time


######################## Parâmetros da execução #########################

repeat = 4000        # Número de repetições do cálculo do produto vetorial
vec_size = 1000000   # Tamanho dos vetores

#########################################################################

# Implementação utilizando njit (como a documentação sugere)
@numba.njit(parallel=True)
def dot_njit(a, b, n, repeat):
    for k in range(repeat):
        dot = 0.0
        for i in range(n):
            dot += a[i] * b[i]
    return dot

# Implementação utilizando jit (como a documentação sugere)
@numba.jit(nopython=True, parallel=True)
def dot_jit(a, b, n, repeat):
    for k in range(repeat):
        dot = 0.0
        for i in range(n):
            dot += a[i] * b[i]
    return dot

# Implementação utilizando variável float do numpy
@numba.njit(parallel=True)
def dot_njit_npFloat(a, b, n, repeat):
    for k in range(repeat):
        dot = np.float32(0.0)
        for i in range(n):
            dot += a[i] * b[i]
    return dot


@numba.jit(nopython=True, parallel=True)
def dot_jit_npFloat(a, b, n, repeat):
    for k in range(repeat):
        dot = np.float32(0.0)
        for i in range(n):
            dot += a[i] * b[i]
    return dot

# Implementação utilizando numba.prange
@numba.njit(parallel=True)
def dot_njit_prange(a, b, n, repeat):
    for k in range(repeat):
        dot = 0.0
        for i in numba.prange(n):
            dot += a[i] * b[i]
    return dot


@numba.jit(nopython=True, parallel=True)
def dot_jit_prange(a, b, n, repeat):
    for k in range(repeat):
        dot = 0.0
        for i in numba.prange(n):
            dot += a[i] * b[i]
    return dot


# Implementação utilizando a operação dot do numpy
@numba.njit(parallel=True)
def dot_njit_npDot(a, b, n, repeat):
    dot = 0.0
    for k in range(repeat):
        dot = np.dot(a, b)
    return dot


@numba.jit(nopython=True, parallel=True)
def dot_jit_npDot(a, b, n, repeat):
    dot = 0.0
    for k in range(repeat):
        dot = np.dot(a, b)
    return dot

# Implementação com função auxiliar
@numba.jit(nopython=True, parallel=True)
def calc_jit(a, b, n, dot):
    for i in numba.prange(n):
        dot += a[i] * b[i]
    return dot


@numba.njit(parallel=True)
def calc_njit(a, b, n, dot):
    for i in numba.prange(n):
        dot += a[i] * b[i]
    return dot


def dot_njit_calc(a, b, n, repeat):
    dot = 0.0
    for k in range(repeat):
        dot = calc_njit(a, b, n, dot)
    return dot


def dot_jit_calc(a, b, n, repeat):
    dot = 0.0
    for k in range(repeat):
        dot = calc_jit(a, b, n, dot)
    return dot

###########################################

# Inicializa os vetores com 0.01
a = np.full(vec_size, 0.01)
b = np.full(vec_size, 0.01)

dot = 0.0

print("Função;Resultado;Tempo(s)")

# Executa cada função 10 vezes e calcula o tempo médio

tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_njit(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_njit;"+str(dot)+";"+str(tempo/10))

tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_jit(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_jit;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_jit_npFloat(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_jit_npFloat;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_njit_npFloat(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_njit_npFloat;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_njit_prange(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_njit_prange;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_jit_prange(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_jit_prange;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_jit_npDot(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_jit_npDot;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_njit_npDot(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_njit_npDot;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_njit_calc(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_njit_calc;"+str(dot)+";"+str(tempo/10))


tempo = 0.0
for i in range(10):
    dot = 0.0
    start_time = time.time()
    dot = dot_jit_calc(a, b, vec_size, repeat)
    end_time = time.time()
    tempo += end_time - start_time

print("dot_jit_calc;"+str(dot)+";"+str(tempo/10))

