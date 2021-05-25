#include "JumpingMaze.h"

using namespace std;

int main(){

    int n, m;        // n: filas   m: columnas
    int sf, sc;      // sf: fila celda inicio   sc: columna celda inicio
    int df, dc;      // df: fila celda destino   dc: columna celda destino
    
    while(1){

        cin >> n;
        
        if(n == 0)    // Si n = 0, terminar programa
            return 0;
        cin >> m >> sf >> sc >> df >> dc;


        // Definir laberinto
        node **maze;
        maze = (node **)malloc(n * sizeof(node *));
        for(int i = 0; i < n; i++){
            maze[i] = (node *)malloc(m * sizeof(node));
        }

        // Leer laberinto
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> maze[i][j].val;
                maze[i][j].visited = false;
            }
        }

        // Crear obj laberinto para resolver
        JumpingMaze jm = JumpingMaze(maze, n, m, sf, sc, df, dc);
        // Resolver
        int res = jm.Resolve();

        if(res != -1)
        // Pasos que toma resolver el laberinto
            cout << res << endl;
        else
            cout << "No tiene solucion" << endl;
    
    }

}

