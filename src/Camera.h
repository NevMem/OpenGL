#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
using namespace std;

class Camera {
private:
	glm::vec3 eye;
	glm::vec3 look;
	glm::vec3 up;

	glm::mat4 lookAtMatrix;

public:
	Camera();
	~Camera(){}

	void move(glm::vec3 m);

	float *getEyePointer();
	float *getEyeMatrix();
};