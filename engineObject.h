#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>

class EngineObject {


    public:
        virtual ~EngineObject() = default;
        virtual void createUI(char *ID) = 0;

        void setName(std::string n);
        std::string getName();

    protected:

        std::string name;

};

#endif
