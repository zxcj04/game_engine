#pragma once

#include <iostream>
#include <limits>
#include <map>

#include <glm/glm.hpp>

#include <constants.hpp>
#include <BuildScene.hpp>
#include <Shader.hpp>

using namespace std;

class Ball
{
    public:
        Ball(glm::vec3, float, glm::vec3);
        ~Ball();

        void draw(Shader, glm::vec3, float, float, float, float);
        void move(vector<Ball>&, bool, float);

        bool check_boundary_collision(vector<glm::vec3>&, float);
        bool check_ball_collision(Ball &, float);

        static int count;

    private:

        glm::vec3 position;
        glm::vec3 speed;
        glm::vec3 acceleration;

        int number;

        unsigned int vao;
        float radius;
        int size;

        vector<glm::vec3> callis;

};