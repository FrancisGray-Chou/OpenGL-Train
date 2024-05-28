#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>;
#include <string>;
#include <fstream>;
#include <sstream>;
#include <iostream>;
using namespace std;
class Shader
{
public:
	unsigned int ourShader;

	Shader(const char* vertexPath, const char* fragmentPath) {
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		//确保ifstream可抛出异常
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			//打开文件
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;
			//读取文件缓冲内容到数据流
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//关闭文件处理
			vShaderFile.close();
			fShaderFile.close();
			//转换数据流到string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "FAIL,SHADER,file not succesfully read" << endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//编译着色器
		unsigned int vertex, fragment;
		char infoLog[1024];
		int success;
		//顶点着色器
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}
		//片段着色器
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << endl;
		}
		//附加源码并编译 + 链接所有着色器
		ourShader = glCreateProgram();
		glAttachShader(ourShader, vertex);
		glAttachShader(ourShader, fragment);
		glLinkProgram(ourShader);
		glGetProgramiv(ourShader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ourShader, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void use()
	{
		glUseProgram(ourShader);
	}
	void setBool(const string& name, bool value) 
	{
		glUniform1i(glGetUniformLocation(ourShader, name.c_str()), (int)value);
	}
	void setInt(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ourShader, name.c_str()), value);
	}
	void setFloat(const string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ourShader, name.c_str()), value);
	}
private:

};

#endif // !SHADER_H

