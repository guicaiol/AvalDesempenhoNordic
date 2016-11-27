#include <QCoreApplication>
#include <iostream>

#include <StationTester/rxstation.hh>
#include <StationTester/txstation.hh>

#define SERIALPORT_BAUDRATE 1000000
#define NUM_PACKETS 100
#define DATA_SIZE 4

#include <StationTester/packet.hh>

int main(int argc, char *argv[]) {
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
    std::cout << "TX rate: " << txRate << " Hz\n";
    std::cout << "PKT size: " << pktSize << " bytes\n";

    // Create stations
    TXStation tx(txPortName, SERIALPORT_BAUDRATE);
    tx.setNumPackets(NUM_PACKETS);
    tx.setPacketSize(pktSize);
    tx.setDataSize(DATA_SIZE);
    tx.setTXrate(txRate);

    RXStation rx(rxPortName, SERIALPORT_BAUDRATE);
    rx.setNumPackets(NUM_PACKETS);
    rx.setPacketSize(pktSize);
    rx.setDataSize(DATA_SIZE);

    // Start stations
    std::cout << "\nRunning TX and RX...\n";
    tx.start();
    rx.start();

    // Wait stations to finish jobs
    tx.wait();
    rx.wait();

    // End
    std::cout << "Finished TX and RX!\n";

    return 0;
}
