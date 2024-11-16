from datetime import datetime

# Форматы дат для каждой газеты
formats = [
    '%A, %B %d, %Y',    # The Moscow Times — Wednesday, October 2, 2002
    '%A, %d.%m.%y',     # The Guardian — Friday, 11.10.13
    '%A, %d %B %Y'      # Daily News — Thursday, 18 August 1977
]

while True:
    date_str = input('Введите дату (или введите "q" для выхода): ')
    if date_str.lower() == 'q':
        break
    for fmt in formats:
        try:
            date_obj = datetime.strptime(date_str, fmt)
            print(date_obj)
            break  # Если успешно, выходим из цикла по форматам
        except ValueError:
            continue  # Переходим к следующему формату
    else:
        # Если ни один формат не подошел, продолжаем цикл
        continue
