#
# SSC0643 - Avaliação de Desempenho de Sistemas Computacionais
# University of Sao Paulo (USP) at Sao Carlos
# Authors:
# Guilherme Caixeta de Oliveira
# Lucas dos Santos Luchiari
#
# This file is part of StationTester project.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Application info
TEMPLATE = app
DESTDIR = bin
TARGET = StationTester
VERSION = 1.0
CONFIG += c++11

# Qt config
CONFIG += console
CONFIG -= app_bundle
QT += core serialport

# Optimization flags
QMAKE_CXXFLAGS  -= -O -O1
QMAKE_CXXFLAGS  += -O2 -ansi

# Libs
LIBS +=

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# Source files
INCLUDEPATH *= . src

SOURCES += \
    src/main.cc \
    src/StationTester/rxstation.cc \
    src/StationTester/station.cc \
    src/StationTester/txstation.cc

# Header files
HEADERS += \
    src/StationTester/rxstation.hh \
    src/StationTester/station.hh \
    src/StationTester/txstation.hh

# Other files
DISTFILES += \
    LICENSE
