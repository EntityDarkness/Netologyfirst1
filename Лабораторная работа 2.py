# Словарь для хранения цен на товары в разных магазинах
prices = {}

    # Запрашиваем у пользователя список магазинов
num_stores = int(input("Введите количество магазинов: "))
stores = []

for i in range(num_stores):
    store_name = input(f"Введите название магазина {i + 1}: ")
    stores.append(store_name)
    prices[store_name] = {}

    # Запрашиваем у пользователя список товаров и их цены в каждом магазине
while True:
    item = input("Введите название товара (или 'стоп' для завершения ввода): ")
    if item.lower() == 'стоп':
        break

    for store in stores:
        price = float(input(f"Введите цену на {item} в магазине '{store}': "))
        prices[store][item] = price

    # Вычисляем общую стоимость покупок в каждом магазине
total_costs = {}
for store, items in prices.items():
    total_cost = sum(items.values())
    total_costs[store] = total_cost

    # Выводим общую стоимость покупок в каждом магазине
print("\nОбщая стоимость покупок в каждом магазине:")
for store, total in total_costs.items():
    print(f"{store}: {total:.2f} руб.")

    # Определяем магазин с минимальной общей стоимостью
min_cost_store = min(total_costs, key=total_costs.get)
min_cost_value = total_costs[min_cost_store]

print(f"\nВы можете сэкономить больше всего, покупая в магазине '{min_cost_store}', "
    f"где общая стоимость составляет {min_cost_value:.2f} руб.")

