import pandas as pd


class Customer:
    def __init__(self, name, title, browser, gender, age, purchase_amount, location):
        """
        Конструктор класса Customer.

        :param name: Имя клиента.
        :param title: Звание клиента (например, г-н, г-жа).
        :param browser: Тип используемого браузера.
        :param gender: Пол клиента (мужской/женский).
        :param age: Возраст клиента (может быть представлен как float).
        :param purchase_amount: Сумма покупки.
        :param location: Регион клиента.
        """
        self.name = name
        self.title = title
        self.browser = browser
        self.gender = gender
        # Преобразуем возраст в целое число, чтобы убрать десятичные части.
        self.age = int(float(age))
        self.purchase_amount = purchase_amount
        self.location = location

    def get_gender_description(self):
        """
        Получает строковое описание пола клиента.

        :return: Описание пола (женского или мужского).
        """
        if self.gender.lower() == 'female':
            return "женского пола"
        elif self.gender.lower() == 'male':
            return "мужского пола"
        else:
            return "неизвестного пола"

    def get_description(self):
        """
        Формирует текстовое описание клиента.

        :return: Строка с полным описанием клиента.
        """
        return f"Пользователь {self.name} {self.title} " \
               f"{self.get_gender_description()}, {self.age} лет совершила покупку на " \
               f"{self.purchase_amount} у.е. с мобильного браузера {self.browser}. " \
               f"Регион, из которого совершалась покупка: {self.location}."


class CustomerDescriptionGenerator:
    def __init__(self, csv_file, output_file):
        """
        Конструктор класса CustomerDescriptionGenerator.

        :param csv_file: Путь к входному CSV файлу с данными клиентов.
        :param output_file: Путь к выходному текстовому файлу для записи описаний.
        """
        self.csv_file = csv_file
        self.output_file = output_file
        self.customers = []  # Список для хранения объектов класса Customer

    def load_csv(self):
        """
        Загружает данные из CSV файла.

        :return: DataFrame с загруженными данными.
        """
        return pd.read_csv(self.csv_file, header=0)  # Заголовок находится в первой строке

    def parse_customer_data(self, data):
        """
        Парсит строку данных в объект класса Customer.

        :param data: Строка с данными клиента.
        :return: Экземпляр класса Customer или None в случае ошибки.
        """
        attributes = data.split(',')

        if len(attributes) < 7:
            print(f"Недостаточно данных для строки: {data}")
            return None

        try:
            return Customer(
                name=attributes[0].strip(),
                title=attributes[1].strip(),
                browser=attributes[2].strip(),
                gender=attributes[3].strip(),
                age=attributes[4].strip(),
                purchase_amount=attributes[5].strip(),
                location=attributes[6].strip()
            )
        except (ValueError, IndexError) as e:
            print(f"Ошибка при парсинге строки: {data}. Ошибка: {e}")
            return None

    def generate_descriptions(self):
        """
        Генерирует описания для всех клиентов, загружая данные и парсируя их.

        Записывает описания в список self.customers.
        """
        data = self.load_csv()
        for index, row in data.iterrows():
            customer_data = ','.join(map(str, row))  # Преобразует строку DataFrame в строку
            customer = self.parse_customer_data(customer_data)
            if customer:
                self.customers.append(customer)

    def write_descriptions_to_file(self):
        """
        Записывает сгенерированные описания клиентов в выходной файл.
        """
        with open(self.output_file, 'w', encoding='utf-8') as f:
            for customer in self.customers:
                f.write(customer.get_description() + "\n")

    def run(self):
        """
        Запускает процесс генерации описаний и записи их в файл.
        """
        self.generate_descriptions()
        self.write_descriptions_to_file()


if __name__ == "__main__":
    input_file = 'web_clients_correct.csv'  # Путь к входному CSV файлу
    output_file = 'customer_descriptions.txt'  # Путь к выходному текстовому файлу

    generator = CustomerDescriptionGenerator(input_file, output_file)  # Создание экземпляра генератора описаний
    generator.run()  # Запуск генерации описаний

