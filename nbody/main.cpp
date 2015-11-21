#include <fstream>
#include <iostream>
#include <string>

struct Vector3D
{
    float x, y, z;
};

struct Destruction
{
    float time; // timestamp of the destruction
    int destructor; // id of the Death Star or X-Wing
    int destructed; // id of the destroyed body
};

struct Collision
{
  float time; // timestamp of the collision
  int body1; // id of the first collided body
  int body2; // id of the second collided body
};

struct BodyPosition
{
  int body;
  Vector3D position;
};

struct Result
{
    Destruction* destructions;
    Collision* collisions;
    BodyPosition* positions;

    int destructions_count;
    int collisions_count;
    int positions_count;
} res;

int N = 0;

void Universe_Initialize(const char* filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        return;
    }

    file >> N;
    res.positions = new BodyPosition[N];

    int id = -1;
    std::string type;
    float mass = 0;
    float size = 0;
    Vector3D pos = {0, 0, 0};
    Vector3D speed = {0, 0, 0};
    Vector3D acc = {0, 0, 0};
    float fuel = 0;
    float consumption = 0;
    float range = 0;

    for(int i = 0; i < N; ++i)
    {
        file >> id;
        file >> type;
        if (type == "Death")
        {
            file >> type;
            type = "Death " + type;
        }

        file >> mass >> size >> pos.x >> pos.y >> pos.z >> speed.x >> speed.y >> speed.z;
        if (type == "Death Star" || type == "X-Wing")
        {
            file >> acc.x >> acc.y >> acc.z;
            file >> fuel >> consumption >> range;
//             printf("acc: %f, %f, %f, fuel: %f, cons: %f, range: %f\n",
//                     acc.x, acc.y, acc.z, fuel, consumption, range);
        }

        res.positions[i] = BodyPosition { id, pos.x, pos.y, pos.z };
    }
}

void Universe_Run(float time, float delta, Result* result)
{
}

void DebugPrint(const Result& result)
{
    // print global state of universe
    for(int i = 0; i < N; ++i)
    {
        const BodyPosition& body = result.positions[i];
        printf("(id: %d) (x, y, z: %f, %f, %f)\n",
               body.body, body.position.x, body.position.y,
               body.position.z);
    }
}

int main()
{
    Universe_Initialize("test.txt");
    DebugPrint(res);

    return (0);
}
