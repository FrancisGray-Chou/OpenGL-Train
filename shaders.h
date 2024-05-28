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
		//ȷ��ifstream���׳��쳣
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			//���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;
			//��ȡ�ļ��������ݵ�������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//�ر��ļ�����
			vShaderFile.close();
			fShaderFile.close();
			//ת����������string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "FAIL,SHADER,file not succesfully read" << endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//������ɫ��
		unsigned int vertex, fragment;
		char infoLog[1024];
		int success;
		//������ɫ��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}
		//Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << endl;
		}
		//����Դ�벢���� + ����������ɫ��
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

