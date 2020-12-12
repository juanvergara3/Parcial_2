#include "canyon.h"

Canyon::Canyon(float x_, float y_, float imp_) {
    posx = x_;
    posy = y_;
    impact_multpliter = imp_;
}

std::vector<Shot *> Canyon::generate_offensive_shots(Canyon target) {
    setDistance(target);
    setImpact_radio(); //calcula la distancia al objetivo y en base a eso el radio de impacto

    std::vector<Shot *> aux;

    int flag = 0; //para romper los ciclos cuando haye los 3 disparos
    float x,y; //posicion del proyectil
    float Vx,Vy; //velocidades en x y y del proyectil
    int V0 = 0; //velocidad inicial del proyectil
    float t = 0;
    int angle = 0; //angulo del proyectil

    for(V0 = 5; ; V0 += 5){ //se va aumentando la velocida de 5 en 5

        for(angle = 0; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

            if(posx < target.getPosx()){ //si el cañon esta ubicado antes del objetivo
                Vx = V0*cos(angle*pi/180);
                Vy = V0*sin(angle*pi/180);
            }
            else if (posx > target.getPosx()){ //si el cañon esta ubicado despues del objetivo
                Vx = V0*cos((angle+90)*pi/180);
                Vy = V0*sin((angle+90)*pi/180);
            }

            x = 0.0;
            y = 0.0;

            for(t = 0; ; t++){ // se aumenta el tiempo de segundo en segundo

                //x = posx + Vx*t; //como no he visto fisica no estoy seguro de esto :)
                x = Vx*t;
                y = posy + Vy*t -(0.5*G*t*t);

                if(sqrt(pow((target.getPosx() - x),2)+pow((target.getPosy() - y),2)) < impact_radio){ //si la distancia entre el proytectil y el destino es menos que el radio de impacto se cuenta como exitoso

                    if(y<0) //es posible que impacte habiendo pasado un poco del suelo (como si se enterrara, pero me parece mejor que se registre como si hubiera impactado en 0)
                        y = 0;

                    aux.push_back(new Shot(x, y, V0, angle, t)); // si sale un disparo exitoso se añade al vector que de va a retornar

                    flag++;
                    // V0 += 50; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                    break;
                }

                if(y < 0) break; // si se pasa del suelo xd

            }

            if(flag == 3) break;

        }

        if(flag == 3) break;

    }

    print_results(aux);
    return aux;
}

void Canyon::print_results(std::vector<Shot *> shots) {
    for(unsigned long long k = 0; k<shots.size(); k++){

        std::cout << "Impacto con un angulo de " << shots.at(k)->getAngle() << " grados" << std::endl;
        std::cout << "Impacto con velocidad incial " << shots.at(k)->getV0() << std::endl;
        std::cout << "Impacto con posicion x: " << shots.at(k)->getX() << std::endl;
        std::cout << "Impacto con posicion y: " << shots.at(k)->getY() << std::endl;
        std::cout << "Con tiempo: " << shots.at(k)->getF_time()<< std::endl;
        std::cout << std::endl;

    }
}
void Canyon::print_results(Shot *shot) {

    std::cout << "Impacto con un angulo de " << shot->getAngle() << " grados" << std::endl;
    std::cout << "Impacto con velocidad incial " << shot->getV0() << std::endl;
    std::cout << "Impacto con posicion x: " << shot->getX() << std::endl;
    std::cout << "Impacto con posicion y: " << shot->getY() << std::endl;
    std::cout << "Con tiempo: " << shot->getF_time()<< std::endl;
    std::cout << std::endl;
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
