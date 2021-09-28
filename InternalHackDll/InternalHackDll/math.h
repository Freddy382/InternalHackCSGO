#include <iostream>
#include <math.h>

double pi = 3.14159265359;

std::pair<float, float> calcAngle(float pos_x, float pos_y, float pos_z, float ent_x, float ent_y, float ent_z) {
	float delta_x = pos_x - ent_x;
	float delta_y = pos_y - ent_y;
	float delta_z = pos_z - ent_z;

	float hyp = sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

	float x = asin(delta_z / hyp) * 180 / pi;
	float y = atan(delta_y / delta_x) * 180 / pi;

	if (delta_x >= 0.0) {
		y += 180.0;
	}

	return std::make_pair(x, y);
}

float calcDistance(float pos_x, float pos_y, float pos_z, float ent_x, float ent_y, float ent_z) {
	float delta_x = pos_x - ent_x;
	float delta_y = pos_y - ent_y;
	float delta_z = pos_z - ent_z;

	float hyp = sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

	return hyp;
}