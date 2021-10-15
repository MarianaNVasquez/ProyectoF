#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    H = 708;
    W = 0;

    // para el inicio del juego
    //setup_interfaz();
    //inicio();

    setup_resorces();
    player1 = new player('g');
    //player1 = new player('s');

    numNivel = 1;
    cargar_niveles(numNivel);

    collisions = new QTimer(this);
    connect(collisions, SIGNAL(timeout()), this, SLOT(detectC()));
    collisions->start(1);
    setup_enemies();
}

void MainWindow::setup_interfaz()
{
    scene = new QGraphicsScene(this);
    setMaximumSize(800,600);
    setMaximumSize(800,600);
    ui->graphicsView->setGeometry(0,0,800,600);
    scene->setSceneRect(0,0,ui->graphicsView->width()-3,ui->graphicsView->height()-3);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/Imagenes/Interfaz/fondoinicio.jpg"));
    setWindowTitle("Gehrin");
}

void MainWindow::inicio()
{
    ui->inicio->show();
    ui->inicio->setGeometry(80,265,ui->inicio->width(),ui->inicio->height());
    ui->inicio->setStyleSheet("QGroupBox {border: transparent}");
    palette.setColor(ui->iniciarsesion->foregroundRole(), QColor(255,255,255));
    ui->iniciarsesion->setPalette(palette);
    ui->registrarse->setPalette(palette);
    ui->dificultad->hide();
    ui->modojuego->hide();
    ui->Partida->hide();
}

void MainWindow::setup_resorces()
{
    scene = new QGraphicsScene(this);
    setGeometry(0,0,1283,770); //en general para el juego
    ui->graphicsView->setGeometry(0,0,1280,711);

    scene->setSceneRect(W,0,ui->graphicsView->width()-3,H-3);
    ui->graphicsView->setScene(scene);

    ui->inicio->hide();
    ui->dificultad->hide();
    ui->modojuego->hide();
    ui->Partida->hide();

    //para ponerle color a la letra al menubar
//    palette.setColor(ui->menubar->foregroundRole(), QColor(21,165,169));
//    ui->menubar->setPalette(palette);


    //Lineas de la escena
    lineUp = new QGraphicsLineItem(0,0,5120,0);
    lineDown = new QGraphicsLineItem(0,708,5120,708);
    lineRight = new QGraphicsLineItem(1280,0,1280,708);
    lineLeft = new QGraphicsLineItem(0,0,0,708);
}

void MainWindow::setup_enemies()
{
    switch (numNivel) {
    case 1:
        for(int p = 0; p < walls.size(); p++){
            if(walls.at(p)->getPosX() != 0){
                if((walls.at(p)->getPosX() == 779 && walls.at(p)->getPosY() == 348) || (walls.at(p)->getPosX() == 1067 && walls.at(p)->getPosY() == 449) ||
                    (walls.at(p)->getPosX() == 1780 && walls.at(p)->getPosY() == 372) || (walls.at(p)->getPosX() == 2508 && walls.at(p)->getPosY() == 372) ||
                    (walls.at(p)->getPosX() == 2032 && walls.at(p)->getPosY() == 224)){

                    if(walls.at(p)->getPosX() == 2032 && walls.at(p)->getPosY() == 224){
                        enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+81,walls.at(p)->getPosY()-64,'b'));
                        scene->addItem(enemigosH.at(enemigosH.size()-1));
                        enemigosH.at(enemigosH.size()-1)->idle();
                        enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+369,walls.at(p)->getPosY()-64,'m'));
                        scene->addItem(enemigosH.at(enemigosH.size()-1));
                        enemigosH.at(enemigosH.size()-1)->setMove('D');
                        enemigosH.at(enemigosH.size()-1)->setBanMove(true);
                        enemigosH.at(enemigosH.size()-1)->mover();
                        enemigosH.at(enemigosH.size()-1)->setBanD(true);
                    }
                    else{
                        enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+0.5*walls.at(p)->getWidth(),walls.at(p)->getPosY()-64,'b'));
                        scene->addItem(enemigosH.at(enemigosH.size()-1));
                        enemigosH.at(enemigosH.size()-1)->idle();
                    }
                }
                else if((walls.at(p)->getPosX() == 1139 && walls.at(p)->getPosY() == 200) ||
                        (walls.at(p)->getPosX() == 2032 && walls.at(p)->getPosY() == 224)){

                    enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+0.5*walls.at(p)->getWidth(),walls.at(p)->getPosY()-64,'m'));
                    scene->addItem(enemigosH.at(enemigosH.size()-1));
                    enemigosH.at(enemigosH.size()-1)->setMove('D');
                    enemigosH.at(enemigosH.size()-1)->setBanMove(true);
                    enemigosH.at(enemigosH.size()-1)->mover();
                    enemigosH.at(enemigosH.size()-1)->setBanD(true);
                }
            }
        }
        break;

    case 2:
        /*for(int p = 0; p < walls.size(); p++){
            if(walls.at(p)->getPosX() != 0){
                if((walls.at(p)->getPosX() == 0 && walls.at(p)->getPosY() == 622) || (walls.at(p)->getPosX() == 484 && walls.at(p)->getPosY() == 427)){
                    enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+0.5*walls.at(p)->getWidth(),walls.at(p)->getPosY()-64,'b'));
                    scene->addItem(enemigosH.at(enemigosH.size()-1));
                    enemigosH.at(enemigosH.size()-1)->idle();
                }
                else if(walls.at(p)->getPosX() == 3455 && walls.at(p)->getPosY() == 240){
                    enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+96,walls.at(p)->getPosY()-64,'m'));
                    enemigosH.push_back(new enemigos(walls.at(p)->getPosX()+386,walls.at(p)->getPosY()-64,'m'));
                    scene->addItem(enemigosH.at(enemigosH.size()-1));
                    scene->addItem(enemigosH.at(enemigosH.size()-2));
                    enemigosH.at(enemigosH.size()-1)->setMove('D');
                    enemigosH.at(enemigosH.size()-2)->setMove('D');
                    enemigosH.at(enemigosH.size()-1)->setBanMove(true);
                    enemigosH.at(enemigosH.size()-2)->setBanMove(true);
                    enemigosH.at(enemigosH.size()-1)->mover();
                    enemigosH.at(enemigosH.size()-2)->mover();
                    enemigosH.at(enemigosH.size()-1)->setBanD(true);
                    enemigosH.at(enemigosH.size()-2)->setBanD(true);
                }
            }
        }*/
        break;

    case 3:

        break;
    }

}

void MainWindow::clean_levels()
{
    for(int m = 0; m < walls.size(); m++){
        scene->removeItem(walls.at(m));
        walls.erase(walls.begin()+m);
        m -= 1;
    }
    for(int f = 0; f < spikes.size(); f++){
        scene->removeItem(spikes.at(f));
        spikes.erase(spikes.begin()+f);
        f -= 1;
    }
    for(int b = 0; b < ataque.size(); b++){
        ataque.erase(ataque.begin()+b);
        b--;
    }
    for(int h = 0; h < enemigosH.size(); h++){
        enemigosH.erase(enemigosH.begin()+h);
        h--;
    }
    for(int hm = 0; hm < ataqueHammer.size();hm++){
        ataqueHammer.erase(ataqueHammer.begin()+hm);
        hm--;
    }
    walls.clear();
    spikes.clear();
    ataque.clear();
}

void MainWindow::cargar_niveles(int Nivel)
{
    QVector<QString> nivel;

    clean_levels();

    if(Nivel == 1){ //Nivel 1

        scene->setBackgroundBrush(QPixmap(":/Imagenes/Fondos/Nivel1.jpeg"));

        //establece las posiciones del jugador dentro del nivel
        player1->setPX(0);
        player1->setPY(623);
        player1->setPos(player1->getPX(),player1->getPY());
        scene->addItem(player1);

        //Aparición del jugador en la escena
        player1->getSpown()->start(250); //The Guy
        //player1->stevenA();

        //Jefe final nivel 1
        jefe1 = new bills(379,414); //4799 311   370, 414
        scene->addItem(jefe1);
        jefe1->setBanSpown(true);
        jefe1->spown();

        nivel = LOne();

        for(int i = 0; i < nivel.size(); i++){
            list = nivel[i].split(',');
            for(int m = 0; m < list.size(); m++){
                switch (m) {
                case 0:
                    posx = list[m];
                    break;

                case 1:
                    posy = list[m];
                    break;

                case 2:
                    width = list[m];
                    break;

                case 3:
                    height = list[m];
                    break;

                case 4:
                    WallType = list[m];
                    break;
                }
            }

            X = posx.toInt();
            Y = posy.toInt();
            tamX = width.toInt();
            tamY = height.toInt();

            walls.push_back(new platform(X,Y,tamX,tamY));
            scene->addItem(walls.back());
        }
    }
    else if(Nivel == 2){ //Nivel 2

        scene->setBackgroundBrush(QPixmap(":/Imagenes/Fondos/Nivel2.jpeg"));

        //posicion del jugador en la escena
        player1->setPX(0);
        player1->setPY(592);
        player1->setPos(player1->getPX(),player1->getPY());
        scene->addItem(player1);

        //Aparición del jugador en la escena
        player1->getSpown()->start(250); //The Guy
        nivel = LTwo();

        for(int i = 0; i < nivel.size(); i++){
            list = nivel[i].split(',');
            for(int m = 0; m < list.size(); m++){
                switch (m) {
                case 0:
                    posx = list[m];
                    break;

                case 1:
                    posy = list[m];
                    break;

                case 2:
                    width = list[m];
                    break;

                case 3:
                    height = list[m];
                    break;

                case 4:
                    WallType = list[m];
                    break;
                }
            }

            X = posx.toInt();
            Y = posy.toInt();
            tamX = width.toInt();
            tamY = height.toInt();

            if(WallType == 'F'){
                walls.push_back(new platform(X,Y,tamX,tamY));
                scene->addItem(walls.back());
            }else{
                spikes.push_back(new spike(X,Y,tamX,tamY));
                scene->addItem(spikes.back());
            }
        }
    }
    else{ //Nivel 3

    }
}

void MainWindow::CollisionEnemy()
{
    for(int h = 0; h < enemigosH.size(); h++){
        if(enemigosH.at(h)->getBanDeath()){
            scene->removeItem(enemigosH.at(h));
            enemigosH.erase(enemigosH.begin()+h);
            h -= 1;
            break;
        }
        else{
            if(enemigosH.at(h)->getBanD() && enemigosH.at(h)->getBanIdle() == false && !enemigosH.empty()){
                for(int i = 0; i < walls.size(); i++){
                    if(player1->collidesWithItem(walls.at(i)) && enemigosH.at(h)->collidesWithItem(walls.at(i)) && enemigosH.at(h)->getBanDeath() == false){
                        if(abs(player1->getPX()-enemigosH.at(h)->getPx()) <= enemigosH.at(h)->getRango() && enemigosH.at(h)->getType() == 'b'){
                            if(enemigosH.at(h)->getBanAttack() == false){
                                enemigosH.at(h)->setBanAttack(true);
                                enemigosH.at(h)->ataque();
                            }
                        }
                        else{
                            if(player1->getPX() < enemigosH.at(h)->getPx()){
                                enemigosH.at(h)->setMove('A');
                                if(enemigosH.at(h)->getBanMove() == false){
                                    enemigosH.at(h)->setBanMove(true);
                                    enemigosH.at(h)->mover();
                                }
                            }
                            else if(player1->getPX() > enemigosH.at(h)->getPx()){
                                enemigosH.at(h)->setMove('D');
                                if(enemigosH.at(h)->getBanMove() == false){
                                    enemigosH.at(h)->setBanMove(true);
                                    enemigosH.at(h)->mover();
                                }
                            }
                        }
                    }
                    else{
                        if(enemigosH.at(h)->getType() == 'm'){
                            if(pow(pow(player1->getPX()-enemigosH.at(h)->getPx(),2)+pow(player1->getPY()-enemigosH.at(h)->getPy(),2),0.5) <= enemigosH.at(h)->getRadioHmm() && enemigosH.at(h)->getBanAttack() == false){
                                if(player1->getPX() < enemigosH.at(h)->getPx()) ataqueHammer.push_back(new hammerattack(enemigosH.at(h)->getPx(),enemigosH.at(h)->getPy(), 'A'));
                                else ataqueHammer.push_back(new hammerattack(enemigosH.at(h)->getPx(),enemigosH.at(h)->getPy(), 'D'));
                                scene->addItem(ataqueHammer.at(ataqueHammer.size()-1));
                                ataqueHammer.at(ataqueHammer.size()-1)->parabola();
                                ataqueHammer.at(ataqueHammer.size()-1)->setEnemigo(h);
                                enemigosH.at(h)->setBanAttack(true);
                            }
                        }
                        if((player1->collidesWithItem(walls.at(i)) || enemigosH.at(h)->collidesWithItem(walls.at(i))) && (enemigosH.at(h)->getBanMove())){
                            if(enemigosH.at(h)->collidesWithItem(walls.at(i))){
                                if(enemigosH.at(h)->getPx()+65 >= walls.at(i)->getPosX()+walls.at(i)->getWidth()){
                                    enemigosH.at(h)->setMove('A');
                                }

                                if(enemigosH.at(h)->getPx() <= walls.at(i)->getPosX()){
                                    enemigosH.at(h)->setMove('D');
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::validateAttackGuy()
{
    if(!ataque.empty() && !enemigosH.empty()){
        for(int h = 0; h < enemigosH.size(); h++){
            for(int it = 0; it < ataque.size(); it++){
                if(jefe1->scene() == scene){
                    if(ataque.at(it)->collidesWithItem(jefe1)){
                        ataque.at(it)->getAguy()->stop();
                        if(jefe1->getVida() == 0 && jefe1->getBanDeath() == false){
                            if(jefe1->getBanMove()){
                                jefe1->setBanMove(false);
                                jefe1->getMove()->stop();
                                //delete jefe1->getMove();
                            }
                            else if(jefe1->getBanAttack()){
                                jefe1->setBanAttack(false);
                                jefe1->getAttack()->stop();
                                delete jefe1->getAttack();
                            }
                            jefe1->setBanDeath(true);
                            jefe1->death();
                        }
                        else{
                            jefe1->setVida(jefe1->getVida()-ataque.at(it)->getDamage());
                        }

                        if(ataque.at(it)->scene() == scene){
                            scene->removeItem(ataque.at(it));
                        }
                        ataque.erase(ataque.begin()+it);
                        it -= 1;
                        break;
                    }
                }

                if(ataque.at(it)->collidesWithItem(enemigosH.at(h))){ //Cuando el jugador ataque al enemigo -> RECORDAR QUE DEPENDE DE LA DIFICULTAD
                    //Se le resta vida y acorde a la vida se elimina o no
                    ataque.at(it)->getAguy()->stop();
                    enemigosH.at(h)->setVidas(enemigosH.at(h)->getVidas()-ataque.at(it)->getDamage());
                    if(enemigosH.at(h)->getVidas() == 0){
                        enemigosH.at(h)->setBanD(false);
                        if(enemigosH.at(h)->getBanMove()){
                            enemigosH.at(h)->setBanMove(false);
                            enemigosH.at(h)->getMove()->stop();
                            enemigosH.at(h)->setPx(enemigosH.at(h)->getObjeto()->rebote(enemigosH.at(h)->getPx(),enemigosH.at(h)->getVx(),0,enemigosH.at(h)->getmMove()));
                            enemigosH.at(h)->setPos(enemigosH.at(h)->getPx(),enemigosH.at(h)->getPy());
                            //enemigoH->rebote(15,0);
                            delete enemigosH.at(h)->getMove();
                        }
                        if(enemigosH.at(h)->getBanAttack()){
                            enemigosH.at(h)->setBanAttack(false);
                            if(enemigosH.at(h)->getType() == 'b'){
                                enemigosH.at(h)->getAttack()->stop();
                                enemigosH.at(h)->setPx(enemigosH.at(h)->getObjeto()->rebote(enemigosH.at(h)->getPx(),enemigosH.at(h)->getVx(),0,enemigosH.at(h)->getmMove()));
                                enemigosH.at(h)->setPos(enemigosH.at(h)->getPx(),enemigosH.at(h)->getPy());
                                delete enemigosH.at(h)->getAttack();
                            }
                            else if(enemigosH.at(h)->getType() == 'm'){
                                enemigosH.at(h)->setPx(enemigosH.at(h)->getObjeto()->rebote(enemigosH.at(h)->getPx(),enemigosH.at(h)->getVx(),0,enemigosH.at(h)->getmMove()));
                                enemigosH.at(h)->setPos(enemigosH.at(h)->getPx(),enemigosH.at(h)->getPy());
                            }
                        }
                        if(enemigosH.at(h)->getType() == 'b') enemigosH.at(h)->muerte();
                        else enemigosH.at(h)->setBanDeath(true);
                    }

                    if(ataque.at(it)->scene() == scene){
                        scene->removeItem(ataque.at(it));
                    }
                    ataque.erase(ataque.begin()+it);
                    it -= 1;
                    break;
                }
            }
        }
        for(int it = 0; it < ataque.size(); it++){
            for(int p = 0; p < walls.size(); p++){
                if((ataque.at(it)->collidesWithItem(walls.at(p))) || (ataque.at(it)->collidesWithItem(lineLeft)) || (ataque.at(it)->collidesWithItem(lineRight))){
                    ataque.at(it)->getAguy()->stop();
                    if(ataque.at(it)->scene() == scene){
                        scene->removeItem(ataque.at(it));
                    }
                    ataque.erase(ataque.begin()+it);
                    break;
                }
            }
        }
    }
}

void MainWindow::validatePlayerMove()
{
    if(player1->getJump()){
        for(int m = 0; m < walls.size(); m++){

            if(player1->getJumpUp() && player1->collidesWithItem(walls.at(m))){ //Revisar esta parte
                player1->setAy(-1);
            }

            if(player1->getJumpDown() && player1->collidesWithItem(walls.at(m))){
                player1->getLeap()->stop();
                player1->setPY(walls.at(m)->getPosY()-49);
                player1->setPos(player1->getPX(),player1->getPY());
                player1->setAy(11);
                player1->setJump(false);
                player1->setJumpUp(false);
                player1->setJumpDown(false);
                player1->setJumpP(false);
                //delete player1->getLeap();
                break;
            }

            if(player1->collidesWithItem(lineUp)){
                player1->setAy(-1);
            }
        }

        if(player1->collidesWithItem(lineLeft)){
            player1->setJumpP(false);
        }

        if(player1->collidesWithItem(lineRight)){
            if(W+1280 < 5120){
                W += 1280;
                scene->setSceneRect(W,0,ui->graphicsView->width()-3,H);
                lineRight->setLine(W+1280,0,W+1280,708);
                //lineLeft->setLine(W,0,W,708);
            }
        }

        if(player1->collidesWithItem(lineDown)){
            //Se posiciona al jugador según la pantalla de nivele en que se encuentre
            if(numNivel == 1){
                if(W == 0){
                    player1->setPX(0);
                    player1->setPY(623);
                    player1->setPos(player1->getPX(),player1->getPY());
                }
                else if(W == 1280){
                    player1->setPX(1458);
                    player1->setPY(623);
                    player1->setPos(player1->getPX(),player1->getPY());
                }
                else if(W == 2560){
                    player1->setPX(2648);
                    player1->setPY(623);
                    player1->setPos(player1->getPX(),player1->getPY());
                }
                player1->getLeap()->stop();
                player1->setAy(11);
                player1->setJump(false);
                player1->setJumpUp(false);
                player1->setJumpDown(false);
                player1->setJumpP(false);
                delete player1->getLeap();
            }
        }
    }
    else{ //Parte de la caída libre del personaje
        for(int m = 0; m < walls.size(); m ++){
            if(player1->collidesWithItem(walls.at(m)) == false){
                if(m+1 == walls.size() && player1->getJumpDown() == false){
                    player1->setAy(-1);
                    player1->walkPlayer('W');
                }
            }
            else{
                break;
            }
        }

        if(player1->collidesWithItem(lineRight)){
            if(W+1280 < 5120){
                W += 1280;
                scene->setSceneRect(W,0,ui->graphicsView->width()-3,H);
                lineRight->setLine(W+1280,0,W+1280,708);
                lineLeft->setLine(W,0,W,708);
            }
        }
    }
}

void MainWindow::validateBillsMove()
{
    if(jefe1->scene() == scene){
        if(jefe1->collidesWithItem(lineUp)){
            jefe1->setVy(20);
        }

        for(int i = 0; i < walls.size(); i++){
            if(jefe1->collidesWithItem(walls.at(i))){
                jefe1->setVy(-20);
            }
        }

        if(jefe1->getBanDis() == true){
            if(jefe1->scene() == scene) scene->removeItem(jefe1);
            //delete jefe1;
        }
        else{
            if(pow(pow(player1->getPX()-jefe1->getPx(),2)+pow(player1->getPY()-jefe1->getPy(),2),0.5) <= jefe1->getRange()){
                if(ataquebills.empty() && jefe1->getBanAttack() == false && jefe1->getBanSpown() == false && jefe1->getBanDeath() == false){
                    jefe1->getMove()->stop();
                    delete jefe1->getMove();
                    jefe1->setBanAttack(true);
                    jefe1->attack();
                    ataquebills.push_back(new billsattack(player1->getPX(),0));
                    scene->addItem(ataquebills.at(ataquebills.size()-1));
                }
            }

            if(!ataquebills.empty() && jefe1->getBanDeath() == false){
                for(int b = 0; b < ataquebills.size(); b++){
                    for(int w = 0; w < walls.size(); w++){
                        if(ataquebills.at(b)->collidesWithItem(player1) || ataquebills.at(b)->collidesWithItem(walls.at(w))){
                            ataquebills.at(b)->getTime()->stop();
                            delete ataquebills.at(b)->getTime();
                            scene->removeItem(ataquebills.at(b));
                            ataquebills.erase(ataquebills.begin()+b);
                            b--;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::validateHammerAttack()
{
    if(!ataqueHammer.empty()){
        for(int a = 0; a < ataqueHammer.size(); a++){
            for(int w = 0; w < walls.size(); w++){
                if(ataqueHammer.at(a)->collidesWithItem(lineDown) || ataqueHammer.at(a)->collidesWithItem(walls.at(w)) || ataqueHammer.at(a)->collidesWithItem(player1)){
                    //cuando toque al jugador le restamos vida -> Muere
                    ataqueHammer.at(a)->getTiro()->stop();
                    scene->removeItem(ataqueHammer.at(a));
                    enemigosH.at(ataqueHammer.at(a)->getEnemigo())->setBanAttack(false);
                    delete ataqueHammer.at(a)->getTiro();
                    ataqueHammer.erase(ataqueHammer.begin()+a);
                    a--;
                    break;
                }
            }
        }
    }
}

void MainWindow::detectC()
{
    validateAttackGuy();
    validatePlayerMove();
    CollisionEnemy();
    if(numNivel == 1) validateBillsMove();
    validateHammerAttack();
}

void MainWindow::keyPressEvent(QKeyEvent *i)
{

    if(i->key() == Qt::Key_W || i->key() == Qt::Key_I){
        if(player1->getJump() == false){
            player1->walkPlayer('W');
            //player1->walkPlayer('I');
        }
    }

    if(i->key() == Qt::Key_D || i->key() == Qt::Key_L){
        for(int i = 0; i < walls.size(); i++){
            if(!enemigosH.empty()){
                for(int h = 0; h < enemigosH.size(); h++){
                    if(player1->collidesWithItem(lineRight) == false && player1->collidesWithItem(walls.at(i)) && player1->getJump() == false && player1->collidesWithItem(enemigosH.at(h)) == false){
                        QList<QGraphicsItem*> items = player1->collidingItems();
                        if(items.size() < 2){
                            player1->cinematica();
                        }
                        break;
                    }
                    else{
                        if(player1->collidesWithItem(enemigosH.at(h))){
                            player1->setPX(player1->getObjeto()->rebote(player1->getPX(),enemigosH.at(h)->getVx(),0,player1->getLado()));
                            player1->setPos(player1->getPX(),player1->getPY());
                            break;
                        }
                    }
                }
            }
            else{
                if(player1->collidesWithItem(lineRight) == false && player1->collidesWithItem(walls.at(i)) && player1->getJump() == false){
                    QList<QGraphicsItem*> items = player1->collidingItems();
                    if(items.size() < 2){
                        player1->cinematica();
                    }
                    break;
                }
            }
        }
        player1->walkPlayer('D');
        //player1->walkPlayer('L');
    }

    if(i->key() == Qt::Key_A || i->key() == Qt::Key_J){
        for(int i = 0; i < walls.size(); i++){
            if(!enemigosH.empty()){
                for(int h = 0; h < enemigosH.size(); h++){
                    if(player1->collidesWithItem(lineLeft) == false && player1->collidesWithItem(walls.at(i)) && player1->getJump() == false && player1->collidesWithItem(enemigosH.at(h)) == false){
                        QList<QGraphicsItem*> items = player1->collidingItems();
                        if(items.size() < 2){
                            player1->cinematica();
                        }
                        break;
                    }
                    else{
                        if(player1->collidesWithItem(enemigosH.at(h))){
                            player1->setPX(player1->getObjeto()->rebote(player1->getPX(),enemigosH.at(h)->getVx(),0,player1->getLado()));
                            player1->setPos(player1->getPX(),player1->getPY());
                            break;
                        }
                    }
                }
            }
            else{
                if(player1->collidesWithItem(lineLeft) == false && player1->collidesWithItem(walls.at(i)) && player1->getJump() == false){
                    QList<QGraphicsItem*> items = player1->collidingItems();
                    if(items.size() < 2){
                        player1->cinematica();
                    }
                    break;
                }
            }
        }
        player1->walkPlayer('A');
        //player1->walkPlayer('J');
    }

    if(i->key() == Qt::Key_Space){
        player1->walkPlayer('T');
        ataque.push_back(new guyattack(player1->getPX(), player1->getPY(), player1->getLado(),'g'));
        //ataque.push_back(new guyattack(player1->getPX(), player1->getPY(), player1->getLado(),'s'));
        scene->addItem(ataque.at(ataque.size()-1));
        ataque.at(ataque.size()-1)->getAguy()->start(75);
    }
}

MainWindow::~MainWindow()
{
    clean_levels();
    delete ui;
    delete scene;
    delete jefe1;
    delete player1;
    delete collisions;
    delete lineDown;
    delete lineLeft;
    delete lineRight;
    delete lineUp;
}

