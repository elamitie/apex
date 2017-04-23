#include "ForwardRenderer.h"
#include "utils/Logger.h"
#include "graphics/scene/Scene.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

ForwardRenderer::ForwardRenderer(uint width, uint height, Scene* parentScene) {
    mWidth = width;
    mHeight = height;
	mDebugMode = true;

	mParentScene = parentScene;

    mCommandBuffer.reserve(1000);
}

void ForwardRenderer::RegisterCamera(CameraPtr camera) {
    mCamera = camera;

    mProj = mCamera->CreateProjection(mWidth, mHeight);
}

void ForwardRenderer::SetLightingMode(LightMode mode) {
	if (mode == LightMode::PHONG) {
		mMode = mode;
		mSkybox = std::make_shared<Skybox>("skybox.vert", "skybox.frag");
	}

	if (mode == LightMode::PBR) {
		mMode = mode;
		mSkybox = std::make_shared<Skybox>("pbr/pbr_background.vert", "pbr/pbr_background.frag");
		mPBRPreComputation = new PBRPreComputation();
		mSkybox->SetCubemap(mPBRPreComputation->GetEnvironmentMap());
	}
}

void ForwardRenderer::ChangeEnvironment(const std::string& envName)
{
	mPBRPreComputation = new PBRPreComputation(envName);
	mSkybox->SetCubemap(mPBRPreComputation->GetEnvironmentMap());
}

void ForwardRenderer::RegisterCustomMaterial(MaterialCustom* mat)
{
	mCustomMat = mat;
}

void ForwardRenderer::Begin() {
    mView = mCamera->GetView();
	mProj = mCamera->CreateProjection(mWidth, mHeight);

    mCommandBuffer.clear();
}

void ForwardRenderer::PushMesh(Mesh* mesh, MaterialBase* material, glm::mat4 transform) {
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
    //mPostProcessor->PushEffect(shader);
}

void ForwardRenderer::End() {
    // TODO: Batching or sorting....?
}

void ForwardRenderer::Flush() {
    for (int i = 0; i < mCommandBuffer.size(); i++) {
        RenderCommand& command = mCommandBuffer[i];

		command.material->Enable();

		// Handle material uniforms
		if (mMode == PHONG) command.material->SetSkybox(mSkybox);
		else if (mMode == PBR) command.material->SetEnvironmentMap(mPBRPreComputation);

		command.material->SetData();
		SetSystemUniforms(command);

        command.mesh->Render(command.material);
    }

    // Render the skybox last so that the fragment culls any pixels
    // behind a scene object
    mSkybox->Render(mView, mProj);

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
	if (ImGui::CollapsingHeader("Scene", 0, true, false))
	{
		if (ImGui::TreeNode("Set Material Type"))
		{
			switch (mMode)
			{
			case PHONG:
				break;
			case PBR:
				if (ImGui::Button("Plastic"))
				{
					Logger::Log("Button click: Plastic");
					mParentScene->OnChangeMaterial("plastic");
					mTweakSliders = false;
				}
				if (ImGui::Button("Gold"))
				{
					Logger::Log("Button click: Gold");
					mParentScene->OnChangeMaterial("gold");
					mTweakSliders = false;
				}
				if (ImGui::Button("Custom"))
				{
					Logger::Log("Button click: Custom");
					mParentScene->OnChangeMaterial("custom");
					mTweakSliders = true;
				}
				break;
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Set Material Values"))
		{
			if (mTweakSliders)
			{
				glm::vec3 albedo = glm::vec3(mCustomMat->mAlbedo.r / 255.f, mCustomMat->mAlbedo.g / 255.f, mCustomMat->mAlbedo.b / 255.f);
				float metallic = mCustomMat->mMetallic;
				float roughness = mCustomMat->mRoughness;
				float ambient = mCustomMat->mAO;

				ImGui::ColorEdit3("Albedo", (float*)&albedo);
				ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f);
				ImGui::SliderFloat("Roughness", &roughness, 0.0f, 0.5f);
				ImGui::SliderFloat("Ambient", &ambient, 0.1f, 1.0f);

				mCustomMat->SetAlbedo(Color(albedo.x * 255, albedo.y * 255, albedo.z * 255));
				mCustomMat->SetMetallic(metallic);
				mCustomMat->SetRoughness(roughness);
				mCustomMat->SetAO(ambient);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Environment Maps"))
		{
			switch (mMode)
			{
			case PHONG:
				break;
			case PBR:
				if (ImGui::Button("Newport Loft"))
				{
					ChangeEnvironment("newport_loft");
				}
				if (ImGui::Button("Pines"))
				{
					ChangeEnvironment("arches_e_pinetree");
				}
				if (ImGui::Button("Gravel Plaza"))
				{
					ChangeEnvironment("gravel_plaza");
				}
				break;
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Camera"))
		{
			float rate = mCamera->mRotationRate;
			ImGui::SliderFloat("Rotation Rate", &rate, 0.0f, 1.0f);

			mCamera->EnableRotation(rotate);

			ImGui::TreePop();
		}
	}

	if (ImGui::CollapsingHeader("Profiling", 0, true, true)) 
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