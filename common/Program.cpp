#include "Program.hpp"
#include <iostream>
#include <string>

Program::Program(const char* directory, const char* vertexShader, const char* fragmentShader,int numberOfLights)
{
    std::string vertex_file_path = FindFile(directory, vertexShader);
    std::string  fragment_file_path = FindFile(directory, fragmentShader);
    num = LoadShaders(vertex_file_path.c_str(), fragment_file_path.c_str());
    SetUpUniformCamera();
    SetUpUniformLights(numberOfLights);
}

void Program::Use()
{
    glUseProgram(num);
}

GLuint Program::GetNum()
{
    return num;
}

void Program::AddUniformVar(const char* name)
{
    GLuint newUniform = glGetUniformLocation(num, name);
    uniformVariable.push_back(newUniform);

}

void Program::SetFloat(GLuint uniform, float value)
{
    glUniform1f(uniform, value);
}

void Program::SetVector(GLuint uniform, vec3 vector)
{
    glUniform3f(uniform, vector.x, vector.y, vector.z);
}

void Program::SetMatrix4(GLuint uniform, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(uniform, count, GL_FALSE, value);

}

void Program::BindTexture(GLuint texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(uniformVariable[3], 0);
}

void Program::SetUpUniformCamera()
{
    AddUniformVar("MVP");
    AddUniformVar("V");
    AddUniformVar("M");
}

void Program::UpdateCamera(const GLfloat* MVP, const GLfloat* V, const GLfloat* M)
{
    SetMatrix4(uniformVariable[0],1,GL_FALSE,MVP);
    SetMatrix4(uniformVariable[1], 1, GL_FALSE, V);
    SetMatrix4(uniformVariable[2], 1, GL_FALSE, M);
}

void Program::SetUpUniformLights(int numberOfLights)
{
    std::string currentPt = "pointLights[]";
    std::string newPt;
     for (int i = 0; i < numberOfLights; i++)
    {
        newPt = currentPt;
        newPt.insert(12, std::to_string(i));
        AddUniformVar((newPt + ".position").c_str());
        AddUniformVar((newPt + ".LightParam_Color").c_str());
        AddUniformVar((newPt + ".LightParam_Power").c_str());
    }
}

void Program::UpdateLights(std::vector<Light*> objectLights)
{
    
    int i;
    int gap = 4;
    int index = 1;

   
    for (i=0; i < objectLights.size(); i++)
    {
        index += 3;
        int index1 = index + 1;
        int index2 = index + 2;
        /*
        std::cout << index << std::endl;
        std::cout << index1 << std::endl;
        std::cout << index2 << std::endl;*/

        float x = objectLights[i]->GetLightPosition().x;
        float y = objectLights[i]->GetLightPosition().y;
        float z = objectLights[i]->GetLightPosition().z;
        
        float x1 = objectLights[i]->GetLightColor().x;
        float y1 = objectLights[i]->GetLightColor().y;
        float z1 = objectLights[i]->GetLightColor().z;

        std::cout << "objectLights[" << i << "] -> " <<
            "light[" << index << "].light_color = " << x1 << "," << y1 << "," << z1 << std::endl;

        std::cout << "objectLights[" << i << "] -> " << 
            "light["<< index2 << "].position = " << x << "," << y << "," << z << std::endl;

        std::cout << "objectLights[" << i << "] -> " <<
              "light[" << index1 << "].light_power = " << objectLights[i]->GetLightPower() << std::endl;
    
        SetVector(uniformVariable[index], objectLights[i]->GetLightColor());

        SetVector(uniformVariable[index2], objectLights[i]->GetLightPosition());

        SetFloat(uniformVariable[index1], objectLights[i]->GetLightPower());
       
      
    }
}

