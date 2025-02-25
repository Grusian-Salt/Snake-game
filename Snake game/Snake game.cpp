﻿#include <iostream>
#include <ctime>

size_t max_x = 15;
size_t max_y = 43;
size_t start_snake_size = 3;
class apple
{
private:
    int x;
    int y;
public:
    int getX() { return x; }
    int getY() { return y; }
    apple(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    apple()
    {
        x = rand() % max_x;
        y = rand() % max_y;
    }
    void rerandom()
    {
        srand(time(0));
        x = rand() % max_x;
        y = rand() % max_y;
    }
};

class snake
{
private:
    struct Node
    {
        size_t X;
        size_t Y;
        Node* Next;
    };

    Node* head;
    size_t size;
    uint8_t tempDirection;
    bool life;
    char charDirection;

    void createNode(uint8_t direction)
    {
        if (direction == 2 && head->Y < max_y)
        {
            Node* NodeA = new Node{ head->X,head->Y + 1,head };
            head = NodeA;

            charDirection = '>';
        }
        else if (direction == 3 && head->X < max_x)
        {
            Node* NodeA = new Node{ head->X + 1,head->Y,head };
            head = NodeA;
            
            charDirection = '!';
        }
        else if (direction == 4 && head->Y > 0)
        {
            Node* NodeA = new Node{ head->X,head->Y - 1,head };
            head = NodeA;
            charDirection = '<';
        }
        else if (direction == 1 && head->X > 0)
        {
            Node* NodeA = new Node{ head->X - 1,head->Y,head };
            head = NodeA;
            
            charDirection = '^';
        }
        else life = false;
    }
    void search_recursive(Node* temp)
    {
        if (temp->X == head->X && temp->Y == head->Y) life = false;
        else
        {
            if (temp->Next != nullptr) search_recursive(temp->Next);
        }
    }
    bool delete_recursive(Node* node)
    {
        if (node->Next != nullptr)
        {
            if (delete_recursive(node->Next) == true) node->Next = nullptr;

        }
        else
        {
            delete node;
            return true;
        }
        return false;
    }

public:
    snake()
    {
        size = start_snake_size;
        head = nullptr;
        tempDirection = 2;
        charDirection = '>';
        life = true;
        for (size_t i = 0; i < start_snake_size; i++)
        {
            Node* NodeA = new Node{ max_x / 2,2 + i,head };
            head = NodeA;
        }
    }
    Node* getHead() { return head; }
    void snakeGo(uint8_t direction, apple* app)
    {
        //Создаём голову
        if (direction == 0) direction = tempDirection;
        createNode(direction);
        //Проверяем, находится ли голова в теле с помощью рекурсии
        Node* temp = head->Next;
        search_recursive(temp);
        //Проверяем, съела ли змея яблоко
        bool deltemp = true;
        if (head->X == app->getX() && head->Y == app->getY())
        {
            size++;
            deltemp = false;
            //Удаляем яблоко
            app->rerandom();
        }
        //Удаляем крайний Node змеи
        if (deltemp == true)delete_recursive(head->Next);
        tempDirection = direction;
    }
    bool public_search_recursive(Node* temp1, size_t X, size_t Y)
    {
        if (temp1->X == X && temp1->Y == Y) return true;
        else
        {
            if (temp1->Next != nullptr)
            {
                if (public_search_recursive(temp1->Next, X, Y) == true) return true;
            }
        }
        return false;
    }
    char getCharDirection(){return charDirection;}
    size_t getSize() { return size; }
    bool getLife() { return life; }
};

uint8_t why(char key)
{
    if (key == 'w' || key == 'W') return 1;
    else if (key == 'd' || key == 'D') return 2;
    else if (key == 's' || key == 'S') return 3;
    else if (key == 'a' || key == 'A') return 4;
    return 0;
}
void gameRestart(apple* app, snake* snk)
{

}
void print(apple* app, snake* snk)
{
    std::cout << "Size:"<<snk->getSize()<<std::endl;
    std::cout << "*";
    for (int i = 0; i < max_y; i++) { std::cout << "-"; }
    std::cout << "*" << std::endl;
    for (int i = 0; i < max_x; i++)
    {
        std::cout << "|";
        for (int j = 0; j < max_y; j++)
        {
            if(snk->getHead()->X == i && snk->getHead()->Y == j) std::cout << snk->getCharDirection();
            else if (snk->public_search_recursive(snk->getHead(), i, j) == true) std::cout << "#";
            else if (app->getX() == i && app->getY() == j) std::cout << "@";
            else std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "*";
    for (int i = 0; i < max_y; i++) { std::cout << "-"; }
    std::cout << "*" << std::endl;
}

int main()
{
    snake snk;
    apple app;
    char key;
    while (snk.getLife() == true && snk.getSize()<max_x * max_y)
    {
        print(&app, &snk);
        std::cin >> key;
        snk.snakeGo(why(key), &app);
        system("CLS");
    }


}



