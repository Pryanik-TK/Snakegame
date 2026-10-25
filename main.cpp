#include "headers.hpp"

int main(){
    Snake snake;
    Field field;
    Game game;

    initialize_field(field, snake);

    field.display();
    while(snake.is_alive()){
        game.step(field, snake);
        std::cout << '\n';
    }
    std::cout << "Ebat ty loh, v stenu v'ebalsa\n";

    return 0;
}