                                            ///___________SET-2___________///

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1416


///Global Variable
float boundary = 50; /// Scene boundary
float border = 40;   /// Game boundary
int score = 0;

///Agent Parameters
float RAgent = 6.0;
float CAgentX = -15, CAgentY = 0;
bool isAgentDestroyed = false;
float agentSpeed = 0.5;

///Agent2 Parameters
float RAgent2 = 6.0;
float CAgent2X = 15, CAgent2Y = 0;
bool isAgent2Destroyed = false;
float agent2Speed = 0.5;

///Enemy Parameters
float REnemy = 4.0;
float CEnemyX = -border, CEnemyY = 0.0;
int E1state = 1;
float enemySpeed = 0.01;

///Enemy2 Parameters
float REnemy2 = 4.0;
float CEnemy2X = border, CEnemy2Y = 0.0;
int E2state = 1;
float enemy2Speed = 0.0015;

void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
		}

	glEnd();

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-border, border);
        glVertex2f(border, border);
        glVertex2f(border, -border);
        glVertex2f(-border, -border);
        glVertex2f(-border, border);
    glEnd();

	if(!isAgentDestroyed)
    {
        glPushMatrix();             ///Green Circle
        glTranslatef(CAgentX, CAgentY,0);
        glColor3f(0.0, 1.0, 0.0);
        circle(RAgent,RAgent);
        glPopMatrix();
    }

    if(!isAgent2Destroyed)
    {
        glPushMatrix();             ///Blue Circle
        glTranslatef(CAgent2X, CAgent2Y,0);
        glColor3f(0.0, 0.0, 1.0);
        circle(RAgent2,RAgent2);
        glPopMatrix();
    }

    glPushMatrix();                 ///Red circle (Static)
	glTranslatef(CEnemyX, CEnemyY,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy,REnemy);
	glPopMatrix();

	glPushMatrix();                 ///Red circle (Static)
	glTranslatef(CEnemy2X, CEnemy2Y,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy2,REnemy2);
	glPopMatrix();

	glFlush();

	/*if(isAgentDestroyed && isAgent2Destroyed)
    {
        //glutIdleFunc(NULL);
        printf("SCORE : %d", score);
        exit(0);
    }
    else
    {
        score++;
    }*/
}

void animate()
{

    ///_______________________________________________Enemy1 Movement______________________________________________________
    if(E1state == 1)
    {
        CEnemyX += enemySpeed;
        CEnemyY -= enemySpeed;

        if(CEnemyX>0 && CEnemyY<-border)
        {
            E1state = 2;
        }
    }
    else if(E1state == 2)
    {
        CEnemyY += enemySpeed;

        if(CEnemyY>border)
        {
            E1state = 3;
        }
    }
    else if(E1state == 3)
    {
        CEnemyX += enemySpeed;
        CEnemyY -= 2*enemySpeed;

        if(CEnemyX>border && CEnemyY<-border)
        {
            E1state = 4;
        }
    }
    else if(E1state == 4){
        CEnemyX -= enemySpeed;
        CEnemyY += 0.5*enemySpeed;

        if(CEnemyX<-border && CEnemyY>0)
        {
            E1state = 1;
        }
    }

    ///_________________________________________Enemy2 Movement_________________________________________________________
    if(E2state == 1)
    {
        CEnemy2X -= enemy2Speed;
        CEnemy2Y += enemy2Speed;

        if(-CEnemy2X>0 && CEnemy2Y>border)
        {
            E2state = 2;
        }
    }
    else if(E2state == 2)
    {
        CEnemy2X -= enemy2Speed;
        CEnemy2Y -= 2*enemy2Speed;

        if(-CEnemy2Y>border && -CEnemy2X>-border)
        {
            E2state = 3;
        }
    }
    else if(E2state == 3)
    {
        CEnemy2X += enemy2Speed;
        CEnemy2Y += enemy2Speed;

        if(CEnemy2X>=0 && CEnemy2Y>=0)
        {
            E2state = 4;
        }
    }
    else if(E2state == 4){
        CEnemy2X += enemy2Speed;
        CEnemy2Y == enemy2Speed;

        if(CEnemy2X>border && CEnemy2Y>0)
        {
            E2state = 1;
        }
    }

    ///Attack Logic
    float distance = sqrt((CAgentX-CEnemyX)*(CAgentX-CEnemyX) + (CAgentY-CEnemyY)*(CAgentY-CEnemyY));   ///Agent1 & Enemy1
    float distance2 = sqrt((CAgentX-CEnemy2X)*(CAgentX-CEnemy2X) + (CAgentY-CEnemy2Y)*(CAgentY-CEnemy2Y));   ///Agent1 & Enemy2
    float distance3 = sqrt((CAgent2X-CEnemyX)*(CAgent2X-CEnemyX) + (CAgent2Y-CEnemyY)*(CAgent2Y-CEnemyY));   ///Agent2 & Enemy1
    float distance4 = sqrt((CAgent2X-CEnemy2X)*(CAgent2X-CEnemy2X) + (CAgent2Y-CEnemy2Y)*(CAgent2Y-CEnemy2Y));   ///Agent2 & Enemy2
    if(distance <= RAgent+REnemy)
    {
        isAgentDestroyed = true;
    }
    if(distance2 <= RAgent+REnemy2)
    {
        isAgentDestroyed = true;
    }
    if(distance3 <= RAgent2+REnemy)
    {
        isAgent2Destroyed = true;
    }
    if(distance4 <= RAgent2+REnemy2)
    {
        isAgent2Destroyed = true;
    }

    glutPostRedisplay();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-boundary, boundary, -boundary, boundary, -boundary, boundary);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
                CAgentX -= agentSpeed;

                if(CAgentX<0 && -CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
                CAgentX += agentSpeed;

                if(CAgentX>0 && CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
                CAgentY -= agentSpeed;
                if(CAgentY<0 && -CAgentY>border - RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
                CAgentY += agentSpeed;
                if(CAgentY>0 && CAgentY>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

void keyboard_action(unsigned char key, int x, int y)
{
    if(key == 'u')
    {
        CAgent2Y += agent2Speed;
        if(CAgent2Y>0 && CAgent2Y>border-RAgent2)
        {
            isAgent2Destroyed = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'd')
    {
        CAgent2Y -= agent2Speed;
        if(CAgent2Y<0 && -CAgent2Y>border-RAgent2)
        {
            isAgent2Destroyed = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'l')
    {
        CAgent2X -= agent2Speed;
        if(CAgent2X<0 && -CAgent2X>border-RAgent2)
        {
            isAgent2Destroyed = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'r')
    {
        CAgent2X += agent2Speed;
        if(CAgent2X>0 && CAgent2X>border-RAgent2)
        {
            isAgent2Destroyed = true;
        }
        glutPostRedisplay();
    }
}

int main()
{
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Circle");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(keyboard_action);
	glutMainLoop();
	return 0;
}


