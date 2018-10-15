#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Object {
    public:
        virtual void getVertices() = 0;
        virtual void getTriangles() = 0;

        virtual glm::mat4 getTransform() = 0;
}
