#pragma once
#include "Test.h"
#include "Renderer.h"
#include "VBLayout.h"
#include "Texture.h"
#include "Shader.h"
#include "imgui/imgui.h"

namespace test {
	class ColorQuadTest : public Test
	{
	public:
		ColorQuadTest();
		~ColorQuadTest();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

		float m_QuadColor[4];
		glm::vec3 m_Translation;
		glm::mat4 m_Proj, m_View;

	};
}