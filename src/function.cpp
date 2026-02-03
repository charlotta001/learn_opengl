#include "config.h"
#include "function.h"
    
void window_pos_callback(GLFWwindow* window, int width, int height)
{
    int xwidth, yheight;
    glfwGetWindowSize(window, &xwidth, &yheight);
    std::cout << "xwidth: " << xwidth << "|| yheight: " << yheight << std::endl;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
    int xpos = (mode->width - width)/2;
    int ypos = (mode->height - height)/2;
   

    std::cout << "xpos: " << xpos << "|| ypos: " << ypos << std::endl;
    glfwSetWindowPos(window,xpos,ypos);
    glViewport(0,0, xwidth, yheight);
    
    
    
}

GLuint make_module(const std::string &shaderPath,int shaderModule){
        const char* shaderChar;
        std::ifstream shaderFile(shaderPath);
        std::string shaderString1;
        std::stringstream bufferedLines;
        std::string shaderString2;
        GLuint shaderName;

        if(!shaderFile.is_open()){
            std::cerr<<"cant open file" << std::endl;
    }
    
        while(getline(shaderFile, shaderString1)){
            bufferedLines << shaderString1 << std::endl;
        }
        // while(getline(shaderFile, shaderString1)) {
        //     std::cout << shaderString1 << std::endl;
        // }

        shaderString2 = bufferedLines.str();
        shaderChar =  shaderString2.c_str();

        shaderName = glCreateShader(shaderModule);
        glShaderSource(shaderName, 1, &shaderChar,NULL);
        glCompileShader(shaderName);

        int success;
        char infoLog[1024];
        glGetShaderiv(shaderName, GL_COMPILE_STATUS, &success);

        if(!success){
            glGetShaderInfoLog(shaderName, 1024, NULL, infoLog);
            std::cout << "FAILED COMPILE SHADER V/F" << infoLog << std::endl;
        }

        return shaderName;       
}
    
GLuint make_shader(const std::string &vertexPath, const std::string &fragmentPath){
   
    std::vector <GLuint> shader;
    shader.push_back(make_module(vertexPath, GL_VERTEX_SHADER));
    shader.push_back(make_module(fragmentPath, GL_FRAGMENT_SHADER));

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

   for(auto attach: shader) {
    glAttachShader(shaderProgram, attach);
   }
   glLinkProgram(shaderProgram);


   int success;
   char infoLog[1024];
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if(!success) {
        glGetProgramInfoLog(shaderProgram,1024,NULL,infoLog);
        std::cout << "FAILED TO COMPILE PROGRAM " << infoLog << std::endl;
   }

   

   return shaderProgram;
    
}
