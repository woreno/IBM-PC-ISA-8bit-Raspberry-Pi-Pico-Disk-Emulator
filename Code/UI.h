UI_SIMPLE_PAGE		*ui_main_page;
UI_PAGE_SOURCE_LIST *ui_files_page;
 
W8					ui_curr_drive  = 0;

FS_Source			*ui_file_page_source;
UI_ITEM_VALUE		ui_main_page_itemValues[3];

W0 ui_init_progressBar()
{
	const W16 uiProgressBarWidth = 40;
	Ret uiProgressBar = Ret(uiProgressBarWidth, DISP_HEIGHT-12, DISP_WIDTH-uiProgressBarWidth*2, 2);
	uiProgressBar.expand(4);
	draw_rect(uiProgressBar, Color_Black);
	uiProgressBar.expand(-2);
	draw_rect(uiProgressBar, Color_White);
	DRAW_UPDATE
}
W8 ui_icon_attrib_fx(FatEntry* e_)
{
	if (e_->isUpperDir()) return ICON_NONE;
	if (e_->isDir()) return ICON_FOLDER;
	e_->ext[0]=tolower(e_->ext[0]);
	e_->ext[1]=tolower(e_->ext[1]);
	e_->ext[2]=tolower(e_->ext[2]);
	if (strncmp((SW8*)(e_->ext), "ima", 3)==0) return ICON_FLOPPY;
	return ICON_FILE;	
}

W0 ui_set_drive_operation_icons(W8 driveId_, W32 function_)
{
	idleTimer = 0;

	// mesma operacao
	if ((ui_drives_last_used==driveId_) &&  ui_drives_last_operation==function_)
	{
		return;
	}

	W1 firstTime = ui_drives_first_time == true;
	W1 sameDrive = driveId_ == ui_drives_last_used;

	ui_drives_first_time		= 0;
	ui_drives_last_operation	= function_;
	ui_drives_last_used			= driveId_;

	

	W32 width = (DISP_WIDTH/3);
	Ret r(0, 45, width, 20);
	
	r.expand(-3);

	if (firstTime)
	{
		draw_clear(0xFFFF);
		draw_centered_icon<3>((*DISK_FLAG_DRVA_IS_PHYSICAL)?ICON_FDD:ICON_FLOPPY, -52,-18, false);
		draw_centered_icon<3>((*DISK_FLAG_DRVB_IS_PHYSICAL)?ICON_FDD:ICON_FLOPPY  ,   0,-18, false);
		draw_centered_icon<3>(ICON_HDD,     52,-18, (*DISK_FLAG_DRVC_EXISTS)?false:true);
	}

	W8  rStart= r.x;
	if (firstTime || !sameDrive)
	{
		for (W32 i=0; i< 3; i++, r.x+=width)
			draw_rect(r, Color_GrayLight);  
	}
	r.x = rStart + width * driveId_;
	draw_rect(r, (function_==3)? Color_Red : Color_Green);
	

	if (firstTime || !sameDrive)
	{
		if (!firstTime && !sameDrive)
		{
			// apagar o debaixo
			Ret rBig(0, 61, DISP_WIDTH, DISP_HEIGHT-61);
			draw_rect(rBig, Color_White);
		}
		SW8 str[64];
		sprintf(str, "%s %s", drives[driveId_].letter, drives[driveId_].name);
		draw_text_centered(-1, 78, str);
	}

	turnDisplay();

	DRAW_UPDATE
	
		/*
	if (firstTime)
	{
		DRAW_UPDATE
	}
	else
	{
		if (sameDrive)
		{
			DRAW_UPDATE_RRECT(r);
		}
		else
		{
			DRAW_UPDATE_RRECT(rBig);
		}
	}*/
	
	turnSD();
}
W0 ui_unset_drive_operation_icons()
{
	if (++idleTimer == 500000) 
	{ 
		ui_drives_last_used = -1;
		ui_drives_last_operation = -1;
		ui_drives_first_time = 1;
		ui_main_page->draw();
		turnDisplay(); 
		DRAW_UPDATE
		turnSD();
	}

}

W0  ui_draw_wait()
{
	turnDisplay();
		draw_clear(0xFFFF);
		draw_text_centered(-1, -1, str_wait);
		DRAW_UPDATE
	turnSD();

}
W1	ui_draw_sd_question_mark = true;
W8  ui_draw_sd_question(W1 sd_)
{
	turnDisplay();
	draw_clear(0xFFFF);
	
		if (sd_)
		{
			draw_text_centered(-1, 75, ui_strs_sd);
			draw_centered_icon<3>(ICON_SD,-5,-13);
		}
		else
		{
			draw_text_centered(-1, 75, ui_strs_fs);
			draw_centered_icon<3>(ICON_FOLDER,-5,-13);
		}
		if (ui_draw_sd_question_mark) 
		{
			//draw_text_centered(-1, 17, "?");
			draw_centered_icon<2>(ICON_QUESTION,+15,+3);
		}
		DRAW_UPDATE
		ui_draw_sd_question_mark=!ui_draw_sd_question_mark;
		
	turnSD();
	return 0;
}

//////////////////////////////////////////////////////////////////////
W0 ui_update_main_page()
{
	for (W32 i=0; i< 3; i++)
	{
		UI_ITEM_VALUE *itemValue = ui_main_page->cachedItems[i].value;

		itemValue->type = UI_ITEM_VALUE_STRING;

		if (i<2)
		{
			if (drives[i].type == Drive::DISK_TYPE_FD_PHYSICAL)
				itemValue->valuePtr = (W0*)str_is_physical;
			else
				itemValue->valuePtr = (W0*)drives[i].name;
		}
		else
		{
			if (*DISK_FLAG_DRVC_EXISTS)
			{
				if (*DISK_FLAG_DRVC_USE)	
					itemValue->valuePtr = (W0*)str_hdd_name;
				else
					itemValue->valuePtr = (W0*)str_dont_use;
			}
			else
				itemValue->valuePtr = (W0*)str_not_found;
		}
	}
	turnDisplay();
		ui_main_page->draw();
		DRAW_UPDATE
	turnSD();
}
W0 ui_files_page_fdd_hit_filename(UI_ITEM* item_)
{
	std::string path = ui_file_page_source->get_current_full_path() + "/" + std::string(item_->name);
	
	drives[ui_curr_drive].init(path);
	
	//printf("\nSELECTED! currDrive:%i path:%s", ui_curr_drive,  path.c_str());
	
	ui_draw_wait();
	DELAY_MS(100);
	uiCurrPage = ui_main_page;
	ui_update_main_page();
}
W0 ui_create_files_page()
{
	turnSD();	 
		fs_getRootDirNode(&rootNode);
	
		ui_file_page_source = new FS_Source(ui_icon_attrib_fx);
		if (!ui_file_page_source) fatal(UI, UI_ERROR_ALLOC);

		ui_file_page_source->page = FS_Source::FS_Source_DirPage;
		ui_file_page_source->initAsFSNode(&rootNode);
		ui_file_page_source->fxBeforeSourceAccess = turnSD;
		ui_file_page_source->fxAfterSourceAccess  = turnDisplay;

		ui_files_page = new UI_PAGE_SOURCE_LIST();
		if (!ui_files_page) fatal(UI, UI_ERROR_ALLOC);
		ui_files_page->init(ui_file_page_source, ui_files_page_fdd_hit_filename); 
}
W0 ui_create_pages()
{ 
	ui_main_page	 = new UI_SIMPLE_PAGE();

	if (!ui_main_page) fatal(UI, UI_ERROR_ALLOC);

	ui_create_files_page();
	if (!ui_files_page) fatal(UI, UI_ERROR_ALLOC); 
	
	ui_main_page->init("Emulator", 3);
	ui_main_page->addItem("A:",	&ui_main_page_itemValues[0]);
	ui_main_page->addItem("B:",	&ui_main_page_itemValues[1]);
	ui_main_page->addItem("C:", &ui_main_page_itemValues[2]);
	
	ui_main_page->cachedItems[0].setIcon(ICON_FLOPPY);
	ui_main_page->cachedItems[1].setIcon(ICON_FLOPPY);
	ui_main_page->cachedItems[2].setIcon(ICON_HDD);
	
	ui_update_main_page();

}


W0  ui_display_int19h()
{
	SW8 str[128];
	W8 lastBootFlag;
	while(1)
	{
		lastBootFlag = *DISK_FLAG_BOOT;
		switch(*DISK_FLAG_BOOT)
		{
			case 1:
			case 2:
				draw_centered_icon<3>(ICON_FLOPPY,-20);
			break;
			case 3: 
				draw_centered_icon<3>(ICON_HDD,-20);
			break;
		};
		
		switch(*DISK_FLAG_BOOT)
		{
			case 0:
				draw_centered_icon<3>(ICON_QUESTION);
			break;
			case 1: case 2: case 3:
			{
				SW32 drive = *DISK_FLAG_BOOT-1;
				sprintf(str, "Boot from %s?", 
					( (drive==0)?"FDD0":(drive==1?"FDD1":"HDD")));
				draw_text_centered(-1, 75, str);
				draw_centered_icon<3>(ICON_QUESTION,+20,0);
				break;
			}
		};
	}
}

W0  ui_menus_update(SW32 x, SW32 y)
{
	UI_BUTTONS	ui_newAction = UI_BUTTON_NONE;
	if (x < 100 )
		ui_newAction =  UI_BUTTON_LEFT;
	else if (x > 2000)
		ui_newAction = UI_BUTTON_RIGHT;
	if (y < 100  )
		ui_newAction = UI_BUTTON_DOWN ;
	else if (y > 2000)
		ui_newAction = UI_BUTTON_UP;

	
	if (ui_newAction==UI_BUTTON_NONE) return;
	
	//printf("\nACTION");


	turnDisplay();
	if (uiCurrPage==ui_files_page) //menu inicial
	{
		switch(ui_newAction)
		{
			case UI_BUTTON_LEFT:
				uiCurrPage = ui_main_page;
			break;
			default:
				uiCurrPage->action(ui_newAction);
			break;
		}
	}
	else
	{
		switch(ui_newAction)
		{
			case UI_BUTTON_UP:
			case UI_BUTTON_DOWN:
				uiCurrPage->action(ui_newAction);
				ui_curr_drive = uiCurrPage->offset;
			break;

			case UI_BUTTON_RIGHT:
			case UI_BUTTON_ENTER:
				if (ui_curr_drive == 2)	
				{
					*DISK_FLAG_DRVC_USE=!(W1)(*DISK_FLAG_DRVC_USE);
					ui_update_main_page();
				}
				else
				{
					if (!fs_isRootDirNode(&rootNode))
					{
						//printf("\nReset Dir");
						ui_draw_wait();
						fs_getRootDirNode(&rootNode);
					}
					else
					{
						//printf("\nDir Not reset");
					}
					ui_file_page_source->initAsFSNode(&rootNode);
					ui_files_page->init(ui_file_page_source, ui_files_page_fdd_hit_filename); 

					turnDisplay();
					uiCurrPage = (UI_PAGE*)ui_files_page;
				}
			break;
			case UI_BUTTON_LEFT:
			{
				if ((ui_curr_drive) == 2 && (*DISK_FLAG_DRVC_EXISTS))	
				{
					*DISK_FLAG_DRVC_USE=!(W1)(*DISK_FLAG_DRVC_USE);
				}
				else
				{
					drives[ui_curr_drive].initPhysical();
				}
				ui_update_main_page();
			}
			break;
		}
	} 

	ui_newAction=UI_BUTTON_NONE;
	uiCurrPage->draw();
	DRAW_UPDATE
	DELAY_MS(40);
}























W0 ui_debug_icons()
{
	#ifdef UI_DEBUG_ICONS
		W8 i = 0;
		W8 y = DRAW_ICON_SIZE;
		W8 x = DRAW_ICON_SIZE;
		while(1)
		{
			draw_icon<1>(x, y, (ICON)i);
			x+=DRAW_ICON_SIZE;
			if (x > DISP_WIDTH-DRAW_ICON_SIZE) {  y+=DRAW_ICON_SIZE; }
			
			DRAW_UPDATE
			DELAY_MS(1000);
			i++;
			if (i==ICON_NONE) break;
		}
	#endif
}