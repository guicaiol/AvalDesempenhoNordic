#include <QCoreApplication>
#include <QMap>
#include <iostream>
#include <StationTester/rxstation.hh>
#include <StationTester/txstation.hh>

#define SERIALPORT_BAUDRATE 1000000
#define NUM_PACKETS 3000
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

    // Generate random packets
    QMap<unsigned,Packet> packets;
    srand(time(NULL));
    for(unsigned i=0; i<NUM_PACKETS; i++) {
        Packet packet(i+1);

        // Generate random data
        int numData = (int)(pktSize/DATA_SIZE) - 1;
        for(int j=0; j<numData; j++) {
            int data = (rand()%INT_MAX);
            packet.addData(data);
        }

        // Append packet
        packets.insert(i, packet);
    }

    // Create stations
    TXStation tx(txPortName, SERIALPORT_BAUDRATE);
    tx.setNumPackets(NUM_PACKETS);
    tx.setPacketSize(pktSize);
    tx.setDataSize(DATA_SIZE);
    tx.setTXrate(txRate);
    tx.setPackets(packets);

    RXStation rx(rxPortName, SERIALPORT_BAUDRATE);
    rx.setNumPackets(NUM_PACKETS);
    rx.setPacketSize(pktSize);
    rx.setDataSize(DATA_SIZE);
    rx.setPackets(packets);

    // Start stations
    std::cout << "\nRunning TX and RX...\n";
    tx.start();
    rx.start();

    // Wait stations to finish jobs
    tx.wait();
    rx.wait();

    // End
    std::cout << "Finished TX and RX!\n";
    std::cout << "Packets sent: " << tx.packetsSent() << "\n";
    std::cout << "Packets received: " << rx.packetsReceived() << "\n";

    return 0;
}
