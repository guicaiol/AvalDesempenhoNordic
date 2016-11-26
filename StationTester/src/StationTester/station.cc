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

#include "station.hh"
#include <iostream>

Station::Station(QString portName, int baudRate) {
    _portName = portName;
    _baudRate = baudRate;
}

void Station::run() {
    if(initialization()==false)
        return;
    worker();
    finalization();
}

bool Station::initialization() {
    // Create serial port
    _port = new QSerialPort();

    // Configure serial port
    _port->setPortName(_portName);
    _port->setBaudRate(_baudRate);
    _port->setParity(QSerialPort::NoParity);
    _port->setStopBits(QSerialPort::OneStop);
    _port->setFlowControl(QSerialPort::NoFlowControl);
    _port->setDataBits(QSerialPort::Data8);

    // Open serial port
    if(_port->open(QIODevice::ReadWrite) == false) {
        std::cout << "[ERROR] Failed to start " << name().toStdString() << " on " << _portName.toStdString() << ".\n";
        return false;
    }

    return true;
}

void Station::finalization() {
    // Close serial port
    _port->close();

    // Delete serial port
    delete _port;
}
