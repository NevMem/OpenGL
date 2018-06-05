class vec2 {
public:
	double x, y;

	vec2(): x(0), y(0) {}
	vec2(double value): x(value), y(value) {}
	vec2(double a, double b): x(a), y(b) {}
	~vec2(){}
};

double cross(vec2 a, vec2 b){
	return a.x * b.y - a.y * b.x;
}

double dot(vec2 a, vec2 b){
	return a.x * b.x + a.y * b.y;
}