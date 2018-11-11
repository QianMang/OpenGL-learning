#include "MyWindow.h"



MyWindow::MyWindow()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
	mouseFirstMoved = true;
	xChange = 0.0f;
	yChange = 0.0f;
}

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
	mouseFirstMoved = true;
	xChange = 0.0f;
	yChange = 0.0f;
}

int MyWindow::Initialise()
{
	//initialize glfw
	if (!glfwInit()) {
		std::cout << "glfw init failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	//setup glfw windows properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "test", NULL, NULL);
	if (!mainWindow) {
		std::cout << "window failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	//get buffer size information
	
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//handle key + mouse input
	createCallbacks();
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//allow modern extension features
	glewExperimental = GL_TRUE;


	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// 3D depth
	glEnable(GL_DEPTH_TEST);

	//setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	//
	glfwSetWindowUserPointer(mainWindow, this);
}


GLfloat MyWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat MyWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

MyWindow::~MyWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}

void MyWindow::createCallbacks()                         //
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void MyWindow::handleKeys(GLFWwindow * window, int key, int code, int action,int mode)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			//std::cout << "Pressed " <<key<< std::endl;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			//std::cout << "Released " << key << std::endl;
		}
	}
}

void MyWindow::handleMouse(GLFWwindow * window, double xPos, double yPos)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));//
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//std::cout << "x:" <<  theWindow->xChange  << ", y:" <<  theWindow->yChange  << std::endl;
}

