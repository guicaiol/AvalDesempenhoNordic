#include <QCoreApplication>
#include <QtSerialPort/QtSerialPort>
#include <cstdlib>
#include <ctime>
#include <limits.h>

#define BAUDRATE 1000000
#define PKGNUNBER 1000
#define MAXRAND INT_MAX

typedef struct{
    int id;
    QList<int> data;
}package;

int main(int argc, char *argv[])
{
    if (argc == 0) {exit(0);}

    const QString& portNameTx = argv[1];
    const QString& portNameRx = argv[2];
    const int rate = argv[3];
    const int length = argv[4];

    QCoreApplication a(argc, argv);
    QSerialPort serialPortTx;
    QSerialPort serialPortRx;

    //Sets the BaudRate
    serialPortTx.setBaudRate(BAUDRATE);
    serialPortTx.setParity(QSerialPort::NoParity);
    serialPortTx.setStopBits(QSerialPort::OneStop);
    serialPortTx.setFlowControl(QSerialPort::NoFlowControl);
    serialPortTx.setDataBits(QSerialPort::Data5);

    serialPortRx.setBaudRate(BAUDRATE);
    serialPortRx.setParity(QSerialPort::NoParity);
    serialPortRx.setStopBits(QSerialPort::OneStop);
    serialPortRx.setFlowControl(QSerialPort::NoFlowControl);
    serialPortRx.setDataBits(QSerialPort::Data5);

    // Opens the Tx port in ReadWrite mode
    serialPortTx.setPortName(portNameTx);
    bool ok = serialPortTx.open(QIODevice::ReadWrite);
    if(!ok){cout << "Pau na abertura da porta serial\n"; exit(0);}

    // Opens the Rx port in ReadWrite mode
    serialPortRx.setPortName(portNameRx);
    ok = serialPortRx.open(QIODevice::ReadWrite);
    if(!ok){cout << "Pau na abertura da porta serial\n"; exit(0);}

    // Random Seed
    srand(time(NULL));


    // Creates the package data list
    QList<package> packList;

    // Package Generation
    for(int i=0; i<PKGNUNBER; i++)
    {
        package aux;
        aux.id = i;
        for(int j=0; j<length/sizeof(int); j++)
        {
            int info = rand()%MAXRAND;
            aux.data.append(info);
        }
        packList.append(aux);
    }

    // Sending
    for(int i=0; i<PKGNUNBER; i++)
    {

    }


    return a.exec();
}
