#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

class Person
{
protected:
    friend class List;
    char name[20];
    char add[40];
    char tel[15];
    int age;
    Person *next;
    static Person *ptr; // 类静态变量，所有该类及派生类的对象共享此唯一指针

public:
    Person(char*, int, char*, char*);
    virtual void print();
    virtual Person* insert();
};

class Staff : public Person
{
private:
    friend class List;
    float hourly_wages;

public:
    Staff(char*, int, char*, char*, float);
    void print() override;
    Person* insert() override;
};

class Student : public Person
{
private:
    friend class List;
    float gpa;
    int level;

public:
    Student(char*, int, char*, char*, int, float);
    void print() override;
    Person* insert() override;
};

class Teacher : public Person
{
private:
    friend class List;
    float salary;

public:
    Teacher(char*, int, char*, char*, float);
    void print() override;
    Person* insert() override;
};

class List
{
private:
    Person* root;

public:
    List();
    void insert_Person(Person *node);
    void print_List();
    void remove(char *name);
    void ReadFiles(); // 读取指定文件中的所有记录按照字母序插入到链表中
    void WriteFile(); // 将内存中链表中节点数据依次写入到指定文件中
};

#endif // PERSON_H


#include "person.h"

Person* Person::ptr = nullptr;

Person::Person(char* n, int a, char* ad, char* t)
{
    age = a;
    next = nullptr;
    strncpy(name, n, 19);
    name[19] = '\0';
    strncpy(add, ad, 39);
    add[39] = '\0';
    strncpy(tel, t, 14);
    tel[14] = '\0';
}

void Person::print()
{
    cout << "Person:" << endl;
    cout << "Name: " << name << " ";
    cout << "Age: " << age << " ";
    cout << "Address: " << add << " ";
    cout << "Tel: " << tel << endl;
}

Person* Person::insert()
{
    Person::ptr = this;
    return ptr;
}

Staff::Staff(char* myname, int myage, char* myadd, char* mytel, float myhw)
    : Person(myname, myage, myadd, mytel), hourly_wages(myhw) {}

void Staff::print()
{
    cout << "Staff:" << endl;
    cout << "Name: " << name << " ";
    cout << "Age: " << age << " ";
    cout << "Address: " << add << " ";
    cout << "Tel: " << tel << " ";
    cout << "Hourly Wages: " << hourly_wages << endl;
}

Person* Staff::insert()
{
    Person::ptr = this;
    return ptr;
}

Student::Student(char* myname, int myage, char* myadd, char* mytel, int mylevel, float mygpa)
    : Person(myname, myage, myadd, mytel), level(mylevel), gpa(mygpa) {}

void Student::print()
{
    cout << "Student:" << endl;
    cout << "Name: " << name << " ";
    cout << "Age: " << age << " ";
    cout << "Address: " << add << " ";
    cout << "Tel: " << tel << " ";
    cout << "Level: " << level << " ";
    cout << "GPA: " << gpa << endl;
}

Person* Student::insert()
{
    Person::ptr = this;
    return ptr;
}

Teacher::Teacher(char* myname, int myage, char* myadd, char* mytel, float mysalary)
    : Person(myname, myage, myadd, mytel), salary(mysalary) {}

void Teacher::print()
{
    cout << "Teacher:" << endl;
    cout << "Name: " << name << " ";
    cout << "Age: " << age << " ";
    cout << "Address: " << add << " ";
    cout << "Tel: " << tel << " ";
    cout << "Salary: " << salary << endl;
}

Person* Teacher::insert()
{
    Person::ptr = this;
    return ptr;
}

List::List()
{
    root = nullptr;
}

void List::insert_Person(Person *node)
{
    char key[20];
    strcpy(key, node->name);
    Person *curr_node = root;
    Person *previous = nullptr;
    while (curr_node != nullptr && strcmp(curr_node->name, key) < 0)
    {
        previous = curr_node;
        curr_node = curr_node->next;
    }
    node->insert();
    node->ptr->next = curr_node;
    if (previous == nullptr)
        root = node->ptr;
    else
        previous->next = node->ptr;
}

void List::print_List()
{
    Person *cur = root;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->next;
    }
}

void List::remove(char *name)
{
    Person* curr_node = root;
    Person* previous = nullptr;
    while (curr_node != nullptr && strcmp(curr_node->name, name) != 0)
    {
        previous = curr_node;
        curr_node = curr_node->next;
    }
    if (curr_node != nullptr)
    {
        if (previous == nullptr)
        {
            root = curr_node->next;
        }
        else
        {
            previous->next = curr_node->next;
        }
        delete curr_node;
    }
}

void List::ReadFiles() // 读取指定文件中的所有记录按照字母序插入到链表中
{
    ifstream infile;
    string filename;
    cout << "请输入读取的文件名:" << endl;
    cin >> filename;
    infile.open(filename);
    while (!infile)
    {
        cout << "文件不存在，请重新输入:" << endl;
        cin >> filename;
        infile.open(filename);
    }

    char type;
    string name, add, tel;
    int age;
    float hourly_wages, gpa, salary;
    while (infile >> type)
    {
        if (type == 'P')
        {
            infile >> name >> add >> tel >> age;
            if (infile.fail())
            {
                cout << "发现输入流挂起，这一整行忽略，流重新复位" << endl;
                infile.clear(); // 状态复位
                infile.ignore(numeric_limits<streamsize>::max(), '\n'); // 把这一行全部清空，复位
                continue;
            }
            Person* per = new Person(const_cast<char*>(name.c_str()), age, const_cast<char*>(add.c_str()), const_cast<char*>(tel.c_str()));
            insert_Person(per);
        }
        else if (type == 'T')
        {
            infile >> name >> add >> tel >> age >> salary;
            if (infile.fail())
            {
                cout << "发现输入流挂起，这一整行忽略，流重新复位" << endl;
                infile.clear(); // 状态复位
                infile.ignore(numeric_limits<streamsize>::max(), '\n'); // 把这一行全部清空，复位
                continue;
            }
            Teacher* tea = new Teacher(const_cast<char*>(name.c_str()), age, const_cast<char*>(add.c_str()), const_cast<char*>(tel.c_str()), salary);
            insert_Person(tea);
        }
        else if (type == 'S')
        {
            infile >> name >> add >> tel >> age >> level >> gpa;
            if (infile.fail())
            {
                cout << "发现输入流挂起，这一整行忽略，流重新复位" << endl;
                infile.clear(); // 状态复位
                infile.ignore(numeric_limits<streamsize>::max(), '\n'); // 把这一行全部清空，复位
                continue;
            }
            Student* stu = new Student(const_cast<char*>(name.c_str()), age, const_cast<char*>(add.c_str()), const_cast<char*>(tel.c_str()), level, gpa);
            insert_Person(stu);
        }
        else if (type == 'E')
        {
            infile >> name >> add >> tel >> age >> hourly_wages;
            if (infile.fail())
            {
                cout << "发现输入流挂起，这一整行忽略，流重新复位" << endl;
                infile.clear(); // 状态复位
                infile.ignore(numeric_limits<streamsize>::max(), '\n'); // 把这一行全部清空，复位
                continue;
            }
            Staff* sta = new Staff(const_cast<char*>(name.c_str()), age, const_cast<char*>(add.c_str()), const_cast<char*>(tel.c_str()), hourly_wages);
            insert_Person(sta);
        }
        else
        {
            cout << "无效的类型，这一整行忽略，流重新复位" << endl;
            infile.clear(); // 状态复位
            infile.ignore(numeric_limits<streamsize>::max(), '\n'); // 把这一行全部清空，复位
        }
    }
    infile.close();
}

void List::WriteFile() // 将内存中链表中节点数据依次写入到指定文件中
{
    string filename;
    cout << "请输入要输出到的文件名：" << endl;
    cin >> filename;
    ofstream outfile;
    outfile.open(filename);
    if (!outfile)
    {
        cout << "文件打开失败，请检查文件路径和权限。" << endl;
        return;
    }

    Person* cur = root;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->next;
    }

    // 按照姓名字段的字典序从小到大排序，输出到文件
    Person* sorted_root = nullptr;
    cur = root;
    while (cur != nullptr)
    {
        Person* temp = cur->next;
        insert_Person(cur);
        cur = temp;
    }

    cur = root;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->next;
    }

    cur = root;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->next;
    }

    cur = root;
    while (cur != nullptr)
    {
        cur->print(outfile);
        cur = cur->next;
    }
    outfile.close();

    // 释放内存
    cur = root;
    while (cur != nullptr)
    {
        Person* temp = cur->next;
        delete cur;
        cur = temp;
    }
    root = nullptr;
}

void Person::print(ofstream& outfile)
{
    outfile << "Person:" << endl;
    outfile << "Name: " << name << " ";
    outfile << "Age: " << age << " ";
    outfile << "Address: " << add << " ";
    outfile << "Tel: " << tel << endl;
}

void Staff::print(ofstream& outfile)
{
    outfile << "Staff:" << endl;
    outfile << "Name: " << name << " ";
    outfile << "Age: " << age << " ";
    outfile << "Address: " << add << " ";
    outfile << "Tel: " << tel << " ";
    outfile << "Hourly Wages: " << hourly_wages << endl;
}

void Student::print(ofstream& outfile)
{
    outfile << "Student:" << endl;
    outfile << "Name: " << name << " ";
    outfile << "Age: " << age << " ";
    outfile << "Address: " << add << " ";
    outfile << "Tel: " << tel << " ";
    outfile << "Level: " << level << " ";
    outfile << "GPA: " << gpa << endl;
}

void Teacher::print(ofstream& outfile)
{
    outfile << "Teacher:" << endl;
    outfile << "Name: " << name << " ";
    outfile << "Age: " << age << " ";
    outfile << "Address: " << add << " ";
    outfile << "Tel: " << tel << " ";
    outfile << "Salary: " << salary << endl;
}

#include "person.h"

int main()
{
    List people;//
    people.ReadFiles();
    people.ReadFiles();
    people.WriteFile();
    return 0;
}
