#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders.h> //���з�װ����ɫ����

using namespace std;

//�����塱 Vertex Shader������ɫ��
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
//�����塱 Fragment ShaderƬ����ɫ��
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
    //���£���������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        cout << "Cannot create window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //���³�ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Cannot to initiallize GLAD" << endl;
        return -1;
    }
    //�����ӿ�Viewport
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    

    //Part2.����VBO(Vertex Buffer Object)���� �Լ� ������ɫ��

    //unsigned int vertexShader; //������ɫ��
    //vertexShader = glCreateShader(GL_VERTEX_SHADER); //���춥����ɫ��
    //unsigned int fragmentShader; //Ƭ����ɫ��
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //����Ƭ����ɫ��
    //unsigned int shaderProgram; //��ɫ������

    unsigned int VBO; //VBO
    unsigned int VAO; //VAO
    unsigned int EBO; //EBO
    Shader ourShader("vertex.vs", "fragment.fs");
    float vertices[] = {
        //����λ��
         0.5f, -0.5f, 0.0f, //���µ�
         1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.0f, //���µ�
         0.0f, 1.0f, 0.0f,

         0.0f, 0.5f, 0.0f, //y = 0.
         0.0f, 0.0f, 1.0f //ͬ�϶�Ӧ����
        //-0.5f, 0.5f, 0.0f, //���ϵ�
        //0.5f, 0.5f, 0.0f, //���ϵ�(x,y,z)��ά����
        //��ɫ
    }; // ���嶥��
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //shaderProgram = glCreateProgram(); //������ɫ������

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    //�󶨻���
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //������ 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //��������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*
    ����Դ�벢����
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    */
    /*����������ɫ������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); 

    glUseProgram(shaderProgram);
    */

    //��ѭ�����Գ�פ���壬��Ⱦѭ��(render loop)
    while (!glfwWindowShouldClose(window)) {
        //������
        processInput(window);
        //��Ⱦָ�� render command
        float timeValue = glfwGetTimerValue();
        float offset = 0.5f;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        ourShader.setFloat("xOffset", offset);
        glBindVertexArray(VAO); //��VAO��Ⱦ

        //�����߿�ģʽ����ס����5���л����߿�ģʽ��
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);//����


        //��鲢�����¼�����������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}