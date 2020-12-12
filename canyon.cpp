#include "canyon.h"

Canyon::Canyon(float x_, float y_, float imp_) {
    posx = x_;
    posy = y_;
    impact_multpliter = imp_;
}

float Canyon::getPosx() const {
    return posx;
}
float Canyon::getPosy() const {
    return posy;
}

float Canyon::getDistance() const {
    return distance;
}
void Canyon::setDistance(Canyon destiny) {
    distance = abs(posx - destiny.getPosx()); //calcula la distancia entre los 2 cañones
}
void Canyon::setDistance(float dis) {
    distance = dis;
}

float Canyon::getImpact_radio() const {
    return impact_radio;
}
void Canyon::setImpact_radio() {
    impact_radio = impact_multpliter*distance;
}
