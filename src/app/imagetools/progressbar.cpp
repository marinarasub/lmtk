#include "progressbar.h"

namespace progressbar {

    std::string getProgressBar(double percent, bool failed)
    { 
        if (percent > 1) throw std::logic_error("cannot have > 100% progress");
        if (percent < 0) throw std::logic_error("cannot have < 0% progress");

        const size_t MAX_BARS = 50;
        constexpr char EMPTY = '.';
        char FILLED = failed? 'X' : '#';

#ifdef _WINDOWS_ANSI
    _WINDOWS_ANSI(); 
#endif
        // TODO get console width
        size_t DONE_BARS = (int) (percent * MAX_BARS);
        std::string clr = (failed || percent == 0) ? RED : percent < 1 ? YELLOW : GREEN;
        std::string format = '\r' + CLEARLINE + clr; //CLEARLINE
        std::string progress = std::to_string(percent * 100.0);
        progress.resize(5);
        std::string lbar = "[" + std::string(DONE_BARS, FILLED) + std::string(MAX_BARS - DONE_BARS, EMPTY) + "]";

        return //'\r' + progress + "% " + lbar;
            format + progress + "% " + lbar + RESET;
    }

}