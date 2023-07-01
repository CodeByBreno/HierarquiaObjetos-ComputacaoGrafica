// Dia 22/06/23 00:08
//
// Trabalho de Computação Gráfica
// Exemplo prático de Hierarquia de Objetos com Guincho móvel
//
// Por Breno Gabriel de Souza Coelho

#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720 
#define LARGURA_JANELA 1000
#define ALTURA_JANELA 700
#define CIRCLE_PRECISION 1000

#define SPEED 4.0f
#define ROT_PRINCIPAL 2.0f
#define RODA_CORDA 2.0f

int * gerarVetorAleatorio(){
	int * vetor = (int *) malloc(sizeof(int)*1000);
	srand(time(NULL));
	for (int i = 0; i < 1000; i++){
		vetor[i] = rand() % 3; 
	}
	return vetor;
}

int * randomList = gerarVetorAleatorio();

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
    int precision = CIRCLE_PRECISION, x;
	float a = (float) 360/precision; //Taxa de variacao do angulo
	glBegin(GL_LINES);
		for(x = 0; x < precision; x++){
			glVertex2f(r*cos(a*x) + x0, r*sin(a*x) + y0);
		}
		glVertex2f(r*cos(a*x) + x0, r*sin(a*x) + y0);
	glEnd();
}

void DesenhaGuincho(float altura_fio){
	glColor3f(0.8f, 0.8f, 0.8f);
	glLineWidth(4.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -altura_fio);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(0.5f, 0.8f, 0.95f);
	DrawRectangle(-10.0f, -altura_fio, 20.0f, 20.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-10.0f, -altura_fio, 20.0f, 20.0f);
}

void DesenhaBracoSecundario(){
	glColor3f(0.8f, 0.42f, 0.31f);

	//Desenhando o braco
	DrawRectangle(-2.0, 2.0, 100.0, 4.0);

	//Desenhando o contorno
	glLineWidth(2.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-2.0, 2.0, 100.0, 4.0);

	//Centro de Rotacao
	glColor3f(0.55f, 0.25f, 0.16f);
	DrawCircle(5.0f, 0.0f, 0.0f); //Parte externa
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(2.0f, 0.0f, 0.0f); //Parte central
}

void DesenhaBracoPrincipal(){
	glColor3f(0.8f, 0.42f, 0.31f);

	//Centro de Rotacao
	glPointSize(4.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
	glEnd();

	//Desenhando o braco
	glBegin(GL_POLYGON);
		glVertex2f(-4.0f, 0.0f);	
		glVertex2f(4.0f, 0.0f);
		glVertex2f(2.0f, 80.0f);
		glVertex2f(-2.0f, 80.0f);
	glEnd();

	//Desenhando o contorno
	glLineWidth(2.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-4.0f, 0.0f);	
		glVertex2f(4.0f, 0.0f);
		glVertex2f(2.0f, 80.0f);
		glVertex2f(-2.0f, 80.0f);
	glEnd();
}

void DesenhaBracos(float angle1, float angle2, float altura_fio){
	glPushMatrix();
		//Primeiro Braco
		glTranslatef(-20.0, -5.0f, 0.0f);   //Centralizando o sistema de coordenadas no eixo de rotacao
		glRotatef(angle1, 0.0f, 0.0f, 1.0f);
		DesenhaBracoPrincipal();
	
		//Segundo Braco
		glTranslatef(0.0f, 78.0f, 0.0f);   //Centralizando o sistema de coordenadas no eixo de rotacao
		glRotatef(angle2, 0.0f, 0.0f, 1.0f);
		DesenhaBracoSecundario();

		//Guincho
		glTranslatef(98.0f, 0.0f, 0.0f);
		glRotatef(-angle2, 0.0f, 0.0f, 1.0f);
		glRotatef(-angle1, 0.0f, 0.0f, 1.0f);
		DesenhaGuincho(altura_fio);
	glPopMatrix();
}

void DesenhaCarro(float whell_angle){
	static int roda_roda = 0.0f;
	glLineWidth(2.0);

	//Rotor para o brao principal
	glColor3f(0.8f, 0.55f, 0.55f);
	DrawCircle(10.0f, -20.0f, -5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawCircleBorder(10.0f, -20.0f, -5.0f);

	//Escavadeira
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawRectangle(-40.0, 0.0f, 80.0f, 20.0f);   //Corpo
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-40.0, 0.0f, 80.0f, 20.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	DrawRectangle(0.0f, 12.0f, 35.0f, 15.0f);   //Cabine 
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

void DesenhaPredios(){

	glPushMatrix();
		glTranslatef(-500.0f, 22.0f, 0.0f);
		glScalef(2.6f,2.6f, 0.0f);
		DesenhaPredio1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-400.0f, 30.0f, 0.0f);
		glScalef(3.0f,3.0f, 0.0f);
		DesenhaPredio1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-250.0, 20.0f, 0.0f);
		glScalef(2.5f, 2.5f, 0.0f);
		DesenhaPredio1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-80.0, 22.0f, 0.0f);
		glScalef(2.8f, 2.8f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(100.0, 14.0f, 0.0f);
		glScalef(2.2f, 2.2f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(240.0, 34.0f, 0.0f);
		glScalef(3.2f, 3.2f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(360.0, 14.0f, 0.0f);
		glScalef(2.2f, 2.2f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(440.0, 40.0f, 0.0f);
		glScalef(3.6f, 3.6f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(620.0, 22.0f, 0.0f);
		glScalef(2.8f, 2.8f, 0.0f);
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(840.0, 22.0f, 0.0f);
		glScalef(2.8f, 2.8f, 0.0f);
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(1040.0, 2.0f, 0.0f);
		glScalef(1.6f, 1.6f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1120.0, 6.0f, 0.0f);
		glScalef(1.8f, 1.8f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(950.0, 40.0f, 0.0f);
		glScalef(3.6f, 3.6f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(1200.0, -6.0f, 0.0f);
		glScalef(1.2f, 1.2f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();	

	glPushMatrix();
		glTranslatef(1260.0, -5.0f, 0.0f);
		glScalef(1.4f, 1.4f, 0.0f);	
		DesenhaPredio1();
	glPopMatrix();		
	
}

void DesenhaGrama(){
	int numero, c = 0;
	for (int i = 0; i < 200; i++){
		for(int j = 0; j < 20; j++){
			c++;
			if (c > 999){
				c = 0;
			}
			numero = randomList[c];

			switch(numero){
				case 0:
					glColor3f(0.56f, 0.9f, 0.42f);  
					break;
				case 1:
					glColor3f(0.22f, 0.73f, 0.36f);    
					break;
				case 2:
					glColor3f(0.0f, 0.50f, 0.13f);   
					break;
			}
			DrawRectangle(-800.0 + i*15, -30.0 - j*10, 15.0, 10.0);
		}
	}
}

void DesenhaBackground(){
	DesenhaPredios();
	DesenhaGrama();

	//Pista
	glColor3f(0.33f, 0.33f, 0.33f);
	DrawRectangle(-800.0, -30.0, 3000.0, 20.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawRectangleBorder(-800.0, -30.0, 3000.0, 20.0);
}

float calc_whell_rotation(float movX){
	//Calcula o tanto que a roda precisa girar de acordo com o quanto que a tela
	//se moveu
	float aux = 18*movX/3.14;
	while (aux > 360){
		aux -= 360;
	}
	return aux;
}

void DesenhaNucleo(float movX, float angle1, float angle2, float altura_fio){
	glClear(GL_COLOR_BUFFER_BIT);

	float w_rotation = calc_whell_rotation(movX);

	glPushMatrix();
		glTranslatef(-movX, 0.0f, 0.0f);
		printf("Deslocamento sofrido pelo background: %f\n", -1*movX);
		DesenhaBackground();
	glPopMatrix();

	glPushMatrix();
		printf("Deslocamento do carrinho: %f\n\n", movX);
		DesenhaBracos(angle1, angle2, altura_fio);
		DesenhaCarro(w_rotation);
	glPopMatrix();

	glFlush();
}

void Desenha(){
	glPushMatrix();
		glTranslatef(0.0f, -30.0f, 0.0f);
		DesenhaNucleo(0.0f, 0.0f, 0.0f, 50.0f);
	glPopMatrix();
}

void Teclado(unsigned char key, int x, int y)
{
	static float movX = 0.0f, angleBracoPrincipal = 0.0f, angleBracoSecundario = 0.0f, altura_fio = 50.0f;

	glClear(GL_COLOR_BUFFER_BIT);

	//Move o carro/tela
	if ((key == 97) && (movX >= -400)){
		movX -= SPEED;
	}
	if ((key == 100) && (movX <= 1200)){
		movX += SPEED;
	}

	//Move o Braço principal
	if ((key == 113) && (angleBracoPrincipal < 44.0)){
		angleBracoPrincipal += ROT_PRINCIPAL;
	}
	if ((key == 101) && (angleBracoPrincipal > -32)){
		angleBracoPrincipal -= ROT_PRINCIPAL;
	}

	//Move o Braço Secundário
	if ((key == 114) && angleBracoSecundario <= 180){
		angleBracoSecundario += ROT_PRINCIPAL;
	}
	if ((key == 102) && angleBracoSecundario > 0){
		angleBracoSecundario -= ROT_PRINCIPAL;
	}	

	//Regula a altura do fio
	if ((key == 116) && altura_fio > 0){
		altura_fio -= RODA_CORDA;
	}
	if((key == 103) && altura_fio < 100){
		altura_fio += RODA_CORDA;
	}

	//Dados sobre a execucao
	if (key == 108){
		printf("Valor da rotacao Principal: %f\n", angleBracoPrincipal);
		printf("Valor da rotacao Secundaria: %f\n", angleBracoSecundario);
		printf("Posicao (deslocamento): %f\n", movX);
	}

	DesenhaNucleo(movX, angleBracoPrincipal, angleBracoSecundario, altura_fio);
	glFlush();
}

void ConstroiTela(void){
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);        
    glutInitWindowPosition(LARGURA_TELA/2 - LARGURA_JANELA/2,
						   ALTURA_TELA/2 - ALTURA_JANELA/2);
    glutCreateWindow("Foguete");  
}

void Inicializar(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluOrtho2D(-216.0, 216.0, -150.0, 150.0); 
	glClearColor(0.0f, 0.75f, 1.0f, 1.0f); 
}

int main() {
	//Inicializando o glut e setando apenas um buffer de cor com cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	ConstroiTela();
	Inicializar();

    glutDisplayFunc(Desenha);    //Estabelecendo a funcao basica para desenho da tela 

	glutKeyboardFunc(Teclado);
    glutMainLoop();
    return 0;
}
