disk_count = int(input("Введите количество дисков: ")) + 1
list_disk = list(range(1, disk_count))
tower_etalon = list_disk[::-1]
towers = [tower_etalon.copy(), [], []]  # Начальные состояния стержней: первый стержень заполнен, остальные пусты

def move_disk(source, target, source_name, target_name, log_file, steps):
    """Перемещает диск между стержнями и увеличивает счётчик шагов."""
    disk = source.pop()
    target.append(disk)
    action_text = f"Блин {disk}: Стержень {source_name} -> Стержень {target_name}\n"
    print(action_text)
    log_file.write(action_text)
    steps[0] += 1  # Увеличиваем счётчик шагов

def hanoi_recursive(n, source, target, auxiliary, log_file, steps):
    """Рекурсивное решение задачи Ханойской башни с подсчётом шагов."""
    if n == 1:
        move_disk(towers[source], towers[target], source + 1, target + 1, log_file, steps)
    else:
        # Переместить n-1 дисков с начального стержня на вспомогательный
        hanoi_recursive(n - 1, source, auxiliary, target, log_file, steps)
        # Переместить оставшийся диск на целевой стержень
        move_disk(towers[source], towers[target], source + 1, target + 1, log_file, steps)
        # Переместить n-1 дисков со вспомогательного стержня на целевой
        hanoi_recursive(n - 1, auxiliary, target, source, log_file, steps)

# Открываем файл для записи
with open("решение.txt", "w") as log_file:
    steps = [0]  # Используем список, чтобы передавать по ссылке и изменять внутри функции
    hanoi_recursive(disk_count - 1, 0, 2, 1, log_file, steps)
    log_file.write(f"Общее количество шагов: {steps[0]}\n")
    print(f"Общее количество шагов: {steps[0]}")


