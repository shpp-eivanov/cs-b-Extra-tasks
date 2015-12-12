#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "filelib.h"
#include "tokenscanner.h"
#include "strlib.h"


using namespace std;

const double STEP = 0.1;
const double AREA_SIZE = 50;

struct Pt{
    double x;
    double y;
    bool operator==(const Pt & n1){
             return (x == n1.x) && (y == n1.y);
    }
};

Pt mashka;
Pt lenka;

struct Obstacle{
    Pt corner1;
    Pt corner2;

    bool isContains(Pt point){
       double max_x = ((corner1.x >= corner2.x) ? corner1.x : corner2.x);
       double min_x = ((corner1.x < corner2.x) ? corner1.x : corner2.x);
       double max_y = ((corner1.y >= corner2.y) ? corner1.y : corner2.y);
       double min_y = ((corner1.y < corner2.y) ? corner1.y : corner2.y);

       return ((point.x >= min_x) && (point.x <= max_x) &&
               (point.y >= min_y) && (point.y <= max_y));
    }
};

struct Ray{
    Pt start;
    Pt finish;

    bool isVertical(){
        return (finish.x == start.x);
    }

    double getA(){
        return ((finish.y - start.y) / (finish.x - start.x));
    }

    double getC(){
        return (start.y - getA() * start.x);
    }

    double getY(double x){
        return getA() * x + getC();
    }

    bool isCrosses(Obstacle& obs){
        double min_x = ((obs.corner1.x <= obs.corner2.x) ? obs.corner1.x : obs.corner2.x);
        double max_x = ((obs.corner1.x >= obs.corner2.x) ? obs.corner1.x : obs.corner2.x);
        double x = min_x;
        while(x <= max_x){
             //cout << x << " ";
             Pt pt;
             pt.x = x;
             pt.y = getY(x);
             if(obs.isContains(pt)){
                //cout << x << " " << pt.y << endl;
                return true;
                break;
             }
             //cout << endl;
             x = x + STEP;
         }
         return false;
    }
};

void loadObstacles(Vector <Obstacle> & vec){
    string inputFile = "INPUT.txt";
    /* Prepare input stream object   */
    ifstream infile;
    infile.open(inputFile.c_str());
    TokenScanner scanner(infile);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.addWordCharacters("-");

    mashka.x = stringToDouble(scanner.nextToken());
    mashka.y = stringToDouble(scanner.nextToken());

    lenka.x = stringToDouble(scanner.nextToken());
    lenka.y = stringToDouble(scanner.nextToken());

    int obstaclesQty = stringToInteger(scanner.nextToken());

    for(int i = 0; i < obstaclesQty; i++){
       double corner1_X = stringToDouble(scanner.nextToken());
       double corner1_Y = stringToDouble(scanner.nextToken());
       Pt cor1;
       cor1.x = corner1_X;
       cor1.y = corner1_Y;
       //cout << corner1_X << " " << corner1_Y << " ";
       double corner2_X = stringToDouble(scanner.nextToken());
       double corner2_Y = stringToDouble(scanner.nextToken());
       Pt cor2;
       cor2.x = corner2_X;
       cor2.y = corner2_Y;
       //cout << corner2_X << " " << corner2_Y << endl;
       Obstacle obs;
       obs.corner1 = cor1;
       obs.corner2 = cor2;
       vec.add(obs);
    }

    infile.close();
}


int  main(){

   Vector <Obstacle> obsVec;

   loadObstacles(obsVec);
   int noConection = 0;

   for(int row = -1 * AREA_SIZE; row <= AREA_SIZE; row++){
       for(int col = -1 * AREA_SIZE; col <= AREA_SIZE; col++){
           Pt vaska; vaska.x = col;  vaska.y = row;
           Ray vaskaMashka;
           vaskaMashka.start = vaska;
           vaskaMashka.finish = mashka;
           Ray vaskaLenka;
           vaskaLenka.start = vaska;
           vaskaLenka.finish = lenka;

           for(Obstacle obs: obsVec){
               if(!vaskaMashka.isCrosses(obs) && (!vaskaLenka.isCrosses(obs)))
                noConection++;
           }

           if(noConection == obsVec.size()){
                cout << "YES! x = " << col << " y = " << row << endl;
                break;
           }
       }
   }



   return 0;
}
