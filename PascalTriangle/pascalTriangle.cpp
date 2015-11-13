#include <iostream>
#include "console.h"
#include "strlib.h"
#include "grid.h"

using namespace std;

void fillGrid(Grid<int>& grid, int value);
void buildTriangle(Grid<int>& grid);
int recursiveTriangle(int row, int col);

// Console settings
void consoleSettings();
const string programTitle = "pascalTriangle";
const bool consoleEcho = false;

int main() {
   consoleSettings();
   /* User input */
   int nHeight = 5;
   int gridColumns = (2 * nHeight - 1);
   Grid<int> grid (nHeight, gridColumns);
   fillGrid(grid, 0);

   buildTriangle(grid);


   /* Result spiral printing */
   for(int i = 0; i < grid.numRows(); i++){
       for(int u = 0; u < grid.numCols(); u++){
           cout << grid[i][u];
       }
       cout << endl;
   }
   cout << "=================" << endl;

   cout << recursiveTriangle(4, 1);

   return 0;
}

int recursiveTriangle(int row, int col){
    if(col == 0){
        return 1;
    }else if (col == row){
        return 1;
    }else{
        int result = (recursiveTriangle((row - 1), (col - 1))
                      + recursiveTriangle((row - 1), (col)));
        cout << "Row " << row << " Col " << col << " Result " << result << endl;
        return result;
    }
}

/* Needs to fill grid by escapes */
void fillGrid(Grid<int>& grid, int value){
    for(int i = 0; i < grid.numRows(); i++){
        for(int u = 0; u < grid.numCols(); u++){
            grid[i][u] = value;
        }
    }
}

void buildTriangle(Grid<int>& grid){
    /*Fill first cell*/
    int centralCell = (grid.numCols() / 2);
    grid.set(0, centralCell, 1);
    /* For each row  */
    for(int row = 1; row < grid.numRows(); row++){
        for(int col = 0; col <= row; col++){
            int pascalValue = 1;
            grid.set(row, (centralCell - row + (2 * col)), pascalValue);
        }
    }
}



/* Make console output window more convenient */
void consoleSettings(){
    setConsoleWindowTitle(programTitle);
    setConsoleEcho(consoleEcho);
}
