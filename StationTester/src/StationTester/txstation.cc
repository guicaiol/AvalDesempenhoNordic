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

}

void TXStation::worker() {
    // Creates the package data list
    QList<Packet> packetList;

    // Packet generation
    srand(time(NULL));
    for(unsigned i=0; i<numPackets(); i++) {
        Packet packet(i+1);

        // Generate random data
        int numData = (int)(packetSize()/dataSize()) - 1;
        for(int j=0; j<numData; j++) {
            int data = (rand()%INT_MAX);
            packet.addData(data);
        }

        // Append packet
        packetList.append(packet);
    }

    // Sending
    QByteArray buffer;
    for(unsigned i=0; i<numPackets(); i++) {
        Packet packet = packetList.at(i);

        // Serialize to buffer
        packet.toBuffer(&buffer);

        // Write to serial port
        port()->write(buffer);

        // Sleep
        QThread::msleep(1000/_txRate);
    }
}
