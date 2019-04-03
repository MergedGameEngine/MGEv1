#ifndef _TEMPMODEL_H_
#define _TEMPMODEL_H_

GLchar *LoadShaderText(const char *fileName);
void LoadMesh(TModelGlobal &mobj);
void LoadAni1(TModelGlobal &mani);
void LoadAni2(TModelGlobal &mani);
void DoAni(TModel &mdl, TAnimationController &ac, TAnimationController &wac);

#endif