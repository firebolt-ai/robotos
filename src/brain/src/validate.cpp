#include <validate.h>
#include <future>
#include <sstream>
#include <string>

#include <boost/algorithm/string/replace.hpp>
#include <boost/thread.hpp>

#if defined(NDEBUG)
# error "[RobotOS][ERROR] Expected assertions, but none found."
#endif
