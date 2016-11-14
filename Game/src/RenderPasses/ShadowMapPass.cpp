
#include "ShadowMapPass.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <util/Exceptions/OpenGLException.h>
#include <Render/Light/DirectionalLight.h>
//#include <util/ioHelper/PortablePixMapImageHelper.h>

using namespace sagame;

ShadowMapPass::ShadowMapPass(float shadowMapWidth, float shadowMapHeight) :
	shadowMapWidth(shadowMapWidth), shadowMapHeight(shadowMapHeight)
{
	setupShaders();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Set up the framebuffer object
	setupFBO();

	GLuint programHandle = shadowShader.getProgramHandle();

	shadowBias = glm::mat4(
		glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	shadowShader.setUniform("Light.Intensity", glm::vec3(0.85f));

	shadowShader.setUniform("ShadowMap", 0);
}

void ShadowMapPass::setupShaders()
{
	shadowShader.attachShader("ShaderSource/shadowmapfirstpass.vs", sag::VERTEX);
	shadowShader.attachShader("ShaderSource/shadowmapfirstpass.fs", sag::FRAGMENT);
	//shadowShader.bindAttribLocation(0, "VertexPosition");
	shadowShader.link();
}

void ShadowMapPass::setupFBO()
{
	GLfloat border[] = { 1.0f, 0.0f,0.0f,0.0f };
	// depth buffer texture
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, shadowMapWidth, shadowMapHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	// Assign the depth buffer texture to texture channel 0
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, depthTex);

	// set up the FBO
	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	GLenum drawBuffers[] = { GL_NONE };
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result != GL_FRAMEBUFFER_COMPLETE)
	{
		throw sag::OpenGLException("ShadowMap framebuffer incomplete.");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapPass::render(const sag::SceneManager& scene, sag::RenderPassData* renderPassDataExchange) const
{
	auto lights = scene.getLights();
	if (lights.size() == 0)
		return;
	auto light = lights.back();
	if (auto directionalLight = dynamic_cast<sag::DirectionalLight*>(light))
	{
		renderPassDataExchange->addTexture("depthTex", depthTex);

		glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);


		auto lightViewMatrix = directionalLight->getView();
		auto lightProjectionMatrix = directionalLight->getPerspective();
		auto lightPV = lightProjectionMatrix * lightViewMatrix;

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(2.0f, 1.0f);

		auto renderableObjects = scene.getRenderableObjects();
		for (auto& renderableObj : renderableObjects)
		{
			renderableObj->render(lightViewMatrix, lightPV, lights, renderPassDataExchange);
		}

		glCullFace(GL_BACK);
		glDisable(GL_POLYGON_OFFSET_FILL);

		glFlush();
		glFinish();
		//writeDepthFboToFile(); // debugging
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

/*
void ShadowMapPass::writeDepthFboToFile() const {
	int size = shadowMapWidth * shadowMapHeight;
	float * buffer = new float[size];
	unsigned char * imgBuffer = new unsigned char[size * 3];

	glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, buffer);

	for (int i = 0; i < shadowMapHeight; i++)
		for (int j = 0; j < shadowMapWidth; j++)
		{
			int imgIdx = 3 * ((i*shadowMapWidth) + j);
			int bufIdx = ((shadowMapHeight - i - 1) * shadowMapWidth) + j;
			float minVal = 0.88f; // tweak for different light configurations
			float scale = (buffer[bufIdx] - minVal) / (1.0f - minVal);
			unsigned char val = (unsigned char)(scale * 255);
			imgBuffer[imgIdx] = val;
			imgBuffer[imgIdx + 1] = val;
			imgBuffer[imgIdx + 2] = val;
		}

	PortablePixMapImageHelper::writePortablePixmap("fbo_depth.ppm", imgBuffer, shadowMapWidth, shadowMapHeight);

	delete[] buffer;
	delete[] imgBuffer;
	exit(1);
}
*/