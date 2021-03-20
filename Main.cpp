// OpenGL library and extension
#include <GL/glew.h>       
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>  // To handle files
#include <string>
#include <sstream>

//  Extra headers

#include "Renderer.h" // This is our "factory"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// Maths

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


const unsigned int InitWidth = 640;
const unsigned int InitHeight = 480;

int main(void){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Specifying a the version that OpenGL is going to use, in this case the 3.3    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context with a new title*/
    window = glfwCreateWindow(InitWidth, InitHeight, "Game of Life", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    
    glEnable(GL_DEPTH_TEST); // Z Buffer
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); 

               
        VertexArray va; // Instantiation a VertexArray object
        VertexBuffer vb(positions,  sizeof(positions)); // Instantiation the vertex buffer with the required data

        VertexBufferLayout layout; // Instantiation a VertexBufferLayout

        // Adding attributes yo our layout (the design) 

        layout.Push<float>(3); 
        layout.Push<float>(2); 

        // Binding the specified attributes to the vertex buffer using the vertex array as an intermediate 

        va.AddBuffer(vb, layout);
    

        Shader shader("res/shaders/Basic.shader"); // Location of the shader that is going to be used
        shader.Bind();
        shader.SetUniform4f("u_Color", 18.0f, 213.0f, 77.0f, 1.0f);

        Texture texture("res/textures/hack.png"); // Location of the texture (with the .png format, remember we can use different type of formats) that is going to be used
        texture.Bind(0); // Binding it 
        shader.SetUniform1i("u_Texture", 0);  // applying the selected texture to the first slot

        va.Unbind();    
        vb.Unbind(); 
        shader.UnBind();

        // Instantiation of our "fabric", the renderer (this is going to take everything that we need and create our graphic)  

        Renderer renderer; 

        // Setting up our variables that will be used in the color animation 

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */

            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Transformations
                    
            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)InitWidth / (float)InitHeight, 0.1f, 100.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
            glm::mat4 model = glm::rotate(glm::mat4(1.0f),(float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
            glm::mat4 mvp = proj * view * model;


            shader.Bind(); // Installing a program object as part of current rendering state
            shader.SetUniform4f("u_Color", r, 213.0f, r, 1.0f); 

            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, shader);

        /* Running from 1 to 0 the first 
            vector so we can see a kind of animation */

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers
               Poll for and process events 
            */

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}



