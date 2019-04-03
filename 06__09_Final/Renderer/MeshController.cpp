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
#include "ViewPort.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "MeshController.hpp"

_RENDERER_API TMeshController::TMeshController() {
	meshes.Resize(0);
}

_RENDERER_API TMeshController::~TMeshController() {
	meshes.DeleteAll();
	meshes.Resize(0);
}

char _RENDERER_API *TMeshController::GetClassName() {
	return "TMeshController";
}

int _RENDERER_API TMeshController::GetClassCode() {
	return CLSID_TMeshController;
}

int _RENDERER_API TMeshController::GetHashCode() {
	return 1;
}

BOOL32 _RENDERER_API TMeshController::IsInstanceof(const char* className) {
	if (strcmp("TMeshController", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _RENDERER_API TMeshController::IsEqualto(IObject &obj) {
	return FALSE;
}

void _RENDERER_API TMeshController::Serialize(IIOStream &iio) {
}

void _RENDERER_API TMeshController::Wait() {
}

void _RENDERER_API TMeshController::Notify() {
}

void _RENDERER_API TMeshController::RenderUnit(TTextureController &tc, TLightController &lc, TShaderController &sc, TViewPort &vp) {
	unsigned int numeshes = meshes.GetLength();
	TShaderObject *so = NULL;
	TTextureObject *to = NULL;
	TLightObject *lo = NULL;
	TMeshObject *mo = NULL;
	for ( unsigned int i1 = 0 ; i1 < numeshes ; i1 ++ ) {
		mo = &meshes[i1];
		so = (TShaderObject*)sc.shaderIndices.Get(mo->shaderName);
		so->UseProgram();
		unsigned int numtextures = mo->textureNames.GetLength();
		for ( unsigned int i2 = 0 ; i2 < numtextures ; i2 ++ ) {
			to = (TTextureObject*)tc.textureIndices.Get(mo->textureNames[i2]);
			to->ActiveTexture();
			to->BindTexture();
			so->SetParameter(to->typeName, to->GetIndex());
		}
		tc.ActiveTexture0();
		unsigned int numlights = mo->lightNames.GetLength();
		for ( unsigned int i3 = 0 ; i3 < numlights ; i3 ++ ) {
			lo = (TLightObject*)lc.lightIndices.Get(mo->lightNames[i3]);
			so->SetParameter(lo->directionParamName, &lo->direction);
			so->SetParameter(lo->halfAngleParamName, &lo->halfAngle);
		}
		so->SetParameter(vp.imvParamName, 1, GL_FALSE, &vp.imvParamName);
		so->SetParameter(mo->boneMatrixParamName, mo->GetNumBoneMatrices(), TRUE, mo->GetBoneMatricesBuffer());
//======
	//	glEnableVertexAttribArray(vertexAttrib);
	//	glEnableVertexAttribArray(normalAttrib);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if ( mo->HasTangents() ) {
			so->EnableVertexAttribArray(mo->tangentParamName);
		}
		if ( mo->HasBinormals() ) {
			so->EnableVertexAttribArray(mo->binormalParamName);
		}
		so->EnableVertexAttribArray(mo->texCoordParamName);
		if ( mo->HasBoneIndices() ) {
			so->EnableVertexAttribArray(mo->boneIndexParamName);
		}
		if ( mo->HasWeights() ) {
			so->EnableVertexAttribArray(mo->vertexWeightParamName);
		}

		mo->BindVerticesBuffer();
		glVertexPointer(3, GL_FLOAT, 0, 0);
		//glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mo->BindNormalsBuffer();
		glNormalPointer(GL_FLOAT, 0, 0);
		//glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if ( mo->HasTangents() ) {
			mo->BindTangentsBuffer();
			so->SetParameter(mo->tangentParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		if ( mo->HasBinormals() ) {
			mo->BindBinormalsBuffer();
			so->SetParameter(mo->binormalParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		// Texture coordinates
		mo->BindTexCoordsBuffer();
		so->SetParameter(mo->texCoordParamName, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		// Bone Indices
		if ( mo->HasBoneIndices() ) {
			mo->BindBoneIndicesBuffer();
			so->SetParameter(mo->boneIndexParamName, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, NULL);
		}
		// Vertex Weights
		if ( mo->HasWeights() ) {
			mo->BindVertexWeightsBuffer();
			so->SetParameter(mo->vertexWeightParamName, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		// Indexes
		mo->BindIndicesBuffer();
	//	glDrawArrays(GL_TRIANGLES, 0, bodyData->GetNumTriangles() * 3);
	//	glDrawElements(GL_TRIANGLES, bodyData->GetNumTriangles() * 3, GL_UNSIGNED_SHORT, 0);
		glDrawElements(GL_TRIANGLES, mo->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	glDisableVertexAttribArray(vertexAttrib);
	//	glDisableVertexAttribArray(normalAttrib);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		if ( mo->HasTangents() ) {
			so->DisableVertexAttribArray(mo->tangentParamName);
		}
		if ( mo->HasBinormals() ) {
			so->DisableVertexAttribArray(mo->binormalParamName);
		}
		so->DisableVertexAttribArray(mo->texCoordParamName);
		if ( mo->HasBoneIndices() ) {
			so->DisableVertexAttribArray(mo->boneIndexParamName);
		}
		if ( mo->HasWeights() ) {
			so->DisableVertexAttribArray(mo->vertexWeightParamName);
		}

//======
		so->UnuseProgram();
	}
}
void _RENDERER_API TMeshController::RenderUnit(TTextureController &tc, TLightController &lc, TShaderController &sc, TViewPort &vp, TArray<Matrix44f> &bm, TString &pn) {
	unsigned int numeshes = meshes.GetLength();
	TShaderObject *so = NULL;
	TTextureObject *to = NULL;
	TLightObject *lo = NULL;
	TMeshObject *mo = NULL;
	for ( unsigned int i1 = 0 ; i1 < numeshes ; i1 ++ ) {
		mo = &meshes[i1];
		so = (TShaderObject*)sc.shaderIndices.Get(mo->shaderName);
		so->UseProgram();
		unsigned int numtextures = mo->textureNames.GetLength();
		for ( unsigned int i2 = 0 ; i2 < numtextures ; i2 ++ ) {
			to = (TTextureObject*)tc.textureIndices.Get(mo->textureNames[i2]);
			to->ActiveTexture();
			to->BindTexture();
			so->SetParameter(to->typeName, to->GetIndex());
		}
		tc.ActiveTexture0();
		unsigned int numlights = mo->lightNames.GetLength();
		for ( unsigned int i3 = 0 ; i3 < numlights ; i3 ++ ) {
			lo = (TLightObject*)lc.lightIndices.Get(mo->lightNames[i3]);
			so->SetParameter(lo->directionParamName, &lo->direction);
			so->SetParameter(lo->halfAngleParamName, &lo->halfAngle);
		}
		so->SetParameter(vp.imvParamName, 1, GL_FALSE, &vp.imvParamName);
		so->SetParameter(pn, bm.GetLength(), TRUE, (void*)bm.GetBuffer());
//======
	//	glEnableVertexAttribArray(vertexAttrib);
	//	glEnableVertexAttribArray(normalAttrib);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		so->EnableVertexAttribArray(mo->tangentParamName);
		so->EnableVertexAttribArray(mo->binormalParamName);
		so->EnableVertexAttribArray(mo->texCoordParamName);
		so->EnableVertexAttribArray(mo->boneIndexParamName);
		so->EnableVertexAttribArray(mo->vertexWeightParamName);

		mo->BindNormalsBuffer();
		glNormalPointer(GL_FLOAT, 0, 0);
		//glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mo->BindTangentsBuffer();
		so->SetParameter(mo->tangentParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		mo->BindBinormalsBuffer();
		so->SetParameter(mo->binormalParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		// Texture coordinates
		mo->BindTexCoordsBuffer();
		so->SetParameter(mo->texCoordParamName, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		// Vertex Weights
		mo->BindVertexWeightsBuffer();
		so->SetParameter(mo->vertexWeightParamName, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		// Bone Indices
		mo->BindBoneIndicesBuffer();
		so->SetParameter(mo->boneIndexParamName, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, NULL);

		mo->BindVerticesBuffer();
		glVertexPointer(3, GL_FLOAT, 0, 0);
		//glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Indexes
		mo->BindIndicesBuffer();
	//	glDrawArrays(GL_TRIANGLES, 0, bodyData->GetNumTriangles() * 3);
	//	glDrawElements(GL_TRIANGLES, bodyData->GetNumTriangles() * 3, GL_UNSIGNED_SHORT, 0);
		glDrawElements(GL_TRIANGLES, mo->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	glDisableVertexAttribArray(vertexAttrib);
	//	glDisableVertexAttribArray(normalAttrib);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		so->DisableVertexAttribArray(mo->tangentParamName);
		so->DisableVertexAttribArray(mo->binormalParamName);
		so->DisableVertexAttribArray(mo->texCoordParamName);
		so->DisableVertexAttribArray(mo->boneIndexParamName);
		so->DisableVertexAttribArray(mo->vertexWeightParamName);

//======
		so->UnuseProgram();
	}
}
