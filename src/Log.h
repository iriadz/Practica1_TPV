

#ifndef LOG_H
#define LOG_H

#include "Platform.h"

class Log : public Platform {
public:
    using Platform::Platform;
    Log(Game* g, GameState* gs, PlayState* ps, std::istream& is);
    virtual ~Log() = default;

private:
    int tipo; 
};

#endif // LOG_H

