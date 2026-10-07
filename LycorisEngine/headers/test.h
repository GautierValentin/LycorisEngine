#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <GLFW/glfw3.h>
#include <components/Script.h>

class CustomScript;

struct CustomScriptDesc {
    using ComponentType = CustomScript;
    Entity* entity;

    ScriptDesc desc;

    Entity* _entity;
    Entity* _entity2;
    Entity* _entity3;
};

class CustomScript : public Script {
public:
    CustomScript(CustomScriptDesc desc) : Script(desc.desc), _centity(desc._entity), _centity2(desc._entity2), _centity3(desc._entity3) {
        _entity = desc.entity;
    };

private:
    Entity* _centity;
    Entity* _centity2;
    Entity* _centity3;

public:
    void Update() override {
        Space space = Space::LOCAL;

        int state = glfwGetKey(_win, GLFW_KEY_ESCAPE);
        if (state == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(_win, true);
        }

        state = glfwGetKey(_win, GLFW_KEY_E);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _centity->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(0, 0, -.01f), space);
        }

        state = glfwGetKey(_win, GLFW_KEY_F);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _centity2->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(0, 0, -.01f), space);
        }

        state = glfwGetKey(_win, GLFW_KEY_R);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _centity3->TryFind<Transform>(tr);
            tr->Rotate(glm::quat(glm::vec3(0, 0, .01f)));
        }

        state = glfwGetKey(_win, GLFW_KEY_W);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _entity->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(0, 0, -.01f), space);
        }
        state = glfwGetKey(_win, GLFW_KEY_S);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _entity->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(0, 0, .01f), space);
        }
        state = glfwGetKey(_win, GLFW_KEY_A);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _entity->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(-.01f, 0, 0), space);
        }
        state = glfwGetKey(_win, GLFW_KEY_D);
        if (state == GLFW_PRESS)
        {
            Transform* tr;
            _entity->TryFind<Transform>(tr);
            tr->Translate(glm::vec3(.01f, 0, 0), space);
        }

        {
            static glm::vec2 oldPos(0.0f);

            double xPos, yPos;
            glfwGetCursorPos(_win, &xPos, &yPos);

            glm::vec2 newPos(xPos, yPos);

            glm::vec2 delta = newPos - oldPos;

            const float sensitivity = 0.01f;

            float yaw = -delta.x * sensitivity;
            float pitch = -delta.y * sensitivity;

            Transform* camTr;
            _entity->TryFind(camTr);

            // Accumulate the rotation.
            static float pitchAcc = camTr->_rotation.x;
            static float yawAcc = camTr->_rotation.y;

            pitchAcc = pitchAcc + pitch;
            yawAcc = yawAcc + yaw;

            // Clamp the CAMERA'S pitch, not the mouse delta.
            pitchAcc = glm::clamp(
                pitchAcc,
                glm::radians(-89.0f),
                glm::radians(89.0f)
            );

            glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
            glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));

            glm::quat rotation = qYaw * qPitch;

            camTr->Rotate(rotation);

            glm::quat pitchRotate = glm::quat(glm::cos(pitch / 2), glm::sin(pitch / 2), 0, 0);

            //camTr->Rotate(pitchRotate);

            oldPos = newPos;
        }
    }
};