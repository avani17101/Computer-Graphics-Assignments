#include "main.h"

class Seven_Segment_Display {
public:
	Seven_Segment_Display () {}
	Seven_Segment_Display (float x, float y, float number);
	glm::vec3 position;
	void set_position(float x, float y);
	void set_number(float number);
	void draw (glm::mat4 VP);
	void update ();
	float number;
	float rotation;
private:
	VAO *one;
	VAO *two;
	VAO *three;
	VAO *four;
	VAO *five;
	VAO *six;
	VAO *seven;
};