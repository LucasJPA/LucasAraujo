/************************************************************************************************************************************************************************
* 4º exercicio - Computação gráfica
* Autor: Lucas José Pereira de Araújo
* Matrícula: 1317149
*
* Desenho com animação 2D
************************************************************************************************************************************************************************/

#include <iostream>
#include <GL/glut.h>

using namespace std;

#define LARGURA 500
#define ALTURA 500

// Limites de fronteira
#define XMAX 16
#define XMIN -16
#define YMAX 18
#define YMIN -16

// Posição corrente do desenho.
GLfloat posicaoX;
GLfloat posicaoY;

// Deslocamento do desenho
GLfloat deslocamentoX;
GLfloat deslocamentoY;

void desenha_casa(void)
{
/**********************************************************************************************************************************************************************/
//Parede
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex2i(LARGURA/4, 0);
		glVertex2i(LARGURA/4, ALTURA/4);
		glVertex2i((LARGURA/4)+(LARGURA/2), ALTURA/4);
		glVertex2i((LARGURA/4)+(LARGURA/2), 0);
	glEnd();
/**********************************************************************************************************************************************************************/
//Teto
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glVertex2i(LARGURA/4, ALTURA/4);
		glVertex2i(LARGURA/2, ALTURA/2);
		glVertex2i((LARGURA/4)+(LARGURA/2), ALTURA/4);
	glEnd();
/**********************************************************************************************************************************************************************/
//Porta
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex2i( (LARGURA/2)-((LARGURA/12)), 0);
		glVertex2i( ((LARGURA/2)-(LARGURA/12)), LARGURA/8 );
		glVertex2i( (LARGURA/2)+((LARGURA/4)/12), LARGURA/8 );
		glVertex2i( (LARGURA/2)+((LARGURA/4)/12), 0);
	glEnd();/***********************************************************************************************************************************************************************/
//Janela
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex2i( (LARGURA/2)+((LARGURA/12)), ALTURA/12);
		glVertex2i( ((LARGURA/2)+(LARGURA/12)), ALTURA/8 );
		glVertex2i( (LARGURA/2)+((LARGURA/2)/3), ALTURA/8 );
		glVertex2i( (LARGURA/2)+((LARGURA/2)/3), ALTURA/12);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);
		glVertex2i( (LARGURA/2)+((LARGURA/8)) ,ALTURA/8);
		glVertex2i( (LARGURA/2)+((LARGURA/8)) ,ALTURA/12);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);
		glVertex2i( (LARGURA/2)+((LARGURA/12)), ALTURA/10);
		glVertex2i( (LARGURA/2)+((LARGURA/2)/3), ALTURA/10);
	glEnd();
/**********************************************************************************************************************************************************************/
}

void Desenha(void)
{	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glTranslatef(posicaoX, posicaoY, 0);
	
	desenha_casa();
	
	glutSwapBuffers();	
}

void Anima(int value)
{
	// Muda a direção quando chega na borda esquerda ou direita
	if( (posicaoX+XMAX) > 40 || (posicaoX+XMIN) < -40 )
	{
		deslocamentoX = -deslocamentoX;
	}

	// Muda a direção quando chega na borda superior ou inferior
	if( ( posicaoY+YMAX ) > 40 || (posicaoY+YMIN) < -40 )
	{
		deslocamentoY = -deslocamentoY;
	}

	// Move a casinha
	posicaoX = posicaoX + deslocamentoX;
	posicaoY = posicaoY + deslocamentoY;

	// Desenha a casa em outra posição
	glutPostRedisplay();
	glutTimerFunc( 150, Anima, 1 );
}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	deslocamentoX = 1;
	deslocamentoY = 1;

	posicaoX = 15;
	posicaoY = 0;
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluOrtho2D( -10, LARGURA, -10, ALTURA );
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Exercicio 4 - Animacao 2D");
	glutDisplayFunc(Desenha);
	glutTimerFunc( 150, Anima, 1 );
	Inicializa();
	glutMainLoop();
}

