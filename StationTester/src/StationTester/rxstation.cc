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

#define READ_TIMEOUT 200 // ms

QString RXStation::name() {
    return "RXStation";
}

RXStation::RXStation(QString portName, int baudRate) : Station(portName, baudRate) {
    _packetsReceived = 0;
}

void RXStation::worker() {
    // Set port with buffer size enough for all packets
    port()->setReadBufferSize(numPackets()*packetSize());

    // Create timer
    Timer timer;
    timer.start();
    timer.stop();

    // Loop
    while(timer.timemsec() <= READ_TIMEOUT) {
        // Wait for
        bool ready = port()->waitForReadyRead(0);

        // Check valid packet
        if(ready && port()->bytesAvailable() >= packetSize()) {
            // Reset timer
            timer.start();

            // Read serial port
            QByteArray buffer = port()->read(packetSize());

            // Deserialize to packet
            Packet packet;
            packet.fromBuffer(&buffer);

            // Analyze packet
            /// TODO

            /// DEBUG
//            std::cout << "[RX] Received packet #" << packet.id() << " (" << buffer.size() << " bytes).\n\n";

            // Inc counter
            _packetsReceived++;
        }

        // Update timer
        timer.stop();
    }

}
