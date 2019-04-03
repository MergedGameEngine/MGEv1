///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#include "GLee.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "ShaderObject.hpp"

_RENDERER_API TShaderObject::TShaderObject() {
	currentParam = 0;
	vertexProgramText = NULL;
	fragmentProgramText = NULL;
	geometryProgramText = NULL;
	fragmentShaderIndex = 0xFFFFFFFF;
	vertexShaderIndex = 0xFFFFFFFF; 
	programIndex = 0xFFFFFFFF; 
	validated = FALSE;
	parameters.Resize(0);
}

_RENDERER_API TShaderObject::~TShaderObject() {
	parameters.DeleteAll();
	parameters.Resize(0);
}

char _RENDERER_API *TShaderObject::GetClassName() {
	return "TShaderObject";
}

int _RENDERER_API TShaderObject::GetClassCode() {
	return CLSID_TShaderObject;
}

int _RENDERER_API TShaderObject::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TShaderObject::IsInstanceof(const char* className) {
	if (strcmp("TShaderObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TShaderObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TShaderObject::Serialize(IIOStream &iio) {
}

void _RENDERER_API TShaderObject::Wait() {
}

void _RENDERER_API TShaderObject::Notify() {
}


void _RENDERER_API TShaderObject::SetVertexShaderText(GLchar *text) {
	vertexProgramText = text;
}
void _RENDERER_API TShaderObject::CreateVertexShader() {
	vertexShaderIndex = glCreateShader(GL_VERTEX_SHADER);
}
void _RENDERER_API TShaderObject::VertexShaderSource() {
	glShaderSource(vertexShaderIndex, 1, (const GLchar**)&vertexProgramText, NULL);
}
void _RENDERER_API TShaderObject::CompileVertexShader() {
	glCompileShader(vertexShaderIndex);
}
GLint _RENDERER_API TShaderObject::GetVertexShaderStatus() {
	GLint success;
	glGetShaderiv(vertexShaderIndex, GL_COMPILE_STATUS, &success);
	return success;
}


void _RENDERER_API TShaderObject::SetFragmentShaderText(GLchar *text) {
	fragmentProgramText = text;
}
void _RENDERER_API TShaderObject::CreateFragmentShader() {
	fragmentShaderIndex = glCreateShader(GL_FRAGMENT_SHADER);
}
void _RENDERER_API TShaderObject::FragmentShaderSource() {
	glShaderSource(fragmentShaderIndex, 1, (const GLchar**)&fragmentProgramText, NULL);
}
void _RENDERER_API TShaderObject::CompileFragmentShader() {
	glCompileShader(fragmentShaderIndex);
}
GLint _RENDERER_API TShaderObject::GetFragmentShaderStatus() {
	GLint success;
	glGetShaderiv(fragmentShaderIndex, GL_COMPILE_STATUS, &success);
	return success;
}

void _RENDERER_API TShaderObject::DeleteProgram() {
	glDeleteProgram(programIndex);
}
void _RENDERER_API TShaderObject::DeleteVertexShader() {
	glDeleteShader(vertexShaderIndex);
}
void _RENDERER_API TShaderObject::DeleteFragmentShader() {
	glDeleteShader(fragmentShaderIndex);
}


void _RENDERER_API TShaderObject::CreateProgram() {
	programIndex = glCreateProgram();
}
void _RENDERER_API TShaderObject::AttachVertexShader() {
	glAttachShader(programIndex, vertexShaderIndex);
}
void _RENDERER_API TShaderObject::AttachFragmentShader() {
	glAttachShader(programIndex, fragmentShaderIndex);
}
void _RENDERER_API TShaderObject::LinkProgram() {
	glLinkProgram(programIndex);
}
GLint _RENDERER_API TShaderObject::GetProgramStatus(GLenum pname) {
	GLint success;
	glGetProgramiv(programIndex, pname, &success);
	return success;
}
void _RENDERER_API TShaderObject::ValidateProgram() {
	glValidateProgram(programIndex);
}


void _RENDERER_API TShaderObject::PrepareShader(GLint &vss, GLint &fss, GLint &lps, GLint &vps) {

	vertexShaderIndex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderIndex, 1, (const GLchar**)&vertexProgramText, NULL);
    glCompileShader(vertexShaderIndex);
    glGetShaderiv(vertexShaderIndex, GL_COMPILE_STATUS, &vss);
	if (!vss) {
		return;
	}

	fragmentShaderIndex = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderIndex, 1, (const GLchar**)&fragmentProgramText, NULL);
    glCompileShader(fragmentShaderIndex);
    glGetShaderiv(fragmentShaderIndex, GL_COMPILE_STATUS, &fss);
	if (!fss) {
		return;
	}

	programIndex = glCreateProgram();
	glAttachShader(programIndex, vertexShaderIndex);
	glAttachShader(programIndex, fragmentShaderIndex);

//	glBindAttribLocationARB(rShaders[0].programIndex, 0, "position");

	glLinkProgram(programIndex);
	glGetProgramiv(programIndex, GL_LINK_STATUS, &lps);
	if (!lps) {
		return;
	}

	validated = FALSE;
    glValidateProgram(programIndex);
 	glGetProgramiv(programIndex, GL_VALIDATE_STATUS, &vps);
	if (!vps) {
		return;
    }
	validated = TRUE;

	vertexProgramText = NULL;
	fragmentProgramText = NULL;
}


void _RENDERER_API TShaderObject::CreateParameters(unsigned int num) {
	parameters.Resize(num);
	parameters.CreateAll();
}
void _RENDERER_API TShaderObject::AddParameter(TString &key, GLchar *pname, unsigned short pcode) {
	parameters[currentParam].SetName(pname);
	parameters[currentParam].SetCode(pcode);
	parameters[currentParam].SetLocation(programIndex);
	paramIndices.Add(key, &parameters[currentParam]);
	currentParam ++;
	currentParam = currentParam % (parameters.GetLength());
}
void _RENDERER_API TShaderObject::SetParameter(TString &key, GLint value) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_uniform_diffuse_map :
			case TShaderParameter::sp_uniform_normal_map :
			case TShaderParameter::sp_uniform_height_map :
			case TShaderParameter::sp_uniform_cube_map :
				glUniform1i(param.GetLocation(), value);
				break;
			case TShaderParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), 1, &value);
				break;
			default :
				break;
		}
	}
}
void _RENDERER_API TShaderObject::SetParameter(TString &key, void *value) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_uniform_diffuse_map :
			case TShaderParameter::sp_uniform_normal_map :
			case TShaderParameter::sp_uniform_height_map :
			case TShaderParameter::sp_uniform_cube_map :
				{
					GLint ivalue = *(GLint*)value;
					glUniform1i(param.GetLocation(), ivalue);
				}
				break;
			case TShaderParameter::sp_uniform_camera_position :
			case TShaderParameter::sp_uniform_model_position :
				glUniform4fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_view_matrix44 :
			case TShaderParameter::sp_uniform_view_invmatrix44 :
			case TShaderParameter::sp_uniform_project_matrix44 :
			case TShaderParameter::sp_uniform_project_invmatrix44 :
			case TShaderParameter::sp_uniform_world_matrix44 :
			case TShaderParameter::sp_uniform_world_invmatrix44 :
			case TShaderParameter::sp_uniform_model_matrix44 :
			case TShaderParameter::sp_uniform_model_invmatrix44 :
				glUniformMatrix4fv(param.GetLocation(), 1, GL_FALSE, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_light_position :
				glUniform3fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), 1, (GLint*)value);
				break;
			case TShaderParameter::sp_uniform_custom_float :
				glUniform1fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector2 :
				glUniform2fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector3 :
				glUniform3fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector4 :
				glUniform4fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix22 :
				glUniformMatrix2fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix33 :
				glUniformMatrix3fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix44 :
				glUniformMatrix4fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			default :
				break;
		}
	}
}
void _RENDERER_API TShaderObject::SetParameter(TString &key, GLsizei num, GLboolean transpose, void *value) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_uniform_light_positions :
				glUniform3fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), num, (GLint*)value);
				break;
			case TShaderParameter::sp_uniform_custom_float :
				glUniform1fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector2 :
				glUniform2fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector3 :
				glUniform3fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_vector4 :
				glUniform4fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix22 :
				glUniformMatrix2fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix33 :
				glUniformMatrix3fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			case TShaderParameter::sp_uniform_custom_matrix44 :
				glUniformMatrix4fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			default :
				break;
		}
	}
}
void _RENDERER_API TShaderObject::SetParameter(TString &key, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_attribute_vertex :
			case TShaderParameter::sp_attribute_normal :
			case TShaderParameter::sp_attribute_tangent :
			case TShaderParameter::sp_attribute_binormal :
				glVertexAttribPointer(param.GetLocation(), 3, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_texcoord :
				glVertexAttribPointer(param.GetLocation(), 2, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_custom_int :
				glVertexAttribPointer(param.GetLocation(), 1, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_custom_float :
				glVertexAttribPointer(param.GetLocation(), 1, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_custom_vector2 :
				glVertexAttribPointer(param.GetLocation(), 2, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_custom_vector3 :
				glVertexAttribPointer(param.GetLocation(), 3, type, normalized, stride, pointer);
				break;
			case TShaderParameter::sp_attribute_custom_vector4 :
				glVertexAttribPointer(param.GetLocation(), 4, type, normalized, stride, pointer);
				break;
			default :
				break;
		}
	}
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, float *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform1fv(location, num, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, TexCoord2f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform2fv(location, num, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, Vector3f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform3fv(location, num, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, Vector4f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform4fv(location, num, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLint value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform1i(location, value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix22f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix2fv(location, num, transpose, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix33f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix3fv(location, num, transpose, (GLfloat*)value);
}
void _RENDERER_API TShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix44f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix4fv(location, num, transpose, (GLfloat*)value);
}

void _RENDERER_API TShaderObject::EnableVertexAttribArray(TString &key) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_attribute_vertex :
			case TShaderParameter::sp_attribute_normal :
			case TShaderParameter::sp_attribute_tangent :
			case TShaderParameter::sp_attribute_binormal :
			case TShaderParameter::sp_attribute_texcoord :
			case TShaderParameter::sp_attribute_custom_int :
			case TShaderParameter::sp_attribute_custom_float :
			case TShaderParameter::sp_attribute_custom_vector2 :
			case TShaderParameter::sp_attribute_custom_vector3 :
			case TShaderParameter::sp_attribute_custom_vector4 :
				glEnableVertexAttribArray(param.GetLocation());
				break;
			default :
				break;
		}
	}
}
void _RENDERER_API TShaderObject::DisableVertexAttribArray(TString &key) {
	TShaderParameter *pParam = (TShaderParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		TShaderParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case TShaderParameter::sp_attribute_vertex :
			case TShaderParameter::sp_attribute_normal :
			case TShaderParameter::sp_attribute_tangent :
			case TShaderParameter::sp_attribute_binormal :
			case TShaderParameter::sp_attribute_texcoord :
			case TShaderParameter::sp_attribute_custom_int :
			case TShaderParameter::sp_attribute_custom_float :
			case TShaderParameter::sp_attribute_custom_vector2 :
			case TShaderParameter::sp_attribute_custom_vector3 :
			case TShaderParameter::sp_attribute_custom_vector4 :
				glDisableVertexAttribArray(param.GetLocation());
				break;
			default :
				break;
		}
	}
}



void _RENDERER_API TShaderObject::UseProgram() {
	glUseProgram(programIndex);
}
void _RENDERER_API TShaderObject::UnuseProgram() {
	glUseProgram(0);
}


TRefArray<TShaderParameter> _RENDERER_API &TShaderObject::GetParameters() {
	return parameters;
}
