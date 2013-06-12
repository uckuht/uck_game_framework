#ifndef PROT_RENDER_H_INCLUDED
#define PROT_RENDER_H_INCLUDED
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: Конфигурационный файл для автоматического подключения модуля рендера.
//============================================================================//

// Под винду по умолчанию подключается DX9c но это можно изменить настройкой E_R_OGL
#ifdef E_P_WIN
#   ifdef E_R_OGL
#       
#   else
#       include "RENDER/RENDER_DX/EC_RENDER.h"
#   endif
#endif

#endif // PROT_RENDER_H_INCLUDED
