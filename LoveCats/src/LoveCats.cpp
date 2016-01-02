#include <iostream>
#include <stdlib.h>
#include <string>
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

    string toString (){
        string result = "Obstacle [";
        result = result + integerToString(corner1.x) + string(", ") + integerToString(corner1.y) + string("]");
        result += "[" + integerToString(corner2.x) + ", " + integerToString(corner2.y) + "]";
        return result;
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
        double obsMin_x = ((obs.corner1.x <= obs.corner2.x) ? obs.corner1.x : obs.corner2.x);
        double obsMax_x = ((obs.corner1.x >= obs.corner2.x) ? obs.corner1.x : obs.corner2.x);
        double x;

        if(isVertical()){
           x = start.x;
           if((start.x >= obsMin_x) && (x <= obsMax_x)){
              return true;
           }else{
              return false;
           }
        }

        x = obsMin_x;
        while(x <= obsMax_x){
            Pt pt;
            pt.x = x;
            pt.y = getY(x);

            if(obs.isContains(pt)){
               return true;
            }

            x = x + STEP;
         }
         return false;
    }
};

void readFileAndloadObstacles(Vector <Obstacle> & vec){
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

   readFileAndloadObstacles(obsVec);
   int noConection = 0;

//   Pt vaska; vaska.x = -46;  vaska.y = -50;

//   mashka.x = -2;
//   mashka.y = 0;

//   Ray vaskaMashka;
//   vaskaMashka.start = vaska;
//   vaskaMashka.finish = mashka;

//   for(Obstacle obs: obsVec){
//       if(vaskaMashka.isCrosses(obs)){
//           cout << "CROSSES: " << obs.toString() << endl;
//       }else{
//           cout << "NO" << endl;
//       }
//   }

   for(int row = -1 * AREA_SIZE; row <= AREA_SIZE; row++){
       if(noConection == obsVec.size()){
           break;
       }

       for(int col = -1 * AREA_SIZE; col <= AREA_SIZE; col++){
           Pt vaska; vaska.x = col;  vaska.y = row;

           Ray vaskaLenka;
           vaskaLenka.start = vaska;
           vaskaLenka.finish = lenka;

           Ray vaskaMashka;
           vaskaMashka.start = vaska;
           vaskaMashka.finish = mashka;

           for(Obstacle obs: obsVec){
               if((!(vaskaMashka.isCrosses(obs))) && (!(vaskaLenka.isCrosses(obs)))){
//                   cout << "Mashka [" << mashka.x << ", " << mashka.y <<
//                           "] Lenka[" << lenka.x << ", " << lenka.y << "]" << endl;

                   noConection++;

                    if(noConection == obsVec.size()){
                        cout << "Mashka [" << mashka.x << ", " << mashka.y <<
                                "] Lenka[" << lenka.x << ", " << lenka.y << "]" << endl;

                        cout << "YES! x = " << col << " y = " << row << endl;
                        break;
                    }
               }
           }


       }

   }

   if(noConection < obsVec.size()){
        cout << "NO" << endl;
   }

   return 0;
}
