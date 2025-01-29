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
#include "VBLayout.h"
#include "Shader.h"
#include "Texture.h"
// GL Math Lib Includes
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"




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
   
        //For Legacy Triangle Input
     /*  float a, b, c, d, e, f;
        std::cin >> a >> b >> c >> d >> e >> f;
        std::getchar;
        std::cout << a;
        LegacyDrawTriangle(a, b, c, d, e, f, window);*/


        float positions[] = {
             200.0f, 200.0f , 0.0f, 0.0f// 0
            ,400.0f, 200.0f , 1.0f, 0.0f// 1
            ,400.0f, 400.0f , 1.0f, 1.0f// 2 
            ,200.0f, 400.0f , 0.0f, 1.0f// 3
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
        //glEnableVertexAttribArray(0);

        //Index Buffer Implementation
        IndexBuffer ib(indices, 6);

        // Creating view projection matrix.
        // here we are projecting on per pixel basis , hence the change in above position coordinates.
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        // view matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        // model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

        glm::mat4 mvp = proj * view * model;

        Shader shader("res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUnifrom4f("u_Color", 0.2f, 0.3f, 0.1f, 1.0f);
        //Setting MVP to the shader
        shader.SetUnifromMat4f("u_MVP", mvp);

        Texture texture("res/Textures/image2.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.UnBind();
        shader.UnBind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;
 
        //temp var to change color
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            shader.Bind(); // Use the shader program
            glEnableVertexAttribArray(0);
            /* Render here */
            renderer.Clear();
            //Draw call to draw a triangle using vertex buffer
            //glDrawArrays(GL_TRIANGLES, 0, 6); 

            //Changing colors on every draw 
            //Uniforms can be refreshed on every draw
            shader.SetUnifrom4f("u_Color", r, 0.2f, 0.1f, 1.0f);
          
            
                //Draw call to draw a triangle using index buffer
                //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
          
            //using the renderer class to draw 
            renderer.Draw(va, ib, shader);

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