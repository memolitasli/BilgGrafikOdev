#include"glew.h"
#include"freeglut.h"
#include<iostream>
#include<random>
#include<list>
#include<string>
using namespace std;

bool devam = true;

class ucgen {
public:

	float renkR;
	float renkG;
	float renkB;
	GLfloat posX;
	GLfloat posY;
	public :
		ucgen(float renkR, float renkG, float renkB, GLfloat posX, GLfloat posY) {
		this->renkR = renkR;
		this->renkB = renkB;
		this->renkG = renkG;
		this->posX = posX;
		this->posY = posY;
	}
public:
	ucgen() {};

};
ucgen ucgenListesi[7];
int gecenSure = 0;

void ucgenOlustur() {
	
	for (int i = 0;i < 7;i++) {
		ucgen u(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1);
		ucgenListesi[i] = u;
		}
	
}
float kutuXKordinatlari[2] = { -0.15,0.15 };
float kutuYKordinatlari[2] = { -0.872,-1 };


void temasKontrol(int index) {
	if (ucgenListesi[index].posY <= kutuYKordinatlari[0] && ((kutuXKordinatlari[0] <= ucgenListesi[index].posX)&&(ucgenListesi[index].posX <= kutuXKordinatlari[1]))) {
		devam = false;
	}
}


void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	for (int sayac = 0;sayac < 7;sayac++) {
		glBegin(GL_TRIANGLES);
		glColor3f(ucgenListesi[sayac].renkR, ucgenListesi[sayac].renkG, ucgenListesi[sayac].renkB);
		glVertex2f(ucgenListesi[sayac].posX, ucgenListesi[sayac].posY);
		glVertex2f(ucgenListesi[sayac].posX - 0.125, ucgenListesi[sayac].posY + 0.125 * 1.7320);
		glVertex2f(ucgenListesi[sayac].posX + 0.125, ucgenListesi[sayac].posY + 0.125 * 1.7320);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glRasterPos2f(0.6, 0.9);
	string yazi = "puan : ";
	const unsigned char* yaziYazi = reinterpret_cast<const unsigned char*>(yazi.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, yaziYazi);

	glColor3f(1, 1, 1);
	glRasterPos2f(0.9, 0.9);
	string puan = to_string(gecenSure * 2);
	const unsigned char* puanYazi = reinterpret_cast<const unsigned char*>(puan.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, puanYazi);
/*
float kutuXKordinatlari[2] = {-0.15,0.15};
	float kutuYKordinatlari[2] = { -0.872,-1 };
*/	
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex2f(kutuXKordinatlari[0], kutuYKordinatlari[0]);
	glVertex2f(kutuXKordinatlari[0], kutuYKordinatlari[1]);
	glVertex2f(kutuXKordinatlari[1], kutuYKordinatlari[1]);
	glVertex2f(kutuXKordinatlari[1], kutuYKordinatlari[0]);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void tmrScore(int) {
	if (devam == true) {
		gecenSure += 1;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, tmrScore, 0);
}
void tmrUcgen(int) {
	if (devam == true) {
		for (int i = 0;i < 7;i++) {
			switch (i) {
			case 0:
				ucgenListesi[i].posY -= 0.0048;
				break;
			case 1:
				ucgenListesi[i].posY -= 0.005;
				break;
			case 2:
				ucgenListesi[i].posY -= 0.008;
				break;
			case 3:
				ucgenListesi[i].posY -= 0.004;
				break;
			case 4:
				ucgenListesi[i].posY -= 0.007;
				break;
			case 5:
				ucgenListesi[i].posY -= 0.00544;
				break;
			case 6:
				ucgenListesi[i].posY -= 0.00666;
				break;
			}
			if (i % 2 == 0) {
				if (ucgenListesi[i].posY <= -1) {
					ucgenListesi[i].posY = 1;
					ucgenListesi[i].posX = -static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
			}
			else {
				if (ucgenListesi[i].posY <= -1) {
					ucgenListesi[i].posY = 1;
					ucgenListesi[i].posX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ucgenListesi[i].renkR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
			}
			temasKontrol(i);

		}
	}
	
	glutPostRedisplay();
	glutTimerFunc(10, tmrUcgen, 0);
}
void oyunResetle() {
	for (int i = 0;i < 7;i++) {
		if (i % 3 == 0) {
			ucgenListesi[i].posY = 1;
			ucgenListesi[i].posX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
		else {
			ucgenListesi[i].posY = 1;
			ucgenListesi[i].posX = -static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			ucgenListesi[i].renkR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}
	/*
	float kutuXKordinatlari[2] = { -0.15,0.15 };
float kutuYKordinatlari[2] = { -0.872,-1 };
	*/
	kutuXKordinatlari[0] = -0.15;
	kutuXKordinatlari[1] = 0.15;
	kutuYKordinatlari[0] = -0.872;
	kutuYKordinatlari[1] = -1;
	gecenSure = 0;
	devam = true;
}
void klavye(int key,int x,int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (kutuXKordinatlari[0] <= -1) {
		}
		else {
			kutuXKordinatlari[0] = kutuXKordinatlari[0] - 0.07;
			kutuXKordinatlari[1] = kutuXKordinatlari[1] - 0.07;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (kutuXKordinatlari[1] >= 1) {

		}
		else {
			kutuXKordinatlari[0] = kutuXKordinatlari[0] + 0.07;
			kutuXKordinatlari[1] = kutuXKordinatlari[1] + 0.07;
		}
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void enterTus(unsigned char key,int x,int y) {
	if (key == 13) {
		oyunResetle();
	}
}

int main(int argc, char** argv)
{
	ucgenOlustur();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(480, 640); 
	glutCreateWindow("17010011024-Mehmet-Tasli");
	glutDisplayFunc(display);
	glutTimerFunc(10, tmrUcgen, 0);
	glutTimerFunc(1000, tmrScore, 0);
	glutSpecialFunc(klavye);
	glutKeyboardFunc(enterTus);
	glutMainLoop();
	
	return 0;
}