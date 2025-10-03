#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "ILogger.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "IHeaderStrategy.hpp"

// Dependency Inversion: Loggers depend on the abstraction IHeaderStrategy

class FileLogger : public ILogger
{
private: 
std::string _filename;
std::ofstream _file;
public:
    FileLogger(const std::string &filename): _filename(filename) {
        _file.open(_filename.c_str(), std::ios::app);
        if (!_file.is_open()) {
            throw std::invalid_argument("Could not open log file: " + _filename);
        }
    }
    virtual void write(const std::string &message) {
        if (_file.is_open()) {
            _file << message << std::endl;
        }
    }
    ~FileLogger() {
        if (_file.is_open()) {
            _file.close();
        }
    }
};


class StreamLoggerWithHeader : public ILogger
{
private:
    std::ostream &_stream;
    IHeaderStrategy *_headerStrategy;
public:
    StreamLoggerWithHeader(std::ostream &stream, IHeaderStrategy *headerStrategy)
        : _stream(stream), _headerStrategy(headerStrategy) {}
    virtual void write(const std::string &message) {
        if (_headerStrategy) {
            _stream << _headerStrategy->getHeader();
        }
        _stream << message << std::endl;
    }
};

class FileLoggerWithHeader : public ILogger{
private:
    std::string _filename;
    std::ofstream _file;
    IHeaderStrategy *_headerStrategy;
public:
    FileLoggerWithHeader(const std::string &filename, IHeaderStrategy *headerStrategy): _filename(filename), _headerStrategy(headerStrategy) {
        _file.open(_filename.c_str(), std::ios::app);
        if (!_file.is_open()) {
            throw std::invalid_argument("Could not open log file: " + _filename);
        }
    }
    virtual void write(const std::string &message) {
        if (_file.is_open()) {
            if (_headerStrategy) {  
                _file << _headerStrategy->getHeader();
            }
            _file << message << std::endl;
        }
    }
    ~FileLoggerWithHeader() {
        if (_file.is_open()) {      
            _file.close();
        }
    }
}; 


class StreamLogger : public ILogger{
private:
    std::ostream &_stream;
    IHeaderStrategy *_headerStrategy;
public:
    StreamLogger(std::ostream &stream, IHeaderStrategy *headerStrategy = NULL): _stream(stream), _headerStrategy(headerStrategy) {}
    virtual void write(const std::string &message) {
        if (_headerStrategy) {  
            _stream << _headerStrategy->getHeader();
        }
        _stream << message << std::endl;
    }
};

#endif
