#include "trainnavigation.h"

TrainNavigation::TrainNavigation()
{

}
bool TrainNavigation::checkNewDirection(bool actualDirection, Rail *actualRail, Rail* newRail)
{
    QPoint railEndPosition;
    if (actualDirection) // direction = from P0 to P3
    {
        railEndPosition = actualRail->getLocation() + actualRail->getP3RelativeLocation().toPoint(); //P3
        if (railEndPosition != newRail->getLocation()) return false; //if true: end P3 -> start P3, false = change direction
    }
    else // direction = from P3 to P0
    {
      railEndPosition = actualRail->getLocation(); //P0
      if (railEndPosition != newRail->getLocation()) return false; //if true: end P0 -> start P3, false = same direction as before
    }
    return true; //set direction to "from P0 to P3" = "directionToEnd" in Train(Actor)
}
