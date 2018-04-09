#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include<QListWidget>

#define On 1
#define Off 0


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




private slots:
    void on_find_clicked();

    void on_R1_on_clicked();

    void on_R1_off_clicked();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void on_BConectar_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Salir_clicked();

    void on_LeerTemp_clicked();

    void on_LeerLuz_clicked();

    void recibir_respuesta();

    void mostrar_conectado();

    void mostrar_desconectado();

    void on_automatizacion_clicked(bool Activo);

    void on_config_auto_clicked();

    void Config_Rele(int Rele,int Modo);

    void on_R2_on_clicked();

    void on_R2_off_clicked();

private:

    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
    QString string;
    bool k = false;

   typedef struct{
   char Comando[10];
   int Modo;
   }Param_Comando_Rele;

   typedef struct{
   char Comando[10];
   int luz;
   int temperatura;
   }Param_Comando_CA;

   typedef struct{
        char Comando[10];
        float dato;
    }Param_Comando_Simple;

};


#endif // MAINWINDOW_H
