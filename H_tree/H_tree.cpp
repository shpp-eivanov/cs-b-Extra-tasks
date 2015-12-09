#include <iostream>
#include "console.h"
#include <stdlib.h>
#include "gbufferedimage.h"


using namespace std;

GBufferedImage* img;

void buildH(GWindow& gw,
                      int lengthCnt,
                      int requiredOrder,
                      GPoint& centerPt,
                      double length,
                      double angle){

    if(requiredOrder >= 0){

        lengthCnt++;
        int koef = lengthCnt%2;

        if(koef){ length = length / 2;
        }else{requiredOrder--;}

        GPoint pt1 = gw.drawPolarLine(centerPt, length, angle);
        GPoint pt2 = gw.drawPolarLine(centerPt, length, (180 + angle));

        /* Left brunch */
        buildH(gw,
                  lengthCnt,
                  requiredOrder,
                  pt1,
                  (length),
                  (angle + 90));
        /* Right brunch */
        buildH(gw,
                  lengthCnt,
                  requiredOrder,
                  pt2,
                  (length),
                  (angle - 90));
    }
}


int main() {
    GWindow gw;
    double length = 200;
    int requiredOrder = 3;//It would be better range 0 - 6;
    double gwWidth = 2 * length;
    double gwHeight = 2 * length ;

    gw.setSize(gwWidth, gwHeight);

    int currentOrder = 0;
    GPoint centerPt((gwWidth / 2), (gwHeight / 2));

    buildH(gw,
            currentOrder,
            requiredOrder,
            centerPt,
            length,
            0);

   return 0;
}

