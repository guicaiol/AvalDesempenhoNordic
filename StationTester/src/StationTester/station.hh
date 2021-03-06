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

#ifndef STATION_HH
#define STATION_HH

#include <QMap>
#include <QThread>
#include <QSerialPort>
#include <StationTester/packet.hh>
#include <StationTester/timer.hh>

class Station : public QThread {
public:
    Station(QString portName, int baudRate);

    // Packet control
    void setNumPackets(unsigned numPackets) { _numPackets = numPackets; }
    void setPacketSize(unsigned packetSize) { _packetSize = packetSize; }
    void setDataSize(unsigned dataSize) { _dataSize = dataSize; }
    void setPackets(QMap<unsigned,Packet> *packets) { _packets = packets; }
    void setTimer(Timer *timer) { _timer = timer; }

protected:
    QSerialPort *port() { return _port; }
    unsigned numPackets() const { return _numPackets; }
    unsigned packetSize() const { return _packetSize; }
    unsigned dataSize() const { return _dataSize; }
    QMap<unsigned,Packet> *packets() const { return _packets; }
    Timer *timer() const { return _timer; }

private:
    // Serial port
    QSerialPort *_port;
    QString _portName;
    int _baudRate;

    // Packet control
    unsigned _numPackets;
    unsigned _packetSize;
    unsigned _dataSize;
    QMap<unsigned,Packet> *_packets;
    Timer *_timer;

    // Thread run implementation
    void run();

    // Abstract methods
    virtual void worker() = 0;
    virtual QString name() = 0;

    // Internal methods
    bool initialization();
    void finalization();
};

#endif // STATION_HH
