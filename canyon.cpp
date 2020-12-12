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
    float x, y; //posicion del proyectil
    float Vx, Vy; //velocidades en x y y del proyectil
    int V0 = 0; //velocidad inicial del proyectil
    int t = 0;
    int angle = 0; //angulo del proyectil

    for(V0 = 5; ; V0 += 5){ //se va aumentando la velocidad de 5 en 5

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

                x = posx + Vx*t;
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
std::vector<Shot *> Canyon::generate_defensive_shots(Canyon origin, Shot target, bool offensive_matters) {

    std::vector<Shot *> shots; //para retornar

    setDistance(origin);
    setImpact_radio(); //calcula la distancia entre los cañones, y en base a eso el radio de impacto

    if(offensive_matters){

        int flag = 0;//para romper los ciclos cuando haye los 3 disparos

        float x, y; //coordenas del disparo defensivo
        int V0 = 0; //velocidad inicial del disparo defensivo
        float Vx, Vy; //velocidades en x y y del disparo defensivo
        int angle = 0; //angulo del disparo defensivo

        float x_offensive, y_offensive; //coordenadas del disparo ofensivo
        float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo ofensivo

        int t = 0;

        Vx_offensive = target.getV0()*cos((target.getAngle())*pi/180);
        Vy_offensive = target.getV0()*sin((target.getAngle())*pi/180);

        for(V0 = 5; ; V0 += 5){  //se va aumentando la velocidad de 5 en 5

            for(angle = 0; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

                Vx = V0*cos((angle+90)*pi/180);
                Vy = V0*sin((angle+90)*pi/180);

                x = 0.0;
                y = 0.0;
                x_offensive = 0.0;
                y_offensive = 0.0;

                for(t = 0; ; t++){// se aumenta el tiempo de segundo en segundo

                    x_offensive = origin.getPosx() + Vx_offensive*(t+2);
                    y_offensive = origin.getPosy() + Vy_offensive*(t+2) -(0.5*G*(t+2)*(t+2)); //note que se tienen en cuenta los 2 segundos que tardo la informacion en llegar

                    x = posx + Vx*t;
                    y = posy + Vy*t -(0.5*G*t*t);

                    if(sqrt(pow((x_offensive - x), 2)+pow((y_offensive - y), 2)) < impact_radio && sqrt(pow((origin.getPosx() - x), 2)+pow((origin.getPosy() - y), 2)) > impact_radio){
                        //si la distancia entre el proytectil y el destino es menos que el radio de impacto Y la distanciancia entre el proyectil y el origen es mayor que el radio de impacto se cuenta como exitoso

                        if(y<0)
                            y = 0;

                        shots.push_back(new Shot(x, y, V0, angle, t)); // si sale un disparo exitoso se añade al vector que de va a retornar (se toma le tiempo desde que se dispara*)

                        flag ++;
                        // V0 += 50; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                        break;
                    }

                    if(y < 0) break; // si se pasa del suelo

                }

                if(flag == 3) break;

            }

            if(flag == 3) break;

        }

    }

    else{ //cuando el cañon ofensivo no importa, y el cañon defensivo mo comprueba si lo impacta o no

        int flag = 0;//para romper los ciclos cuando haye los 3 disparos

        float x, y; //coordenas del disparo defensivo
        int V0 = 0; //velocidad inicial del disparo defensivo
        float Vx, Vy; //velocidades en x y y del disparo defensivo
        int angle = 0; //angulo del disparo defensivo

        float x_offensive, y_offensive; //coordenadas del disparo ofensivo
        float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo ofensivo

        int t = 0;

        Vx_offensive = target.getV0()*cos((target.getAngle())*pi/180);
        Vy_offensive = target.getV0()*sin((target.getAngle())*pi/180);

        for(V0 = 5; ; V0 += 5){  //se va aumentando la velocidad de 5 en 5

            for(angle = 0; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

                Vx = V0*cos((angle+90)*pi/180);
                Vy = V0*sin((angle+90)*pi/180);

                x = 0.0;
                y = 0.0;
                x_offensive = 0.0;
                y_offensive = 0.0;

                for(t = 0; ; t++){// se aumenta el tiempo de segundo en segundo

                    x_offensive = origin.getPosx() + Vx_offensive*(t+2);
                    y_offensive = origin.getPosy() + Vy_offensive*(t+2) -(0.5*G*(t+2)*(t+2)); //note que se tienen en cuenta los 2 segundos que tardo la informacion en llegar

                    x = posx + Vx*t;
                    y = posy + Vy*t -(0.5*G*t*t);

                    if(sqrt(pow((x_offensive - x),2)+pow((y_offensive - y), 2)) < impact_radio){ //si la distancia entre el proytectil y el destino es menos que el radio de impacto se cuenta como exitoso

                        if(y<0)
                            y = 0;

                        shots.push_back(new Shot(x, y, V0, angle, t)); // si sale un disparo exitoso se añade al vector que de va a retornar (se toma le tiempo desde que se dispara*)

                        flag ++;
                        // V0 += 50; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                        break;
                    }

                    if(y < 0) break; // si se pasa del suelo

                }

                if(flag == 3) break;

            }

            if(flag == 3) break;

        }
    }

    print_results(shots);
    return shots;
}
std::vector<Shot *> Canyon::generate_counter_offensive_shots(Canyon target_canyon, Shot target_shot, Shot mine) {

    std::vector<Shot *> shots; //para retornar

    //calcula la distancia entre los cañones, y en base a eso el radio de impacto
    setDistance(target_canyon);
    target_canyon.setDistance(*this);
    setImpact_radio();
    target_canyon.setImpact_radio();

    int flag = 0;//para romper los ciclos cuando haye los 3 disparos

    float x, y; //coordenas del disparo que estamos generando
    int V0 = 0; //velocidad inicial del disparo que estamos generando
    float Vx, Vy; //velocidades en x y y del disparo que estamos generando
    int angle = 0; //angulo del disparo que estamos generando

    float x_offensive, y_offensive; //coordenadas del disparo que va a destruir mi disparo
    float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo que va a destruir mi disparo

    float x_mine, y_mine;  //coordenadas del disparo que dispare inicialmente
    float Vx_mine, Vy_mine; //velocidades en x y y del disparo que dispare inicialmente

    int t = 0;
    int d1 = 3; //delay 1
    int d2 = 1; //delay 2

    Vx_offensive = target_shot.getV0()*cos((target_shot.getAngle()+90)*pi/180);
    Vy_offensive = target_shot.getV0()*sin((target_shot.getAngle()+90)*pi/180);

    Vx_mine = mine.getV0()*cos((mine.getAngle())*pi/180);
    Vy_mine = mine.getV0()*sin((mine.getAngle())*pi/180);

    for(V0 = 5; ; V0 += 5){  //se va aumentando la velocidad de 5 en 5

        for(angle = 0; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

            Vx = V0*cos((angle)*pi/180);
            Vy = V0*sin((angle)*pi/180);

            x = 0.0;
            y = 0.0;
            x_offensive = 0.0;
            y_offensive = 0.0;
            x_mine = 0.0;
            y_mine = 0.0;

            for(t = 0; ; t++){// se aumenta el tiempo de segundo en segundo

                x_mine = posx + Vx_mine*(t+d1);
                y_mine = posy + Vy_mine*(t+d1) - (0.5*G*(t+d1)*(t+d1));  // *** no estoy seguro de los delays ***

                x_offensive = target_canyon.getPosx() + Vx_offensive*(t+d2);
                y_offensive = target_canyon.getPosy() + Vy_offensive*(t+d2) -(0.5*G*(t+d2)*(t+d2));

                x = posx + Vx*t;
                y = posy + Vy*t -(0.5*G*t*t);

                if(sqrt(pow((x_offensive - x),2)+pow((y_offensive - y), 2)) < impact_radio && sqrt(pow((x_mine - x),2)+pow((y_mine - y), 2)) > impact_radio){ //0,005d careful :thinking:
                    // si destruye el proyectil que queremos destruir pero no destruye el que disparamos originalmente

                    if(y<0)
                        y = 0;

                    shots.push_back(new Shot(x, y, V0, angle, t)); // si sale un disparo exitoso se añade al vector que de va a retornar (se toma le tiempo desde que se dispara*)

                    flag ++;
                    break;
                }

                if(y < 0) break; // si se pasa del suelo

            }

            if(flag == 3) break;

        }

        if(flag == 3) break;

    }


    print_results(shots);
    return shots;
}

bool Canyon::confirm_impact(Canyon origin, Shot offense) {

    float x, y; //posicion del proyectil
    float Vx = 0, Vy = 0; //velocidades en x y y del proyectil
    int V0 = 0; //velocidad inicial del proyectil
    int t = 0;

    if(origin.getPosx() < posx){ //si el origen esta ubicado antes del objetivo
        Vx = V0*cos(offense.getAngle()*pi/180);
        Vy = V0*sin(offense.getAngle()*pi/180);
    }
    else if (origin.getPosx() > posx){ //si el origen esta ubicado despues del objetivo
        Vx = V0*cos((offense.getAngle()+90)*pi/180);
        Vy = V0*sin((offense.getAngle()+90)*pi/180);
    }

    for(t = 0; ; t++){ // se aumenta el tiempo de segundo en segundo

        x = origin.getPosx() + Vx*t;
        y = origin.getPosy() + Vy*t -(0.5*G*t*t);

        if(sqrt(pow((posx - x),2)+pow((posy - y),2)) < origin.getImpact_radio()) //si la distancia entre el proytectil y el destino es menos que el radio de impacto se cuenta como un impacto
            return true;

        if(y < 0) // si se pasa del suelo
            break;

    }
    return false;
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
