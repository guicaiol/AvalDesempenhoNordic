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

#ifndef RXSTATION_HH
#define RXSTATION_HH

#include <StationTester/station.hh>

class RXStation : public Station {
public:
    RXStation(QString portName, int baudRate);

    unsigned packetsReceived() const { return _packetsReceived; }

private:
    // Station abstract implementation run implementation
    void worker();
    QString name();

    // Internal
    unsigned _packetsReceived;
};

#endif // RXSTATION_HH
