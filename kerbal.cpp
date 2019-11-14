/* Alunos
*  Lucas Jose Pereira de Araujo 1317149
*  Renan da Silveira Teles 1250207
*/


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdlib.h>
#include <math.h>
#include<string.h>

#define X 5*.525731112119133606
#define Z 5*.850650808352039932
#define PI  2*3.14159265358979323846  /* pi */


//Initializing variables
GLfloat axisX=0.0,
        axisY=0.0, 
        axisZ=0.0, 
        rotation=-90.0,
        rocketAngle=0.0, 
        verticalRotation=0.0, 
        scale = 1.0;

int forward=0;
int left=0;
int right=0;

//Booleans that say they are rising or falling 
bool goingUp = false, goingDown = false;

//Booleans that tell whether the rocket took off or landed
bool isFlying = false, isInTheFloor = false;

GLfloat eye[]={0.0,75.0,-50.0};
GLfloat look[]={0.0,0.0,0.0};

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

static GLfloat vdata1[12][3] = {
        {-X, 0.0, Z}
       ,{X, 0.0, Z}
       ,{-X, 0.0, -Z}
       ,{X, 0.0, -Z}
       ,{0.0, Z, X}
       ,{0.0, Z, -X}
       ,{0.0, -Z, X}
       ,{0.0, -Z, -X}
       ,{Z, X, 0.0}
       ,{-Z, X, 0.0}
       ,{Z, -X, 0.0}
       ,{-Z, -X, 0.0}
   };

static GLuint vindices[20][3] = {
  {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
  {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
  {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
  {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
};

/*
* Configure the lighting
* @param  void
* @return void
*/
void lighting (void) {
    const GLfloat lightPosition[]={2.0,6.0,3.0,0.0};
    const GLfloat ambiente[]={1.0,1.0,1.0,1.0};
    const GLfloat speculate[]={1.0,1.0,1.0,1.0};
    const GLfloat difuse[]={1.0,1.0,1.0,1.0};
    const GLfloat materialSpecularLight[]={0.8,0.8,0.8,1.0};

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_SPECULAR, speculate);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecularLight);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 128.0);
}

/*
* Rotate rocket
* @param  void
* @return void
*/
void fly() {
    if(left)
        glRotatef(-30.0,0.0,0.0,1.0);

    if(right)
        glRotatef(30.0,0.0,0.0,1.0);
}


void asteroids() {
    int i;
    glPushMatrix();
    glTranslated(70,90,200);
    glRotated(0,1,0,0);
    glRotated(90,0,0,1);

    glBegin(GL_TRIANGLES);
    for (i=0; i<20; i++) {
        glVertex3fv(&vdata1[vindices[i][0]][0]);
        glVertex3fv(&vdata1[vindices[i][1]][0]);
        glVertex3fv(&vdata1[vindices[i][2]][0]);
    }
    glEnd();
    
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,90,350);
    glRotated(0,1,0,0);
    glRotated(90,0,0,1);
    
    glBegin(GL_TRIANGLES);
    for (i=0; i<20; i++) {
        glVertex3fv(&vdata1[vindices[i][0]][0]);
        glVertex3fv(&vdata1[vindices[i][1]][0]);
        glVertex3fv(&vdata1[vindices[i][2]][0]);
    }
    glEnd();
    
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,450);
    glRotated(0,1,0,0);
    glRotated(90,0,0,1);
    
    glBegin(GL_TRIANGLES);
    for (i=0; i<20; i++) {
        glVertex3fv(&vdata1[vindices[i][0]][0]);
        glVertex3fv(&vdata1[vindices[i][1]][0]);
        glVertex3fv(&vdata1[vindices[i][2]][0]);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

}

/*
* Draw the floor of moon
* @param  void
* @return void
*/
void moon() {
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(0.82,0.78,0.71);
    double i;
    glBegin(GL_LINES);
    for(i=-2500.0;i<=2500;i+=0.5) {
        glVertex3d(-2500,-11,i);
        glVertex3d(2500,-11,i);
        glVertex3d(i,-11,-2500);
        glVertex3d(i,-11,2500);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}


/*
* Define a Square to form the Sky Cube
* @param  int  a, int b, int c, int d
* @return void
*/
void square(int a,int b,int c,int d) {
    //Universe size
    const GLfloat vertex[8][3]={
         {-500.0,-50.0,-500.0}
        ,{500.0,-50.0,-500.0}
        ,{500.0,500.0,-500.0}
        ,{-500.0,500.0,-500.0}
        ,{-500.0,-50.0,500.0}
        ,{500.0,-50.0,500.0}
        ,{500.0,500.0,500.0}
        ,{-500.0,500.0,500.0}
    };

    //Sky color defined, different shades of dark blue
    const GLdouble colors[8][4]={
         {0.04,0.02,0.36}
        ,{0.01,0.12,0.29}
        ,{0.01,0.12,0.29}
        ,{0.02,0.13,0.29}
        ,{0.02,0.16,0.29}
        ,{0.04,0.19,0.42}
        ,{0.10,0.04,0.42}
        ,{0.16,0.04,0.42}
     };

    glPushMatrix();
    glDisable(GL_LIGHTING);

    glBegin(GL_POLYGON);
    glColor4dv(colors[a]);
    glVertex3fv(vertex[a]);
    glColor4dv(colors[b]);
    glVertex3fv(vertex[b]);
    glColor4dv(colors[c]);
    glVertex3fv(vertex[c]);
    glColor4dv(colors[d]);
    glVertex3fv(vertex[d]);
    glEnd();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

/*
* Draw Sky Cube
* @param  void
* @return void
*/
void sky() {
    glPushMatrix();
    square(0,3,2,1);
    square(2,3,7,6);
    square(0,4,7,3);
    square(1,2,6,5);
    square(4,5,6,7);
    glPopMatrix();
}


/*
* Build Rocket's body
* @param  void
* @return void
*/
void rocketBody() {
    
    GLUquadricObj* q;

    //Nose cone of rocket
    q = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0,0,40);
    gluCylinder(q, 5, 0.0, 15, 120, 30);

    //Propulsion system
    q = gluNewQuadric();
    glTranslatef(0,0,-40);
    gluCylinder(q, 5, 5, 40, 120, 30);
    glPopMatrix();
    
    //Fins: to direct the rocket
    const GLfloat fin1[][3]={
          {0.0,0.0,0.0}
         ,{0.0,20,-10}
         ,{0.0,0.0,20}
     };
    glBegin(GL_TRIANGLES);
    glVertex3fv(fin1[0]);
    glVertex3fv(fin1[1]);
    glVertex3fv(fin1[2]);    
    glEnd();

    const GLfloat fin2[][3]={
      {0.0,0.0,0.0}
     ,{20.0, 0.0,-10}
     ,{0.0,0.0,20}
     };
    glBegin(GL_TRIANGLES);
    glVertex3fv(fin2[2]);
    glVertex3fv(fin2[1]);
    glVertex3fv(fin2[0]);
    glEnd();

    const GLfloat fin3[][3]={
      {0.0,0.0,0.0}
     ,{-20.0, 0.0,-10}
     ,{0.0,0.0,20}
     };
    glBegin(GL_TRIANGLES);
    glVertex3fv(fin3[0]);
    glVertex3fv(fin3[1]);
    glVertex3fv(fin3[2]);
    glEnd();

    const GLfloat fin4[][3]={
      {0.0,0.0,0.0}
     ,{0.0, -20.0,-10}
     ,{0.0,0.0,20}
     };
    glBegin(GL_TRIANGLES);
    glVertex3fv(fin4[2]);
    glVertex3fv(fin4[1]);
    glVertex3fv(fin4[0]);
    glEnd();
    
    //Pilots place
    glTranslatef(0,3,35);
    glPushMatrix();

    glScalef(8,5,10);
    q=gluNewQuadric();
    gluSphere(q,0.5,12,12);
    glPopMatrix();
    glPopMatrix();

}

/*
* Rocket configurations and initialize lights
* @param  void
* @return void
*/
void rocket() {
    glPushMatrix();

    const GLfloat ambientLightRocket[]={0.2,0.2,0.2,1.0};
    const GLfloat diffusedLightRocket[]={0.50,1.00,0.58};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientLightRocket);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusedLightRocket);

    glTranslatef(axisX, axisY, axisZ);
    fly();
    glRotatef(rotation, 1.0, 0.0, 0);
    glRotatef(verticalRotation, 0.0, 0.0, 1.0);
    glScalef(scale,scale,scale);
    rocketBody();
    glPopMatrix();
}

/*
* Method to draw 2 langing places in moon floor
* @param  void
* @return void
*/
void landingPlace() {
    //Flight Place
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(0.12,0.30,0.46);
    glTranslatef(0.0,-9.0,-1.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glScalef(1.0,1.0,0.1);
    
    glBegin(GL_QUADS);
    glVertex3f(-50,-50,50);
    glVertex3f(-50,50,50);
    glVertex3f(50,50,50);
    glVertex3f(50,-50,50);
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //Langing Place
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(0.0,-9.0,500);
    glRotatef(-90.0,1.0,0.0,0.0);
    glScalef(1.0,1.0,0.1);
    glColor3f(0.7,0,0);

    glBegin(GL_QUADS);
    glVertex3f(-50,-50,50);
    glVertex3f(-50,50,50);
    glVertex3f(50,50,50);
    glVertex3f(50,-50,50);
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}


/*
* Display figures
* @param  void
* @return void
*/
void display (void) {

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eye[0],eye[1],eye[2],look[0],look[1],look[2],0.0,1.0,0.0);

    lighting(); //Configure the lighting
    
    moon();//Draw moon
    
    glTranslatef(axisX+2,axisY+2,axisZ+2);

    sky(); //Draw Sky Cube

    glTranslatef(-axisX+2,-axisY+2,-axisZ+2);

    rocket(); //Rocket configurations
    landingPlace(); //Draw the landing place
    asteroids(); //Draw asteroids

    glFlush();
    glutSwapBuffers();
}

/*
* Method to reshape
* @param  int w, int h
* @return void
*/
void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (100, (GLfloat)w / (GLfloat)h, 0.1, 1500.0);
    glMatrixMode (GL_MODELVIEW);
    glutPostRedisplay();
}

/*
* Get keyboad input and execute an action
* @param  chars
* @return void
*/
void keyboard (unsigned char key, int x, int y) {

    if (isFlying) {
        if(key=='s')
            rotation--;  
        if(key=='w') 
            rotation++;
        if(key=='d')
            verticalRotation++;
        if(key=='a')
            verticalRotation--;
        if(key=='+')
            scale += 0.2;
        if(key=='-')
            scale -= 0.2;
        
        glutPostRedisplay();
    }

}

/*
* Get special keys from keyboad and execute an action
* @param  int key, int x, int y
* @return void
*/
void specialKeys(int key,int x,int y) {

    if(isFlying) {
        if(key==GLUT_KEY_UP) {
            axisZ++; 
            eye[2]+=1.0;
            look[2]+=1.0;
            forward=1; 
        }
        if(key==GLUT_KEY_RIGHT) {
            axisX--; 
            eye[0]-=1.0;
            look[0]-=1.0;
            right=1;
        }
        if(key==GLUT_KEY_LEFT) {
            //Anda em direção ao axis X com o eye e o look acompanhando o foguete
            axisX++; 
            eye[0]+=1.0;
            look[0]+=1.0;
            left=1;
        }
        if(key==GLUT_KEY_DOWN) {
            if(axisY>0.0)
                axisY--;
            if(eye[1]>0)
                eye[1]-=1.0;
            look[1]-=1.0;
        }
        glutPostRedisplay();
    }
}

void idle() {

    if(goingUp) {
        if(rocketAngle<100)
            rocketAngle+=200.0;
        else if(rocketAngle<200)
            rocketAngle+=20.5;
        else if(rocketAngle<300)
            rocketAngle+=300.0;
        else if(rocketAngle<400)
            rocketAngle+=300.5;
        else
            rocketAngle+=500.0;

        if(rocketAngle>1000 && rocketAngle<100000) {
            if(axisY<100) {
                axisY += 1.0;
                look[1] += 1.0;
                if(rotation < -15)
                    rotation++;
                glutPostRedisplay();
            } else {
                goingUp = false;
                isInTheFloor = false;
                isFlying = true;
            }
        }

    } else if(goingDown) {
        //While dont touch the moon
        if(axisY>0.0) {
            //Go down
            axisY-=1.0;
            //tilt your head down
            look[1]-=1.0;
            if(eye[1]>0)
                eye[1] -= 2.0;
            if(rotation > -90)
                rotation -= 2;
            glutPostRedisplay();
        } else {
            isInTheFloor = true;
            goingDown = false;
            isFlying = false;
        }

    }
}


/*
* Free keyboard key
* @param  int key, int x, int y
* @return void
*/
void freeKey(int key,int x,int y) {
    if(key==GLUT_KEY_UP)
        forward = 0;
    if(key==GLUT_KEY_RIGHT)
        right = 0;
    if(key==GLUT_KEY_LEFT)
        left = 0;
    glutPostRedisplay();
}


/*
* Change perspective according to each sub menu option
* @param  int id
* @return void
*/
void subMenu(int id) {
    switch(id) {
        case 1:
            eye[0]=axisX;
            eye[1]=20+axisY;
            eye[2]=30.0+axisZ;
            look[0]=eye[0];
            look[1]=eye[1];
            look[2]=15.0+eye[2];
            break;
        case 2:
            eye[0]=axisX;
            eye[1]=100.0+axisY;
            eye[2]=-15.0+axisZ;
            look[0]=axisX;
            look[1]=axisY;
            look[2]=axisZ;
            break;
    }

    glutPostRedisplay();
}

/*
* Actions for menu
* @param  int id
* @return void
*/
void menu(int id) {
    switch(id) {
        case 1:
            goingUp = true;
            rocketAngle=0.0;
            eye[0]=40.0+axisX;
            eye[1]=0.0+axisY;
            eye[2]=0.0+axisZ;
            break;
        case 2:
            goingDown = true;
            break;
    }
    glutPostRedisplay();
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Kerbal Space Program from DeepWeb");
    init ();
    glutDisplayFunc (display);

    glutIdleFunc (idle);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(freeKey);
    glutReshapeFunc (reshape);

    GLint sub_menu[1];
    sub_menu[0] = glutCreateMenu(subMenu);
    glutAddMenuEntry("Jebediah", 1);
    glutAddMenuEntry("Sky", 2);

    glutCreateMenu(menu);
    glutAddMenuEntry("Start",1);
    glutAddSubMenu("Perspective",sub_menu[0]);
    glutAddMenuEntry("Landing",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop ();
}
