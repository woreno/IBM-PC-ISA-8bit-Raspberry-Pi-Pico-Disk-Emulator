#ifdef UI_USE_OLD_BUTTONS

	#ifdef UI_DEBUG_BUTTONS
		const SW8* uiButtonStrs[] = {"U", "L", "R", "D", "ENT", "ESC", "NO"};
	#endif 
	
	#define UI_BUTTONS_THRESH_DEF(X_)\
	X_(UI_BUTTON_UP    ,  13788 , 0      , 192368   ,    0 )\
	X_(UI_BUTTON_LEFT  ,  0    , 0       , 0        ,    0 )\
	X_(UI_BUTTON_RIGHT ,  0    , 0       , 0        ,    0 )\
	X_(UI_BUTTON_DOWN  ,  13342 , 0      , 1611854  ,    0 )\
	X_(UI_BUTTON_ENTER ,  13463 , 0      , 492002   ,    0 )\
	X_(UI_BUTTON_ESC   ,  14098 , 0      , 859375   ,    0 )
		//			   media   desvio max.   media   desvio max.
		//             \________________/    \________________/
		//                 sinal low             sinal hi

	#define UI_BUTTONS_TEST_ARR_(BUT_, LOW_, LOWVAR_, HI_, HIVAR_)  \
			{LOW_, HI_},
	#define UI_BUTTONS_TEST_COND   UI_BUTTONS_THRESH_DEF(UI_BUTTONS_TEST_COND_)
	W32 uiButtonsAv[][2] = {UI_BUTTONS_THRESH_DEF(UI_BUTTONS_TEST_ARR_) };

#endif