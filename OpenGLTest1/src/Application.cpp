#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VBLayout.h"
#include "Shader.h"
#include "Texture.h"
//Test Cases
#include "Tests/TestClearColor.h"
#include "Tests/ColorQuadTest.h"
#include "Tests/TestTexture2D.h"
// GL Math Lib Includes
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); 
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!!" << std::endl;
    }
    else
    {
        std::cout << "OpenGL ver. " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Texture Units Supported : " << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << std::endl;

    }


       GLCall(glEnable(GL_BLEND));
       GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
       
 
        Renderer renderer;

        //imgui context creation
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
        
        // Setup ImGui style
        ImGui::StyleColorsDark();

        test::Test* currenttest = nullptr;
        test::TestMenu* testmenu = new test::TestMenu(currenttest);
        currenttest = testmenu;

        testmenu->RegisterTest<test::TestClearColor>("Clear Color");
        testmenu->RegisterTest<test::ColorQuadTest>("Quad Color");
        testmenu->RegisterTest<test::TestTexture2D>("Test Texture2D");


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
             // Use the shader program
            glEnableVertexAttribArray(0);
            /* Render here */
            renderer.Clear();
            // Start the Dear ImGui frame   
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currenttest)
            {
                currenttest->OnUpdate(0.0f);
                currenttest->OnRender();
                ImGui::Begin("GL Debugger Slate");
                if (currenttest != testmenu && ImGui::Button("<-"))
                {
                    delete currenttest;
                    currenttest = testmenu;
                }
                currenttest->OnImGuiRender();
                ImGui::End();
            }
          

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currenttest;
        if (currenttest != testmenu)
            delete testmenu;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}