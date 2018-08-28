/* Isnaldo Francisco de Melo junior
 Apresentação de modelos tridimensionais através de CAVE
 Introdução, apresentação e produto parcial baseado no código de Nigel Stewart November 2003, tutorial sobre Aplicações em Dev C/C++ aplicando FreeGLUT.
 Assim como o tutoriais e apostilas disponíveis na internet em:
http://www.bdjogos.com (site acessado dias na semana 20-27 fevereiro)
http://www.ceset.unicamp.br/~magic/opengl/index2006.html (site acessado diversos dias incluindo 20-27 de fevereiro)
http://algol.dcc.ufla.br/~bruno/aulas/cg/monte-mor/55.htm
As funções básicas  que compoem o movimento são:
Transladar que ao ser aplicada a um objeto, reposiciona o mesmo mudando suas coordenadas (x,y,z) no espaço tridimensional. Simplesmente move.
Rotacionar um objeto significa girar o mesmo em torno de um eixo de acordo com determinado ângulo. Simplesmente gira.
  Eh possível alterar a velocidade de rotação da partícula através do comando
  + /-
*/
//Includes:
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
//Defines:
#define R 32
static int rot = 16; //Variável usada para controle em tempo real da velocidade de rotação
static float growth =1; //Variável usada para aproximar ou afastar o átomo

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
// Prototipos das funções que serão chamadas pela Glut ( Callback ):
static void display(void); //Função que mostra as coisas
static void resize(int,int); //Função chamada ao se redimensionar a tela
static void key(unsigned char, int, int); //Função de teclado
static void idle(void);//Função padrão                         
void Mouse(int button, int state, int x, int y);//função mouse
void DesenhaTexto(char *string,float x, float y) ;
// Main
int main(int argc, char *argv[])
{

    glutInit(&argc, argv); // Essa função serve para iniciar a biblioteca Glut.
    glutInitWindowSize(640,480); // Seta o tamanho inicial da janela e a
    glutInitWindowPosition(0,0); //  Posição em que ela será mostrada.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //Seta os parametros de inicialização do OpenGL,no nosso programa base estamos usando 3 parametros: GLUT_RGB Inicia a janela com modo RGB GLUT_DOUBLE Inicia a janela em modo double buffer da OpenGL GLUT_DEPTH Indica que nossa janela terá profundidade ( o eixo Z )
    glutCreateWindow("Teste Esferas");   //Cria uma janela top-level window. O nome que você dará para esta janela, será o nome utilizado pelo sistema operacional também.
    // Callbacks
    glutReshapeFunc(resize); //Ela avisa ao GLUT que quando o usuário redimensionar a janela do programa
    glutDisplayFunc(display); //Função que registra uma função que irá receber as interrupções de teclado.
    glutKeyboardFunc(key); //Função que uma função que irá receber as interrupções de teclado.
    glutMouseFunc(Mouse);  
    //glutCreateMenu(Menu); 
    glutIdleFunc(idle);          //Callback da função de teclado
    glClearColor(0,0,0,0);      //Ela vai dexar nossa tela preta O último parâmetro é o canal alfa, utilizado para tratar com transparências.
    glEnable(GL_CULL_FACE);//Esta função serve para habilitar várias funcionalidades da OpenGL
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient); //Light, responsável em definir as características de uma fonte de luz.
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient); //Define as propriedades do material do objeto
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glutMainLoop();//Essa função chama todos os Callbacks ( funções registradas ) para que o programa funcione perfeitamente.
    return EXIT_SUCCESS;
}
//GLUT callback
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
  
    glViewport(0, 0, width, height); //Essa função especifica as novas coordenadas de janela para a OpenGL.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0); //Frustum é o espaço "piramidal" que pode ser visto pela camera ( observador ) em um espaço em 3D.
  
    glMatrixMode(GL_MODELVIEW); //GL_MODELVIEW Aplica operações em matrizes que estão sequencialmente guardadas na pilha modelview matrix stack.
    glLoadIdentity() ;// Esta função troca a matrix atual ( em que estamos trabalhando. No caso do programa base, ainda não estamos trabalhando com nenhuma ) pela matrix identidade!
}
//Função que desenha texto:
void DesenhaTexto(char *string,float x, float y) 
{  
      glPushMatrix();
    glRasterPos3f(x,y,0);
    while (!string) 
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
     
     glPopMatrix();
        /*while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); */
}


// Função que é chamada quando for preciso mostrar ou atualizar a tela
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    const double b = t*180.0;
  
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o buffer
    glColor3d(1,0,0);
    DesenhaTexto("Apresentação de modelos quimicos",0,0); //Desenha recebe uma string,
    
    //Criação de esfera principal (Núcleo)
    glPushMatrix();
        getchar();
        glColor3d(0,1,0);
        glTranslated(0.0,0.0,-5);
        //glRotated(200,10,5,0);
        glRotated(a*rot,0,1,0); // Z sai da tela, X na horizontal, Y para cima
        glutWireSphere(growth*0.3,R,R*2);
    glPopMatrix();
  
    //Toróide:
    glPushMatrix(); //glPushMatrix armazena a matriz atual.
        glColor3d(0,0,1);  //Levemente Verde para se distinguir do fundo e do proton
        glTranslated(0,-0,-4);
        glRotated(10,10,50,0); //Inclinação que da o volume ao objeto
        glRotated(90,1,0,0);  //Rotação de 90 graus na horizontal,
        glutWireTorus(0.0000125,1.7,R*2,R); //void glutWireTorus(GLdouble innerRadius,GLdouble outerRadius,Glint nsides,Glint rings)
                                         // Raio interno, raio externo, numero de lados para cada seção, numero de subdivisões  ( ,Raio na horizontal,,);
    glPopMatrix(); //glPopMatrix retira da memória a matriz e da um replace na matriz atual.
    
    //Esfera secundária (Eletron)  
    glPushMatrix();  
        glColor3d(1,0,0);
        glTranslated(0.0,0.0,-5);
        glRotated(10,10,50,0); //Inclinação que da volume ao objeto
        glRotated((a*rot)/2,0,10,0);//O que faz ela girar
        glTranslated(0.0,0.0,-2);
        
        
        glutWireSphere(0.0125,R,R*2); // void glutWireSphere(GLdouble raio, GLint slices, GLint stacks);
        
    glPopMatrix();
    
    glutSwapBuffers();
}
// Função que é chamada quando uma tecla é apertada
static void key(unsigned char key, int x, int y) //Ao se usar outras teclas que não alfanuméricas, utilizar validação especial
{
    switch (key)
    {
        case 27: //Função de ESC para sair do programa
        case 'E':
            exit(0);
            break;
        case '+':
            rot++;
            break;
        case '-':
            if(rot>3)
               rot--;
            break;
        case 'G':
             growth*=1.05;
            break;
        case 'D':
             growth/=1.05;   
            break;
            
    }
    glutPostRedisplay();
}
//Função com mouse:
void Mouse(int button, int state, int x, int y)
{        
    if (state == GLUT_DOWN)
    {     
    growth++;
         //if(state == GLUT_DOWN) 
            DesenhaTexto("Botao pressionado",x,y);
    }
         
    glutPostRedisplay();
}
// Função que executa rotinas padrões da Glut: Idle
static void idle(void)
{ 
    glutPostRedisplay();
}
