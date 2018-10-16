#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class DrawableObject {
    public:
        virtual void getVertices() = 0;
        virtual void getTriangles() = 0;

        virtual glm::mat4 getTransform() = 0;

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat) = 0;

    protected:
        virtual void createVAO() = 0;
        virtual void deleteVAO() = 0;
        virtual void setUniform() = 0;
};
