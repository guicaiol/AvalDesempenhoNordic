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

#include "repeaterstation.hh"
#include <iostream>

#define READ_TIMEOUT 100 // ms

RepeaterStation::RepeaterStation(QString txPortName, QString rxPortName, int baudRate) {
    _txPortName = txPortName;
    _rxPortName = rxPortName;
    _baudRate = baudRate;
}

bool RepeaterStation::initialization() {
    // Create serial port
    _rxPort = new QSerialPort();
    _txPort = new QSerialPort();

    // Configure TX port
    _txPort->setPortName(_txPortName);
    _txPort->setBaudRate(_baudRate);
    _txPort->setParity(QSerialPort::NoParity);
    _txPort->setStopBits(QSerialPort::OneStop);
    _txPort->setFlowControl(QSerialPort::NoFlowControl);
    _txPort->setDataBits(QSerialPort::Data8);

    // Configure RX port
    _rxPort->setPortName(_rxPortName);
    _rxPort->setBaudRate(_baudRate);
    _rxPort->setParity(QSerialPort::NoParity);
    _rxPort->setStopBits(QSerialPort::OneStop);
    _rxPort->setFlowControl(QSerialPort::NoFlowControl);
    _rxPort->setDataBits(QSerialPort::Data8);

    // Open TX port
    if(_txPort->open(QIODevice::ReadWrite) == false) {
        std::cout << "[ERROR] Failed to start TX serial port on " << _txPortName.toStdString() << ".\n";
        return false;
    }

    // Open RX port
    if(_rxPort->open(QIODevice::ReadWrite) == false) {
        std::cout << "[ERROR] Failed to start RX serial port on " << _rxPortName.toStdString() << ".\n";
        return false;
    }

    return true;
}

void RepeaterStation::run() {
    if(initialization()==false)
        return;
    worker();
    finalization();
}

void RepeaterStation::worker() {
    // Clear
    _rxPort->clear();
    _rxPort->flush();
    _txPort->clear();
    _txPort->flush();

    // Create timer
    Timer timeoutTimer;
    timeoutTimer.start();

    // Loop
    while(timeoutTimer.timemsec() <= READ_TIMEOUT) {
        // Check ready
        bool ready = _rxPort->waitForReadyRead(0);

        // Check valid packet
        if(ready && _rxPort->bytesAvailable() >= _packetSize) {
            // Reset timer
            timeoutTimer.start();

            // Read RX serial port
            QByteArray buffer = _rxPort->read(_packetSize);

            // Write to TX serial port
            _txPort->write(buffer);
            _txPort->waitForBytesWritten(-1);
            _txPort->flush();

        }
    }

}

void RepeaterStation::finalization() {
    // Close serial ports
    _rxPort->close();
    _txPort->close();

    // Delete serial ports
    delete _rxPort;
    delete _txPort;
}



