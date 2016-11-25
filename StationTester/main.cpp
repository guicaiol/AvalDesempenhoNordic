#include <QCoreApplication>
#include <QtSerialPort/QtSerialPort>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits.h>

#define SERIALPORT_BAUDRATE 1000000
#define PKT_NUMBER 1000
#define DATA_SIZE 4

// Packet definition
typedef struct{
    int id;
    QList<int> data;
} Packet;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Check arguments
    if(argc <= 1) {
        std::cout << "Usage: ./StationTester txPortName rxPortName txRate pktSize\n";
        return EXIT_FAILURE;
    }

    // Parse arguments
    const QString txPortName(argv[1]);
    const QString rxPortName(argv[2]);
    const int txRate = atoi(argv[3]);
    const int pktSize = atoi(argv[4]);

    std::cout << "CONFIGURATION:\n";
    std::cout << "TX serial port: " << txPortName.toStdString() << "\n";
    std::cout << "RX serial port: " << rxPortName.toStdString() << "\n";

    // Create serial ports
    QSerialPort tx, rx;

    // Config TX
    tx.setPortName(txPortName);
    tx.setBaudRate(SERIALPORT_BAUDRATE);
    tx.setParity(QSerialPort::NoParity);
    tx.setStopBits(QSerialPort::OneStop);
    tx.setFlowControl(QSerialPort::NoFlowControl);
    tx.setDataBits(QSerialPort::Data8);

    // Config RX
    rx.setPortName(rxPortName);
    rx.setBaudRate(SERIALPORT_BAUDRATE);
    rx.setParity(QSerialPort::NoParity);
    rx.setStopBits(QSerialPort::OneStop);
    rx.setFlowControl(QSerialPort::NoFlowControl);
    rx.setDataBits(QSerialPort::Data8);

    // Open TX
    if(tx.open(QIODevice::ReadWrite) == false) {
        std::cout << "[ERROR] Failed to open TX on " << txPortName.toStdString() << ".\n";
        return EXIT_FAILURE;
    }

    // Open RX
    if(rx.open(QIODevice::ReadWrite) == false) {
        std::cout << "[ERROR] Failed to open RX on " << rxPortName.toStdString() << ".\n";
        return EXIT_FAILURE;
    }

    // Creates the package data list
    QList<Packet> packetList;

    // Packet generation
    srand(time(NULL));
    for(int i=0; i<PKT_NUMBER; i++) {
        Packet aux;

        // Set id
        aux.id = i+1;

        // Generate other random data
        int numPackets = (int)(pktSize/DATA_SIZE) - 1;
        for(int j=0; j<numPackets; j++) {
            int data = (rand()%INT_MAX);
            aux.data.append(data);
        }

        // Append packet
        packetList.append(aux);
    }

    // Sending
    for(int i=0; i<PKT_NUMBER; i++) {

    }

    return app.exec();
}
