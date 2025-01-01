#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"





void LegacyDrawTriangle(float a, float b, float c, float d, float e, float f, GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Legacy OpenGL Implementation
      /*  glBegin(GL_TRIANGLES);
        glVertex2f(a, b);
        glVertex2f(c, d);
        glVertex2f(e, f);
        glEnd();*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    }
   
        //For Legacy Triangle Input
     /*  float a, b, c, d, e, f;
        std::cin >> a >> b >> c >> d >> e >> f;
        std::getchar;
        std::cout << a;
        LegacyDrawTriangle(a, b, c, d, e, f, window);*/


        float positions[] = {
            -0.5f, -0.5f // 0
            ,0.5f, -0.5f // 1
            ,0.5f,  0.5f // 2 
            ,-0.5f, 0.5f // 3
        };

        //Indices for a Index Buffer
        unsigned int indices[]{
            0,1,2,
            2,3,0
        };

        VertexArray va;
        //Vertex Buffer now in "VertexBuffer.cpp"
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VBLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        //glEnableVertexAttribArray(0);

        //Index Buffer Implementation
        IndexBuffer ib(indices, 6);

        Shader shader("res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUnifrom4f("u_color", 0.2f, 0.3f, 0.1f, 1.0f);


        va.UnBind();
        shader.UnBind();
        vb.Unbind();
        ib.Unbind();

 
        //temp var to change color
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            shader.Bind(); // Use the shader program
            glEnableVertexAttribArray(0);
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //Draw call to draw a triangle using vertex buffer
            //glDrawArrays(GL_TRIANGLES, 0, 6); 

            //Changing colors on every draw 
            //Uniforms can be refreshed on every draw
            shader.SetUnifrom4f("u_Color", r, 0.2f, 0.1f, 1.0f);
            va.Bind();
            ib.Bind();
                //Draw call to draw a triangle using index buffer
                GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            //changing r val
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    glfwTerminate();
    return 0;
}