#include "ColorQuadTest.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



test::ColorQuadTest::ColorQuadTest()
    : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
    m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Translation(200.0f, 200.0f, 0.0f),
    m_QuadColor{ 0.2f, 0.3f, 0.8f, 1.0f }
{
    float positions[] = {
            -50.0f, -50.0f , 0.0f, 0.0f// 0
           ,50.0f, -50.0f , 1.0f, 0.0f// 1
           ,50.0f, 50.0f , 1.0f, 1.0f// 2 
           ,-50.0f, 50.0f , 0.0f, 1.0f// 3
    };

    //Indices for a Index Buffer
    unsigned int indices[]{
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //Using smart pointers
    m_VAO = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VBLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);

    //Index Buffer Implementation
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
    m_Shader->Bind();
    m_Shader->SetUniform1i("UseTex", 0);
    m_Shader->SetUnifrom4f("u_Color", m_QuadColor[0], m_QuadColor[1], m_QuadColor[2], m_QuadColor[3]);
    m_Texture = std::make_unique<Texture>("res/Textures/image2.png");
    m_Shader->SetUniform1i("u_Texture", 0);

}

test::ColorQuadTest::~ColorQuadTest()
{
   
}

void test::ColorQuadTest::OnUpdate(float deltaTime)
{

}

void test::ColorQuadTest::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_Texture->Bind();
    // Draw OBJ 1
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUnifromMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    m_Shader->SetUnifrom4f("u_Color", m_QuadColor[0], m_QuadColor[1], m_QuadColor[2], m_QuadColor[3]);

}

void test::ColorQuadTest::OnImGuiRender()
{
	
    ImGui::ColorEdit4("Quad Color", m_QuadColor);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
