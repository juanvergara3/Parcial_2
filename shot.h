#ifndef SHOT_H
#define SHOT_H


class Shot{

public: //variables
    float x, y; //posicion del disparo
    int V0; //velocidad inicial del disparo
    float f_time; //tiempo final de impacto
    int angle; //angulo inicial del disparo

private: //variables

public: //methods
    Shot(float posx, float posy, int velocity, int angle_, int final_time);
    Shot();
    ~Shot();

    int getAngle() const;
    int getV0() const;
    float getF_time() const;
    float getX() const;
    float getY() const;

    void setX(float value);
    void setY(float value);
    void setAngle(int value);
    void setF_time(float value);
    void setV0(int value);

private: //methods

};

#endif // SHOT_H
