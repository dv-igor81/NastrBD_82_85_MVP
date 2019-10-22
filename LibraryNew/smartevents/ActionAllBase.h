//#pragma once
#ifndef __ACTION_ALL_BASE_H
#define __ACTION_ALL_BASE_H

#include "IArguments.h"
#include "IContainer.h"

// Максимальное количество ссылок-событий (объектов ActionEventBase) внутри подписчика/обработчика (ActionSelfBase)
#define MAX_SIZE_LINK_EVENT 10

// Максимальное количество ссылок-подписчика/обработчика (объектов ActionSelfBase) внутри события (ActionEventBase)
#define MAX_SIZE_LINK_SELF 10

// Макс. длина сообщений (шаблонные классы ActionSelf и ActionEvent)
#define MAX_SIZE_FOR_ACTION_TEXT_LENGTH 250

#endif // #ifndef __ACTION_ALL_BASE_H