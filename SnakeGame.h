#include <iostream>
#include <conio.h> 
#include <windows.h> 

using namespace std;

class SnakeGame{
    
// Aqui definimos la clase SnakeGame, la cual contiene sus distintos atributos privados,
// como las dimensiones del juego, el puntaje, distintas coordenadas, etc.
    private:
        // Dimensiones del juego
        const int width = 40; 
        const int height = 20; 

        // Coordenadas:
        int x, y; // Para la cabeza de la serpiente
        int fruitCordX, fruitCordY; // Para la fruta

        int playerScore; // Puntaje del jugador

        int difficulty; // Dificultad del juego

        int snakeTailX[100], snakeTailY[100]; // Array donde se guardan las coordenadas de la cola de la serpiente
        int snakeTailLen; // Longitud de la cola de la serpiente

        enum snakesDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // Enumeracion para direccionar la serpiente
        snakesDirection sDir; // Aqui se guarda la direccion que tomara la serpiente

        bool specialFruit; // Bool para saber si la fruta especial aparecera o no
        bool isGameOver; // Bool para saber si el juego termino

// Tambien contiene las funciones publicas que se encargan de inicializar el juego,
// de imprimir el juego en la pantalla, de actualizar el juego, de definir la dificultad, etc.
    public:
        void GameInit(); // Inicializacion del juego y de sus respectivas variables
        void GameRender(); // Esta funcion se encarga de imprimir el juego en la pantalla, tanto como el espacio, como la serpiente y la fruta
        void UpdateGame(); // Esta funcion se encarga de actualizar el juego, es decir, de actualizar la posicion de la serpiente
        int SetDifficulty(); // Aqui se define la dificultad del juego, es decir que tan rapido se ira imprimiendo el juego
        void UserInput(); // Function to handle user UserInput 
        bool IsGameOver(); // Funcion para saber si el juego termino
};
