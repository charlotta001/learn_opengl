#include "config.h"
// GLSL VERSION 4.6

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    
    window = glfwCreateWindow(800, 600, "My window", NULL, NULL);
    glfwMakeContextCurrent(window);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        return -1;
    }
    
    float vertices[] = {
        0.0,0.0,0.0
    };
    float color[] = {
        1.0,0.0,0.0
    };
    GLuint program = make_shader("../src/shaders/vertexShader.txt","../src/shaders/fragmentShader.txt");
    
    std::vector <GLuint> VBOs;
    VBOs.resize(2);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2,VBOs.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 *sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 3 *sizeof(float),(void*)0);
    glEnableVertexAttribArray(1);
   

    glfwSetWindowPos(window, 587, 254);
    glfwSetWindowSizeCallback(window, window_pos_callback);
    
    glEnable(GL_PROGRAM_POINT_SIZE);
    while(!glfwWindowShouldClose(window)){
        
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(1.0f,0.0f,0.0f,1.0f);
        glfwPollEvents();
        glUseProgram(program);
        glBindVertexArray(VAO);
        glPointSize(100.0f);
        glDrawArrays(GL_POINTS, 0,1);
      
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

