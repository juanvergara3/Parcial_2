#include <iostream>
#include <limits>
#include <windows.h>

#include "canyon.h"

int main() {

    bool loop = true, sub_loop;
    short selec;

    int tempx, tempy;

    std::string inputs;

    std::string menu =
            "Parcial 2: Juan Esteban Vergara Sanchez\n"
            "\n"
            "1. Genenar disparos ofensivos\n"
            "2. Generar disparos defensivos\n"
            "3. Generar disparos contra-ofensivos\n"
            "4. Salir";

    std::cout<<"El canon ofensivo esta fijo en (0,0) y los multiplicadores de radio son valores fijos. Ingrese las coordenadas (X,Y) del canon defensivo: "<<std::endl;

    while(true){ // posx añon defensivo
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
    while(true){ // posy añon defensivo
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
                std::cin>>inputs;

                if(inputs == "d" || inputs == "D" || inputs == "o" || inputs == "O") break;

                else if (inputs == "-1") sub_loop = false;

                else {
                    system("CLS");
                    std::cout<<"Opcion invalida"<<std::endl;
                }
            }

            if(sub_loop == true){

                if( inputs == "d" || inputs == "D")
                    defensive.generate_offensive_shots(ofensive);

                else if (inputs == "o" || inputs == "O")
                    ofensive.generate_offensive_shots(defensive);

                std::cout<<"Presiona ESC para volver"<<std::endl;
                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

            }
            break;
        }
        case 2:{ //Generar disparos defensivos

            break;
        }
        case 3:{ //Generar disparos contra-ofensivos

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
