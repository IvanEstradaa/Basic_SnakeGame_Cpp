#include "SnakeGame.h"

// To compile program, insert the next command line in terminal: 
//x86_64-w64-mingw32-g++ -o output.exe *.cpp --static && output.exe

void SnakeGame::GameInit(){ 
	isGameOver = false; 
	sDir = STOP; 
	x = width / 2; 
	y = height / 2; 
	fruitCordX = rand() % width; 
	fruitCordY = rand() % height; 
	specialFruit = false;
	playerScore = 0; 
}

void SnakeGame::GameRender(){ 
	system("cls"); // Limpiamos la consola/terminal

	// Paredes de arriba
	for(int i = 0; i < width + 2; i++){
		cout << "-";
    }
	cout << endl; 

	for(int i = 0; i < height; i++){ 
		for (int j = 0; j <= width; j++){ 
			// Imprimimos las paredes laterales al inicio y al final de cada linea de impresion
			if(j == 0 || j == width){
				cout << "|"; 
            }
			else if(i == y && j == x){ // Cuando nos encontramos en las coordenadas de la cabeza de la serpiente, imprimimos "O" 
				cout << "O";
            }
			else if(i == fruitCordY && j == fruitCordX){ // Cuando nos encontramos en las coordenadas aleatorias de la fruta, imprimimos "@" 
				if(specialFruit){
					cout << "$"; // Fruta especial
				}
				else{
					cout << "@"; // Fruta normal
				}
            }
			else{ 
				bool prTail = false; // Bool para saber si se imprimio la cola de la serpiente
				for(int k = 0; k < snakeTailLen; k++){ 
					if (snakeTailX[k] == j && snakeTailY[k] == i){ 
						cout << "o"; 
						prTail = true; 
					} 
				} 
				if(!prTail){
					cout << " ";
                }
			} 
		} 
		cout << endl; 
	} 

	// Paredes de abajo
	for (int i = 0; i < width + 2; i++) 
		cout << "-"; 
	cout << endl; 

	// Finalmente imprimimos el puntaje del jugador 
	cout << "Score: " << playerScore << endl; 
} 

void SnakeGame::UpdateGame(){ 
	// Guardamos las coordenadas de la cola de la serpiente
	int prevX = snakeTailX[0]; 
	int prevY = snakeTailY[0]; 
	int prev2X, prev2Y; 
	snakeTailX[0] = x; 
	snakeTailY[0] = y; 

	for (int i = 1; i < snakeTailLen; i++){ // Actualizamos las coordenadas de la cola de la serpiente 
		// Guardamos la segunda coordenadas de la cola de la serpiente
		prev2X = snakeTailX[i]; 
		prev2Y = snakeTailY[i]; 
		// Actualizamos las coordenadas de la cola de la serpiente
		snakeTailX[i] = prevX; 
		snakeTailY[i] = prevY; 
		// Actualizamos las primeras coordenadas de la cola de la serpiente con las segunda coordenadas de la cola de la serpiente
		prevX = prev2X; 
		prevY = prev2Y; 
	} 

	// Actualizamos la direccion de la serpiente, para ello modificamos las coordenadas x o y de la cabeza de la serpiente
	switch (sDir) { 
	case LEFT: 
		x--; 
		break; 
	case RIGHT: 
		x++; 
		break; 
	case UP: 
		y--; 
		break; 
	case DOWN: 
		y++; 
		break; 
	} 

	// Revisa si la serpiente se sale de los limites del juego
	if((x >= width || x < 0 || y >= height || y < 0) && this->difficulty != 1){
		isGameOver = true; 
    }
	else{ // si la dificultad esta en facil (1), el juego no termina al salirse de los limites del mapa
		if(x >= width){
			x = 0;
		}
		else if(x < 0){
			x = width - 1;
		}
		if(y >= height){
			y = 0;
		}
		else if(y < 0){
			y = height - 1;
		}
	}

	// Revisa si la serpiente se come a si misma
	for(int i = 0; i < snakeTailLen; i++){ 
		if (snakeTailX[i] == x && snakeTailY[i] == y){
			isGameOver = true;
        }
	} 

	// Revisa si la serpiente se come la fruta
	if(x == fruitCordX && y == fruitCordY){ 
		if(specialFruit == true){ // Si la fruta es especial, el puntaje aumenta en 50
			playerScore += 50;
		}
		else{
			playerScore += 10;
		}
		// Se vuelve a generar una fruta con coordenadas aleatorias
		fruitCordX = rand() % width; 
		fruitCordY = rand() % height; 
		if((rand() % width) % 12 == 0){
			specialFruit = true;
		}
		else{
			specialFruit = false;
		}
		snakeTailLen++; // Incrementamos la longitud de la cola de la serpiente
	} 
} 

int SnakeGame::SetDifficulty(){ 
	int dfc;
	cout << "\nControles:"
			"\nw = arriba a = izquierda"
			"\ns = abajo d = derecha"
			"\nx = Finalizar Juego\n"
			"\nSelecciona la dificultad del juego"
            "\nFacil....(1)"
            "\nNormal...(2)"
            "\nDificil..(3)\n"
			"\n::Si no se selecciona una dificultad, la dificultad se establecera como Normal::\n"
            "\n-> "; 
	cin >> this->difficulty;
	switch(this->difficulty){ 
	case 1: 
		dfc = 150;
		break; 
	case 2: 
		dfc = 100; 
		break; 
	case 3: 
		dfc = 25; 
		break; 
	default: 
		dfc = 50; 
		this->difficulty = 2;
		break;
	} 
	return dfc; 
} 

// Function to handle user UserInput 
void SnakeGame::UserInput(){ 
	if (_kbhit()){ // _kbhit() es un funcion que detecta si se presiono una tecla 
		switch (_getch()) { // _getch() es una funcion que obtiene el caracter presionado
		case 'a': 
			sDir = LEFT; 
			break; 
		case 'd': 
			sDir = RIGHT; 
			break; 
		case 'w': 
			sDir = UP; 
			break; 
		case 's': 
			sDir = DOWN; 
			break; 
		case 'x': 
			isGameOver = true; 
			break; 
		} 
	} 
    // tanto _kbhit() como _getch() son funciones de la libreria conio.h
} 

bool SnakeGame::IsGameOver(){
	return isGameOver;
}

// En la funcion main se ejecuta el juego y llamamos a las distintas funciones
// para que el juego funcione
int main(){ 
	SnakeGame game;

	int dfc = game.SetDifficulty(); // Seteamos la dificultad del juego

	game.GameInit(); // Inicializamos el juego con sus valores iniciales
	while(!game.IsGameOver()){ 
		game.GameRender(); 
		game.UserInput(); 
		game.UpdateGame(); 
		Sleep(dfc); // El delay con el que la pantalla se ira imprimiendo, depende de la dificultad ingresada al inicio
	} 

	return 0; 
}