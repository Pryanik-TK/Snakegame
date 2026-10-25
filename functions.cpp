#include "headers.hpp"

void initialize_field(Field& field, Snake& snake){
    for(int i=0; i < snake.size; i++){
        field.draw_point(snake.body[i]);
    }
}