#include <cmath>

#include <windows.h>
#include <Gl/gl.h>
#include <GL/glut.h>

struct Window {
	int width;
	int height;
} window;

const double PI = 4 * atan(1);
const double PI2 = 8 * atan(1);

void drawWireTriangle(double size) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; ++i) {
		glVertex2f(size * cos(i * PI2 / 3), size * sin(i * PI2 / 3));
	}
	glEnd();
}

void drawSolidTriangle(double size) {
	static float colors[3][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
	};
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; ++i) {
		glColor3fv(colors[i]);
		glVertex2f(size * cos(i * PI2 / 3), size * sin(i * PI2 / 3));
	}
	glEnd();
	glColor3f(1, 1, 1);
}

void drawWireSquare(double size) {
	float h = size * sqrt(2) / 2;
	glBegin(GL_LINE_LOOP);
	glVertex2f(-h, h);
	glVertex2f(h, h);
	glVertex2f(h, -h);
	glVertex2f(-h, -h);
	glEnd();
}

static double rotateY = 0;
static double rotateX = 0;

static int primitiveNumber = 5;

void drawPrimitive() {
	switch (primitiveNumber % 9) {
	case 0: glutWireTeapot(1.2); break;
	case 1: glutWireSphere(1, 20, 20); break;
	case 2: glutWireCube(1); break;
	case 3: glutWireCone(1, 1, 20, 20); break;
	case 4: glutWireTorus(0.8, 1, 20, 20); break;
	case 5: glutWireDodecahedron(); break;
	case 6: glutWireOctahedron(); break;
	case 7: glutWireTetrahedron(); break;
	case 8: glutWireIcosahedron(); break;
	}
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(180. / 2 * rotateY, 0, 1, 0);
	glRotatef(180. / 2 * rotateX, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	drawPrimitive();

	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	drawWireTriangle(0.3);

	glLoadIdentity();
	glTranslatef(-0.5, -0.5, 0);
	drawWireSquare(0.3);

	glLoadIdentity();
	glTranslatef(0.5, -0.5, 0);
	drawSolidTriangle(0.3);

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (GLUT_DOWN != state) return;
	++primitiveNumber;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': rotateX -= 0.1; break;
	case 's': rotateX += 0.1; break;
	case 'a': rotateY += 0.1; break;
	case 'd': rotateY -= 0.1; break;
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	window.width = width;
	window.height = height;
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Title goes here");
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}