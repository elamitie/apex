#include "application.h"
#include "input/keyboard.h"

void Application::init()
{
    mCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    mMeshShader = std::make_shared<Shader>("../resources/shaders/prototype1_lighting.vert",
                                           "../resources/shaders/prototype1_lighting.frag");
    mMeshShader->addAttribute("position");
    mMeshShader->addAttribute("normal");
    mMeshShader->addAttribute("texCoords");

    mScreenShader = std::make_shared<Shader>("../resources/shaders/basic_framebuffer.vert",
                    "../resources/shaders/basic_framebuffer.frag");
    mScreenShader->addAttribute("position");
    mScreenShader->addAttribute("texCoords");

    mMesh = std::make_shared<Mesh>("../resources/models/nanosuit/nanosuit.obj");

    mLightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    mFrameBuffer = new FrameBuffer(getWidth(), getHeight(), DEPTH_RENDER_BUFFER);
    mPostProcessor = new PostProcessor();
    mPostProcessor->init();
    mPostProcessor->pushEffect(mScreenShader);

    setColor({ int(0.1f * 255.f), int(0.1f * 255.f), int(0.1f * 255.f), int(1.0f * 255.f) });
}

void Application::update()
{
    Engine::update();

    if (Keyboard::keyDown(GLFW_KEY_W))
        mCamera->handleKeyboard(CamForward, deltaTime());
    if (Keyboard::keyDown(GLFW_KEY_S))
        mCamera->handleKeyboard(CamBack, deltaTime());
    if (Keyboard::keyDown(GLFW_KEY_A))
        mCamera->handleKeyboard(CamLeft, deltaTime());
    if (Keyboard::keyDown(GLFW_KEY_D))
        mCamera->handleKeyboard(CamRight, deltaTime());
}

void Application::render()
{
    mMeshShader->enable();

    mMeshShader->setUniform("light.position", mLightPos);
    mMeshShader->setUniform("viewPos", mCamera->position);

    mMeshShader->setUniform("light.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
    mMeshShader->setUniform("light.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
    mMeshShader->setUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    mMeshShader->setUniform("material.shininess", 32.0f);

    glm::mat4 view;
    view = mCamera->getView();
    glm::mat4 proj = glm::perspective(mCamera->properties.zoom,
                                      (GLfloat)getWidth() / (GLfloat)getHeight(), 0.1f, 100.0f);

    mMeshShader->setUniform("view", view);
    mMeshShader->setUniform("projection", proj);

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(elapsedTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    mMeshShader->setUniform("model", model);

    mFrameBuffer->bind();
    mMesh->render(mMeshShader);
    mFrameBuffer->unbind();

    mPostProcessor->process(mFrameBuffer->getColorTexture());

    console()->log("Light Pos: " + glm::to_string(mLightPos));

    console()->begin();
    console()->render();
    console()->end();
}

void Application::cleanup()
{
}
