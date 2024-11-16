import json

# Чтение данных из файла 'purchase_log.txt' в память
user_data = {}
with open('purchase_log.txt', 'r', encoding='utf-8') as file_find:
    for line_find in file_find:
        data = json.loads(line_find)
        user_data[data["user_id"]] = data["category"]  # Заполняем словарь {user_id: category}

# Открываем файл 'funnel.csv' один раз для записи
with open('funnel.csv', 'w') as output_file:
    # Чтение из файла 'visit_log__1___2_.csv' построчно
    with open('visit_log__1___2_.csv', 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()  # Удаляем лишние пробелы и символы перевода строки
            line_id = line.split(',', 1)[0]  # Получаем id до первой запятой
            # Ищем соответствие в словаре user_data
            if line_id in user_data:
                # Пишем в файл 'funnel.csv' данные о визите и категории
                print(f"{line},{user_data[line_id]}\n")
                output_file.write(f"{line},{user_data[line_id]}\n")
