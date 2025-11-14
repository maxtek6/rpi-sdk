#include <rpi.h>

#include <alsa/asoundlib.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace rpi
{
    class exception
    {
    public:
        exception() = default;
        int error() const { return _error_code; }
    private:
        int _error_code;    
    };

    template<class Func, class... Args> int try_catch(Func&& func, Args&&... args)
    {
        try
        {
            return func(std::forward<Args>(args)...);
        }
        catch(const exception& e)
        {

        }
    }
}