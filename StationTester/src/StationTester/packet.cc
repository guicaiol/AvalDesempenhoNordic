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

#include "packet.hh"

Packet::Packet(unsigned id) {
    _id = id;
}

void Packet::addData(int data) {
    _data.append(data);
}

QList<int> Packet::getData() const {
    return _data;
}

int Packet::id() const {
    return _id;
}

void Packet::toBuffer(QByteArray *buffer) {
    // Clear
    buffer->clear();

    // Append id
    buffer->append(QByteArray((const char *)&_id, sizeof(int)));

    // Append data
    for(int i=0; i<_data.size(); i++)
        buffer->append(QByteArray((const char *)&_data[i], sizeof(int)));
}

void Packet::fromBuffer(QByteArray *buffer) {
    QByteArray tmp(*buffer);

    // ID
    QByteArray id = tmp.left(sizeof(int));
    char *integer = id.data();
    _id = *((int*) integer);
    tmp.remove(0, sizeof(int));

    // Data
    _data.clear();

    int dataNum = tmp.size()/sizeof(int);
    for(int i=0; i<dataNum; i++) {
        QByteArray dataArray = tmp.left(sizeof(int));
        char *integer = dataArray.data();
        int data = *((int*) integer);
        tmp.remove(0, sizeof(int));

        _data.append(data);
    }
}
