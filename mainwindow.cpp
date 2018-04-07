#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtBluetooth>

//Configuracion inicial:
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
   socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
  /* connect(socket, SIGNAL(messageReceived(QString,QString)),
           this, SLOT(showMessage(QString,QString)));*/
   connect(socket,SIGNAL(readyRead()),this,SLOT(escribir_Temp()));
   connect(socket,SIGNAL(connected()),this,SLOT(mostrar_conectado()));
   connect(socket,SIGNAL(disconnected()),this,SLOT(mostrar_desconectado()));

}

//Destructor de la clase:
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mostrar_conectado(){
     ui->status->setText("Estado: Conectado");
}

void MainWindow::mostrar_desconectado(){
     ui->status->setText("Estado: Desconectado");
}


void MainWindow::on_find_clicked()
{
    ui->comboBox->clear();
    agent->start();
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->comboBox->addItem(device.address().toString());
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    string = arg1;
}

void MainWindow::on_BConectar_clicked()
{
     socket->connectToService(QBluetoothAddress(string),1);
}

void MainWindow::on_Salir_clicked()
{
    socket->write("Comando_CP");
    socket->close();
    this->close();
}

void MainWindow::on_R1_on_clicked()
{
  Config_Rele(1,On);
}

void MainWindow::on_R1_off_clicked()
{
   Config_Rele(1,Off);
}

void MainWindow::on_R2_on_clicked()
{
    Config_Rele(2,On);
}

void MainWindow::on_R2_off_clicked()
{
    Config_Rele(2,Off);
}

void MainWindow::Config_Rele(int Rele,int Modo){

    Param_Comando_Rele *param= new Param_Comando_Rele;
    switch (Rele){
        case 1 :
            strcpy(param->Comando,"Comando_R1");
            break;
        case 2 :
            strcpy(param->Comando,"Comando_R2");
            break;
        default:
            printf("error");  }
    param->Modo=Modo;

    char *p = (char*)param;
    QByteArray packet(p, sizeof(Param_Comando_Rele));
    socket->write(packet);

}


void MainWindow::escribir_Temp(){
    QString lines = socket->read(1024);
   ui->label_2->setText(lines);
}

void MainWindow::on_LeerTemp_clicked()
{
     socket->write("Leer_Temp");

}



void MainWindow::on_LeerLuz_clicked()
{
    typedef struct
    {
    QString Comando;
    int result_code; // true if sucessful, false otherwise
    } estructura;

    estructura *receipt = new estructura;
    receipt->Comando="C";
    receipt->result_code = 15;
    char *p = (char*)receipt; // cast it to char* to make a QByteArray
    QByteArray packet(p, sizeof(estructura));


    socket->write(packet);
}

void MainWindow::on_automatizacion_clicked(bool Activo)
{
    if(Activo){
        socket->write("Comando_AA");
    }
    else{
        socket->write("Comando_NA");

    }
}

void MainWindow::on_config_auto_clicked()
{
    Param_Comando_CA *param = new Param_Comando_CA;
    strcpy(param->Comando,"Comando_CA");
    param->luz = ui->spinLuz->text().toInt();
    param->temperatura=ui->spinTemp->text().toInt();
    char *p = (char*)param;
    QByteArray packet(p, sizeof(Param_Comando_CA));
    socket->write(packet);
}


