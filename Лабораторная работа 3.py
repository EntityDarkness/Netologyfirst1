"""
n,m=map(int,(input("Введите стороны шоколадки через запятую:").split(",")))
min_side = min(n,m)
max_side = max(n,m)
counter = min_side
broken = 0
while counter > 0:
    broken = broken + (max_side - 1)
    counter -= 1
broken = broken+(min_side-1)
print(broken)
"""

def min_breaks(n, m):
    # Базовый случай: если n или m равны 1, нам не нужно ломать шоколадку
    if n == 1 and m == 1:
        return 0
    # Мы можем разломать шоколадку горизонтально или вертикально
    # Если сломаем горизонтально, уменьшаем n на 1
    horizontal_break = 1 + min_breaks(n - 1, m)
    # Если сломаем вертикально, уменьшаем m на 1
    vertical_break = 1 + min_breaks(n, m - 1)
    # Возвращаем минимальное количество разломов
    return min(horizontal_break, vertical_break)

# Ввод размеров шоколадки
n, m = map(int, input("Введите стороны шоколадки через запятую: ").split(","))
# Получаем минимальное количество разломов
result = min_breaks(n, m)
print(f"Минимальное количество разломов: {result}")