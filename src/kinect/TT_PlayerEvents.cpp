//
//  TT_PlayerEvents.cpp
//  openNi recorder
//
//  Created by Thomas Eberwein on 19/06/2012.
//  Copyright 2012 Thomas Traum Ltd. All rights reserved.
//

#include <iostream>
#include "TT_PlayerEvents.h"

ofEvent<TT_NewUserEvent>             TT_NewUserDispatcher;
ofEvent<TT_UserLostEvent>            TT_UserLostEventDispatcher;
