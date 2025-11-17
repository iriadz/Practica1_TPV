#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class GameError : public std::logic_error {
public:
    explicit GameError(const std::string& msg) : std::logic_error(msg) {}
};

class SDLError : public GameError {
public:
    explicit SDLError(const std::string& msg) : GameError("SDL Error: " + msg) {}
};

class FileNotFoundError : public GameError {
public:
    explicit FileNotFoundError(const std::string& filename)
        : GameError("File not found: " + filename) {
    }
};

class FileFormatError : public GameError {
public:
    FileFormatError(const std::string& filename, int line, const std::string& msg)
        : GameError(filename + ":" + std::to_string(line) + " - " + msg) {
    }
};

#endif