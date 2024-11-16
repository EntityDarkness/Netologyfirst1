disk_count = int(input("Введите количество дисков: "))+1
list_disk = list(range(1,disk_count))
tower_etalon = list_disk[::-1]
tower_1 = tower_etalon.copy()
tower_2 = []
tower_3 = []
def step_chet(et,l1, l2, l3,log_file):
    # Перемещение диска из стержня 1 в стержень 2
    if l1 and (not l2 or l1[-1] < l2[-1]):
        last_l1 = l1.pop()
        l2.append(last_l1)
        text1 = f"Блин {last_l1}: Стержень 1 -> Стержень 2\n"
        print(text1)
        log_file.write(text1)
    elif l2:  # Проверка, если l2 не пуст
        last_l1 = l2.pop()
        l1.append(last_l1)
        text1 = f"Блин {last_l1}: Стержень 2 -> Стержень 1\n"
        print(text1)
        log_file.write(text1)
    if l2 == et or l3 == et:
        return 1
    # Перемещение диска из стержня 1 в стержень 3
    if l1 and (not l3 or l1[-1] < l3[-1]):
        last_l2 = l1.pop()
        l3.append(last_l2)
        text2 = f"Блин {last_l2}: Стержень 1 -> Стержень 3\n"
        print(text2)
        log_file.write(text2)
    elif l3:  # Проверка, если l3 не пуст
        last_l2 = l3.pop()
        l1.append(last_l2)
        text2 = f"Блин {last_l2}: Стержень 3 -> Стержень 1\n"
        print(text2)
        log_file.write(text2)
    if l2 == et or l3 == et:
        return 2
    # Перемещение диска из стержня 2 в стержень 3
    if l2 and (not l3 or l2[-1] < l3[-1]):
        last_l3 = l2.pop()
        l3.append(last_l3)
        text3 = f"Блин {last_l3}: Стержень 2 -> Стержень 3\n"
        print(text3)
        log_file.write(text3)
    elif l3:  # Проверка, если l3 не пуст
        last_l3 = l3.pop()
        l2.append(last_l3)
        text3 = f"Блин {last_l3}: Стержень 3 -> Стержень 2\n"
        print(text3)
        log_file.write(text3)
    if l2 == et or l3 == et:
        return 3
    else:
        return 3

def step_nechet(et,l1, l2, l3,log_file):
    # Перемещение диска из стержня 1 в стержень 3
    if l1 and (not l3 or l1[-1] < l3[-1]):
        last_l2 = l1.pop()
        l3.append(last_l2)
        text2 = f"Блин {last_l2}: Стержень 1 -> Стержень 3\n"
        print(text2)
        log_file.write(text2)
    elif l3:  # Проверка, если l3 не пуст
        last_l2 = l3.pop()
        l1.append(last_l2)
        text2 = f"Блин {last_l2}: Стержень 3 -> Стержень 1\n"
        print(text2)
        log_file.write(text2)
    # Перемещение диска из стержня 1 в стержень 2
    if l1 and (not l2 or l1[-1] < l2[-1]):
        last_l1 = l1.pop()
        l2.append(last_l1)
        text1 = f"Блин {last_l1}: Стержень 1 -> Стержень 2\n"
        print(text1)
        log_file.write(text1)
    elif l2:  # Проверка, если l2 не пуст
        last_l1 = l2.pop()
        l1.append(last_l1)
        text1 = f"Блин {last_l1}: Стержень 2 -> Стержень 1\n"
        print(text1)
        log_file.write(text1)
    if l2 == et or l3 == et:
        return 1
    if l2 == et or l3 == et:
        return 2
    # Перемещение диска из стержня 2 в стержень 3
    if l2 and (not l3 or l2[-1] < l3[-1]):
        last_l3 = l2.pop()
        l3.append(last_l3)
        text3 = f"Блин {last_l3}: Стержень 2 -> Стержень 3\n"
        print(text3)
        log_file.write(text3)
    elif l3:  # Проверка, если l3 не пуст
        last_l3 = l3.pop()
        l2.append(last_l3)
        text3 = f"Блин {last_l3}: Стержень 3 -> Стержень 2\n"
        print(text3)
        log_file.write(text3)
    if l2 == et or l3 == et:
        return 3
    else:
        return 3

def hanoi(et,tower1,tower2,tower3,log_file):
    step = 0
    if (disk_count-1)%2 == 0:
        while not (tower2 == et or tower3 == et):
            cikl = step_chet(et,tower1,tower2,tower3,log_file)
            step += cikl
        log_file.write(f"Общее количество шагов: {step}")
        return f"Общее количество шагов: {step}"
    else:
        while not (tower2 == et or tower3 == et):
            cikl = step_nechet(et,tower1,tower2,tower3,log_file)
            step += cikl
        log_file.write(f"Общее количество шагов: {step}")
        return f"Общее количество шагов: {step}"

# Открываем файл для записи
with open("решение.txt", "w") as log_file:
    print(hanoi(tower_etalon,tower_1, tower_2, tower_3, log_file), tower_etalon, tower_1, tower_2, tower_3)

