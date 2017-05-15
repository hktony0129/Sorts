#include "backend.h"

backend::backend()
{

}

void backend::sort(){
    int tempvalue;
    int distance = v.size();
    int base = v[v.size() - 1];
    for (int x = 0; x < distance; x++){


    if (v[x] > base){
        tempvalue = v[x];
        v.erase(v.begin()+x);
        x = x - 1;
        distance = distance - 1;
        v.push_back(tempvalue);

        QElapsedTimer *timer = new QElapsedTimer();
        timer->restart();

        while(timer->elapsed() < 2000){

        }


        for (int z = 0; z < v.size(); z++){
           r[z]->setRect(z*600/v.size(), 420 - v[z]*400/max, 600/v.size(), v[z]*400/max);
        }

        }
    }
}
