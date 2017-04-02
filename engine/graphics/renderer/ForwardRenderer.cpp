#include "ForwardRenderer.h"
#include "utils/Logger.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

ForwardRenderer::ForwardRenderer(uint width, uint height) {
    mWidth = width;
    mHeight = height;
	mDebugMode = true;

    mDefaultPostEffect = std::make_shared<Shader>();
    mDefaultPostEffect->Attach("textured_quad.vert")->Attach("framebuffer_default.frag")->Link()->AddAttribs({
        "position", "texCoords"
    });

    mFramebuffer = std::make_shared<FrameBuffer>(mWidth, mHeight, DEPTH_RENDER_BUFFER, true);
    mPostProcessor = std::make_shared<PostProcessor>();
    mPostProcessor->Init();
    mPostProcessor->PushEffect(mDefaultPostEffect);

    mCommandBuffer.reserve(1000);
}

void ForwardRenderer::RegisterCamera(CameraPtr camera) {
    mCamera = camera;

    mProj = mCamera->CreateProjection(mWidth, mHeight);
}

void ForwardRenderer::SetLightingMode(LightMode mode) {
	// @Refactor - both PBR and Phong should be able to use the same
	// skybox interface. Right now, however, one would need a skybox and the other
	// and environment map.
	if (mode == LightMode::PHONG) {
		mSkybox = std::make_shared<Skybox>();
	}
}

void ForwardRenderer::Begin() {
    mView = mCamera->GetView();

    mCommandBuffer.clear();
    mFramebuffer->Bind();
}

void ForwardRenderer::PushMesh(Mesh* mesh, Material* material, glm::mat4 transform) {
    RenderCommand command;
    command.mesh = mesh;
    command.material = material;
    command.transform = transform;
    mCommandBuffer.push_back(command);
}

void ForwardRenderer::PushNode(SceneNodePtr node) {
	glm::mat4 transform = node->GetFinalTransform();
	PushMesh(node->mesh, node->material, transform);
	for (SceneNodePtr child : node->GetChildren()) {
		PushNode(child);
	}
}

void ForwardRenderer::PushPostEffect(ShaderPtr shader) {
    mPostProcessor->PushEffect(shader);
}

void ForwardRenderer::End() {
    // TODO: Batching or sorting....?
}

void ForwardRenderer::Flush() {
    for (int i = 0; i < mCommandBuffer.size(); i++) {
        RenderCommand& command = mCommandBuffer[i];

		// Handle material uniforms
		if (mSkybox) command.material->SetSkybox(mSkybox);
		else {} // This is where I'd set an environment map I guess?
		command.material->Enable();
		command.material->SetData();
		SetSystemUniforms(command);

        command.mesh->Render(command.material);
    }

    // Render the skybox last so that the fragment culls any pixels
    // behind a scene object
    mSkybox->Render(mView, mProj);

    mFramebuffer->Unbind();
    mPostProcessor->Process(mFramebuffer->GetColorTexture());

	if (mDebugMode) Interface();
}

void ForwardRenderer::SetSystemUniforms(RenderCommand& command) {
	command.material->SetMatrix("view", mView);
	command.material->SetMatrix("projection", mProj);
	command.material->SetMatrix("model", command.transform);
}

void ForwardRenderer::Interface() {
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::Begin("Apex Engine v0.1", nullptr, ImVec2(0, 0));
	if (ImGui::CollapsingHeader("Stuff", 0, true, true))
	{
		std::string version = std::string((char*)glGetString(GL_VERSION));
		std::string hardware = std::string((char*)glGetString(GL_RENDERER));

		std::string gl = "OpenGL Version: " + version;
		std::string hw = "Hardware Info: " + hardware;

		ImGui::Text(gl.c_str());
		ImGui::Text(hw.c_str());
		ImGui::Text("\nFramerate %.2f FPS / Frametime %.4f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	}

	ImGui::End();
	ImGui::Render();
}