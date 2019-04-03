#ifndef _COREIMPORT_H_
#define _COREIMPORT_H_

#include "../Core/EventFilter.h"
#include "../Core/EventListener.h"
#include "../Core/EventProcessor.h"
#include "../Core/AnimationController.h"
#include "../Core/ModelController.h"
#include "../Core/Animator.h"
#include "../Core/Section.h"
#include "../Core/Area.h"
#include "../Core/Level.h"
#include "../Core/TWindow.h"
#include "../Core/Core.h"

#ifdef _ARRAY_API
#ifdef TArray
extern "C" template class _BASE_API TArray<TEvent>;
extern "C" template class _BASE_API TArray<TMessage>;
#endif
#ifdef TRefArray
extern "C" template class _BASE_API TRefArray<TEventListener>;
extern "C" template class _BASE_API TRefArray<TEventProcessor>;
extern "C" template class _BASE_API TRefArray<TAnimationController>;
extern "C" template class _BASE_API TRefArray<TModelController>;
extern "C" template class _BASE_API TRefArray<TAnimator>;
extern "C" template class _BASE_API TRefArray<TSection>;
extern "C" template class _BASE_API TRefArray<TArea>;
extern "C" template class _BASE_API TRefArray<TLevel>;
extern "C" template class _BASE_API TRefArray<TWindow>;
#endif
#endif

#endif