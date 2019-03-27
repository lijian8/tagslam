/* -*-c++-*--------------------------------------------------------------------
 * 2019 Bernd Pfrommer bernd.pfrommer@gmail.com
 */

#include "tagslam/factor/tag_projection.h"
#include "tagslam/graph.h"
#include <geometry_msgs/Point.h>
#include <string>
#include <sstream>

namespace tagslam {
  namespace factor {
    VertexDesc TagProjection::attachTo(Graph *g) const {
      auto f = std::shared_ptr<TagProjection>(new TagProjection(*this));
      f->setKey(0);
      return (g->add(f));
    }
    OptimizerKey TagProjection::addToOptimizer(Graph *g) {
      return (g->addToOptimizer(this));
    }
    
    TagProjection::TagProjection(const ros::Time &t,
                                 const std::shared_ptr<const Camera2> &cam,
                                 const std::shared_ptr<const Tag2> &tag,
                                 const geometry_msgs::Point *imgCorn,
                                 double pxn,
                                 const std::string   &name) :
      Factor(name, t), cam_(cam), tag_(tag), pixelNoise_(pxn) {
      imgCorners_ <<
        imgCorn[0].x, imgCorn[0].y,
        imgCorn[1].x, imgCorn[1].y,
        imgCorn[2].x, imgCorn[2].y,
        imgCorn[3].x, imgCorn[3].y;
    }
    std::string TagProjection::getLabel() const {
      std::stringstream ss;
      ss << "proj:" << name_ << ",t:" << format_time(time_);
      return (ss.str());
    }
  } // namespace factor
}  // namespace tagslam
