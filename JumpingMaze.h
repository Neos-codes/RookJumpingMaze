#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef struct{

    int val;                 // 0 = Goal
    char dir;                // Letra que guarda la dirección en que se llegó a este nodo
    std::pair<int,int> p;    // Coordenadas de la posición del padre de este nodo
    bool visited = false;    // visitado = true

}node;

class JumpingMaze{
    public:
        // Metodos
        JumpingMaze(node **maze, int n, int m, int sf, int sc, int df, int dc);   // Constructor
        int Resolve();


    private:
        // Variables
        std::queue<std::pair<int,int>> nodes;  // Cola para BFS
        std::queue<std::pair<int,int>> visit;  // Almacena todos los nodos visitados
        std::vector<char> path;                // Almacenamos las direcciones que llevan a la solucion
        node **maze;               // Aqui almacenamos el maze como matriz
        int sf, sc;                // sf: Fila celda inicio, sc: Columna celda inicio
        int df, dc;                // df; Fila celda destino, dc: Columna celda destino
        int n;                     // Filas laberinto
        int m;                     // Columnas laberinto
        bool solved = false;       // solved = true, laberinto tiene solucion
        // Metodos
        void BFS();
        int Backtracking();        // Retorna la cantidad de pasos para resolver el laberinto
        void PrintMatrix();        // Imprime el laberinto
        void PrintPath();          // Imprime el camino solucion desde el nodo de inicio
        void VisitedMatrix();      // Imprime la matriz de nodos visitados
        void VisitedNodes();       // Imprime en orden los nodos visitados


};

// Constructor
JumpingMaze::JumpingMaze(node **maze, int n, int m, int sf, int sc, int df, int dc){
    this -> maze = maze;
    // Guardar dimensiones
    this -> n = n;
    this -> m = m;
    // Guardar coordenadas celda de inicio
    this -> sf = sf;
    this -> sc = sc;
    // Guardar coordenadas celda de destino
    this -> df = df;
    this -> dc = dc;
    // Nodo raiz se marca cuyo nodo padre es (-1, -1)
    this -> maze[sf][sc].p.first = -1;
    this -> maze[sf][sc].p.second = -1;
    this -> maze[df][dc].val = 0;
}

int JumpingMaze::Resolve(){
    this -> BFS();
    return Backtracking();
}

void JumpingMaze::BFS(){

    // Introducir inicio en la cola
    nodes.push(std::make_pair(sf,sc));
    visit.push(std::make_pair(sf,sc));
    // Marcar como visitado
    maze[sf][sc].visited = true;

    // Iterar hasta terminar BFS
    while(!nodes.empty()){

        int f = nodes.front().first;     // Fila del nodo actual
        int c = nodes.front().second;    // Columna del nodo actual

        //std::cout << "Visitando posicion " << f << " " << c << " con alcance " << maze[f][c].val << std::endl;

    // Primero, revisar si es el nodo de destino
        if(maze[f][c].val == 0){
            // Si lo es, marcar como resuelto y salir del ciclo
            //std::cout << "Meta conseguida!" << std::endl;
            solved = true;
            break;
        }

        // Revisar 4 direcciones para añadir a la cola
        int range = maze[f][c].val;
        // Hacia arriba
        if(f - range >= 0){
            if(!maze[f - range][c].visited){  // condicion en 2 if para evitar segmentation fault
                //std::cout << "Puedo ir hacia arriba! La pos es: [" << f - range << "][" << c << "]" << std::endl;
                // Añadir a la cola para BFS
                nodes.push(std::make_pair(f - range, c));
                // Añadir a la cola de nodos visitados
                visit.push(std::make_pair(f - range, c));
                // Guardar direccion que se tomo para llegar a este nodo
                maze[f - range][c].dir = 'u';
                // Asignar padre
                maze[f - range][c].p.first = f;
                maze[f - range][c].p.second = c;
                // Marcar como visitado
                maze[f - range][c].visited = true;
            }
        }
        // Hacia abajo
        if(f + range < n){
            if(!maze[f + range][c].visited){
                //std::cout << "Puedo ir hacia abajo! La pos es: [" << f + range << "][" << c << "]" << std::endl;
                // Añadir a la cola
                nodes.push(std::make_pair(f + range, c));
                // Añadir a la cola de nodos visitados
                visit.push(std::make_pair(f + range, c));
                // Guardar la direccion que se tomo para llegar a este nodo
                 maze[f + range][c].dir = 'd';
                // Asignar padre
                maze[f + range][c].p.first = f;
                maze[f + range][c].p.second = c;
                // Marcar como visitado
                maze[f + range][c].visited = true;
            }
        }
        // Hacia la derecha
        if(c + range < m){
            if(!maze[f][c + range].visited){
                //std::cout << "Puedo ir hacia la derecha! La pos es: [" << f << "][" << c + range << "]" << std::endl;
                // Añadir a la cola
                nodes.push(std::make_pair(f, c + range));
                // Añadir a la cola de nodos visitados
                visit.push(std::make_pair(f, c + range));
                // Guardar la direccion que se tomo para llegar a este nodo
                maze[f][c + range].dir = 'r';
                // Asignar padre
                maze[f][c + range].p.first = f;
                maze[f][c + range].p.second = c;
                // Marcar como visitado
                maze[f][c + range].visited = true;
            }
        }
        // Hacia la izquierda
        if(c - range >= 0){
            if(!maze[f][c - range].visited){
                //std::cout << "Puedo ir hacia la izquierda! La pos es: [" << f << "][" << c - range << "]" << std::endl;
                // Añadir a la cola
                nodes.push(std::make_pair(f, c - range));
                // Añadir a la cola de visitados
                visit.push(std::make_pair(f, c - range));
                // Guardar la direccion que se tomo para llegar a este nodo
                maze[f][c - range].dir = 'l';
                // Asignar padre
                maze[f][c - range].p.first = f;
                maze[f][c - range].p.second = c;
                // Marcar como visitado
                maze[f][c - range].visited = true; 
            }
        }
        //std::cout << "Posicion: [" << nodes.front().first << "][" << nodes.front().second << "] popped!" << std::endl;
        nodes.pop();
    }
    
    // Imprimir Matriz Almacenada
    //PrintMatrix();

    // Imprimir Nodos visitados
    //VisitedNodes();

    // Imprimir matriz de visitados
    //VisitedMatrix();

}

int JumpingMaze::Backtracking(){
    
    //std::cout << "Bactracking..." << std::endl;

    if(solved){
        int steps = 0;        // Contador de pasos que toma llegar a la meta
        int f = df, c = dc;   // Aqui guardamos las coordenadas de los nodos padres
        while(maze[f][c].p.first != -1 && maze[f][c].p.second != -1){
            //std::cout << "Padre de nodo " << f << " " << c << ": " << maze[f][c].p.first << " " << maze[f][c].p.second << std::endl;
            // Antes del backtracking, guardamos la direccion que siguio el padre
            path.push_back(maze[f][c].dir);
            // Vamos al padre por las coordenadas almacenadas en el hijo
            int aux_f = f;
            f = maze[f][c].p.first;
            c = maze[aux_f][c].p.second;
            steps++;
        }
        // Para imprimir el camino desde el nodo inicial
        PrintPath();
        return steps;
    }

    else
        return -1;
}

void JumpingMaze::VisitedMatrix(){
    std::cout << "Visited matrix" << std::endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cout << maze[i][j].visited;
        }
        std::cout << std::endl;
    }
}

void JumpingMaze::VisitedNodes(){

    std::queue<std::pair<int,int>> aux =  this -> visit;

    std::cout << "Lista de visitados: " << std::endl;
    while(!aux.empty()){
        std::cout << "(" << aux.front().first << ", " << aux.front().second << ")" << std::endl;
        aux.pop();
    }
}

void JumpingMaze::PrintMatrix(){
    std::cout << "Matriz Almacenada" << std::endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            std::cout << maze[i][j].val << " ";
        std::cout << std::endl;
    }
}

void JumpingMaze::PrintPath(){
    std::cout << "Camino a la solucion:" << std::endl;
    int len = path.size();
    for(int i = len - 1; i >= 0; i--){
        if(path[i] == 'u')
            std::cout << "Up ";
        else if(path[i] == 'd')
            std::cout << "Down ";
        else if(path[i] == 'r')
            std::cout << "Right ";
        else
            std::cout << "Left ";
    }
    std::cout << std::endl;
}