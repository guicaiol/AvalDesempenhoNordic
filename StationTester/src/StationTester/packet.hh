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

#ifndef PACKET_HH
#define PACKET_HH

#include <QList>

class Packet {
public:
    Packet();
    Packet(unsigned id);

    // Data management
    void addData(int data);
    QList<int> getData() const;
    int id() const;
    double timestamp() const;

    // Timestamp
    void setTimestamp(double timestamp);

    // Serialization
    void toBuffer(QByteArray *buffer);
    void fromBuffer(QByteArray *buffer);

    // Compare
    bool equals(const Packet &packet);

private:
    // ID
    int _id;

    // Data
    QList<int> _data;

    // Timestamp (TX)
    double _timestamp; // ms
};

#endif // PACKET_HH
