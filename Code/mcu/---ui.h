#include "uiHeads.h"
#include <vector>
#include <string>

//-----------------------------------------------------------------------------
#ifndef USE_VISUAL_STUDIO
// quando baixar a linha
volatile W1  uiHasInterrupted = false; 

#define BUTTON_SAMPLE_N 3
PIN_IRQ_HANDLER(ui_interrupt)
{
	PIN_UNINSTALL_IRQ_ONFALL(PIN_UI_BUTTONS)
	uiButton = UI_BUTTON_NONE;
	float best = FLT_MAX;
	W8  bestId = (W8)UI_BUTTON_NONE;

	// amostrar a onda 
	W32 sample, vmax[2];
	sample=0;
	while(PIN_READ(PIN_UI_BUTTONS)==LOW)  
		if (++sample==0) { break; goto interruptEnd; }
	sample=0;
	while(PIN_READ(PIN_UI_BUTTONS)==HIGH) 
		if (++sample==0) { break; goto interruptEnd; }

	sample=0;
	while(PIN_READ(PIN_UI_BUTTONS)==LOW)  
		if (++sample==0) { break; goto interruptEnd; }
	vmax[0] =sample;
	sample=0;
	while(PIN_READ(PIN_UI_BUTTONS)==HIGH) 
		if (++sample==0) { break; goto interruptEnd; }
	vmax[1] = sample;
	 
	//vmax[0]/=(BUTTON_SAMPLE_N-1);
	//vmax[1]/=(BUTTON_SAMPLE_N-1);
  
	for (W8 i=0; i< UI_BUTTON_NONE; i++)
	{
		float d[] = {
			 (float)uiButtonsAv[i][0]-(float)vmax[0],
			 (float)uiButtonsAv[i][1]-(float)vmax[1]};
		const float diff = d[0]*d[0]+d[1]*d[1];
		if (diff < best)
		{
			best = diff;
			bestId = i;
		}
	}
	uiButton = (UI_BUTTONS) bestId;
 
	#ifdef UI_DEBUG_BUTTONS
		//W32 th0 = VL_MAX(sample[0]-vmin[0] , vmax[0]-sample[0]);
		//W32 th1 = VL_MAX(sample[1]-vmin[1] , vmax[1]-sample[1]);
		//DEBUG("\n*Butt { %i %i %i |+-%i } { %i %i %i |+-%i} -> %s", 
		//			vmin[0], sample[0], vmax[0], th0,
		//			vmin[1], sample[1], vmax[1], th1,
		//			uiButtonStrs[uiButton]);
		DEBUG("\n*Butt { %i} { %i } -> %s", 
					vmax[0], vmax[1], 
					uiButtonStrs[uiButton]);
	#endif
	interruptEnd:
	uiHasInterrupted = true;
}
#endif
/*
//-----------------------------------------------------------------------------
#ifdef APP_FILESYSTEM_ON
ICON ui_fs_attribIcon(FatEntry* e_)
{
	if (e_->isUpperDir()) return ICON_DIR_BACK;
	if (e_->isDir()) return ICON_FOLDER;
	e_->ext[0]=tolower(e_->ext[0]);
	e_->ext[1]=tolower(e_->ext[1]);
	e_->ext[2]=tolower(e_->ext[2]);
	if (strncmp((SW8*)(e_->ext), "txt", 3)==0) return ICON_FILE_TEXT;
	if (strncmp((SW8*)(e_->ext), "wav", 3)==0) return ICON_FILE_TAPE;
	if (strncmp((SW8*)(e_->ext), "a2r", 3)==0) return ICON_FILE_FLOPPY;
	return ICON_FILE;	
}


class FS_Source: public Source
{
public:
	struct Dir
	{	
		std::string name;
		W32 cluster;
		Dir(SW8* name_, W32 cluster_)
		{
			name = std::string(name_);
			cluster = cluster_;
		}
	};

	enum FS_Source_Page { FS_Source_MBRPage, FS_Source_DirPage };
	FS_Source_Page  page; // página 0 partições, pagina = 1 dir
	FSNode  *node;
	std::vector<Dir*> dirStack;
	std::string currDirName;
	typedef ICON (*ATTRIBICON_FX)(FatEntry* e_);
	
	FS_Source(FSNode* node_)
	{
		page = FS_Source_MBRPage;
		node = node_;
		currDirName = std::string(ui_strs_mbr_volumes);
	}
	W0 enterDir(UI_ITEM* item_)
	{
		Dir *d = new Dir((SW8*)currDirName.data(), node->cluster);
		if (!d) fatal(UI_ALLOC);
		dirStack.push_back(d);
		node->setValid();
		node->setAsDir(true);
		node->cluster		 = item_->itemData32;
		node->dir.fileCount  = fs_countDirFiles_(node->cluster);
		currDirName = std::string(item_->name);
	}
	W1 exitDir()
	{
		if (!dirStack.size()) return 1;
		Dir* dir = *(dirStack.end()-1);
		currDirName = dir->name;
		node->cluster = dir->cluster;
		node->dir.fileCount = fs_countDirFiles_(node->cluster);
		delete dir;
		dirStack.pop_back();
		return 0;
	}
	W0 getTitle(SW8** title_, W1& isAllocated_)
	{
		if (page == FS_Source_MBRPage)
		{
			*title_ = (SW8*)ui_strs_mbr_volumes;
			isAllocated_ = 1;
		}
		else
		{
			*title_ = (SW8*)currDirName.data();
			isAllocated_ = 1;
		}
	}
	
	static W1  fs_source_itfx(FatEntry* e_, W0* arg_)
	{
		//DEBUG_PRINT("\nui_fs_entry");
		UI_ITEM_CACHE* ch = (UI_ITEM_CACHE*)arg_;
		SW8 name[13];
		e_->getShortName(name);
		//DEBUG("\n ** %s", name);

		UI_ITEM* nextItem;
		const W1 stopIteration = ch->nextItem(&nextItem);
		if (nextItem) 
			nextItem->init(name, true,  
							(e_->clusterHi<<16)|(e_->clusterLow), 
							 e_->isDir() ||e_->isUpperDir(), 
							 ui_fs_attribIcon(e_));
		return stopIteration? FS_ITERATE_STOP: FS_ITERATE_CONTINUE;	
	}
	W16 getItems(UI_ITEM_CACHE* strct)
	{
		if (page==FS_Source_MBRPage) // partições
		{
			SW8 volumeName[12];
			FS_TYPE type;
			for (W8 i=0; i< 4; i++)
			{
				const W8 status = fs_detectVolume_(i, false, &type, volumeName);
				if (status == RES_OK)
				{
					sprintf(dgStr, "%i FAT%s %s", i, (type==FS_FAT16)?"16":"32", volumeName);
					strct->items[i].init(volumeName, true, i, true, ICON_SD_DISK);
				}
				else
					strct->items[i].init(ui_strs_invalid, false, i, false, ICON_ERROR);
			}
			return 4;
		}
		else
		{
			//DEBUG_PRINT("\nFS_Source:GetItems");
			fs_iterateDir(node, fs_source_itfx, strct);
			return node->dir.fileCount;
		}
	}
	W16 getItemsTotal()
	{
		if (page==FS_Source_MBRPage)  
			return 4;
		else
			return node->dir.fileCount;
	}

	SOURCE_ACTION_RES action(UI_ITEM* item_, SOURCE_ACTION action_)
	{
		switch(action_)
		{
			case SOURCE_ACTION_ENTER:
				if (strcmp(item_->name,"..")==0) goto escape;
				if (!item_->hasContents()) return SOURCE_ACTION_RES_HIT_LEAF;

				if (page==FS_Source_MBRPage) 
				{ 
					currDirName = (SW8*)ui_strs_vol_root;
					page = FS_Source_DirPage;
					fs_getRootDirNode(node, item_->itemData32);
					//DEBUG("\naction - %u", node->dir.fileCount);
				}
				else
				{
					//entrar para ex. dir "DOS"
					enterDir(item_);
				}
				return SOURCE_ACTION_RES_NEEDS_RESTART;
			break;
			case SOURCE_ACTION_ESCAPE:
				escape:

				if (page == FS_Source_MBRPage)
					return SOURCE_ACTION_RES_HIT_SAME_POINT;

				if (exitDir() == 1)
					page = FS_Source_MBRPage;
				
				return SOURCE_ACTION_RES_NEEDS_RESTART;
			break;
		}
		return SOURCE_ACTION_RES_DONTCARE;
	}
};
#endif

W0 selectFile(UI_ITEM* item_)
{
	SW8* ext;
	if (!(ext = getFilenameExt(item_->name))) return;

	if (!strncmp(ext,"wav",3)){}

}
*/

/*
//-----------------------------------------------------------------------------
class UI_PAGE_SOURCE_LIST: public UI_PAGE
{
public:
	Source* source;
	UI_PAGE_SOURCE_LIST()
	{
		numCachedItems = 0;
		source=0;
		numItems = 0;
		title = 0;
		cachedItems = new UI_ITEM[UI_CACHEFILES_MAXSIZE];
		if (!cachedItems) fatal(UI_ALLOC);
	}
		
	W0  actionEnter()
	{
     	animateSelection(); 

		UI_ITEM* item = getSelectedItem();
		SOURCE_ACTION_RES res = source->action(item, SOURCE_ACTION_ENTER);
		if (res == SOURCE_ACTION_RES_NEEDS_RESTART) 
			init(source);
	//	else if (res == SOURCE_ACTION_RES_HIT_LEAF)
	//		hitItem(item);

		SW8 *newTitle=0;
		W1   allocNewTitle = false;
		source->getTitle(&newTitle, allocNewTitle); 
		setTitle(newTitle, allocNewTitle);

		animatePage(UI_ANIMATE_PAGE_DIR_ENTER); 
	}
	W0  actionEsc()
	{
		// para se notar que se premiu o botão
		#ifndef USE_VISUAL_STUDIO
			draw_addColor(dispBuf,1,0,(DISP_WIDTH*DISP_HEIGHT));
			DRAW_UPDATE
		#endif

		SOURCE_ACTION_RES res = source->action(cachedItems+offsetInCache, SOURCE_ACTION_ESCAPE);

		if (res == SOURCE_ACTION_RES_HIT_SAME_POINT) 
			uiCurrPage = returnPage;
		else if (res == SOURCE_ACTION_RES_NEEDS_RESTART) 
			init(source);
		
		SW8* newTitle;
		W1 isAllocated;
		source->getTitle(&newTitle, isAllocated); 
		setTitle(newTitle, isAllocated);

		animatePage(UI_ANIMATE_PAGE_DIR_RETURN); 
	}
	W16 sourceGet_(W16 stIdx_, W16 endIdx_)
	{
		//DEBUG_PRINT("\nui:Source_List: sourceGet_");

		for (W8 i=0; i< UI_CACHEFILES_MAXSIZE; i++)
		{
			if (cachedItems[i].isNameAllocated()) delete[] cachedItems[i].name;
			cachedItems[i].setNameAllocated(false);
			cachedItems[i].name = 0;
		}

		UI_ITEM_CACHE strct;
		strct.items     = cachedItems;
		strct.startIdx  = stIdx_;
		strct.currIdx   = 0;
		strct.endIdx    = endIdx_;
		source->getItems(&strct);
		return endIdx_-stIdx_;
	}
	W0  init(Source* source_)
	{ 
		reset();
		if (!source_) return;
		source = source_;
		numItems = source->getItemsTotal();
		//DEBUG("\nui:UI_PAGE_SOURCE_LIST:init(Source) items:%i",numItems );
		numCachedItems = sourceGet_(0, VL_MIN(UI_CACHEFILES_MAXSIZE-1, numItems - 1));
		
		SW8* newTitle;
		W1 isAllocated;
		source->getTitle(&newTitle, isAllocated); 
		setTitle(newTitle, isAllocated);
	}
};


//-----------------------------------------------------------------------------
W0 ui_init()
{
	#ifndef USE_VISUAL_STUDIO
	#ifdef APP_DISPLAY_INTRO_ON
			draw_displayFrameBlocks(40,0x0EEE);
			W8 y;  
			#ifdef UI_DEBUG_ICONS
				y=ICON_SIZE;
				W8 x=ICON_SIZE;
				for (W8 i=0; i< ICON_NUMBER; i++)
				{	
					draw_icon<1>(x, y, (ICON)i);
					x+=ICON_SIZE;
					if (x > DISP_WIDTH-ICON_SIZE) { x=ICON_SIZE; y+=ICON_SIZE; }
				}
				y+=ICON_SIZE; 
			#else
				y=(DISP_WIDTH-fontBlockY)/2 - fontBlockY; 
			#endif
			//DELAY_MS(4000);
			SW8 str[] = "Apple// Storage";
			Sz tsz = draw_getTextSize(str);
			draw_text((DISP_WIDTH-tsz.width)/2,y,str);
			DRAW_UPDATE
			DELAY_MS(1000);
		#endif
	#endif

	uiButton           = UI_BUTTON_NONE;
	uiPageOptions      = new UI_PAGE_OPTIONS();
	uiPageFileSelector = new UI_PAGE_SOURCE_LIST(); 
	//uiPageTextViewer   = new UI_PAGE_TEXT(); 

	#ifdef APP_FILESYSTEM_ON
		FSNode* node = new FSNode();
		FS_Source* fsSource = new FS_Source(node); //, ui_fs_attribIcon);
		uiPageFileSelector->init(fsSource);
		uiPageFileSelector->returnPage = uiPageOptions;
		uiPageFileSelector->hitItemFunc = selectFile;

	#else
		uiPageFileSelector->init(0);
	#endif
		uiCurrPage = uiPageOptions;


	for (;;)
	{
		uiCurrPage->draw();

		#ifndef USE_VISUAL_STUDIO
			DRAW_UPDATE
			DELAY_MS(5);
			PIN_INSTALL_IRQ_ONFALL(PIN_UI_BUTTONS, ui_interrupt)
			uiHasInterrupted = false;
			uiButton = UI_BUTTON_NONE;
			while(!uiHasInterrupted){}
			PIN_UNINSTALL_IRQ_ONFALL(PIN_UI_BUTTONS)
			//DEBUG_PRINT("\ncatch");
		#else
			dispCon->updateAll();
			W8 key = getch();
			switch(key)
			{	
				case  27:  uiButton = UI_BUTTON_ESC; break;
				case  13:  uiButton = UI_BUTTON_ENTER; break;
				case  'w': uiButton = UI_BUTTON_UP; break;
				case  's': uiButton = UI_BUTTON_DOWN; break;
				case  'a': uiButton = UI_BUTTON_RIGHT; break;
				case  'd': uiButton = UI_BUTTON_LEFT; break;
				default:
					uiButton = UI_BUTTON_NONE;
				break;
			}
		#endif
		uiCurrPage->action(uiButton);
	}

}

*/