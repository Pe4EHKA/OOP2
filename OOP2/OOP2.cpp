#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

class Square {
protected:
    int side;
    int perimeter;
    int area;
    int which_constructor;
public:
    Square() : side(3), perimeter(12), area(9), which_constructor(1) {  // Конструктор
        printf("Square()\n");
    }
    Square(int side) {  // Конструктор с параметрами
        printf("Square(int side)\n");
        this->side = side;
        perimeter = side * 4;
        area = side * side;
        which_constructor = 2;
    }
    Square(const Square &other) {  // Конструктор копирования
        printf("Square(const Square &other)\n");
        side = other.side;
        perimeter = other.perimeter;
        area = other.area;
        which_constructor = 3;
    }
    ~Square() {  // Деструктор
        printf("~Square(%d)\n", which_constructor);
        printf("%d, %d, %d\n", side, perimeter, area);
    }

    void increase_side(int add) {
        side = side + add;
        perimeter = side * 4;
        area = side * side;
    }

    void reset_side();

};

void Square::reset_side() {
    side = 3;
    perimeter = side * 4;
    area = side * side;
}

// Сделать класс - потомок для вывода изображения (квадрата)
// с нужными размерами

class ViewedSquare : public Square {
private:
    std::vector<std::vector<std::string>> sqr;
public:
    ViewedSquare() : Square() {  // Конструктор
        printf("ViewedSquare()\n");
        sqr.resize(side);
        for (int i = 0; i < side; ++i) {
            sqr[i].resize(side);
        }
    }
    ViewedSquare(int side, std::vector<std::vector<std::string>> sqr) : Square(side) {  // Конструктор с параметрами
        printf("ViewedSquare(int side)\n");
        this->side = side;
        this->sqr = sqr;
    }
    ViewedSquare(const ViewedSquare& other) : Square(other),  sqr(other.sqr) {  // Конструктор копирования
        printf("ViewedSquare(const ViewedSquare &other)\n");
    }
    ~ViewedSquare () {  // Деструктор
        printf("~ViewedSquare(%d)\n", which_constructor);
        printf("%d, %d, %d\n", side, perimeter, area);
    }

    void View() {
        sqr.resize(side);
        for (int i = 0; i < side; ++i) {
            sqr[i].resize(side);
        }
        for (int i = 0; i < side; ++i) {
            if (i == 0 || i == side - 1) {
                for (int j = 0; j < side; ++j) {
                    sqr[i][j] = "X";
                }
            }
            else {
                sqr[i][0] = "X";
                sqr[i][side - 1] = "X";
            }
        }
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                if (sqr[i][j] == "X") {
                    printf("%s", sqr[i][j].c_str());
                    
                }
                else {
                    printf("%c", ' ');
                }
            }
            printf("\n");
        }
        printf("\n");
    }


};

class HowMuch{
private:
    Square k1;
    Square k2;
public:
    HowMuch() {  // Конструктор
        printf("HowMuch()\n");
        k1.reset_side();
        k2.reset_side();
    }
    HowMuch(int side) : k1(side), k2(side) {  // Конструктор с параметрами
        printf("HowMuch(int side)\n");
    }
    HowMuch(const HowMuch& other) : k1(other.k1), k2(other.k2) {  // Конструктор копирования
        printf("HowMuch(const HowMuch &other)\n");
    }
    ~HowMuch() {  // Деструктор
        printf("~HowMuch(?)\n");
    }

};

class HowMuch2 {
private:
    Square* k1;
    Square* k2;
public:
    HowMuch2() : k1(new Square), k2(new Square) {  // Конструктор
        printf("HowMuch2()\n");
        //k1 = new Square;
        //k2 = new Square;
    }
    HowMuch2(int side) : k1(new Square(side)), k2(new Square(side)) {  // Конструктор с параметрами
        printf("HowMuch2(int side)\n");
        //k1 = new Square(side);
        //k2 = new Square(side);
    }
    HowMuch2(const HowMuch2& other) : k1(new Square(*(other.k1))), k2(new Square(*(other.k2))) {  // Конструктор копирования
        printf("HowMuch2(const HowMuch2 &other)\n");
        //k1 = new Square(*(other.k1));
        //k2 = new Square(*(other.k2));
    }
    ~HowMuch2() {  // Деструктор
        printf("~HowMuch2(?)\n");
        delete k1;
        delete k2;
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("------Статически создаваемые объекты------\n");
    Square First;
    Square Second(5);
    Square Third(Second);
    First.increase_side(3);
    Second.reset_side();
    _getch();
    printf("------Динамически создаваемые объекты------\n");
    Square* s1 = new Square;
    Square* s2 = new Square(10);
    Square* s3 = new Square(*s2);
    _getch();
    printf("------Удаление динамически созданных объектов------\n");
    delete s1;
    delete s2;
    delete s3;
    _getch();
    printf("------Наследование------\n");
    std::vector<std::vector<std::string>> sqr;
    int side = 5;
    ViewedSquare* p1 = new ViewedSquare();
    ViewedSquare* p2 = new ViewedSquare(5, sqr);
    ViewedSquare* p3 = new ViewedSquare(*p2);
    p2->increase_side(3);
    p2->View();
    p3->View();
    p3->reset_side();
    p3->View();
    delete p1;
    delete p2;
    delete p3;
    _getch();

    printf("------Перемещение объектов в переменные различных типов------\n");

    Square* obj = new ViewedSquare();
    // У obj есть методы только базового класса
    ViewedSquare* obj2 = new ViewedSquare(6, sqr);
    // У obj2 есть также методы класса потомка
    delete (ViewedSquare*)obj;  // Привел к типу указателя, для которого была выделена память 
    delete obj2;

    printf("------Композиция(Объектом класса А является другой объект класса B)------\n");

    HowMuch hey1;
    printf("_____---__-__\n");
    HowMuch hey2(5);
    HowMuch hey3(hey2);

    printf("------Композиция(Объект класса А является !указатель! на другой объект класса B)------\n");

    HowMuch2* ob1 = new HowMuch2;
    HowMuch2* ob2 = new HowMuch2(5);
    HowMuch2* ob3 = new HowMuch2(*ob1);
    delete ob1;
    delete ob2;
    delete ob3;

    printf("------(Деструкторы)Статически создаваемые объекты------\n");


    return 0;
}

