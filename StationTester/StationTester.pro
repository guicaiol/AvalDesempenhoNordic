QT += core
QT -= gui

CONFIG += c++11
QT += core gui widgets serialport

TARGET = StationTester
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
