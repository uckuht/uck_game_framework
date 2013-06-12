#ifndef PROT_EMACRO_H_INCLUDED
#define PROT_EMACRO_H_INCLUDED
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-28
// Desc:

// Оформление
#define mOLDCODE(date)
#define mBLOCK(text)
#define UNSAFE ;

// Логирование
#ifdef E_LOG_CONSOLE
# include <iostream>
#   define mLOG(text)       std::cout<<'\n'<<text
#else
#   define mLOG(text)
#endif // E_LOG_CONSOLE

#   define mLOGWARN(text)   mLOG("!WARNING "<<text)
#   define mLOGERROR(text)  mLOG("!ERROR   "<<text)
#   define mLOGDEV(text)    mLOG("##text## = "<<text)
#   define mLOGNOTIFY(text)
#   define mLOGTODO(text)   mLOG("!TODO "        <<text)

#endif // PROT_EMACRO_H_INCLUDED
