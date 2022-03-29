#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glut.h>

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

struct TriangleState{
  GLdouble tx, ty;
  GLdouble angle, scale;
  TriangleState() : tx(0), ty(0), angle(0), scale(1) {}
};

std::vector<TriangleState> triangles;
GLint currentTriangle = -1;

void handleDisplayFunc() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (GLint i = 0; i < (GLint)triangles.size(); ++i) {
    auto& st = triangles[i];
    glPushMatrix();
    glScaled(st.scale, st.scale, 1.0);
    glTranslated(st.tx, st.ty, 0);
    glRotated(st.angle, 0.0, 0.0, 1.0);
    if (i == currentTriangle) {
      glColor3f(0.0, 1.0, 0.0);
    } else {
      glColor3f(1.0, 0.0, 0.0);
    }
    glBegin(GL_TRIANGLES);
      glVertex2f(-0.5, -0.5);
      glVertex2f(0.5, -0.5);
      glVertex2f(0.0, 0.5);
    glEnd();
    glPopMatrix();
  }

  glutSwapBuffers();
}


void handleKeyboardFunc(GLubyte key, GLint x, GLint y) {
  // select triangle
  if (key == '\t' && triangles.size() > 0) {
    currentTriangle = (currentTriangle + 1) % triangles.size();
  }
  // create new triangle
  if (key == '+') {
    triangles.push_back(TriangleState());
    triangles.back().tx = -0.5;
    triangles.back().ty = 0.5;
  }
  // delete triangle
  if (key == '-' && !triangles.empty()) {
    triangles.erase(triangles.begin() + currentTriangle);
  }
  // translate object
  auto& st = triangles[currentTriangle];
  if (key == 'w') {
    st.ty += 0.03;
  } else if (key == 's') {
    st.ty += -0.03;
  } else if (key == 'd') {
    st.tx += 0.03;
  } else if (key == 'a') {
    st.tx += -0.03;
  }
  // rotate object
  if (key == 'r') {
    st.angle += 1;
  } else if (key == 't') {
    st.angle += -1;
  }
  // scale object
  if (key == 'i') {
    st.scale += 0.03;
  } else if (key == 'u') {
    st.scale += -0.03;
  }
  glutPostRedisplay();
}

void init() {
  triangles.push_back(TriangleState());
  currentTriangle = 0;
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("Janela");

  init();

  glutDisplayFunc(handleDisplayFunc);
  glutKeyboardFunc(handleKeyboardFunc);
  glutMainLoop();
  
  return EXIT_SUCCESS;
}



