#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include<QListWidget>




namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QByteArray temperatura;


private slots:
    void on_find_clicked();

    void on_on_clicked();

    void on_off_clicked();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void on_BConectar_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Salir_clicked();

    void on_LeerTemp_clicked();

    void on_LeerLuz_clicked();

    void escribir_Temp();

    void mostrar_conectado();


    void on_automatizacion_clicked(bool checked);

    void on_config_auto_clicked();

private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
    QString string;
   bool k = false;
};


#endif // MAINWINDOW_H
