///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef __GL_TYPES_H_
#define __GL_TYPES_H_

#ifndef GLchar
typedef char GLchar; 
#endif

#ifndef GLenum
typedef unsigned int GLenum;
#endif

#ifndef GLboolean
typedef unsigned char GLboolean;
#endif

#ifndef GLbitfield
typedef unsigned int GLbitfield;
#endif

#ifndef GLbyte
typedef signed char GLbyte;
#endif

#ifndef GLshort
typedef short GLshort;
#endif

#ifndef GLint
typedef int GLint;
#endif

#ifndef GLsizei
typedef int GLsizei;
#endif

#ifndef GLubyte
typedef unsigned char GLubyte;
#endif

#ifndef GLushort
typedef unsigned short GLushort;
#endif

#ifndef GLuint
typedef unsigned int GLuint;
#endif

#ifndef GLfloat
typedef float GLfloat;
#endif

#ifndef GLclampf
typedef float GLclampf;
#endif

#ifndef GLdouble
typedef double GLdouble;
#endif

#ifndef GLclampd
typedef double GLclampd;
#endif

#ifndef GLvoid
typedef void GLvoid;
#endif

#ifndef _PTRDIFF_T_DEFINED
#ifdef  _WIN64
typedef __int64             ptrdiff_t;
#else
typedef _W64 int            ptrdiff_t;
#endif
#define _PTRDIFF_T_DEFINED
#endif

#ifndef GLintptr
typedef ptrdiff_t GLintptr;
#endif

#ifndef GLsizeiptr
typedef ptrdiff_t GLsizeiptr;
#endif

#endif