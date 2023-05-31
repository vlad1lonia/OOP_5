//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OBJECTSCLASS_H
#define OOP_5_COPIED_OBJECTSCLASS_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define end_line '\n'
#define space ' '
#define tab '\t'

#define double_space "  "
#define quintuple_space "     "

#define SIGNAL_D(signalMethod) ((TYPE_SIGNAL) (&signalMethod))
#define HANDLER_D(handlerMethod) ((TYPE_HANDLER) (&handlerMethod))

using namespace std;

class ObjectsClass;
typedef void (ObjectsClass::* TYPE_SIGNAL) ( string & );
typedef void (ObjectsClass::* TYPE_HANDLER) ( string );

struct Connection {
    TYPE_SIGNAL signal;
    ObjectsClass* target_object;
    TYPE_HANDLER handler;
};

class ObjectsClass {

private:
    string object_name;                  // Наименование объекта
    ObjectsClass* head_pointer;          // Указатель на головной объект
    vector<ObjectsClass*> class_objects; // Массив указателей на подчинённые объекты

    int state = 0; // Поле готовности объекта, начальное значение = 0 (Поле не готово, "is not ready")
    int class_num; // Поле номера класса

    // Контейнер хранения установленных связей
    vector<Connection*> connections;

public:
    // Конструктор класса с параметрами
    ObjectsClass(ObjectsClass* head_pointer,
                 string object_name = "Base_object");
    ~ObjectsClass(); // Деструктор класса

    bool set_object_name(string object_name); // Метод изменения имени объекта
    string get_object_name();                 // Метод получения имени объекта

    ObjectsClass* get_head_object();                   // Метод получения указателя на головной объект
    bool move_head_object(ObjectsClass* head_pointer); // Метод переопределения головнго объекта в дереве иерархий

    ObjectsClass* find_object_name(string object_name);         // Метод полуения объекта по имени
    ObjectsClass* find_object_branch(string object_name);       // Метод получения объекта в ветке по имени
    ObjectsClass* find_object_tree(string object_name);         // Метод получения объекта в дереве по имени
    ObjectsClass* find_object_by_coordinate(string coordinate); // Метод получения объекта в дереве по координате

    void print_class_objects(int tab_num);     // Метод вывода дерева иерархий объектов
    vector<ObjectsClass*> get_class_objects(); // метод получения дерева иерархий объектов

    void set_state(int state_num);  // Метод изменения значения закрытого поля state
    int get_state();                // Метод получения значения закрытого поля state
    void print_states(int tab_num); // Метод для вывода дерева иерархий объектов и готовности каждого объекта
    void set_state_for_all();       // Метод установления значения поля state для всех объектов в дереве иерархий

    void delete_object(string object_name); // Метод удаления объекта в дереве по имени

    void set_class_num(int new_num); // Метод установления значения поля номера класса class_num
    int get_class_num();             // Метод получения значения поля номера класса class_num

    string get_absolute_path(); // Метод полуения абсоютного пути объекта в дереве иерархий

    // Метод установления связи между сигналом текущего объекта и обработчиком целевого
    void set_connection(TYPE_SIGNAL signal, ObjectsClass* target_object, TYPE_HANDLER handler);
    // Метод удаления связи между сигналом текущего объекта и обработчиком целевого
    void delete_connection(TYPE_SIGNAL signal, ObjectsClass* target_object, TYPE_HANDLER handler);

    /**
    * Метод сигнала от текущего объекта с передачей строкового параметра
    * Метод вызывается при вводе команды "EMIT" пользователем
    */
    void emit_command(TYPE_SIGNAL signal, string& command);
};


#endif //OOP_5_COPIED_OBJECTSCLASS_H
