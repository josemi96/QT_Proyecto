#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtBluetooth>


//RX -> tx
//tx -> Rx
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
   // agent->start();


   socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);






}


MainWindow::~MainWindow()
{
    delete ui;




}


void MainWindow::on_find_clicked()
{ ui->comboBox->clear();
    //agent->stop();
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




void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
 string =item->text();


 //static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));





}

void MainWindow::on_BConectar_clicked()
{
     socket->connectToService(QBluetoothAddress(string),1);
     if(socket->isOpen()){
         ui->status->setText("Status: Conectado");
     }else{
         ui->status->setText("Status: No Conectado");
     }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    string = arg1;
}

void MainWindow::on_Salir_clicked()
{
    socket->write("Cerrar_Programa");
}

void MainWindow::on_LeerTemp_clicked()
{
     socket->write("Leer_Temp");
}

void MainWindow::on_LeerLuz_clicked()
{
     socket->write("Leer_Luz");
}
