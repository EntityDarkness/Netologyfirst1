import time
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor


def formula_1(x):
    return x ** 2 - x ** 2 + x ** 4 - x ** 5 + x + x


def formula_2(x):
    return x + x


def formula_3(result_1, result_2):
    return result_1 + result_2


def run_with_threads(iterations):
    print("Запуск с потоками...")

    def run_iteration(x):
        result_1 = formula_1(x)
        result_2 = formula_2(x)
        return formula_3(result_1, result_2)

    start_time = time.time()

    with ThreadPoolExecutor() as executor:
        executor.map(run_iteration, range(iterations))

    elapsed_time = time.time() - start_time
    print(f"Завершено выполнение с потоками за {elapsed_time:.2f} секунд")
    return elapsed_time


def run_with_processes(iterations):
    print("Запуск с процессами...")

    def run_iteration(x):
        result_1 = formula_1(x)
        result_2 = formula_2(x)
        return formula_3(result_1, result_2)

    start_time = time.time()

    with ProcessPoolExecutor() as executor:
        executor.map(run_iteration, range(iterations))

    elapsed_time = time.time() - start_time
    print(f"Завершено выполнение с процессами за {elapsed_time:.2f} секунд")
    return elapsed_time


if __name__ == '__main__':
    iterations_list = [10000, 100000]

    for iterations in iterations_list:
        print(f"\n{iterations} итераций:")

        thread_time = run_with_threads(iterations)
        process_time = run_with_processes(iterations)


