#ifndef UTILS_LOG_HPP
#define UTILS_LOG_HPP

#include <string>

namespace Utils {

class Log {
public:
    Log(std::ostream &os) : mOs(os) {}

    template <typename T>
    Log& operator<<(const T& t);
private:
    std::ostream &mOs;
};

template <typename T>
Log& Log::operator<<(const T& t) {
    mOs << t;
    return *this;
}

extern Log log;

}

#endif
