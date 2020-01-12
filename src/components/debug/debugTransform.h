#ifndef DEBUGTRANSFORM_H
#define DEBUGTRANSFORM_H

#include "../component.h"

class DebugTransform : public Component {
public:

    DebugTransform(){setName("Debug Transform");}
    void createUI() override;

private:

};

#endif