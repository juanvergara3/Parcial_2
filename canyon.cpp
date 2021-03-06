#include "canyon.h"

Canyon::Canyon(float x_, float y_, float imp_) {
    posx = x_;
    posy = y_;
    impact_multpliter = imp_;
}

std::vector<Shot *> Canyon::generate_offensive_shots(Canyon target, bool print) {
    setDistance(target);
    setImpact_radio(); //calcula la distancia al objetivo y en base a eso el radio de impacto

    std::vector<Shot *> aux;

    int flag = 0; //para romper los ciclos cuando haye los 3 disparos
    float x, y; //posicion del proyectil
    float Vx, Vy; //velocidades en x y y del proyectil
    int V0 = 0; //velocidad inicial del proyectil
    int t = 0;
    int angle = 1; //angulo del proyectil

    for(V0 = 5; ; V0 += 5){ //se va aumentando la velocidad de 5 en 5

        for(angle = 1; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

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
                    V0 += 10; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                    break;
                }

                if(y < 0) break; // si se pasa del suelo xd

            }

            if(flag == 3) break;

        }

        if(flag == 3) break;

    }
    if(print)
        print_results(aux);
    return aux;
}
std::vector<Shot *> Canyon::generate_defensive_shots(Canyon origin, Shot target, bool offensive_matters, bool print) {

    std::vector<Shot *> shots; //para retornar

    setDistance(origin);
    setImpact_radio(); //calcula la distancia entre los cañones, y en base a eso el radio de impacto

    if(offensive_matters){

        int flag = 0;//para romper los ciclos cuando haye los 3 disparos

        float x, y; //coordenas del disparo defensivo
        int V0 = 0; //velocidad inicial del disparo defensivo
        float Vx, Vy; //velocidades en x y y del disparo defensivo
        int angle = 1; //angulo del disparo defensivo

        float x_offensive, y_offensive; //coordenadas del disparo ofensivo
        float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo ofensivo

        int t = 0;

        Vx_offensive = target.getV0()*cos((target.getAngle())*pi/180);
        Vy_offensive = target.getV0()*sin((target.getAngle())*pi/180);

        for(V0 = 5; ; V0 += 5){  //se va aumentando la velocidad de 5 en 5

            for(angle = 1; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

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
                        V0 += 10; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                        break;
                    }

                    if(y < 0) break; // si se pasa del suelo

                    if(flag == 3) break;

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
        int angle = 1; //angulo del disparo defensivo

        float x_offensive, y_offensive; //coordenadas del disparo ofensivo
        float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo ofensivo

        int t = 0;

        Vx_offensive = target.getV0()*cos((target.getAngle())*pi/180);
        Vy_offensive = target.getV0()*sin((target.getAngle())*pi/180);

        for(V0 = 5; ; V0 += 5){  //se va aumentando la velocidad de 5 en 5

            for(angle = 1; angle < 90; angle++){ // se aumenta el  angulo de 1 en 1 hasta que sea 90

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
                        V0 += 10; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                        break;
                    }

                    if(y < 0) break; // si se pasa del suelo

                    if(flag == 3) break;

                }

                if(flag == 3) break;

            }

            if(flag == 3) break;

        }
    }
    if(print)
        print_results(shots);
    return shots;
}
std::vector<Shot *> Canyon::generate_counter_offensive_shots(Canyon defensive_canyon, Shot defensive_shot, Shot offensive_shot) {

    std::vector<Shot *> shots; //para retornar

    //calcula la distancia entre los cañones, y en base a eso el radio de impacto
    setDistance(defensive_canyon);
    defensive_canyon.setDistance(*this);
    setImpact_radio();
    defensive_canyon.setImpact_radio();

    int flag = 0;//para romper los ciclos cuando haye los 3 disparos

    float x, y; //coordenas del disparo que estamos generando
    int V0; //velocidad inicial del disparo que estamos generando
    float Vx, Vy; //velocidades en x y y del disparo que estamos generando
    int angle = 1; //angulo del disparo que estamos generando

    float x_defensive, y_defensive; //coordenadas del disparo que va a destruir mi disparo
    float Vx_defensive, Vy_defensive; //velocidades en x y y del disparo que va a destruir mi disparo

    float x_offensive, y_offensive;  //coordenadas del disparo que dispare inicialmente
    float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo que dispare inicialmente

    int t = 0;
    int d1 = 3; //delay 1
    int d2 = 1; //delay 2

    Vx_defensive = defensive_shot.getV0()*cos((defensive_shot.getAngle()+90)*pi/180);
    Vy_defensive = defensive_shot.getV0()*sin((defensive_shot.getAngle()+90)*pi/180);

    Vx_offensive = offensive_shot.getV0()*cos((offensive_shot.getAngle())*pi/180);
    Vy_offensive = offensive_shot.getV0()*sin((offensive_shot.getAngle())*pi/180);

    for(V0 = 5; ; V0 += 1) {  //se va aumentando la velocidad de 5 en 5

        for(angle = 1; angle < 90; angle++) { // se aumenta el  angulo de 1 en 1 hasta que sea 90

            Vx = V0*cos((angle)*pi/180);
            Vy = V0*sin((angle)*pi/180);

            x = 0.0;
            y = 0.0;
            x_defensive = 0.0;
            y_defensive = 0.0;
            x_offensive = 0.0;
            y_offensive = 0.0;

            for(t = 0; ; t++){// se aumenta el tiempo de segundo en segundo

                x_offensive = posx + Vx_offensive*(t+d1);
                y_offensive = posy + Vy_offensive*(t+d1) - (0.5*G*(t+d1)*(t+d1));  // *** no estoy seguro de los delays ***

                x_defensive = defensive_canyon.getPosx() + Vx_defensive*(t+d2);
                y_defensive = defensive_canyon.getPosy() + Vy_defensive*(t+d2) - (0.5*G*(t+d2)*(t+d2));

                x = posx + Vx*t;
                y = posy + Vy*t - (0.5*G*t*t);

                if(sqrt(pow((x_defensive - x),2)+pow((y_defensive - y), 2)) <= 0.005*distance && sqrt(pow((x_offensive - x),2)+pow((y_offensive - y), 2)) > 0.005*distance){
                    // si destruye el proyectil que queremos destruir pero no destruye el que disparamos originalmente

                    shots.push_back(new Shot(x, y, V0, angle, t)); // si sale un disparo exitoso se añade al vector que de va a retornar (se toma le tiempo desde que se dispara*)

                    flag ++;
                    //V0 += 10; //se usaba para crear disparos que no fueran muy parecidos los unos a los otros, pero es probable que ya no la use
                    break;
                }

                if(sqrt(pow((x_offensive - x_defensive), 2)+pow((y_offensive - y_defensive), 2)) < defensive_canyon.impact_radio) break; //si el proyectil defensivo impacta con el ofensivo

                if(flag == 3) break;

            }

            if(flag == 3) break;

        }

        if(flag == 3) break;

    }


    print_results(shots);
    return shots;
}

bool Canyon::confirm_impact(Canyon origin, Shot ofense) {

    float x, y; //posicion del proyectil
    float Vx = 0, Vy = 0; //velocidades en x y y del proyectil
    int V0 = ofense.getV0(); //velocidad inicial del proyectil
    int t = 0;

//    if(origin.getPosx() > posx){ //si el origen esta ubicado antes del objetivo
//        Vx = V0*cos(ofense.getAngle()*pi/180);
//        Vy = V0*sin(ofense.getAngle()*pi/180);
//    }
//    else if (origin.getPosx() < posx){ //si el origen esta ubicado despues del objetivo
//        Vx = V0*cos((ofense.getAngle()+90)*pi/180);
//        Vy = V0*sin((ofense.getAngle()+90)*pi/180);
//    }

    Vx = V0*cos(ofense.getAngle()*pi/180);
    Vy = V0*sin(ofense.getAngle()*pi/180);

    origin.setDistance(*this);
    origin.setImpact_radio(); //calcula la distancia entre los cañones, y en base a eso el radio de impacto

    for(t = 0; ; t++){ // se aumenta el tiempo de segundo en segundo

        x = origin.getPosx() + Vx*t;
        y = origin.getPosy() + Vy*t -(0.5*G*t*t);

        if(sqrt(pow((posx - x), 2)+pow((posy - y), 2)) < origin.getImpact_radio()) //si la distancia entre el proytectil y el destino es menos que el radio de impacto se cuenta como un impacto
            return true;

        if(y < -1*(origin.getImpact_radio()*2))
            break;

    }
    return false;
}
bool Canyon::confirm_impact(Canyon ofensive, Shot of, Canyon defensive, Shot def) {

    float x_defensive, y_defensive; //coordenas del disparo defensivo
    float Vx_defensive, Vy_defensive; //velocidades en x y y del disparo defensivo

    float x_offensive, y_offensive; //coordenadas del disparo ofensivo
    float Vx_offensive, Vy_offensive; //velocidades en x y y del disparo ofensivo

    Vx_defensive = def.getV0()*cos((def.getAngle()+90)*pi/180);
    Vy_defensive = def.getV0()*sin((def.getAngle()+90)*pi/180);

    Vx_offensive = of.getV0()*cos((of.getAngle())*pi/180);
    Vy_offensive = of.getV0()*sin((of.getAngle())*pi/180);

    ofensive.setDistance(defensive);
    ofensive.setImpact_radio();
    defensive.setDistance(ofensive);
    defensive.setImpact_radio();

    for(int t = 0; ; t++){// se aumenta el tiempo de segundo en segundo

        x_offensive = ofensive.getPosx() + Vx_offensive*(t+2);
        y_offensive = ofensive.getPosy() + Vy_offensive*(t+2) -(0.5*G*(t+2)*(t+2)); //note que se tienen en cuenta los 2 segundos que tardo la informacion en llegar

        x_defensive = defensive.getPosx() + Vx_defensive*t;
        y_defensive = defensive.getPosy() + Vy_defensive*t -(0.5*G*t*t);

        if(sqrt(pow((x_offensive - x_defensive), 2)+pow((y_offensive - y_defensive), 2)) < defensive.getImpact_radio()) //si la distancia entre el proytectil y el destino es menos que el radio de impacto se cuenta como exitoso
            return true;


        if(y_defensive < -1*(defensive.getImpact_radio()*2) || y_offensive < -1*(ofensive.getImpact_radio()*2)) break; // si se pasa del suelo

    }

    return false;
}

void Canyon::print_results(std::vector<Shot *> shots) {
    for(unsigned long long k = 0; k<shots.size(); k++){

        std::cout << "Impacto con un angulo de " << shots.at(k)->getAngle() << " grados" << std::endl;
        std::cout << "Impacto con velocidad incial: " << shots.at(k)->getV0() << std::endl;
        std::cout << "Impacto con posicion x: " << shots.at(k)->getX() << std::endl;
        std::cout << "Impacto con posicion y: " << shots.at(k)->getY() << std::endl;
        std::cout << "Tiempo de vuelo: " << shots.at(k)->getF_time()<< std::endl;
        std::cout << std::endl;

    }
}
void Canyon::print_results(Shot *shot) {

    std::cout << "Impacto con un angulo de " << shot->getAngle() << " grados" << std::endl;
    std::cout << "Impacto con velocidad incial: " << shot->getV0() << std::endl;
    std::cout << "Impacto con posicion x: " << shot->getX() << std::endl;
    std::cout << "Impacto con posicion y: " << shot->getY() << std::endl;
    std::cout << "Tiempo de vuelo: " << shot->getF_time()<< std::endl;
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
