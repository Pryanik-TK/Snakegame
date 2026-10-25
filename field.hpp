#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <conio.h>
#include <windows.h>
#include "point.hpp"

class Snake;
class Field;
class Apple;
class Game;

class Field{
    private: 
        static constexpr int size = 13; 
        char field[size][size] {
            {'|', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '|'},
            {'|', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '|'}
        };

    public: 

        void display(){
            for (int i=0; i < size; i++){
                for (int j=0; j < size; j++){
                    std::cout << field[i][j] << ' ';
                }
                std::cout << '\n';
            }
        }

        void draw_apple(Point apple){
            field[apple.x][apple.y] = '@';
        }

        void draw_point(Point draw){
            field[draw.x][draw.y] = '#';
        }

        void erase_point(Point erase){
            field[erase.x][erase.y] = '.';
        } 

        friend void initialize_field(Field& field, Snake& snake);
};

class Snake{
    private:
        static constexpr Point move_error = {-1, -1};

        std::vector<Point> body{{7,5}, {7, 6}, {7, 7}};
        bool alive = 1;
        int size = 3;
        char cur_way = 'd';
        const std::set<char> ways = {'w', 'a', 's', 'd'};        

        void move(Point head){
            for (int i = 0; i < size - 1; i++){
                body[i] = body[i+1]; 
            }

            body[size - 1] = head;
        }

    public:        

        void grow(Point head){
            body.push_back(head);
            size++;
        }

        void check_alive(Point new_head){
            if (new_head.x == 0 || new_head.x == 12 || new_head.y == 0 || new_head.y == 12){
                alive = false;
            }
        }

        void next_step(){
            Point res = body[size - 1];
            switch(cur_way){
                case 'w':
                    res.x--;
                break;

                case 's':
                    res.x++;
                break;

                case 'a':
                    res.y--;
                break;

                case 'd':
                    res.y++;
                break;
                
                default:
                    
                break;

            }
            check_alive(res);

            if (alive){
                move(res);
            }
        }

        bool is_alive(){
            return alive;
        }

        Point get_head(){
            return body[size-1]; 
        }

        Point get_tail(){
            return body[0];
        }

        char get_way(){

            if (kbhit()){
                char move = getch();
                if ((ways.find(move) != ways.end())){
                    cur_way = move;
                }
            }
            else {
                Sleep(500);
            }

            return cur_way;
        }

        friend void initialize_field(Field& field, Snake& snake);
};

class Apple{
    private:
        Point position;

    public:
        Point get_position(){
            return position;
        }

        void set_position(Point tmp){
            position = tmp;
        }


};

class Game{
    public:
        void step(Field& field, Snake& snake){
            field.erase_point(snake.get_tail());
            snake.get_way();
            snake.next_step();
            if (snake.is_alive()){                
                field.draw_point(snake.get_head());
                field.display();
            }
        }
};