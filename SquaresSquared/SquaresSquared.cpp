#include <iostream>
#include "console.h"
#include "strlib.h"
#include "grid.h"

using namespace std;

string getStringSequence(long long startInt, long long endInt);
int getInternalRectSide(int digitsQty, int initSize);
string addStars(string output,int internalRectSide);
int getExternalRectSide(int internalRectSide);

void createSpiral(int externalRectSide, int internalRectSide, string numbers);
Grid<int> findStartPoint(auto& grid, int internalRectSide);
void getNextDirection(auto& previousDirection);
void fillGrid(Grid<string>& grid, string value);
void buildSpiral(auto& grid, auto cellPointer, string outputString, int stepsQty);

string recursiveLongLongToString(long long intValue, string result);

// Console settings
void consoleSettings();
const string programTitle = "SquaresSquared";
const bool consoleEcho = false;

int main() {
   consoleSettings();
   /* User input */
   long long startNum = 10LL;
   /* I not managed to solve problem of end values -
    * I have got stack overflow error */
   long long endNum = 1000000LL * 1000000LL;

cout << recursiveLongLongToString(endNum, "") << endl;
   /* Two user's numbers create sequence */
   string output = getStringSequence(startNum, endNum);
cout << output << endl;
   /* Determines size of internal rectangle in spiral */
   int internalRectSide = getInternalRectSide(output.length(), 1);
   /* Add star symbols to output string to fill whole internal rectangle  */
   output = addStars(output, internalRectSide);

   /* Shows sequence which  will create spiral */
   cout << "Result string to display " << output << endl;
   cout << "Internal rectangle side length " << internalRectSide << endl;

   /* Determines size of external spiral-rectangle side length */
   int externalRectSide = getExternalRectSide(internalRectSide);
   cout << "Neccessary external spiral side length " << externalRectSide << endl;

   /* Builds spiral with obtained output number */
   createSpiral(externalRectSide, internalRectSide, output);

   return 0;
}

/* Get sequence of numbers from start value to end value
 * each new value will be rised to square last value
 * Here is problem with this function - modifing integers
 * values wich hiegher 1*e9 is not correct  */
string getStringSequence(long long startNum, long long endNum){
    if(startNum > endNum){
        return "";
    }else{       
        long long nextValue = startNum * startNum;
        string result = recursiveLongLongToString(startNum, "")+ getStringSequence(nextValue, endNum);
        return result;
    }
}

/* Recursive loop process */
string recursiveLongLongToString(long long intValue, string result){
    /* Divide input value in two parts - n/10 and n%10 */
    long long nextValue = intValue/10;
    if(nextValue == 0){
        /* Returns string value of integer */
        return ((char)(intValue + '0') + result);
    }else{
        /* finds remain of n%10 process and concantenate it to result  */
        long long remain = intValue % 10;
        char remainChar = (char)(remain + '0');
        result = remainChar + result;
        return recursiveLongLongToString(nextValue, result);
    }
}

/* Get side length of rectangle wich will be displaed */
int getInternalRectSide(int digitsQty, int initSize){
    if(digitsQty <= (initSize * initSize)){
        return initSize;
    }else{
        initSize++;
        return getInternalRectSide(digitsQty, initSize);
    }
}

/* Concantenate as many stars to obtained sequence as neccessary
 * to fill whole internal rectangle */
string addStars(string output, int internalRectSide){
    int maxLength = internalRectSide * internalRectSide;
    if(output.length() == maxLength){
        return output;
    }else{
        output += "*";
       return addStars(output, internalRectSide);
    }
}

/* Get side length of external rectangle which is neccessary to
 * insert internal rect with turn angle - 45 degrees */
int getExternalRectSide(int internalRectSide){
    return ((2 * internalRectSide) - 1);
}

/* Build output spiral with obtained output sequence digits */
void createSpiral(int externalRectSide, int internalRectSide, string outputString){
    /* External rectangle grid */
    Grid<string> grid (externalRectSide, externalRectSide);
    fillGrid(grid, " ");
    /* Pointer cell grid - current coordinates store to movie across external grid */
    Grid<int> cellPointer (1, 2);
    /* Fills pointer by coordinates of first cell into grid - center of spiral */
    cellPointer = findStartPoint(grid, internalRectSide);
    /* Fills start cell by first symbol value */
    grid[(cellPointer[0][0])][(cellPointer[0][1])] = outputString[0];
    /* Maximum possible quantity of steps is equal to internal rectangle cells quantity */
    int stepsQty = internalRectSide * internalRectSide;
    /* Main spiral building process */
    buildSpiral(grid, cellPointer, outputString, stepsQty);
    /* Result spiral printing */
    for(int i = 0; i < grid.numRows(); i++){
        for(int u = 0; u < grid.numCols(); u++){
            cout << grid[i][u];
        }
        cout << endl;
    }
}

/* Main process - make all possible steps after start cell filling:
 * - each new step fills next cell by digit from outputString
 * - filled cells create a spiral into internal rectangle wich turned in 45 degrees */
void buildSpiral(auto& grid, auto cellPointer, string outputString, int stepsQty){
    /* Direction pointer - store for values of moving direction (dY, dX) through grid */
    Grid<int> dir(1,2);
    /* Start step direction settings - Y - 1 step down, X - 1 step right */
    dir.set(0,0,1); //dY
    dir.set(0,1,1); //dX
    /* Index to count steps of movements with filling cells - start cell is filled yet  */
    int moveIndex = 1;
    /* Value of steps wich have to be made in each direction */
    int stepsDueDirection = 1;
    /* Main spiral movements */
    while(moveIndex < stepsQty){
        /* Make sides of spiral of same length */
        for(int stepsPair = 0; stepsPair < 2; stepsPair++){
            if(moveIndex < stepsQty){
                for(int step = 1; step <= stepsDueDirection; step++){
                    /* One spiral side making */
                    if(moveIndex < stepsQty){
                        /* Take direction of coordinates changig */
                        int dY = dir[0][0];
                        int dX = dir[0][1];
                        /* Change coordinates in grid */
                        cellPointer[0][0] += dY;
                        cellPointer[0][1] += dX;
                        /* Count new movement */
                        moveIndex++;
                        /* Fill current cell by next value */
                        grid[(cellPointer[0][0])][(cellPointer[0][1])] = outputString[(moveIndex - 1)];
                    }else{
                        break;
                    }
                }
                /* Change direction after this side */
                getNextDirection(dir);
            }else{
                break;
            }
        }
        /* Rise length of spiral side */
        stepsDueDirection++;
    }
}

/* Return coordinates of cell in grid wich will be filled by start digit */
Grid<int> findStartPoint(auto& grid, int internalRectSide){
    Grid<int> startPosition (1, 2);
    int sideCells = grid.numCols();
    int center_X = sideCells / 2;
    int center_Y;
    if((internalRectSide % 2) == 0){
        center_Y = (sideCells / 2) - 1;
    }else{
        center_Y = (sideCells / 2);
    }
    startPosition[0][0] = center_Y;
    startPosition[0][1] = center_X;
    return startPosition;
}

/* Changes direction values due to previous values */
void getNextDirection(auto& currentDirection){
    Grid<int> directionsTurn (4, 2);
    directionsTurn.set(0,0,1);
    directionsTurn.set(0,1,1);
    directionsTurn.set(1,0,1);
    directionsTurn.set(1,1,-1);
    directionsTurn.set(2,0,-1);
    directionsTurn.set(2,1,-1);
    directionsTurn.set(3,0,-1);
    directionsTurn.set(3,1,1);
    int nextRow;
    for(int row = 0; row < directionsTurn.numRows(); row++){
        if(directionsTurn[row][0] == currentDirection[0][0]){
            if(directionsTurn[row][1] == currentDirection[0][1]){
                if(row == 3){
                    nextRow = 0;
                    break;
                }else{
                    nextRow = row + 1;
                    break;
                }
            }
        }
    }
    currentDirection[0][0] = directionsTurn[nextRow][0];
    currentDirection[0][1] = directionsTurn[nextRow][1];
}

/* Needs to fill grid by escapes */
void fillGrid(Grid<string>& grid, string value){
    for(int i = 0; i < grid.numRows(); i++){
        for(int u = 0; u < grid.numCols(); u++){
            grid[i][u] = value;
        }
    }
}

/* Make console output window more convenient */
void consoleSettings(){
    setConsoleWindowTitle(programTitle);
    setConsoleEcho(consoleEcho);
}
