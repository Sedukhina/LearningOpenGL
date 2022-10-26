#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderProgram.cpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Learn OpenGL", nullptr, nullptr);		//Creating window
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);	//Getting  window width and height 

	glViewport(0, 0, width, height);

	GLfloat hexVertices[] = {	//Coordinates for triangle vertices
		 0.7f,  0.00f, 0.0f,
		-0.7f,  0.00f, 0.0f,
		-0.4f,  0.55f, 0.0f,
		-0.4f, -0.55f, 0.0f,
		 0.4f,  0.55f, 0.0f,
		 0.4f, -0.55f, 0.0f
	};

	GLfloat vertices[] = {
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	GLuint hexIndices[] = {  //Order for vertices
		1, 2, 3,
		3, 4, 2,
		3, 4, 5,
		0, 4, 5
	};

	GLuint indices[] = {  //Order for vertices
		1, 2, 3,
		0, 1, 2
	};

	//Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);		//Binding VAO

	//Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);	//Generating buffer object name
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//Binding buffer object name with a specific binding point
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//Allocating memory where data will be stored

	//Element(Index) Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	//Setting up how to interpritate data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);	//Unbinding VAO

	ShaderProgram shaderProgram = ShaderProgram("Shaders/Shader.vert", "Shaders/Shader.frag");
	shaderProgram.Use();

	glfwSetKeyCallback(window, key_callback);	//Setting function responsible for actions when any key pressed or released

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Enabling wireframe drawing mode

	while (!glfwWindowShouldClose(window))	//Window is opened while it`s not closed
	{
		glfwPollEvents();

		glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);		//Clearing color buffer

		/*GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");*/
		shaderProgram.Use();
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);		//Swapping buffers
	}

	glfwTerminate();
	return 0;
}


//Function responsible for actions when any key pressed or released
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)		//Closing window on ESC 
		glfwSetWindowShouldClose(window, GL_TRUE);
}
