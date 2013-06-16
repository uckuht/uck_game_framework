#ifndef PROT_EMACRO_H_INCLUDED
#define PROT_EMACRO_H_INCLUDED
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-28
// Desc:
//============================================================================//
//============================================================================//
// Оформление
#define mOLDCODE(date)
#define mBLOCK(text)
#define UNSAFE ;

// Отладка
#   define mDEBUG_BREAK
#   define mDEBUG_BREAK_ERROR

// Логирование
#ifdef E_LOG_CONSOLE
# include <iostream>
#   define mLOG(text)       std::cout<<'\n'<<text
#else
#   define mLOG(text)
#endif // E_LOG_CONSOLE

#   define mLOGWARN(text)               mLOG("!WARNING          "<<text)        // следует обратить внимание, может приводить к ошибкам
#   define mLOGIMPWARN(text)            mLOG("!No implementation"<<text)        // следует обратить внимание, может приводить к ошибкам
#   define mLOGERROR(text)              mLOG("!ERROR            "<<text)        // ошибка обработана
#   define mLOG_CRASH_ERROR(text)       mLOG("!CRASH ERROR      "<<text)        // если ошибка вероятно приведет к падению
#   define mLOG_CRITICAL_ERROR(text)    mLOG("!CRITICAL ERROR   "<<text)        // если нет смысла больше
#   define mLOGDEV(text)                mLOG("##text## = "<<text)
#   define mLOGNOTIFY(text)
#   define mLOGTODO(text)

//============================================================================//
//============================================================================//
#endif // PROT_EMACRO_H_INCLUDED
