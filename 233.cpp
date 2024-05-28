#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders.h> //自行封装的着色器库

using namespace std;

//“定义” Vertex Shader顶点着色器
/* const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"

    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";
 */
//“定义” Fragment Shader片段着色器
/*
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"

    " void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\0";
*/
//Callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
//Input Function
void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //以下，创建窗体
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        cout << "Cannot create window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //以下初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Cannot to initiallize GLAD" << endl;
        return -1;
    }
    //设置视口Viewport
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    

    //Part2.生成VBO(Vertex Buffer Object)对象 以及 顶点着色器

    //unsigned int vertexShader; //顶点着色器
    //vertexShader = glCreateShader(GL_VERTEX_SHADER); //创造顶点着色器
    //unsigned int fragmentShader; //片段着色器
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //创造片段着色器
    //unsigned int shaderProgram; //着色器程序

    unsigned int VBO; //VBO
    unsigned int VAO; //VAO
    unsigned int EBO; //EBO
    Shader ourShader("vertex.vs", "fragment.fs");
    float vertices[] = {
        //顶点位置
         0.5f, -0.5f, 0.0f, //右下点
         1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.0f, //左下点
         0.0f, 1.0f, 0.0f,

         0.0f, 0.5f, 0.0f, //y = 0.
         0.0f, 0.0f, 1.0f //同上对应顶点
        //-0.5f, 0.5f, 0.0f, //左上点
        //0.5f, 0.5f, 0.0f, //右上点(x,y,z)三维坐标
        //颜色
    }; // 定义顶点
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //shaderProgram = glCreateProgram(); //创造着色器程序

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //绑定数据 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*
    附加源码并编译
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    */
    /*链接所有着色器对象
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); 

    glUseProgram(shaderProgram);
    */

    //死循环，以常驻窗体，渲染循环(render loop)
    while (!glfwWindowShouldClose(window)) {
        //输入检测
        processInput(window);
        //渲染指令 render command
        float timeValue = glfwGetTimerValue();
        float offset = 0.5f;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        ourShader.setFloat("xOffset", offset);
        glBindVertexArray(VAO); //绑定VAO渲染

        //设置线框模式（按住数字5，切换至线框模式）
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);//开画


        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}