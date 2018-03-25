#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtBluetooth>


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

}

void MainWindow::mostrar_conectado(){
     ui->status->setText("Status: Conectado");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_find_clicked()
{
    ui->comboBox->clear();
    agent->start();
}


void MainWindow::on_on_clicked()
{
   socket->write("Activar_Rele");
}


void MainWindow::on_off_clicked()
{
   socket->write("Desactivar_Rele");
}


void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->comboBox->addItem(device.address().toString());
}

void MainWindow::on_BConectar_clicked()
{
     socket->connectToService(QBluetoothAddress(string),1);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    string = arg1;
}

void MainWindow::on_Salir_clicked()
{
    socket->write("Cerrar_Programa");
    socket->close();
    this->close();
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
     socket->write("Leer_luz");
}

void MainWindow::on_automatizacion_clicked(bool checked)
{
    if(checked){
        socket->write("Automatizacion");
    }
    else{
        socket->write("No_Automatizacion");

    }
}

void MainWindow::on_config_auto_clicked()
{
    socket->write("Config_Auto");
    std::string str1 = ui->spinLuz->text().toStdString();
    const char* p1 = str1.c_str();
    std::string str2 = ui->spinTemp->text().toStdString();
    const char* p2 = str2.c_str();
    socket->write(p1);
    socket->write(p2);
}
