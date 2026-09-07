#ifndef LEARN_OPENGL_VIEW_H
#define LEARN_OPENGL_VIEW_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct MVP
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};
#endif //LEARN_OPENGL_VIEW_H
