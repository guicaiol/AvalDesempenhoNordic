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

#include "rxstation.hh"
#include <StationTester/packet.hh>
#include <StationTester/timer.hh>
#include <iostream>

#define READ_TIMEOUT 100 // ms

QString RXStation::name() {
    return "RXStation";
}

RXStation::RXStation(QString portName, int baudRate) : Station(portName, baudRate) {
    _packetsReceived = 0;
    _packetsCorrect = 0;
    _meanResponseTime = 0;
}

void RXStation::worker() {
    // Clear
    port()->clear();
    port()->flush();

    // Set port with buffer size enough for all packets
    port()->setReadBufferSize(numPackets()*packetSize());

    // Create timer
    Timer timeoutTimer;
    timeoutTimer.start();

    // Loop
    while(timeoutTimer.timemsec() <= READ_TIMEOUT) {
        // Check ready
        bool ready = port()->waitForReadyRead(0);

        // Check valid packet
        if(ready && port()->bytesAvailable() >= packetSize()) {
            // Reset timer
            timeoutTimer.start();

            // Read serial port
            QByteArray buffer = port()->read(packetSize());

            // Deserialize to packet
            Packet recvdPacket;
            recvdPacket.fromBuffer(&buffer);

            // Save RX time
            double rxTimestamp = timer()->timemsec();

            /// DEBUG
//            std::cout << "[RX] Received packet #" << recvdPacket.id() << " (" << buffer.size() << " bytes).\n\n";

            // Analyze packet
            if(packets()->contains(recvdPacket.id())) {
                _packetsReceived++;

                // Get source packet
                Packet source = packets()->value(recvdPacket.id());

                // Calc response time
                const double dt = rxTimestamp - source.timestamp();
                _responseTimes.append(dt);

                // Check correct
                if(recvdPacket.equals(source))
                    _packetsCorrect++;
                else {
                    /// DEBUG
//                    std::cout << "[RX] Received wrong packet...\n";
//                    std::cout << "[RX] Source (#" << source.id() << "): ";
//                    for(int i=0; i<source.getData().size(); i++)
//                        printf("%d ", source.getData().at(i));
//                    printf("\n");

//                    std::cout << "[RX] Received (#" << recvdPacket.id() << "): ";
//                    for(int i=0; i<recvdPacket.getData().size(); i++)
//                        printf("%d ", recvdPacket.getData().at(i));
//                    printf("\n\n");

                }
            }

        }

    }

    // Calc mean response time
    double sum = 0;
    for(int i=0; i<_responseTimes.size(); i++)
        sum += _responseTimes.at(i);
    _meanResponseTime = sum/_responseTimes.size();
}
