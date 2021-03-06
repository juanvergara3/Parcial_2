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

    std::vector <Shot *> generate_offensive_shots(Canyon target, bool print); //puntos 1 y 2 (target es el cañon que se quiere destruir)
    std::vector <Shot *> generate_defensive_shots(Canyon origin, Shot target, bool offensive_matters, bool print); //puntos 3 y 4 (target es el disparo que se quiere destruir y origin es el cañon que los disparó)
    std::vector<Shot *> generate_counter_offensive_shots(Canyon defensive_canyon, Shot defensive_shot, Shot offensive_shot); //punto 5 (target_canyon es el cañon que se quiere destruir, target_shot es el disparo que hay que destruir, y mine es el disparo que hayq ue proteger)

    bool confirm_impact(Canyon origin, Shot ofense); //confirma que el diaparo impacta su destino (el cañon que realiza este calculo es el destino (this) )
    bool confirm_impact(Canyon ofensive, Shot of, Canyon defensive, Shot def);

    void print_results( std::vector <Shot *> shots);
    void print_results(Shot* shot);

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
