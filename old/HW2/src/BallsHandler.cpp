#include <BallsHandler.hpp>

BallsHandler::BallsHandler()
{
    random_device rd;

    rd_generator = mt19937(rd());
}

BallsHandler::~BallsHandler()
{

}

void BallsHandler::add_ball(float boundary_size, glm::vec3 position, float radius, glm::vec3 speed)
{
    _balls.push_back(Ball(position, radius, speed));
}

void BallsHandler::add_ball(float boundary_size)
{
    uniform_real_distribution<float> unif_position(-boundary_size / 2, boundary_size / 2);
    uniform_real_distribution<float> unif_radius(50, 250);
    uniform_real_distribution<float> unif_speed(-50, 50);

    float radius = unif_radius(rd_generator);

    glm::vec3 position;
    glm::vec3 speed;

    do
    {
        position.x = unif_position(rd_generator);
        position.y = unif_position(rd_generator);
        position.z = unif_position(rd_generator);

    } while (abs(position.x) + radius >= 1000 ||
             abs(position.y) + radius >= 1000 ||
             abs(position.z) + radius >= 1000);

    speed = glm::vec3(
        unif_speed(rd_generator),
        unif_speed(rd_generator),
        unif_speed(rd_generator)
    );

    add_ball(boundary_size, position, radius, speed);
}

void BallsHandler::draw_balls(Shader shader, glm::vec3 player_position, float yaw, float pitch, float near, float far)
{
    for(auto & ball: _balls)
        ball.draw(shader, player_position, yaw, pitch, near, far);
}

void BallsHandler::move_balls(bool cool, float decay)
{
    for(int i = 0; i < _balls.size(); i++)
        for(int j = i + 1; j < _balls.size() ; j++)
        {
            _balls[i].check_ball_collision(_balls[j], decay);
        }

    for(auto & ball: _balls)
        ball.move(_balls, cool, decay);
}

void BallsHandler::reset_balls()
{
    _balls.clear();

    Ball::count = 0;
}