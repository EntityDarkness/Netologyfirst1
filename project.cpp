#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

// Класс для представления записи в расписании
class ScheduleEntry {
private:
    int id;                 // Код записи
    string group;           // Группа
    string subject;         // Предмет
    string teacher;         // Преподаватель
    unsigned char dayOfWeek; // День недели (1-7)
    unsigned char lessonNum; // Номер пары (1-4)

public:
    // Конструктор
    ScheduleEntry(int id, string group, string subject, string teacher, 
                 unsigned char dayOfWeek, unsigned char lessonNum)
        : id(id), group(group), subject(subject), teacher(teacher), 
          dayOfWeek(dayOfWeek), lessonNum(lessonNum) {}
    
    // Конструктор по умолчанию
    ScheduleEntry() : id(0), dayOfWeek(1), lessonNum(1) {}
    
    // Геттеры
    int getId() const { return id; }
    string getGroup() const { return group; }
    string getSubject() const { return subject; }
    string getTeacher() const { return teacher; }
    unsigned char getDayOfWeek() const { return dayOfWeek; }
    unsigned char getLessonNum() const { return lessonNum; }
    
    // Сеттеры
    void setId(int id) { this->id = id; }
    void setGroup(string group) { this->group = group; }
    void setSubject(string subject) { this->subject = subject; }
    void setTeacher(string teacher) { this->teacher = teacher; }
    void setDayOfWeek(unsigned char day) { 
        if (day >= 1 && day <= 7) 
            this->dayOfWeek = day; 
    }
    void setLessonNum(unsigned char num) { 
        if (num >= 1 && num <= 4) 
            this->lessonNum = num; 
    }
    
    // Метод для вывода дня недели в текстовом формате
    string getDayOfWeekString() const {
        string days[] = {"Понедельник", "Вторник", "Среда", "Четверг", 
                         "Пятница", "Суббота", "Воскресенье"};
        return days[dayOfWeek - 1];
    }
};

// Класс для работы с базой данных расписания
class ScheduleDatabase {
private:
    vector<ScheduleEntry> entries;
    string filename;
    bool modified;

public:
    ScheduleDatabase() : modified(false) {}
    
    // Загрузка базы данных из файла
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        entries.clear();
        this->filename = filename;
        
        int id;
        string group, subject, teacher;
        unsigned char dayOfWeek, lessonNum;
        
        while (file >> id >> group >> subject >> teacher >> 
               reinterpret_cast<unsigned int&>(dayOfWeek) >> 
               reinterpret_cast<unsigned int&>(lessonNum)) {
            entries.push_back(ScheduleEntry(id, group, subject, teacher, dayOfWeek, lessonNum));
        }
        
        file.close();
        modified = false;
        return true;
    }
    
    // Сохранение базы данных в файл
    bool saveToFile(const string& filename = "") {
        string saveFilename = filename.empty() ? this->filename : filename;
        if (saveFilename.empty()) {
            return false;
        }
        
        ofstream file(saveFilename);
        if (!file.is_open()) {
            return false;
        }
        
        for (const auto& entry : entries) {
            file << entry.getId() << " " 
                 << entry.getGroup() << " " 
                 << entry.getSubject() << " " 
                 << entry.getTeacher() << " " 
                 << static_cast<int>(entry.getDayOfWeek()) << " " 
                 << static_cast<int>(entry.getLessonNum()) << endl;
        }
        
        file.close();
        
        if (!filename.empty()) {
            this->filename = filename;
        }
        
        modified = false;
        return true;
    }
    
    // Добавление новой записи
    void addEntry(const ScheduleEntry& entry) {
        entries.push_back(entry);
        modified = true;
    }
    
    // Удаление записи по ID
    bool removeEntry(int id) {
        auto it = find_if(entries.begin(), entries.end(), 
                          [id](const ScheduleEntry& e) { return e.getId() == id; });
        
        if (it != entries.end()) {
            entries.erase(it);
            modified = true;
            return true;
        }
        
        return false;
    }
    
    // Получение всех записей
    const vector<ScheduleEntry>& getEntries() const {
        return entries;
    }
    
    // Проверка, были ли изменения в базе данных
    bool isModified() const {
        return modified;
    }
    
    // Сортировка записей по различным критериям
    void sortEntries(int sortType) {
        switch (sortType) {
            case 1: // По ID
                sort(entries.begin(), entries.end(), 
                     [](const ScheduleEntry& a, const ScheduleEntry& b) {
                         return a.getId() < b.getId();
                     });
                break;
            case 2: // По группе
                sort(entries.begin(), entries.end(), 
                     [](const ScheduleEntry& a, const ScheduleEntry& b) {
                         return a.getGroup() < b.getGroup();
                     });
                break;
            case 3: // По предмету
                sort(entries.begin(), entries.end(), 
                     [](const ScheduleEntry& a, const ScheduleEntry& b) {
                         return a.getSubject() < b.getSubject();
                     });
                break;
            case 4: // По преподавателю
                sort(entries.begin(), entries.end(), 
                     [](const ScheduleEntry& a, const ScheduleEntry& b) {
                         return a.getTeacher() < b.getTeacher();
                     });
                break;
            case 5: // По дню недели и номеру пары
                sort(entries.begin(), entries.end(), 
                     [](const ScheduleEntry& a, const ScheduleEntry& b) {
                         if (a.getDayOfWeek() != b.getDayOfWeek()) {
                             return a.getDayOfWeek() < b.getDayOfWeek();
                         }
                         return a.getLessonNum() < b.getLessonNum();
                     });
                break;
        }
        
        modified = true;
    }
    
    // Поиск записей по группе
    vector<ScheduleEntry> findByGroup(const string& group) const {
        vector<ScheduleEntry> result;
        for (const auto& entry : entries) {
            if (entry.getGroup() == group) {
                result.push_back(entry);
            }
        }
        return result;
    }
    
    // Поиск записей по преподавателю
    vector<ScheduleEntry> findByTeacher(const string& teacher) const {
        vector<ScheduleEntry> result;
        for (const auto& entry : entries) {
            if (entry.getTeacher() == teacher) {
                result.push_back(entry);
            }
        }
        return result;
    }
    
    // Поиск записей по предмету
    vector<ScheduleEntry> findBySubject(const string& subject) const {
        vector<ScheduleEntry> result;
        for (const auto& entry : entries) {
            if (entry.getSubject() == subject) {
                result.push_back(entry);
            }
        }
        return result;
    }
    
    // Проверка корректности расписания
    void checkScheduleConflicts() const {
        // Карта для хранения конфликтов групп
        map<string, map<pair<unsigned char, unsigned char>, vector<string>>> groupConflicts;
        // Карта для хранения конфликтов преподавателей
        map<string, map<pair<unsigned char, unsigned char>, vector<string>>> teacherConflicts;
        
        // Проверяем каждую запись
        for (const auto& entry : entries) {
            string group = entry.getGroup();
            string teacher = entry.getTeacher();
            string subject = entry.getSubject();
            unsigned char day = entry.getDayOfWeek();
            unsigned char lesson = entry.getLessonNum();
            
            // Добавляем предмет в список предметов группы на данной паре
            groupConflicts[group][{day, lesson}].push_back(subject);
            
            // Добавляем группу в список групп преподавателя на данной паре
            teacherConflicts[teacher][{day, lesson}].push_back(group);
        }
        
        // Выводим конфликты групп
        bool hasGroupConflicts = false;
        for (const auto& group : groupConflicts) {
            for (const auto& timeslot : group.second) {
                if (timeslot.second.size() > 1) {
                    if (!hasGroupConflicts) {
                        cout << "Конфликты в расписании групп:" << endl;
                        hasGroupConflicts = true;
                    }
                    
                    cout << "Группа " << group.first << ", день " 
                         << static_cast<int>(timeslot.first.first) << ", пара " 
                         << static_cast<int>(timeslot.first.second) << ": ";
                    
                    for (size_t i = 0; i < timeslot.second.size(); ++i) {
                        cout << timeslot.second[i];
                        if (i < timeslot.second.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }
        }
        
        // Выводим конфликты преподавателей
        bool hasTeacherConflicts = false;
        for (const auto& teacher : teacherConflicts) {
            for (const auto& timeslot : teacher.second) {
                if (timeslot.second.size() > 1) {
                    if (!hasTeacherConflicts) {
                        cout << "Конфликты в расписании преподавателей:" << endl;
                        hasTeacherConflicts = true;
                    }
                    
                    cout << "Преподаватель " << teacher.first << ", день " 
                         << static_cast<int>(timeslot.first.first) << ", пара " 
                         << static_cast<int>(timeslot.first.second) << ": ";
                    
                    for (size_t i = 0; i < timeslot.second.size(); ++i) {
                        cout << timeslot.second[i];
                        if (i < timeslot.second.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }
        }
        
        if (!hasGroupConflicts && !hasTeacherConflicts) {
            cout << "Расписание составлено корректно, конфликтов не обнаружено." << endl;
        }
    }
    
    // Вывод расписания для конкретной группы
    void printGroupSchedule(const string& group) const {
        vector<ScheduleEntry> groupEntries = findByGroup(group);
        
        if (groupEntries.empty()) {
            cout << "Расписание для группы " << group << " не найдено." << endl;
            return;
        }
        
        // Сортируем по дням недели и номерам пар
        sort(groupEntries.begin(), groupEntries.end(), 
             [](const ScheduleEntry& a, const ScheduleEntry& b) {
                 if (a.getDayOfWeek() != b.getDayOfWeek()) {
                     return a.getDayOfWeek() < b.getDayOfWeek();
                 }
                 return a.getLessonNum() < b.getLessonNum();
             });
        
        cout << "Расписание для группы " << group << ":" << endl;
        
        unsigned char currentDay = 0;
        
        for (const auto& entry : groupEntries) {
            if (entry.getDayOfWeek() != currentDay) {
                currentDay = entry.getDayOfWeek();
                cout << "\n" << entry.getDayOfWeekString() << ":" << endl;
            }
            
            cout << "  Пара " << static_cast<int>(entry.getLessonNum()) << ": " 
                 << entry.getSubject() << " (преп. " << entry.getTeacher() << ")" << endl;
        }
    }
    
    // Получение списка всех групп
    set<string> getAllGroups() const {
        set<string> groups;
        for (const auto& entry : entries) {
            groups.insert(entry.getGroup());
        }
        return groups;
    }
    
    // Получение списка всех преподавателей
    set<string> getAllTeachers() const {
        set<string> teachers;
        for (const auto& entry : entries) {
            teachers.insert(entry.getTeacher());
        }
        return teachers;
    }
    
    // Получение списка всех предметов
    set<string> getAllSubjects() const {
        set<string> subjects;
        for (const auto& entry : entries) {
            subjects.insert(entry.getSubject());
        }
        return subjects;
    }
};

// Функция для отображения меню и обработки пользовательского ввода
void displayMenu(ScheduleDatabase& db) {
    int choice;
    bool exit = false;
    
    while (!exit) {
        cout << "\n=== МЕНЮ УПРАВЛЕНИЯ РАСПИСАНИЕМ ===" << endl;
        cout << "1. Загрузить базу данных из файла" << endl;
        cout << "2. Сохранить базу данных в файл" << endl;
        cout << "3. Просмотреть все записи" << endl;
        cout << "4. Добавить новую запись" << endl;
        cout << "5. Удалить запись" << endl;
        cout << "6. Сортировать записи" << endl;
        cout << "7. Поиск записей" << endl;
        cout << "8. Проверить корректность расписания" << endl;
        cout << "9. Вывести расписание группы" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;
                
                if (db.isModified()) {
                    char save;
                    cout << "База данных была изменена. Сохранить изменения? (y/n): ";
                    cin >> save;
                    
                    if (save == 'y' || save == 'Y') {
                        db.saveToFile();
                    }
                }
                
                if (db.loadFromFile(filename)) {
                    cout << "База данных успешно загружена." << endl;
                } else {
                    cout << "Ошибка при загрузке базы данных." << endl;
                }
                break;
            }
            case 2: {
                string filename;
                cout << "Введите имя файла (или пустую строку для сохранения в текущий файл): ";
                cin.ignore();
                getline(cin, filename);
                
                if (db.saveToFile(filename)) {
                    cout << "База данных успешно сохранена." << endl;
                } else {
                    cout << "Ошибка при сохранении базы данных." << endl;
                }
                break;
            }
            case 3: {
                const vector<ScheduleEntry>& entries = db.getEntries();
                
                if (entries.empty()) {
                    cout << "База данных пуста." << endl;
                } else {
                    cout << "Список всех записей:" << endl;
                    cout << setw(4) << "ID" << " | " 
                         << setw(10) << "Группа" << " | " 
                         << setw(15) << "Предмет" << " | " 
                         << setw(15) << "Преподаватель" << " | " 
                         << setw(10) << "День" << " | " 
                         << setw(4) << "Пара" << endl;
                    cout << string(65, '-') << endl;
                    
                    for (const auto& entry : entries) {
                        cout << setw(4) << entry.getId() << " | " 
                             << setw(10) << entry.getGroup() << " | " 
                             << setw(15) << entry.getSubject() << " | " 
                             << setw(15) << entry.getTeacher() << " | " 
                             << setw(10) << entry.getDayOfWeekString() << " | " 
                             << setw(4) << static_cast<int>(entry.getLessonNum()) << endl;
                    }
                }
                break;
            }
            case 4: {
                int id;
                string group, subject, teacher;
                unsigned int dayOfWeek, lessonNum;
                
                cout << "Введите ID: ";
                cin >> id;
                cout << "Введите группу: ";
                cin >> group;
                cout << "Введите предмет: ";
                cin >> subject;
                cout << "Введите преподавателя: ";
                cin >> teacher;
                cout << "Введите день недели (1-7): ";
                cin >> dayOfWeek;
                cout << "Введите номер пары (1-4): ";
                cin >> lessonNum;
                
                if (dayOfWeek < 1 || dayOfWeek > 7 || lessonNum < 1 || lessonNum > 4) {
                    cout << "Некорректные данные. День недели должен быть от 1 до 7, номер пары от 1 до 4." << endl;
                } else {
                    ScheduleEntry entry(id, group, subject, teacher, 
                                      static_cast<unsigned char>(dayOfWeek), 
                                      static_cast<unsigned char>(lessonNum));
                    db.addEntry(entry);
                    cout << "Запись успешно добавлена." << endl;
                }
                break;
            }
            case 5: {
                int id;
                cout << "Введите ID записи для удаления: ";
                cin >> id;
                
                if (db.removeEntry(id)) {
                    cout << "Запись успешно удалена." << endl;
                } else {
                    cout << "Запись с указанным ID не найдена." << endl;
                }
                break;
            }
            case 6: {
                int sortType;
                cout << "Выберите тип сортировки:" << endl;
                cout << "1. По ID" << endl;
                cout << "2. По группе" << endl;
                cout << "3. По предмету" << endl;
                cout << "4. По преподавателю" << endl;
                cout << "5. По дню недели и номеру пары" << endl;
                cout << "Ваш выбор: ";
                cin >> sortType;
                
                if (sortType >= 1 && sortType <= 5) {
                    db.sortEntries(sortType);
                    cout << "Записи отсортированы." << endl;
                } else {
                    cout << "Некорректный выбор." << endl;
                }
                break;
            }
            case 7: {
                int searchType;
                cout << "Выберите тип поиска:" << endl;
                cout << "1. По группе" << endl;
                cout << "2. По предмету" << endl;
                cout << "3. По преподавателю" << endl;
                cout << "Ваш выбор: ";
                cin >> searchType;
                
                string searchQuery;
                cout << "Введите строку для поиска: ";
                cin >> searchQuery;
                
                vector<ScheduleEntry> results;
                
                switch (searchType) {
                    case 1:
                        results = db.findByGroup(searchQuery);
                        break;
                    case 2:
                        results = db.findBySubject(searchQuery);
                        break;
                    case 3:
                        results = db.findByTeacher(searchQuery);
                        break;
                    default:
                        cout << "Некорректный выбор." << endl;
                        continue;
                }
                
                if (results.empty()) {
                    cout << "Записи не найдены." << endl;
                } else {
                    cout << "Найденные записи:" << endl;
                    cout << setw(4) << "ID" << " | " 
                         << setw(10) << "Группа" << " | " 
                         << setw(15) << "Предмет" << " | " 
                         << setw(15) << "Преподаватель" << " | " 
                         << setw(10) << "День" << " | " 
                         << setw(4) << "Пара" << endl;
                    cout << string(65, '-') << endl;
                    
                    for (const auto& entry : results) {
                        cout << setw(4) << entry.getId() << " | " 
                             << setw(10) << entry.getGroup() << " | " 
                             << setw(15) << entry.getSubject() << " | " 
                             << setw(15) << entry.getTeacher() << " | " 
                             << setw(10) << entry.getDayOfWeekString() << " | " 
                             << setw(4) << static_cast<int>(entry.getLessonNum()) << endl;
                    }
                }
                break;
            }
            case 8: {
                db.checkScheduleConflicts();
                break;
            }
            case 9: {
                set<string> groups = db.getAllGroups();
                
                if (groups.empty()) {
                    cout << "В базе данных нет записей о группах." << endl;
                    break;
                }
                
                cout << "Доступные группы:" << endl;
                for (const auto& group : groups) {
                    cout << "- " << group << endl;
                }
                
                string group;
                cout << "Введите название группы: ";
                cin >> group;
                
                db.printGroupSchedule(group);
                break;
            }
            case 0:
                if (db.isModified()) {
                    char save;
                    cout << "База данных была изменена. Сохранить изменения? (y/n): ";
                    cin >> save;
                    
                    if (save == 'y' || save == 'Y') {
                        db.saveToFile();
                    }
                }
                
                exit = true;
                break;
            default:
                cout << "Некорректный выбор. Попробуйте снова." << endl;
        }
    }
}

// Функция для создания тестовой базы данных с 25 записями
void createTestDatabase(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка при создании тестовой базы данных." << endl;
        return;
    }
    
    // Группы
    vector<string> groups = {"ИВТ-101", "ИВТ-102", "ПИ-201", "ПИ-202", "ИБ-301"};
    
    // Предметы
    vector<string> subjects = {"Математика", "Программирование", "Физика", 
                              "Английский", "Базы_данных", "Сети", 
                              "Алгоритмы", "Веб-разработка"};
    
    // Преподаватели
    vector<string> teachers = {"Иванов", "Петров", "Сидоров", "Кузнецова", 
                              "Смирнова", "Попов", "Соколова"};
    
    // Генерируем 25 записей
    for (int i = 1; i <= 25; ++i) {
        string group = groups[rand() % groups.size()];
        string subject = subjects[rand() % subjects.size()];
        string teacher = teachers[rand() % teachers.size()];
        unsigned char day = (rand() % 5) + 1; // Пн-Пт (1-5)
        unsigned char lesson = (rand() % 4) + 1; // Пары 1-4
        
        file << i << " " << group << " " << subject << " " << teacher << " " 
             << static_cast<int>(day) << " " << static_cast<int>(lesson) << endl;
    }
    
    file.close();
    cout << "Тестовая база данных успешно создана в файле " << filename << endl;
}

int main() {
    // Установка русской локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    ScheduleDatabase db;
    
    cout << "Программа для работы с расписанием занятий" << endl;
    cout << "Хотите создать тестовую базу данных? (y/n): ";
    
    char createTest;
    cin >> createTest;
    
    if (createTest == 'y' || createTest == 'Y') {
        string filename;
        cout << "Введите имя файла для тестовой базы данных: ";
        cin >> filename;
        createTestDatabase(filename);
        
        // Загружаем созданную базу данных
        if (db.loadFromFile(filename)) {
            cout << "Тестовая база данных успешно загружена." << endl;
        }
    }
    
    displayMenu(db);
    
    return 0;
}
