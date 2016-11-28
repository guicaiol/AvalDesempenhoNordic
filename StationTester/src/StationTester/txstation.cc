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

#include "txstation.hh"
#include <iostream>
#include <StationTester/packet.hh>

QString TXStation::name() {
    return "TXStation";
}

TXStation::TXStation(QString portName, int baudRate) : Station(portName, baudRate) {
    _packetsSent = 0;
}

void TXStation::worker() {
    // Clear
    port()->clear();
    port()->flush();

    QList<Packet> packetsList = packets()->values();

    // Sending
    QByteArray buffer;
    for(unsigned i=0; i<numPackets(); i++) {
        Packet packet = packetsList.at(i);

        // Update sending time on packet
        packet.setTimestamp(timer()->timemsec());
        packets()->insert(packet.id(), packet);

        // Serialize to buffer
        packet.toBuffer(&buffer);
//        buffer.append('\0');

        // Write to serial port
        int numBytes = port()->write(buffer);
        port()->waitForBytesWritten(-1);
        port()->flush();

        // Inc counter
        _packetsSent++;

        /// DEBUG
//        if(numBytes == buffer.size())
//            std::cout << "[TX] Sent packet #" << packet.id() << " (" << buffer.size() << " bytes)...\n";
//        else
//            std::cout << "[TX] FAILED to send packet #" << packet.id() << " (" << buffer.size() << " bytes)!\n";

        // Sleep
        QThread::usleep(1E6f/_txRate);
    }
}
