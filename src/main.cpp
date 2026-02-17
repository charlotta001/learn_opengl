#include "config.h"

// GLSL VERSION 4.6

int main()
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    
    window = glfwCreateWindow(800, 600, "My window", NULL, NULL);
    glfwMakeContextCurrent(window);
    int w,h;
    glfwGetWindowSize(window,&w,&h);
    std::cout << "w : " << h << " || h: " << w << std::endl;


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        return -1;
    }
    
    float vertices[] = {
        0.0,0.0,0.0,
        0.5,0.0,0.0,
        -0.5,0.0,0.0

    };
    float color[] = {
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0
    };

    // float mytextue[] = {
    //     0.0f,0.0f,
    //     1.0f,0.0f,
    //     1.0f,1.0f,
    //     0.0f,1.0f
    // };


    Material* material = new Material("../img/iuno.png");
    GLuint program = make_shader("../src/shaders/vertexShader.txt","../src/shaders/fragmentShader.txt");

    
    std::vector <GLuint> VBOs;
    VBOs.resize(2);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position
    glGenBuffers(2,VBOs.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 *sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // color
    //glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    //glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 3 *sizeof(float),(void*)0);
    //glEnableVertexAttribArray(1);
   
    //texture
    //Material* ourTexture = new Material("../img/iuno.png");
    //glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "ourTexture"), 0);
    glfwSetWindowPos(window, 587, 254);
    glfwSetWindowSizeCallback(window, window_pos_callback);
    glViewport(0,0,800,600);
    


    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    //glEnable(GL_DEPTH_TEST);


    //glEnable(0x8861); // GL_POINT_SPRITE (Force enable)
    //glEnable(GL_POINT_SPRITE_COORD_ORIGIN);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Add this!


    while(!glfwWindowShouldClose(window)){
        
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(1.0f,0.0f,0.0f,1.0f);
        glfwPollEvents();
        glUseProgram(program);
        glBindVertexArray(VAO);
        //glPointSize(100.0f);
        material->use();
        glDrawArrays(GL_POINTS, 0,3);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

