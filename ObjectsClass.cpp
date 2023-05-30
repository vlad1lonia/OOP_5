#include "ObjectsClass.h"
#include <iostream>

#include <cstring>
#include <string>

#define end_line '\n'
#define space ' '
#define double_space "  "
#define tab_space "    "

using namespace std;

// Конструктор класса с параметрами
ObjectsClass::ObjectsClass(ObjectsClass* head_pointer, string object_name) {
    this->head_pointer = head_pointer;
    this->object_name = object_name;

    if (this->head_pointer != nullptr) {
        head_pointer->class_objects.push_back(this);
    }
}

// Деструктор класса
ObjectsClass::~ObjectsClass() {

    ObjectsClass* root_object = find_object_by_coordinate("/");

    vector<ObjectsClass*> local_objects;
    local_objects.push_back(root_object);

    while (!local_objects.empty()) {

        ObjectsClass* current_object = local_objects.back();
        local_objects.pop_back();

        if (current_object != nullptr) {

            int index = 0;

            while (index < current_object->connections.size()) {

                if (current_object->connections[index]->target_object == this) {
                    current_object->delete_connection(current_object->connections[index]->signal,
                                                      this, current_object->connections[index]->handler);
                } else {
                    index++;
                }
            }

            for (index = 0; index < current_object->class_objects.size(); index++) {
                local_objects.push_back(current_object->class_objects[index]);
            }
        }
    }

    for (int index = 0; index < connections.size(); index++) {
        delete connections[index];
    }
    connections.clear();

    for (int index = 0; index < class_objects.size(); index++) {
        delete class_objects[index];
        class_objects[index] = nullptr;
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод изменения имени объекта
bool ObjectsClass::set_object_name(string object_name) {
    if (this->head_pointer != nullptr &&
        this->head_pointer->find_object_name(object_name) != nullptr) {
        return false; // Значение не было изменено, поэтому возвращается "Ложь"
    }

    this->object_name = object_name;
    return true; // Значение было изменено, поэтому возвращается "Истина"
}

// Метод получения имени объекта
string ObjectsClass::get_object_name() {
    return this->object_name;
}

// Метод получения указателя на головной объект
ObjectsClass* ObjectsClass::get_head_object() {
    return this->head_pointer;
}

// Метод переопределения головнго объекта в дереве иерархий
bool ObjectsClass::move_head_object(ObjectsClass* head_pointer) {
    string object_name = this->get_object_name();
    ObjectsClass* current_head_pointer = head_pointer;

    if (this->head_pointer == nullptr || head_pointer == nullptr
        || head_pointer->find_object_name(object_name) != nullptr) {
        return false;
    }

    while (current_head_pointer->get_head_object() != nullptr) {
        if (current_head_pointer->get_head_object() == this) {
            return false;
        }

        current_head_pointer = current_head_pointer->get_head_object();
    }

    head_pointer->class_objects.push_back(this);
    current_head_pointer = this->head_pointer;

    for (int index = 0; index <
                        current_head_pointer->class_objects.size(); index++) {
        if (current_head_pointer->class_objects[index]
                    ->get_object_name() == object_name) {
            current_head_pointer->class_objects.erase(
                    current_head_pointer->class_objects.begin() + index);
        }
    }

    this->head_pointer = current_head_pointer;
    return true;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод полуения ссылки на объект по имени
ObjectsClass* ObjectsClass::find_object_name(string object_name) {

    for (int index = 0; index < this->class_objects.size(); index++) {
        if (this->class_objects[index]->get_object_name() == object_name) {
            return this->class_objects[index];
        }
    }

    return nullptr;
}

// Метод получения ссылки на объект в ветке по имени
ObjectsClass* ObjectsClass::find_object_branch(string object_name) {

    ObjectsClass* class_object;
    int object_count = 0;

    vector<ObjectsClass*> objects_vector;
    objects_vector.push_back(this);

    while (!objects_vector.empty()) {
        ObjectsClass* local_class_object = objects_vector.back();
        objects_vector.pop_back();

        if (local_class_object->object_name == object_name) {
            class_object = local_class_object; object_count++;
        }

        for (int index = 0; index < local_class_object->
                class_objects.size(); index++) {
            objects_vector.push_back(local_class_object->
                    class_objects[index]);
        }
    }

    if (object_count == 1) {
        return class_object;
    } else {
        return nullptr;
    }
}

// Метод получения ссылки на объект в дереве по имени
ObjectsClass* ObjectsClass::find_object_tree(string object_name) {

    ObjectsClass* root_object;
    root_object = this;

    while (root_object->head_pointer != nullptr) {
        root_object = root_object->head_pointer;
    }

    return root_object->find_object_branch(object_name);
}

// Метод получения объекта в дереве по координате
ObjectsClass* ObjectsClass::find_object_by_coordinate(string coordinate) {
    string object_name;
    ObjectsClass* class_object = this;
    int index = 0;

    if (coordinate[0] == '/') {
        while (class_object->head_pointer != nullptr) {
            class_object = class_object->head_pointer;
        }
    }

    if (coordinate.length() == 1) {
        return class_object;
    }

    if (coordinate[0] == '/' || coordinate[0] == '.') {
        index = 1;
    }

    if (coordinate[0] == '/' && coordinate[1] == '/') {
        object_name = coordinate.substr(2);
        return class_object->find_object_branch(object_name);
    }

    while (index < coordinate.length()) {
        if (coordinate[index] == '/') {
            class_object = class_object->find_object_name(object_name);
            if (class_object == nullptr) {
                return nullptr;
            }

            object_name = "";
        } else {
            object_name += coordinate[index];
        }

        index++;
    }

    if (coordinate[0] == '.') {
        return class_object->find_object_branch(object_name);
    }

    return class_object->find_object_name(object_name);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод вывода дерева иерархий объектов
void ObjectsClass::print_class_objects(int tab_num) {

    cout << this->get_object_name();
    for (int index = 0; index < this->class_objects.size(); index++) {

        cout << end_line;
        for (int index_j = 0; index_j < tab_num; index_j++) {
            cout << tab_space;
        }

        this->class_objects[index]->print_class_objects(tab_num + 1);
    }
}

// Метод получения дерева иерархий объектов
vector<ObjectsClass*> ObjectsClass::get_class_objects() {
    return this->class_objects;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод изменения значения закрытого поля state
void ObjectsClass::set_state(int state_num) {
    if (head_pointer == nullptr || head_pointer->state != 0) {
        if (state_num == 0) {
            for (int index = 0; index < this->class_objects.size(); index++) {
                this->class_objects[index]->set_state(0);
            }
        }

        this->state = state_num;
    }
}

// Метод получения значения закрытого поля состояния объекта state
int ObjectsClass::get_state() {
    return this->state;
}

// Метод для вывода дерева иерархий объектов и готовности каждого объекта
void ObjectsClass::print_states(int tab_num) {

    cout << this->get_object_name() << space;
    if (this->state != 0) {
        cout << "is ready";
    } else {
        cout << "is not ready";
    }

    for (int index = 0; index < this->class_objects.size(); index++) {
        cout << end_line;

        for (int index_j = 0; index_j < tab_num; index_j++) {
            cout << tab_space;
        }

        this->class_objects[index]->print_states(tab_num + 1);
    }
}

// Метод установления значения поля state для всех объектов в дереве иерархий
void ObjectsClass::set_state_for_all() {
    this->state = 1;

    for (int index = 0; index < this->class_objects.size(); index++) {
        class_objects[index]->set_state_for_all();
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод удаления объекта из дерева иерархий по имени
void ObjectsClass::delete_object(string object_name) {
    ObjectsClass* class_object;

    for (int index = 0; index < this->class_objects.size(); index++) {
        if (this->class_objects[index]->get_object_name() == object_name) {
            class_object = this->class_objects[index];
            this->class_objects.erase(this->class_objects.begin() + index);
            delete class_object;

            return;
        }
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод изменения значения поля номера класса class_num
void ObjectsClass::set_class_num(int new_num) {
    this->class_num = new_num;
}

// Метод получения значения поля номера класса class_num
int ObjectsClass::get_class_num() {
    return this->class_num;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод получения абсолютного пути в дереве иерархий до объекта
string ObjectsClass::get_absolute_path() {
    string path;
    ObjectsClass* class_object = this;

    if (class_object->get_head_object() == nullptr) {
        return "/";
    }

    while (class_object->get_head_object() != nullptr) {
        path = "/" + class_object->get_object_name() + path;
        class_object = class_object->get_head_object();
    }

    return path;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод установления связи между сигналом текущего объекта и обработчиком целевого
void ObjectsClass::set_connection(TYPE_SIGNAL signal, ObjectsClass* target_object, TYPE_HANDLER handler) {

    Connection* connection;

    /**
    * Цикл проверки существования похожего соединения в контейнере сигналов connections
    * Если похожее соединение было найдено, то работа метода завершается
    */
    for (int index = 0; index < connections.size(); index++) {
        if (connections[index]->signal == signal && connections[index]->target_object == target_object
            && connections[index]->handler == handler) {

            return;
        }
    }

    connection = new Connection();

    connection->signal = signal; connection->target_object = target_object;
    connection->handler = handler;

    connections.push_back(connection);
}

// Метод удаления связи между сигналом текущего объекта и обработчиком целевого
void ObjectsClass::delete_connection(TYPE_SIGNAL signal, ObjectsClass* target_object, TYPE_HANDLER handler) {

    Connection* connection;

    /**
    * Цикл для нахождения соединения соединения в контейнере connections
    * Если такое соединения было найдено, то оно удаляется из контейнера connections
    */

    int index = 0;
    while (index < connections.size()) {

        if (connections[index]->signal == signal && connections[index]->target_object == target_object
            && connections[index]->handler == handler) {

            connection = connections[index];
            connections.erase(connections.begin() + index);

            delete connection;
        } else {
            index++;
        }
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/**
* Метод сигнала от текущего объекта с передачей строкового параметра
* Метод вызывается при вводе команды "EMIT" пользователем
*/
void ObjectsClass::emit_command(TYPE_SIGNAL signal, string command) {

    TYPE_HANDLER handler; ObjectsClass* class_object;

    /**
    * Проверка поля состояния объекта state
    * Если он равен 0 (То есть поле "Не готово"), то работа метода завершается
    */
    if (this->state == 0) {
        return;
    }

    // Строка вызова метода сигнала
    (this->*signal) (command);

    for (int index = 0; index < this->connections.size(); index++) {

        if (connections[index]->signal == signal) {

            handler = connections[index]->handler;
            class_object = connections[index]->target_object;

            if (class_object->state != 0) {
                // Строка вызова метода обработчика
                (class_object->*handler) (command);
            }
        }
    }
}