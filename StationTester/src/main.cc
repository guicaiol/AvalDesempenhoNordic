#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits.h>

#include <StationTester/rxstation.hh>
#include <StationTester/txstation.hh>

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

    // Create stations
    TXStation tx(txPortName, SERIALPORT_BAUDRATE);
    RXStation rx(rxPortName, SERIALPORT_BAUDRATE);

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
