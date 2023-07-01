#include <stdio.h>
#include <math.h>
#include <gl/glut.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720 
#define LARGURA_JANELA 600
#define ALTURA_JANELA 600
#define CIRCLE_PRECISION 1000

void DrawRectangleBorder(float x0, float  y0, float width, float height){
	glBegin(GL_LINE_LOOP);
		glVertex2f(x0, y0);
		glVertex2f(x0 + width, y0);
		glVertex2f(x0 + width, y0 - height);
		glVertex2f(x0, y0 - height);
	glEnd();
}

void DrawRectangle(float x0, float  y0, float width, float height){
	glBegin(GL_QUADS);
		glVertex2f(x0, y0);
		glVertex2f(x0 + width, y0);
		glVertex2f(x0 + width, y0 - height);
		glVertex2f(x0, y0 - height);
	glEnd();
}

void DrawCircle(float r, float x0, float y0){
    int precision = CIRCLE_PRECISION;
	float a = (float) 360/precision; //Taxa de variacao do angulo
	glBegin(GL_POLYGON);
		for(int x = 0; x < precision; x++){
			glVertex2f(r*cos(a*x) + x0, r*sin(a*x) + y0);
		}
	glEnd();
}

void DrawCircleBorder(float r, float x0, float y0){
    int precision = CIRCLE_PRECISION;
	float a = (float) 360/precision; //Taxa de variacao do angulo
	glBegin(GL_LINES);
		for(int x = 0; x < precision; x++){
			glVertex2f(r*cos(a*x) + x0, r*sin(a*x) + y0);
			if (x != 0){
				glVertex2f(r*cos(a*(x-1)) + x0, r*sin(a*(x-1)) + y0);
			}
		}
	glEnd();
}

void Inicializar(void){
	//Setando a cor de limpeza do buffer de cores
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

	//Setando a janela de trabalho
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0); //Mapeamento das dimensões da janela
}

void DesenhaCarro(float whell_angle){
	static int roda_roda = 0.0f;
	glLineWidth(10.0);

	//Rotor para o braco principal
	glColor3f(0.8f, 0.55f, 0.55f);
	DrawCircle(10.0f, -20.0f, -5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawCircleBorder(10.0f, -20.0f, -5.0f);

	//Escavadeira
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawRectangle(-40.0, 0.0f, 80.0f, 20.0f);   
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-40.0, 0.0f, 80.0f, 20.0f);

	//Cabine 
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawRectangle(0.0f, 12.0f, 35.0f, 15.0f);   
	DrawRectangle(0.0f, 20.0f, 25.0f, 15.0f); 
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(25.0f, 12.0f);
		glVertex2f(35.0f, 12.0f);
		glVertex2f(0.0f, 20.0f);
		glVertex2f(25.0f, 20.0f);
		glVertex2f(0.0f, 20.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(25.0f, 20.0f);
		glVertex2f(25.0f, 12.0f);
		glVertex2f(35.0f, 12.0f);
		glVertex2f(35.0f, 0.0f);
	glEnd();	

	//Vidros da cabine
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawRectangle(2.0f, 18.0f, 20.0f, 18.0f);    
	DrawRectangle(25.0f, 10.0f, 8.0f, 10.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(2.0f, 18.0f, 20.0f, 18.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(25.0f, 10.0f, 8.0f, 10.0f);

	//Para Choque do carro
	glColor3f(0.5f, 0.5f, 0.5f);	
	DrawRectangle(35.0f, -2.0f, 8.0f, 12.0f);    
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(35.0f, -2.0f, 8.0f, 12.0f); 
	DrawRectangleBorder(35.0f, -6.0f, 8.0f, 0.5f);
	DrawRectangleBorder(35.0f, -10.0f, 8.0f, 0.5f);  

	//Segundo Farol traseiro
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawRectangle(-40.0f, -2.0f, 6.0f, 4.0f);   
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-40.0f, -2.0f, 6.0f, 4.0f);

	//Farol Vermelho traseiro
	glColor3f(0.8f, 0.8f, 0.8f);
	DrawRectangle(-40.0f, -6.0f, 6.0f, 4.0f);   
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-40.0f, -6.0f, 6.0f, 4.0f);

	//lataria inferior
	glColor3f(0.6f, 0.6f, 0.6f);
	DrawRectangle(-42.0f, -18.0f, 84.0f, 4.0f);	
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-42.0f, -18.0f, 84.0f, 4.0f);

	//Rodas
	glPushMatrix();
		glPushMatrix();
			glTranslatef(-25.0f, -20.0f, 0.0f); //Centralizo o sistema na roda
			glRotatef(80.0f - whell_angle, 0.0f, 0.0f, 1.0f); //Roda a roda!
			//Parte de fora do pneu
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawCircle(10.0, 0.0, 0.0);     
 			//Parte de Dentro
			glColor3f(0.8f, 0.8f, 0.8f);
			DrawCircle(5.0, 0.0, 0.0);    
			//Desenhando uma marquinha na roda para dar a sensacao de que ela vai girar
			glLineWidth(10.0f);
			glColor3f(0.9f, 0.9f, 0.9f);
			DrawRectangle(7.0, 0.0f, 2.5f, 1.0f);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(25.0f, -20.0f, 0.0f); //Centralizo o sistema na segunda roda
			glRotatef(-whell_angle, 0.0f, 0.0f, 1.0f);  //Roda a roda!
			//Parte de fora do pneu
			glColor3f(0.0f, 0.0f, 0.0f);       
			DrawCircle(10.0, 0.0, 0.0);
			//Parte de dentro
			glColor3f(0.8f, 0.8f, 0.8f);
			DrawCircle(5.0, 0.0, 0.0);
			//Desenhando uma marquinha na roda para dar a sensacao de que ela vai girar
			glLineWidth(10.0f);
			glColor3f(0.9f, 0.9f, 0.9f);
			DrawRectangle(7.0f, 0.0f, 2.5f, 1.0f);
		glPopMatrix();
	glPopMatrix;
}


void Desenha(void){
	//Limpando o buffer com a cor definida por glClearColor
	glClear(GL_COLOR_BUFFER_BIT);
	DesenhaCarro(0.0f);
	glFlush();
}

int main(){
	//Setando o modo do OpenGL com apenas um buffer de cores e cor em RGB
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );

	//Criando uma janela no SO
	glutInitWindowPosition((int)(LARGURA_TELA/2 - LARGURA_JANELA/2), (int)(ALTURA_TELA/2 - ALTURA_JANELA/2));
	glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
	glutCreateWindow("Primitivas Gráficas");

	//Setando a função padrão de desenho
	glutDisplayFunc(Desenha);
	
	Inicializar();
	//Loop de callback e captura de eventos
	glutMainLoop();
}
