#include "huesos.h"

huesos::huesos(int x, int y)
{
    px = x;
    py = y;
    Vx = 10;

    for(int d = 0; d < 8; d++){
        sprite[d] = 0;
        pos[d] = true;
    }
}

void huesos::ataque()
{
    Attack = new QTimer(this);
    connect(Attack, SIGNAL(timeout()), this, SLOT(HuesosAttack()));
    Attack->start(200);
}

void huesos::movimiento() //Se debe de mover hacia donde se encuentre el jugador
{

}

void huesos::HuesosIdle() //Se podría tener en cuenta un tiempo para que se quede quieto
{
    QTransform tr;
    tr.rotate(180,Qt::YAxis);
    setPixmap(QPixmap(HIdle[sprite[5]]).scaled(tam,tam).transformed(tr,Qt::SmoothTransformation));

    if(sprite[5] == 3){
        sprite[5] = 0;
        move = 'D';
        ataque();
        delete Idle;
    }
    sprite[5] += (2*pos[5])-1;
}

void huesos::HuesosAttack()
{
    int At = 1;
//    std::uniform_int_distribution<int> A(1,2);
//    At = A(*QRandomGenerator::global());

    if(At == 1){ //Modo 1
        if(move == 'D'){
            setPixmap(QPixmap(AttackRM1[sprite[3]]).scaled(tam,tam));
            if(sprite[3] == 3){
                sprite[3] = 0;
            }
            else sprite[3] += (2*pos[3])-1;
        }
        else if(move == 'A'){
            setPixmap(QPixmap(AttackLM1[sprite[2]]).scaled(tam,tam));
            if(sprite[2] == 2){
                sprite[2] = 0;
            }
            else sprite[2] += (2*pos[2])-1;
        }
    }
}















