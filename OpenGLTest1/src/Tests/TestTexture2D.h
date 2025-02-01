#pragma once

#include "Test.h"
#include "Renderer.h"
#include "VBLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include <memory>

namespace test {
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

		glm::vec3 m_Translation;
		glm::vec3 m_Scale;
		glm::vec3 m_RotAxis;
		float m_Angle;
		glm::mat4 m_Proj, m_View;
		
		bool m_UseTexture = true;
	
	};
}
