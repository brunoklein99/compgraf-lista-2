/* Hello Triangle - c�digo fornecido em https://learnopengl.com/#!Getting-started/Hello-Triangle
*
* Adaptado por Rossana Baptista Queiroz
* para a disciplina de Computa��o Gr�fica - Jogos Digitais - Unisinos
* Vers�o inicial: 7/4/2017
* �ltima atualiza��o em 08/08/2017
*
*/

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

#include <GL/glew.h>
#include "Shader.h"

// GLEW
//#define GLEW_STATIC -- se habilitar, n�o precisa da dll

// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	/* get version info */
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader ourShader(
		"I:\\Source\\compgrafica\\Lista2\\HelloTriangle - 3 Triangles\\Debug\\3.3.shader.vs",
		"I:\\Source\\compgrafica\\Lista2\\HelloTriangle - 3 Triangles\\Debug\\3.3.shader.fs"); // you can name your shader files however you like

	float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f, // left 
		0.0f, -0.5f, 0.0f, // right
		-0.45f, 0.5f, 0.0f, // top 
		
		// second triangle
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f,  // top 
		
		// third triangle
		-0.45f, 0.5f, 0.0f, // left 
		0.45f, 0.5f, 0.0f,  // right 
		0.0f, -0.5f, 0.0f,  // top
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// create transformations
		glm::mat4 rotation;
		rotation = glm::translate(rotation, glm::vec3(0.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// draw our first triangle

		//glUseProgram(shaderProgram);
		ourShader.use();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(rotation));
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 9); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
										  // glBindVertexArray(0); // no need to unbind it every time 

										  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
										  // -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

