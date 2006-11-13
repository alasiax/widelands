/*
 * Copyright (C) 2002-2004, 2006 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef __S__BUILDING_STATISTICS_MENU_H
#define __S__BUILDING_STATISTICS_MENU_H

#include "ui_unique_window.h"
class Interactive_Player;
namespace UI {
template <typename T, typename ID> struct IDButton;
struct Progress_Bar;
struct Textarea;
struct Table;
};

struct Building_Statistics_Menu : public UI::UniqueWindow {
	Building_Statistics_Menu(Interactive_Player &, UI::UniqueWindow::Registry &);
      virtual ~Building_Statistics_Menu(void);

      void think(void);
      void draw(RenderTarget*);

   private:
	enum Jump_Targets {
		Prev_Owned,        Next_Owned,
		Prev_Construction, Next_Construction,
		Prev_Unproductive, Next_Unproductive
	};

      UI::Table*            m_table;
      Interactive_Player* m_parent;
      UI::Progress_Bar*     m_progbar;
      UI::Textarea*         m_owned, *m_build;
      uint                m_anim;
      uint                m_lastupdate;
      uint                m_end_of_table_y;
      int                 m_selected;
	UI::IDButton<Building_Statistics_Menu, Jump_Targets> * m_btn[6];
      int                 m_last_building_index;

   private:
	void clicked_help();
	void clicked_jump(Jump_Targets);
      void table_changed(int);
      void update();
      int validate_pointer(int*,int);
};

#endif
