#include "pcheaders.h"
#include <Phoenix.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Phoenix;

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example"),
		camera(-1.6f, 1.6f, -0.9f, 0.9f),
		camPos(0.0f) {
		triangleVertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> triangleVertexBuffer;
		std::shared_ptr<IndexBuffer> triangleIndexBuffer;
		////////////////////////////////////////////////////////////////
		//// Render a triangle ////////////////////////////////////////
		//////////////////////////////////////////////////////////////

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,	 0.5f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	 1.0f, 0.0f, 1.0f, 1.0f,
		};

		triangleVertexBuffer.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		BufferLayout triangleLayout = {
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }
		};
		triangleVertexBuffer->SetLayout(triangleLayout);
		triangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		triangleIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		triangleVertexArray->AddIndexBuffer(triangleIndexBuffer);

		std::string triangleVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color;
			
			uniform mat4 viewProjection;
			uniform mat4 transform;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main() {
				vPosition = position;
				vColor = color;
				gl_Position = viewProjection * transform * vec4(position, 1.0);
			}
		)";

		std::string triangleFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			in vec4 vColor;

			void main() {
				color = vec4(vPosition * 0.5 + 0.5, 1.0);
				color = vColor;
			}
		)";

		/////////////////////////////////////////////////////////////
		//// Render a square ////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		squareVertexArray.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		std::shared_ptr<IndexBuffer> squareIndexBuffer;

		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "position" },
		};
		squareVertexBuffer->SetLayout(squareLayout);
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->AddIndexBuffer(squareIndexBuffer);

		std::string squareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			uniform mat4 viewProjection;
			uniform mat4 transform;

			out vec3 vPosition;
			
			void main() {
				vPosition = position;
				gl_Position = viewProjection * transform * vec4(position, 1.0);
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			
			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		triangleShader.reset(Shader::Create(triangleVertexSrc, triangleFragmentSrc));
		squareShader.reset(Shader::Create(squareVertexSrc, squareFragmentSrc));
	}

	//-- Update per frame --//
	void OnUpdate(Timestep ts) override {

		PHX_CORE_INFO("Delta time: {0}", ts.GetSeconds());

		if (Input::IsKeyPressed(PHX_KEY_D)) {
			PHX_INFO("Camera shifting right.");
			camPos.x += cameraSpeed * ts.GetSeconds();
		}
		else if (Input::IsKeyPressed(PHX_KEY_A)) {
			PHX_INFO("Camera shifting right.");
			camPos.x -= cameraSpeed * ts.GetSeconds();
		}
		if (Input::IsKeyPressed(PHX_KEY_W)) {
			PHX_INFO("Camera shifting up.");
			camPos.y += cameraSpeed * ts.GetSeconds();
		}
		else if (Input::IsKeyPressed(PHX_KEY_S)) {
			PHX_INFO("Camera shifting down.");
			camPos.y -= cameraSpeed * ts.GetSeconds();
		}

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
		//RenderCommand::EnableAntiAliasing();

		camera.SetPosition(camPos);

		Renderer::BeginScene(camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int i = 0; i < 5; i++) {
			Renderer::Submit(squareVertexArray, squareShader, transform * scale);
		}

		Renderer::Submit(triangleVertexArray, triangleShader);

		Renderer::EndScene();

		// Renderer::Flush(); Multi thread
	}

	//-- Implement ImGui here --//
	void OnImGuiRender() override {
		bool show = true;
		ImGui::Begin("Output");
		ImGui::Text("Phoenix Engine Output");
		ImGui::End();
	}

	//-- Implement event action for this layer --//
	void OnEvent(Phoenix::Event& event) override {
		if (event.GetEventType() == Phoenix::EventType::MouseScrolled) {
			
		}
	}
private:
	std::shared_ptr<VertexArray> triangleVertexArray;
	std::shared_ptr<VertexArray> squareVertexArray;

	std::shared_ptr<Shader> triangleShader;
	std::shared_ptr<Shader> squareShader;

	OrthoCamera camera;
	float cameraSpeed = 0.2;
	glm::vec3 camPos;

};

class Sandbox : public Phoenix::Application {
public:
	// Pushing layers and overlays into Sandbox
	Sandbox() {
		PushLayer(new ExLayer());
	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox();
}