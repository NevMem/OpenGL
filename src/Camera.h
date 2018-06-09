#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
using namespace std;

class Camera {
private:
	glm::vec4 eye;
	glm::vec4 look;
	glm::vec4 up;

	glm::mat4 lookAtMatrix;

public:
	Camera();
	~Camera(){}

	void move(glm::vec3 m);
	void moveForward();
	void moveBackward();
	void rotateHorizontal(float angle);
	void rotateVertical(float angle);

	float *getEyeMatrix();
};