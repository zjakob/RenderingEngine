#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>

#include <memory>

#include ".\util\ioHelper\ioHelper.h"
#include ".\util\ShaderHelper\glslHelper.h"
#include ".\util\Math\MathUtil.h"

//#include <EventSystem\EventSystem.h>
#include <EventSystem\EventManager.h>
#include <EventSystem\Dispatcher\QueuedEventDispatchStrategy.h>
#include <EventSystem\Listener\Strategy\SafeEventCallbackStrategy.h>
#include <EventSystem\Event\KeyDownEvent.h>

#include <util\keyboardHelper.h>

#include "camera\Camera.h"
#include "camera\Camera.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

EventManager<
	KeyDownEvent,
	SafeEventCallbackStrategy<KeyDownEvent>,
	QueuedEventDispatchStrategy<KeyDownEvent, SafeEventCallbackStrategy<KeyDownEvent> > > keyDownManager;

glm::mat4 model = glm::mat4(1.0f);
Camera cam(glm::vec3(0.0f, 0.0f, 1.0f));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keyboardHelper::KeyboardKey pressedKey;
		switch (key)
		{
		case GLFW_KEY_A:
			pressedKey = keyboardHelper::KeyboardKey::a;
			break;
		case GLFW_KEY_S:
			pressedKey = keyboardHelper::KeyboardKey::s;
			break;
		case GLFW_KEY_D:
			pressedKey = keyboardHelper::KeyboardKey::d;
			break;
		case GLFW_KEY_W:
			pressedKey = keyboardHelper::KeyboardKey::w;
			break;
		default:
			break;
		}

		keyDownManager.dispatchEvent(std::make_unique<KeyDownEvent>(pressedKey));
	}
}

int main(void)
{
	keyDownManager.addEventCallback<KeyDownEvent>(std::bind(&Camera::handleKeyDownEvent, &cam, std::placeholders::_1));

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);


	// init glew
	if (glewInit())
		return -1;

	/* Prepare opengl resources for rendering */
	char* vsSource;
	GLint vsLen;
	ioHelper::loadFromFile(".\\src\\shaders\\movingtri.vs", &vsSource, vsLen);
	char* fsSource;
	GLint fsLen;
	ioHelper::loadFromFile(".\\src\\shaders\\movingtri.fs", &fsSource, fsLen);

	GLuint shader_program = glslHelper::makeShaderProgram(vsSource, vsLen, fsSource, fsLen);
	
	GLint           mvp_location;
	mvp_location = glGetUniformLocation(shader_program, "mvp");

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLushort vertex_indices[] =
	{
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		6, 0, 2,
		2, 4, 6,
		7, 5, 3,
		7, 3, 1
	};

	static const GLfloat vertex_positions[] =
	{
		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,
		-0.25f, -0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
	};


	GLuint          position_buffer;

	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertex_positions),
		vertex_positions,
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	GLuint          index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(vertex_indices),
		vertex_indices,
		GL_STATIC_DRAW);

	glEnable(GL_CULL_FACE);
	// glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		int i;
		static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
		static const GLfloat one = 1.0f;

		glViewport(0, 0, 800, 600);
		glClearBufferfv(GL_COLOR, 0, green);
		glClearBufferfv(GL_DEPTH, 0, &one);

		glUseProgram(shader_program);

		double currentTime = 1.0;
		float f = (float)currentTime * 0.3f;

		glm::mat4 MVP = cam.getMvMatrix() * model;
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(MVP));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		keyDownManager.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader_program);
	glDeleteBuffers(1, &position_buffer);

	glfwTerminate();
	return 0;
}
