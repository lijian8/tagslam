/* -*-c++-*--------------------------------------------------------------------
 * 2019 Bernd Pfrommer bernd.pfrommer@gmail.com
 */


#include "tagslam/vertex.h"

#include <sstream>

namespace tagslam {
  std::ostream &operator<<(std::ostream &os, const Vertex &v) {
    os << v.toString();
    return (os);
  }

  std::string Vertex::toString() const {
    return (getLabel() + "," + (isValid() ? "V" : "I") + ","
            + (isOptimized() ? "O" : "U"));
  }

  std::string Vertex::format_time(const ros::Time &t) {
    // wrap around every 100 seconds,
    // resolution is in milliseconds
    uint64_t tw = (t.toNSec() % 100000000000UL) / 1000000L;
    std::stringstream ss;
    ss << tw;
    return (ss.str());
  }
}
