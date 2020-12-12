#ifndef CANYON_H
#define CANYON_H
#include <vector>
#include <math.h>
#include <iostream>
#include "shot.h"

#define G 9.81
#define pi 3.141617

class Canyon {

public: //variables

private: //variables
    float posx, posy;
    float impact_multpliter;
    float impact_radio;
    float distance;

public: //methods
    Canyon(float x_, float y_, float imp_);

    std::vector <Shot *> generate_offensive_shots(Canyon target); //puntos 1 y 2 (target es el cañon que se quiere destruir)
    std::vector <Shot *> generate_defensive_shots(Canyon origin, Shot target, bool destroy); //puntos 3 y 4 (target es el disparo que se quiere destruir y origin es el cañon que los disparó)
    std::vector<Shot *> generate_counter_offensive_shots(Canyon target_canyon, Shot target_shot, Shot mine); //punto 5 (target_canyon es el cañon que se quiere destruir, target_shot es el disparo que hay que destruir, y mine es el disparo que hayq ue proteger)

    float getPosx() const;
    float getPosy() const;

    float getDistance() const;
    void setDistance(Canyon destiny);
    void setDistance(float dis);

    float getImpact_radio() const;
    void setImpact_radio();

private: //methods

};

#endif // CANYON_H
