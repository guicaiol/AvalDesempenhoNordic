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

#include "timer.hh"
#include <QMutexLocker>

Timer::Timer() {
    clock_gettime(CLOCK_REALTIME, &_time1);
    clock_gettime(CLOCK_REALTIME, &_time2);
}

void Timer::start() {
    QMutexLocker locker(&_mutex);
    clock_gettime(CLOCK_REALTIME, &_time1);
}

void Timer::_stop() {
    clock_gettime(CLOCK_REALTIME, &_time2);
}

double Timer::_timensec() {
    _stop();
    return (_time2.tv_sec*1E9 + _time2.tv_nsec) - (_time1.tv_sec*1E9 + _time1.tv_nsec);
}

double Timer::timesec() {
    QMutexLocker locker(&_mutex);
    return _timensec()/1E9;
}

double Timer::timemsec() {
    QMutexLocker locker(&_mutex);
    return _timensec()/1E6;
}

double Timer::timeusec() {
    QMutexLocker locker(&_mutex);
    return _timensec()/1E3;
}

double Timer::timensec() {
    QMutexLocker locker(&_mutex);
    return _timensec();
}
