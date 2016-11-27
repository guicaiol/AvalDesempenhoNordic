/*
 * SSC0643 - Avaliação de Desempenho de Sistemas Computacionais
 * University of Sao Paulo (USP) at Sao Carlos
 * Authors:
 * Guilherme Caixeta de Oliveira
 * Lucas dos Santos Luchiari
 *
 * This file is part of StationTester project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCoreApplication>
#include <QMap>
#include <iostream>
#include <StationTester/rxstation.hh>
#include <StationTester/txstation.hh>
#include <StationTester/repeaterstation.hh>
#include <StationTester/timer.hh>

#define ST_TYPE_ANALYSIS 0
#define ST_TYPE_REPEATER 1

#define SERIALPORT_BAUDRATE 1000000
#define NUM_PACKETS 10
#define DATA_SIZE 4

#include <StationTester/packet.hh>

int main(int argc, char *argv[]) {
    // Check arguments
    if(argc <= 5) {
        std::cout << "Usage: ./StationTester stType txPortName rxPortName txRate pktSize\n";
        return EXIT_FAILURE;
    }

    // Parse arguments
    const int stType = atoi(argv[1]);
    const QString txPortName(argv[2]);
    const QString rxPortName(argv[3]);
    const int txRate = atoi(argv[4]);
    const int pktSize = atoi(argv[5]);

    std::cout << "CONFIGURATION:\n";
    std::cout << "TX serial port: " << txPortName.toStdString() << "\n";
    std::cout << "RX serial port: " << rxPortName.toStdString() << "\n";

    // SWITCH STATION TYPE
    if(stType==ST_TYPE_ANALYSIS) {

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
            packets.insert(i+1, packet);
        }

        // Create timer to calculate response time
        Timer timer;

        // Create stations
        TXStation tx(txPortName, SERIALPORT_BAUDRATE);
        tx.setNumPackets(NUM_PACKETS);
        tx.setPacketSize(pktSize);
        tx.setDataSize(DATA_SIZE);
        tx.setTXrate(txRate);
        tx.setPackets(&packets);
        tx.setTimer(&timer);

        RXStation rx(rxPortName, SERIALPORT_BAUDRATE);
        rx.setNumPackets(NUM_PACKETS);
        rx.setPacketSize(pktSize);
        rx.setDataSize(DATA_SIZE);
        rx.setPackets(&packets);
        rx.setTimer(&timer);

        // Start stations
        std::cout << "\nRunning TX and RX...\n";
        timer.start();
        tx.start(QThread::TimeCriticalPriority);
        rx.start(QThread::TimeCriticalPriority);

        // Wait stations to finish jobs
        tx.wait();
        rx.wait();

        // End
        float responseRate = ((float) rx.packetsReceived()/tx.packetsSent())*100;
        float hitRate = ((float) rx.packetsCorrect()/rx.packetsReceived())*100;

        std::cout << "Finished TX and RX!\n";

        std::cout << "\nRESULTS: \n";
        std::cout << "- Packets sent: " << tx.packetsSent() << "\n";
        std::cout << "- Packets received: " << rx.packetsReceived() << " (" << responseRate << " %)\n";
        std::cout << "- Packets correct: " << rx.packetsCorrect() << " (" << hitRate << " %)\n";
        std::cout << "- Mean response time: " << rx.meanResponseTime() << " ms\n";

    } else if(stType==ST_TYPE_REPEATER) {

        // Create station
        RepeaterStation rStation(txPortName, rxPortName, SERIALPORT_BAUDRATE);
        rStation.setPacketSize(pktSize);

        // Start repeater
        std::cout << "\nRunning Repeater Station...\n";
        rStation.start(QThread::TimeCriticalPriority);

        // Wait station to finish job
        rStation.wait();

        std::cout << "Finished Repeater Station!\n";
    }

    return 0;
}
