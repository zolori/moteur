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

void Program::BindTexture(GLuint texture, uint unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
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
        AddUniformVar((newPt + ".color").c_str());
        AddUniformVar((newPt + ".position").c_str());
        AddUniformVar((newPt + ".power").c_str());
    }
}

void Program::UpdateLights(std::vector<Light*> objectLights)
{
    
    int i;
    int gap = 4;
    int index = 0;
 
    /*
    for (int i = 0; i < uniformVariable.size(); i++)
    {
        std::cout << i << ": " << uniformVariable[i] << std::endl;
    }
    
    GLuint p0Color = glGetUniformLocation(num, (newPt+".color").c_str());
    GLuint p0Position = glGetUniformLocation(num, (newPt + ".position").c_str());
    GLuint p0Power = glGetUniformLocation(num, (newPt + ".power").c_str());

    SetVector(p0Color, objectLights[0]->GetLightColor());
    SetVector(p0Position, objectLights[0]->GetLightPosition());
    SetFloat(p0Power, objectLights[0]->GetLightPower());

    std::string testPt = "pointLights[1]";*/

    /*
    GLuint p1Color = glGetUniformLocation(num, (testPt + ".color").c_str());
    GLuint p1Position = glGetUniformLocation(num, (testPt + ".position").c_str());
    GLuint p1Power = glGetUniformLocation(num, (testPt + ".power").c_str());

    SetVector(p1Color, objectLights[1]->GetLightColor());
    SetVector(p1Position, objectLights[1]->GetLightPosition());
    SetFloat(p1Power, objectLights[1]->GetLightPower());

    
    std::string test2Pt = "pointLights[2]";

    GLuint p3Color = glGetUniformLocation(num, (test2Pt + ".color").c_str());
    GLuint p3Position = glGetUniformLocation(num, (test2Pt + ".position").c_str());
    GLuint p3Power = glGetUniformLocation(num, (test2Pt + ".power").c_str());

    SetVector(p3Color, objectLights[2]->GetLightColor());
    SetVector(p3Position, objectLights[2]->GetLightPosition());
    SetFloat(p3Power, objectLights[2]->GetLightPower());
    */

    /*
    SetVector(uniformVariable[4], objectLights[0]->GetLightPosition());
    SetFloat(uniformVariable[5], objectLights[0]->GetLightPower());
    SetVector(uniformVariable[6], objectLights[0]->GetLightColor());

    SetVector(uniformVariable[7], objectLights[1]->GetLightColor());
    SetVector(uniformVariable[9], objectLights[1]->GetLightPosition());
    SetFloat(uniformVariable[8], objectLights[1]->GetLightPower());*/

   
    for (i=0; i < objectLights.size(); i++)
    {
        index += 3;
        int index1 = index + 1;
        int index2 = index + 2;
     
        SetVector(uniformVariable[index], objectLights[i]->GetLightColor());
        SetVector(uniformVariable[index1], objectLights[i]->GetLightPosition());
        SetFloat(uniformVariable[index2], objectLights[i]->GetLightPower());
    }  
}

