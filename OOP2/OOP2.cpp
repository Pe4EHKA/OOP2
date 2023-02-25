#include <iostream>

#include <conio.h>

class Square {
private:
    int side;
    int perimeter;
    int area;
    int which_constructor;
public:
    Square() {  // Конструктор
        printf("Square()\n");
        side = 1;
        perimeter = 4;
        area = 1;
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
    ~Square() {
        printf("~Square(%d)\n", which_constructor);
        printf("%d, %d, %d\n", side, perimeter, area);
    }

};


int main()
{
    setlocale(LC_ALL, "Russian");
    printf("------Статически создаваемые объекты------\n");
    Square First;
    Square Second(5);
    Square Third(Second);
    _getch();
    printf("------Динамически создаваемые объекты------\n");
    Square* s1 = new Square;
    Square* s2 = new Square(10);
    Square* s3 = new Square(*s2);
    printf("------Удаление динамически созданных объектов------\n");
    delete s1;
    delete s2;
    delete s3;


    return 0;
}

