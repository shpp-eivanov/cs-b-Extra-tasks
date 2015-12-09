#include <iostream>
#include "console.h"
#include <stdlib.h>
#include "gbufferedimage.h"
#include "random.h"


using namespace std;

GBufferedImage* img;

void buildTree(GWindow& gw,
                      int currentOrder,
                      int requiredOrder,
                      GPoint& bottomPt,
                      double length,
                      double angle){

    if(currentOrder <= requiredOrder){
        currentOrder++;

        GPoint topPt = gw.drawPolarLine(bottomPt, length, angle);

        /* Left brunch */
        buildTree(gw,
                  currentOrder,
                  requiredOrder,
                  topPt,
                  (length / (randomReal(1.2, 2))),
                  (angle + 45 * (randomReal(0.7, 1.3))));
        /* Right brunch */
        buildTree(gw,
                  currentOrder,
                  requiredOrder,
                  topPt,
                  (length / (randomReal(1.2, 2))),
                  (angle - 45 * (randomReal(0.7, 1.3))));
    }
}


int main() {
    GWindow gw;
    double length = 200;
    int requiredOrder = 10;//It would be better range 0 - 15;
    double gwWidth = 3 * length;
    double gwHeight = 3 * length ;

    gw.setSize(gwWidth, gwHeight);

    int currentOrder = 0;
    GPoint bottomPt((gwWidth / 2), gwHeight);

    buildTree(gw,
                currentOrder,
                requiredOrder,
                bottomPt,
                length,
                90);
    int width = gw.getWidth();
    int height = gw.getHeight();
    //gw.setSize(width, height);


   return 0;
}

