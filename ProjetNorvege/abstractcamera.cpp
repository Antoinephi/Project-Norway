#include "abstractcamera.h"

AbstractCamera::AbstractCamera()
{
}

bool AbstractCamera::equalsTo(AbstractCamera* c){
    return this == c;
}
