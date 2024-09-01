#include "camera_system.hpp"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow* window) {
    this->window = window;

    glUseProgram(shader);
    view_location = glGetUniformLocation(shader, "view");
    camera_position_location = glGetUniformLocation(shader, "cameraPosition");
}

bool CameraSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transform_components,
    unsigned int camera_id, CameraComponent& camera_component, float dt) {

    glm::vec3& pos = transform_components[camera_id].position;
    glm::vec3& eulers = transform_components[camera_id].eulers;
    float theta = glm::radians(eulers.z);
    float phi = glm::radians(eulers.y);

    glm::vec3& right = camera_component.right;
    glm::vec3& up = camera_component.up;
    glm::vec3& forwards = camera_component.forwards;

    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    right = glm::normalize(glm::cross(forwards, global_up));
    up = glm::normalize(glm::cross(right, forwards));

    glm::mat4 view = glm::lookAt(pos, pos + forwards, up);

    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(camera_position_location, 1, glm::value_ptr(pos));

    //Keys
    glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        dPos.x += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        dPos.y -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        dPos.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        dPos.y += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        dPos.z += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        dPos.z -= 1.0f;
    }
    if (glm::length(dPos) > 0.1f) {
        dPos = glm::normalize(dPos);
        pos += 0.1f * dPos.x * forwards;
        pos += 0.1f * dPos.y * right;
        pos += 0.1f * dPos.z * up;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        return true;
    }

    //Mouse
    glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    glfwSetCursorPos(window, 320.0, 240.0);
    glfwPollEvents();

    dEulers.z = -0.1f * static_cast<float>(mouse_x - 320.0);
    dEulers.y = -0.1f * static_cast<float>(mouse_y - 240.0);

    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + dEulers.y));

    eulers.z += dEulers.z;
    if (eulers.z > 360) {
        eulers.z -= 360;
    }
    else if (eulers.z < 0) {
        eulers.z += 360;
    }

    return false;
}