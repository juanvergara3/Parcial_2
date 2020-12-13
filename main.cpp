#include <iostream>
#include <limits>
#include <windows.h>
#include<bits/stdc++.h>

#include "canyon.h"

int main() {

    bool loop = true, sub_loop;
    short selec;

    int tempx, tempy;

    std::string inputs1, inputs2;

    std::string menu =
            "Parcial 2: Juan Esteban Vergara Sanchez\n"
            "\n"
            "1. Genenar disparos ofensivos\n"
            "2. Generar disparos defensivos\n"
            "3. Generar disparos contra-ofensivos\n"
            "4. Salir";

    std::cout<<"El canon ofensivo esta fijo en (0,0) y los multiplicadores de radio son valores fijos. Ingrese las coordenadas (X,Y) del canon defensivo: "<<std::endl;

    while(true){ // posx cañon defensivo
        std::cout<<"Ingresa al posicion en X (X > 0): ";
        std::cin>>tempx;

        while(std::cin.fail()) { //validacion de entrada
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            system("CLS");
            std::cout << "Entrada invalida"<<std::endl;
            std::cout<<"Ingresa al posicion en X (X > 0): "; std::cin>>tempx;
        }

        if(tempx>0) break;

        else {
            system("CLS");
            std::cout<<"Fuera de rango"<<std::endl;
        }
    }
    while(true){ // posy cañon defensivo
        std::cout<<"Ingresa al posicion en Y (Y >= 0): ";
        std::cin>>tempy;

        while(std::cin.fail()) { //validacion de entrada
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            system("CLS");
            std::cout << "Entrada invalida"<<std::endl;
            std::cout<<"Ingresa al posicion en Y (Y >= 0): "; std::cin>>tempy;
        }

        if(tempy>=0) break;

        else {
            system("CLS");
            std::cout<<"Fuera de rango"<<std::endl;
        }
    }

    Canyon ofensive(0, 0, 0.05), defensive(tempx, tempy, 0.025);

    while(loop){

        system("CLS");

        std::cout<<menu<<std::endl;
        std::cout<<"-> ";std::cin>>selec;

        while(std::cin.fail()) { //validacion de entrada
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            system("CLS");

            std::cout<<menu<<std::endl;
            std::cout << "   Opcion no valida"<<std::endl;
            std::cout<<"-> "; std::cin>>selec;
        }
        system("CLS");

        switch (selec) {

        case 1:{ //Genenar disparos ofensivos
            sub_loop = true;
            while(sub_loop){

                std::cout<<"Desde que canon desea realizar el disparo? (\"O\" para el canon ofensivo, \"D\" para el canon defensivo, o -1 para cancelar): ";
                std::cin>>inputs1;

                if(inputs1 == "d" || inputs1 == "D" || inputs1 == "o" || inputs1 == "O") break;

                else if (inputs1 == "-1") sub_loop = false;

                else {
                    system("CLS");
                    std::cout<<"Opcion invalida"<<std::endl;
                }
            }

            if(sub_loop == true){

                if( inputs1 == "d" || inputs1 == "D")
                    defensive.generate_offensive_shots(ofensive, true);

                else if (inputs1 == "o" || inputs1 == "O")
                    ofensive.generate_offensive_shots(defensive, true);

                std::cout<<"Presiona ESC para volver"<<std::endl;
                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

            }
            break;
        }
        case 2:{ //Generar disparos defensivos
            sub_loop = true;
            while(sub_loop){
                std::cout<<"Ingrese \"G\" para usar un disparo ofensivo generado automaticamente, \"M\" para ingresar los parametros del disparo a mano o -1 para cancelar: "; std::cin>>inputs1;

                if(inputs1 == "g" || inputs1 == "G" || inputs1 == "m" || inputs1 == "M") break;

                else if (inputs1 == "-1") sub_loop = false;

                else {
                    system("CLS");
                    std::cout<<"Opcion invalida"<<std::endl;
                }
            }
            while(sub_loop){
                std::cout<<"Le intereza si el canon enemigo es destruido? (Y/N): "; std::cin>>inputs2;

                if(inputs2 == "Y" || inputs2 == "y" || inputs2 == "N" || inputs2 == "n") break;

                else {
                    system("CLS");
                    std::cout<<"Opcion no valida"<<std::endl;
                }
            }

            if(sub_loop == true){

                if( inputs1 == "g" || inputs1 == "G"){

                    Shot *s = new Shot(*ofensive.generate_offensive_shots(defensive, false)[0]);

                    if(defensive.confirm_impact(ofensive, *s)){

                        if(inputs2 == "Y" || inputs2 == "y")
                            defensive.generate_defensive_shots(ofensive, *s, true, true);
                        else if(inputs2 == "N" || inputs2 == "n")
                            defensive.generate_defensive_shots(ofensive, *s, false, true);
                    }
                    else if(defensive.confirm_impact(ofensive, *s)) //why is this printing tho ***
                        std::cout<<"El disparo no impacta"<<std::endl;

                    delete  s;
                }
                else if (inputs1 == "m" || inputs1 == "M"){

                    while(true){ // angulo
                        std::cout<<"Ingresa el angulo del disparo [0 - 90): ";
                        std::cin>>tempx;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa el angulo del disparo [0 - 90): "; std::cin>>tempx;
                        }

                        if(tempx >= 0 && tempx < 90) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }
                    while(true){ // V0
                        std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): ";
                        std::cin>>tempy;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): "; std::cin>>tempy;
                        }

                        if(tempy>0) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }

                    Shot *s = new Shot(tempy, tempx);

                    if(defensive.confirm_impact(ofensive, *s)){

                        if(inputs2 == "Y" || inputs2 == "y")
                            defensive.generate_defensive_shots(ofensive, *s, true, true);
                        else if(inputs2 == "N" || inputs2 == "n")
                            defensive.generate_defensive_shots(ofensive, *s, false, true);
                    }
                    else
                        std::cout<<"El disparo no impacta"<<std::endl;

                    delete  s;
                }

                std::cout<<"Presiona ESC para volver"<<std::endl;
                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;
            }
            break;
        }
        case 3:{ //Generar disparos contra-ofensivos

            sub_loop = true;
            while(sub_loop){
                std::cout<<"Ingrese \"GG\" para generar tanto el disparo ofensivo como el defensivo, \"GM\" para solo generar el ofensivo e ingresar el defensivo, "
                           "\"MG\" para solo generar el defensivo e ingresar el ofensivo, \"MM\" para ingresar tanto el disparo ofensivo como el defensivo,  o -1 para cancelar: "; std::cin>>inputs1;

               transform(inputs1.begin(), inputs1.end(), inputs1.begin(), ::toupper);

                if(inputs1 == "GG" || inputs1 == "GM" || inputs1 == "MG" || inputs1 == "MM") break;

                else if (inputs1 == "-1") sub_loop = false;

                else {
                    system("CLS");
                    std::cout<<"Opcion invalida"<<std::endl;
                }
            }

            if(sub_loop == true){

                if( inputs1 == "GG"){

                    Shot *of = new Shot(*ofensive.generate_offensive_shots(defensive, false)[0]);
                    Shot *def = new Shot(*defensive.generate_defensive_shots(ofensive, *of, false, false)[0]);

                    ofensive.generate_counter_offensive_shots(defensive, *def, *of);

                    delete  of;
                    delete  def;
                }
                else if (inputs1 == "GM"){

                    Shot *of = new Shot(*ofensive.generate_offensive_shots(defensive, false)[0]);

                    while(true){ // angulo
                        std::cout<<"Ingresa el angulo del disparo [0 - 90): ";
                        std::cin>>tempx;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa el angulo del disparo [0 - 90): "; std::cin>>tempx;
                        }

                        if(tempx >= 0 && tempx < 90) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }
                    while(true){ // V0
                        std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): ";
                        std::cin>>tempy;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): "; std::cin>>tempy;
                        }

                        if(tempy>0) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }

                    Shot *def = new Shot(tempy, tempx);

                    if(ofensive.confirm_impact(ofensive, *of, defensive, *def)){

                        ofensive.generate_counter_offensive_shots(defensive, *def, *of);
                    }
                    else
                        std::cout<<"El disparo ingresado no impacta"<<std::endl;

                    delete  of;
                    delete  def;
                }
                else if (inputs1 == "MG"){ //pendiente

                    while(true){ // angulo
                        std::cout<<"Ingresa el angulo del disparo [0 - 90): ";
                        std::cin>>tempx;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa el angulo del disparo [0 - 90): "; std::cin>>tempx;
                        }

                        if(tempx >= 0 && tempx < 90) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }
                    while(true){ // V0
                        std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): ";
                        std::cin>>tempy;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): "; std::cin>>tempy;
                        }

                        if(tempy>0) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }

                    Shot *of = new Shot(tempy, tempx);


                    if(defensive.confirm_impact(ofensive, *of)){

                        Shot *def = new Shot(*defensive.generate_defensive_shots(ofensive, *of, false, false)[0]);

                        ofensive.generate_counter_offensive_shots(defensive, *def, *of);

                        delete  def;
                    }
                    else
                        std::cout<<"El disparo ingresado no impacta"<<std::endl;

                    delete  of;
                }
                else if (inputs1 == "MM"){ //pendiente

                    while(true){ // angulo primer disparo
                        std::cout<<"Ingresa el angulo del disparo [0 - 90): ";
                        std::cin>>tempx;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa el angulo del disparo [0 - 90): "; std::cin>>tempx;
                        }

                        if(tempx >= 0 && tempx < 90) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }
                    while(true){ // V0 primer disparo
                        std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): ";
                        std::cin>>tempy;

                        while(std::cin.fail()) { //validacion de entrada
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                            system("CLS");
                            std::cout << "Entrada invalida"<<std::endl;
                            std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): "; std::cin>>tempy;
                        }

                        if(tempy>0) break;

                        else {
                            system("CLS");
                            std::cout<<"Fuera de rango"<<std::endl;
                        }
                    }

                    Shot *of = new Shot(tempy, tempx);

                    if(defensive.confirm_impact(ofensive, *of)){

                        while(true){ // angulo segundo disparo
                            std::cout<<"Ingresa el angulo del disparo [0 - 90): ";
                            std::cin>>tempx;

                            while(std::cin.fail()) { //validacion de entrada
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                system("CLS");
                                std::cout << "Entrada invalida"<<std::endl;
                                std::cout<<"Ingresa el angulo del disparo [0 - 90): "; std::cin>>tempx;
                            }

                            if(tempx >= 0 && tempx < 90) break;

                            else {
                                system("CLS");
                                std::cout<<"Fuera de rango"<<std::endl;
                            }
                        }
                        while(true){ // V0 segundo disparo
                            std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): ";
                            std::cin>>tempy;

                            while(std::cin.fail()) { //validacion de entrada
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                system("CLS");
                                std::cout << "Entrada invalida"<<std::endl;
                                std::cout<<"Ingresa la velocidad inicial del disparo ( > 0): "; std::cin>>tempy;
                            }

                            if(tempy>0) break;

                            else {
                                system("CLS");
                                std::cout<<"Fuera de rango"<<std::endl;
                            }
                        }

                        Shot *def = new Shot(tempy, tempx);

                        if(ofensive.confirm_impact(ofensive, *of, defensive, *def)){

                            ofensive.generate_counter_offensive_shots(defensive, *def, *of);

                        }
                        else
                            std::cout<<"El disparo ingresado no impacta"<<std::endl;

                        delete def;
                    }
                    else
                        std::cout<<"El disparo ingresado no impacta"<<std::endl;

                    delete of;
                }

            }

            std::cout<<"Presiona ESC para volver"<<std::endl;
            while(true)
                if (GetAsyncKeyState(VK_ESCAPE))
                    break;

            break;
        }
        case 4:{ //Salir
            loop = false;
            break;
        }
        }
    }

    return 0;
}
