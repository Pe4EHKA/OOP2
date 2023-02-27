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
    Square() {  // Конструктор
        printf("Square()\n");
        side = 3;
        perimeter = 12;
        area = 9;
        which_constructor = 1;
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

    void increase_side() {
        side = side + 2;
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
        this->sqr = sqr;
    }
    ViewedSquare(const ViewedSquare& other) {  // Конструктор копирования
        printf("ViewedSquare(const ViewedSquare &other)\n");
        side = other.side;
        perimeter = other.perimeter;
        area = other.area;
        this->sqr = other.sqr;
        which_constructor = 3;
        
    }
    ~ViewedSquare () {  // Деструктор
        printf("~ViewedSquare(%d)\n", which_constructor);
        printf("%d, %d, %d\n", side, perimeter, area);
        delete ViewedSquare;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("------Статически создаваемые объекты------\n");
    Square First;
    Square Second(5);
    Square Third(Second);
    First.increase_side();
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
    p2->increase_side();
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
    delete obj;  // Не вызывается деструктор класса потомка!?
    delete obj2;

    printf("------Композиция------\n");



    return 0;
}

