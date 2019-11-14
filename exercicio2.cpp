#include <GL/glut.h>
#include <iostream>

using namespace std;

#define LARGURA 500
#define ALTURA 500

GLfloat tx = 0;
GLfloat ty = 0;
GLfloat tamanhoX = 0.5;
GLfloat tamanhoY = 0.5;

GLfloat janela = 25;
GLfloat ombro = -180;
GLfloat cotovelo = 0;

//**********************************************************************************************************************************************************************
void desenha_cabeca(void)
{
	glBegin(GL_POLYGON);
		glColor3f(0.86f, 0.86f, 0.86f );
		glVertex2f(3.0, 10.0);
		
		glColor3f(0.86f, 0.86f, 0.86f );
		glVertex2f(3.0, 6.5);	
		
		glColor3f(0.66f,0.66f,0.66f );		
		glVertex2f(-1.5, 6.5);
		
		glColor3f(0.66f,0.66f,0.66f );
		glVertex2f(-1.5, 10.0);
	
	glEnd();

}
//**********************************************************************************************************************************************************************
void desenha_corpo(void)
{
	glBegin(GL_POLYGON);
		glColor3f(0.86f, 0.86f, 0.86f );
		glVertex2f( 5.0, 6.0 );
		
		glColor3f(0.86f, 0.86f, 0.86f );
		glVertex2f( 5.0, -12.0 );
		
		glColor3f(0.66f,0.66f,0.66f );	
		glVertex2f( -3.5, -12.0 );
		
		glColor3f(0.66f,0.66f,0.66f );	
		glVertex2f( -3.5, 6.0 );
	
	glEnd();
}	
//**********************************************************************************************************************************************************************
void desenha_braco(void)
{
	glBegin(GL_POLYGON);
		glVertex2f( 1.0,5.0 );
		glVertex2f( 1.0,-1.0 );
		glVertex2f( -1.0,-1.0 );
		glVertex2f( -1.0,5.0 );
	glEnd();
}
//**********************************************************************************************************************************************************************

void inicializa(void)
{
	//define a cor da janela como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void desenha(void)
{
//======================================================================================================================================================================
	//sistema de coordenadas
	glMatrixMode(GL_MODELVIEW);	
	
	//inicializa matriz de transformação
	glLoadIdentity();
//======================================================================================================================================================================
	
	//limpa a janela com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glPushMatrix();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glTranslatef(tx, ty, 0.5f);
	glScalef( tamanhoX, tamanhoY, 1.0f );

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glPushMatrix();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------		
	desenha_cabeca();

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	glPushMatrix();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	desenha_corpo();
	
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glPopMatrix();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glTranslatef( 6.0f, 4.0f, 0.0f );		// Ajusta a posição dos braço
	glRotatef( ombro, 0.0f, 0.0f, 1.0f );    
	glColor3f(0.0f, 0.0f, 1.0f);
	desenha_braco();
	
	glTranslatef( 0.0, 6.0, 0.0f );			// Ajusta a posição do ante-braço
	glRotatef( cotovelo, 0.0f, 0.0f, 1.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );
	desenha_braco();

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	glPopMatrix();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//executa os comandos openGL
	glFlush();
}

void redimencionar_desenho(GLsizei w, GLsizei h)
{
	GLsizei altura, largura;
	
	// Proteção contra divisão por zero.
	if( h == 0 )
	{
		h = 1;
	}

	// Redimensiona a larura e a altura.
	largura = w;
	altura = h;
	
	// Ajusta a largura e altura do Viewport
	glViewport( 0, 0, largura, altura );
	
	// Inicia o sistema de coordenadas
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	if( largura <= altura )
	{ 
		gluOrtho2D ( -25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura );
		janela = 25.0f;
	}              
	else 
	{ 
		gluOrtho2D( -25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f );
		janela = 25.0f*largura/altura;           
	}
}

void gamepad(int key, int x, int y)
{
	switch(key)
	{
//======================================================================================================================================================================
//TRANSLAÇÃO CORPO
		case GLUT_KEY_RIGHT:
					tx+=2;
					if( tx > janela )
					{
						tx = +janela; 							 
					}
					break;	
					
		case GLUT_KEY_LEFT:
					tx-=2;
					if( tx < -janela )
					{
						tx = -janela; 							 
					}
					break;
					
		case GLUT_KEY_UP:
					ty+=2;
					if( ty > janela )
					{
						ty = janela; 							 
					}
					break;
		
		case GLUT_KEY_DOWN:
					ty-=2;
					if( ty < -janela )
					{
						ty = -janela; 							 
					}
					break;
//======================================================================================================================================================================
//ESCALA CORPO
					
		case GLUT_KEY_PAGE_UP:
					tamanhoY += 0.1;
					tamanhoX += 0.1;
					break;
					
		case GLUT_KEY_PAGE_DOWN:
					if(	tamanhoX > 0.2 )
					{
						tamanhoX -= 0.1;
						tamanhoY -= 0.1;
						}
					break;
//======================================================================================================================================================================
//ROTAÇÕES BRAÇO E ANTE-BRAÇO
					
 		case GLUT_KEY_F1:
 					if( ombro > -180  )
					{	
						ombro-=5;					
					}
					break;
					
		case GLUT_KEY_F2:
					if( ombro < 0  )
					{	
						ombro+=5;					
					}
					break;
					
		case GLUT_KEY_F3:
					if( cotovelo > 0  )
					{	
						cotovelo-=5;					
					}
					break;
					
		case GLUT_KEY_F4:
					if( cotovelo < 180  )
					{	
						cotovelo+=5;					
					}
					break;
//======================================================================================================================================================================
	}
	
	glutPostRedisplay();
}

void teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
  


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exercicio 2 - Transformacoes geometricas");
	
	glutDisplayFunc(desenha);
	
	glutReshapeFunc(redimencionar_desenho);
	
	glutSpecialFunc(gamepad);

	glutKeyboardFunc (teclado);
	
	inicializa();	
	
	glutMainLoop();

	return 0;
}
