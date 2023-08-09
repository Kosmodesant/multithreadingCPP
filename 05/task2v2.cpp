#include <iostream>
#include <math.h>
using namespace std;

float clamp(float value, float min, float max)
{
	return fmax(fmin(value, max), min); // т.е. мы берём максимум (fmax) от минимума (fmin) и минимум от максимума (fmax) 
}

struct vec2
{
	float x, y;
	vec2(float value) : x(value), y(value) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}
	vec2 operator+(vec2 const& other) { return vec2(x + other.x, y + other.y); }
	vec2 operator-(vec2 const& other) { return vec2(x - other.x, y - other.y); }
	vec2 operator*(vec2 const& other) { return vec2(x * other.x, y * other.y); }
	vec2 operator/(vec2 const& other) { return vec2(x / other.x, y / other.y); }
};
struct vec3
{
	float x, y, z;

	vec3(float _value) : x(_value), y(_value), z(_value) {};
	vec3(float _x, vec2 const& v) : x(_x), y(v.x), z(v.y) {};
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

	vec3 operator+(vec3 const& other) { return vec3(x + other.x, y + other.y, z + other.z); }
	vec3 operator-(vec3 const& other) { return vec3(x - other.x, y - other.y, z - other.z); }
	vec3 operator*(vec3 const& other) { return vec3(x * other.x, y * other.y, z * other.z); }
	vec3 operator/(vec3 const& other) { return vec3(x / other.x, y / other.y, z / other.z); }
	vec3 operator-() { return vec3(-x, -y, -z); }

};

double sign(double a) { return (0 < a) - (a < 0); }
double step(double edge, double x) { return x > edge; }
float length(vec2 const& v) { return sqrt(v.x * v.x + v.y * v.y); }
float length(vec3 const& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
vec3 norm(vec3 v) { return v / length(v); }
float dot(vec3 const& a, vec3 const& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 abs(vec3 const& v) { return vec3(fabs(v.x), fabs(v.y), fabs(v.z)); }
vec3 sign(vec3 const& v) { return vec3(sign(v.x), sign(v.y), sign(v.z)); }
vec3 step(vec3 const& edge, vec3 v) { return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); }
vec3 reflect(vec3 rd, vec3 n) { return rd - n * (2 * dot(n, rd)); }
vec3 rotateX(vec3 a, double angle)
{
	vec3 b = a;
	b.z = a.z * cos(angle) - a.y * sin(angle);
	b.y = a.z * sin(angle) + a.y * cos(angle);
	return b;
}
vec3 rotateY(vec3 a, double angle)
{
	vec3 b = a;
	b.x = a.x * cos(angle) - a.z * sin(angle);
	b.z = a.x * sin(angle) + a.z * cos(angle);
	return b;
}
vec3 rotateZ(vec3 a, double angle)
{
	vec3 b = a;
	b.x = a.x * cos(angle) - a.y * sin(angle);
	b.y = a.x * sin(angle) + a.y * cos(angle);
	return b;
}
vec2 sphere(vec3 ro, vec3 rd, float r) {
	float b = dot(ro, rd);
	float c = dot(ro, ro) - r * r;
	float h = b * b - c;
	if (h < 0.0) return vec2(-1.0);
	h = sqrt(h);
	return vec2(-b - h, -b + h);
}
vec2 box(vec3 ro, vec3 rd, vec3 boxSize, vec3& outNormal) {
	vec3 m = vec3(1.0) / rd;
	vec3 n = m * ro;
	vec3 k = abs(m) * boxSize;
	vec3 t1 = -n - k;
	vec3 t2 = -n + k;
	float tN = fmax(fmax(t1.x, t1.y), t1.z);
	float tF = fmin(fmin(t2.x, t2.y), t2.z);
	if (tN > tF || tF < 0.0) return vec2(-1.0);
	vec3 yzx = vec3(t1.y, t1.z, t1.x);
	vec3 zxy = vec3(t1.z, t1.x, t1.y);
	outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);
	return vec2(tN, tF);
}
float plane(vec3 ro, vec3 rd, vec3 p, float w) { return -(dot(ro, p) + w) / dot(rd, p); }

float getDisk(vec3 p, float t)
{
	vec2 q = vec2(length(vec2(p.x, p.y)) - 1.0, p.z);
	return length(q) - 0.5;
}


int main()
{
	int width = 120;
	int heigh = 30;
	float aspect = (float)width / heigh;
	float pixelAspect = 11.0f / 24.0f;
	char gradient[] = " .:!/r(l1Z4H     "; // " .:!/r(l1Z4H9W8$@"
    int gradientSize = sizeof(gradient) - 2;

	char* screen = new char[width * heigh + 1];
	screen[width * heigh] = '\0';
	for (int t = 0; t < 100000; t++)
	{
		vec3  light = norm(vec3(sin(t * 0.001), cos(t * 0.001), -1.0));
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < heigh; j++)
			{
				vec2 uv = vec2(i, j) / vec2(width, heigh) * 2.0f - 1.0f;

				vec3 ro = vec3(-2, 0, 0);
				vec3 rd = norm(vec3(1, uv));

				uv.x = uv.x * aspect * pixelAspect;
				uv.x = uv.x + sin(t * 0.001);

				char pixel = ' ';
				int color = 0;

				vec2 intersection = sphere(ro, rd, 1);

				if (intersection.x > 0)
				{
					vec3 itPoint = ro + rd * intersection.x;
					vec3 n = norm(itPoint);
					float diff = dot(n, light);
					color = (int)(diff * 20);
				}
				color = clamp(color, 0, gradientSize);
				pixel = gradient[color];
				screen[i + j * width] = pixel;
			}
		}
		cout << screen;
	}
}

