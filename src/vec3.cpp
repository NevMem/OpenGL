class vec3 {
public: 
	double x, y, z;

	vec3(): x(0), y(0), z(0){}
	vec3(double value): x(value), y(value), z(value) {}
	vec3(double a, double b, double c): x(a), y(b), z(c) {}

	~vec3(){}
};

//   | i   j   k   |
//   | a.x a.y a.z |
//   | b.x b.y b.z |
//
//   i * (a.y * b.z - a.z * b.x) + j * (a.z * b.x - a.x * b.z) + k * (a.x * b.y - a.y * b.x)

vec3 cross(vec3 a, vec3 b){
	return vec3(a.y * b.z - a.z * b.x, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x);
}

double dot(vec3 a, vec3 b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}