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


void Inicializar(void){
	//Setando a cor de limpeza do buffer de cores
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Setando a janela de trabalho
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0); //Mapeamento das dimensões da janela
}

void DesenhaPredio1(){

	//Corpo do prédio
	glLineWidth(4.0f);
	glColor3f(0.41f, 0.41f, 0.41f);
	DrawRectangle(-20.0, 40.0, 40.0, 60.0);

	//Portão
	glColor3f(0.66f, 0.66f, 0.66f);
	DrawRectangle(-10.0, -8.0, 20.0, 12.0);

	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-10.0, -8.0, 20.0, 12.0);

	for (int i = 4; i < 12; i+=4){
		DrawRectangle(-10.0, -8.0 - i, 20.0, 1.0);
	}

	//Borda Externa do Prédio
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-20.0, 40.0, 40.0, 60.0);

	//Detalhe Retangulo Superior
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawRectangle(-22.0, 42.0, 44.0, 5.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-22.0, 42.0, 44.0, 5.0);

	//Detalhe retangulo inferior
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawRectangle(-22.0, 3.0, 44.0, 5.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(4.0f);
	DrawRectangleBorder(-22.0, 3.0, 44.0, 5.0);

	//Tecido
	glColor3f(0.62f, 0.17f, 0.17f); 
	DrawRectangle(-15.0, -4.0, 30.0, 2.0);
	glColor3f(0.81f, 0.47f, 0.47f);
	DrawRectangle(-15.0, -6.0, 30.0, 2.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-15.0, -4.0, 30.0, 4.0);

	//Janelas
	for (int j = 0; j < 3; j++){
		for (int i = 0; i < 5; i++){
			glColor3f(1.0f, 1.0f, 1.0f);
			DrawRectangle(-18 + 8*i, 34 - 10*j, 4, 8);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawRectangleBorder(-18 + 8*i, 34 - 10*j, 4, 8);
		}
	}
}

void Desenha(void){
	//Limpando o buffer com a cor definida por glClearColor
	glClear(GL_COLOR_BUFFER_BIT);
	DesenhaPredio1();
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
