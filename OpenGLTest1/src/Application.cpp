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
       
        VertexArray va;
        //Vertex Buffer now in "VertexBuffer.cpp"
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VBLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        //Index Buffer Implementation
        IndexBuffer ib(indices, 6);

        // Creating view projection matrix.
        // here we are projecting on per pixel basis , hence the change in above position coordinates.
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        // view matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        Shader shader("res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUnifrom4f("u_Color", 0.2f, 0.3f, 0.1f, 1.0f);


        Texture texture("res/Textures/image2.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.UnBind();
        shader.UnBind();
        vb.Unbind();
        ib.Unbind();

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
 
        //vars for the imgui window
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Transform values for Rendered Objects
        glm::vec3 translationA(100, 100, 0);
        glm::vec3 translationB(400, 400, 0);
        glm::vec3 scaleA(1, 1, 1);
        glm::vec3 scaleB(1, 1, 1);
        //What axis we will be rotating on 
        glm::vec3 RotAxis = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));
        float angleA = glm::radians(0.0f);
        float angleB = glm::radians(0.0f);


        //temp var to change color
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
             // Use the shader program
            glEnableVertexAttribArray(0);
            /* Render here */
            renderer.Clear();

            // Start the Dear ImGui frame   
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Draw OBJ 1
            {   
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, translationA);
                model = glm::scale(model, scaleA);
                model = glm::rotate(model, angleA, RotAxis);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUnifromMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }
            // Draw OBJ 2 
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, translationB);
                model = glm::scale(model, scaleB);
                model = glm::rotate(model, angleB, RotAxis);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUnifromMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }
            

            //changing r val
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

          
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("GL Debugger Slate");                
                ImGui::Text("Object Translations");               
                ImGui::Separator();
                ImGui::Text("Object A");               
                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);           
                ImGui::SliderFloat3("Scale A", &scaleA.x, 0.0f, 10.0f);            
                ImGui::SliderAngle("Rotation A", &angleA, -360.0f, 360.0f);
                ImGui::Spacing();
                ImGui::Text("Object B");              
                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("Scale B", &scaleB.x, 0.0f, 100.0f);            
                ImGui::SliderAngle("Rotation B", &angleB, -360.0f, 360.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            //glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}