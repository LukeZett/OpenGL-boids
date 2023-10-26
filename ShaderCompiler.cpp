#include "GL/glew.h"
#include "ShaderCompiler.h"
using namespace std;





int CreateShader(GLenum type, std::filesystem::path path)
{
	int shader = glCreateShader(type);
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	char* raw_code = content.data();
	glShaderSource(shader, 1, &raw_code, NULL);
	glCompileShader(shader);
	return shader;

}

int CreateShaderProgram(GLenum type1, std::filesystem::path path1, GLenum type2, std::filesystem::path path2) {

	int shader1 = CreateShader(type1, path1);
	int shader2 = 0;
	int program = glCreateProgram();
	glAttachShader(program, shader1);


	if (type2 != NULL && path2 != "")
	{
		shader2 = CreateShader(type2, path2);
		glAttachShader(program, shader2);
	}
	glLinkProgram(program);

	glDetachShader(program, shader1);
	glDeleteShader(shader1);

	if (type2 != NULL && path2 != "")
	{
		glDetachShader(program, shader2);
		glDeleteShader(shader2);
	}

	std::cout << "Shaders are reloaded." << std::endl;

	return program;
}

