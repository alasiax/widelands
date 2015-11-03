/*
 * Copyright (C) 2002-2004, 2006, 2009 by the Widelands Development Team
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef WL_WUI_ENCYCLOPEDIA_WINDOW_H
#define WL_WUI_ENCYCLOPEDIA_WINDOW_H

#include <map>
#include <memory>

#include "logic/instances.h"
#include "logic/tribes/tribe_descr.h"
#include "ui_basic/box.h"
#include "ui_basic/listselect.h"
#include "ui_basic/multilinetextarea.h"
#include "ui_basic/table.h"
#include "ui_basic/tabpanel.h"
#include "ui_basic/unique_window.h"
#include "ui_basic/window.h"


class InteractivePlayer;

struct EncyclopediaWindow : public UI::UniqueWindow {
	EncyclopediaWindow(InteractivePlayer &, UI::UniqueWindow::Registry &);
private:
	struct EncyclopediaEntry {
		EncyclopediaEntry(const EncyclopediaEntry& other) :
			EncyclopediaEntry(other.index_, other.descname_, other.icon_)
		{}
		EncyclopediaEntry(const Widelands::WareIndex index, const std::string& descname, const Image* icon)
			:
			index_(index),
			descname_(descname),
			icon_(icon)
			{}
		Widelands::WareIndex index_;
		std::string descname_;
		const Image* icon_;

		bool operator<(const EncyclopediaEntry other) const {
			return descname_ < other.descname_;
		}
	};

	InteractivePlayer & iaplayer() const;

	// Fill table of contents
	void fill_entries(const char* key, std::vector<EncyclopediaEntry>& entries);
	void fill_buildings();
	void fill_wares();
	void fill_workers();

	// Update contents when an entry is selected
	template<typename T>
	void entry_selected(const Widelands::TribeDescr& tribe,
							  const T& map_object,
							  const char* tab,
							  const char* script_name);

	void building_selected(uint32_t);
	void ware_selected(uint32_t);
	void worker_selected(uint32_t);

	// UI elements
	UI::TabPanel tabs_;

	// Wrapper boxes so we can add some padding
	std::map<std::string, std::unique_ptr<UI::Box>> wrapper_boxes_;
	// Main contents boxes for each tab
	std::map<std::string, std::unique_ptr<UI::Box>> boxes_;
	// A tab's table of contents
	std::map<std::string, std::unique_ptr<UI::Listselect<Widelands::WareIndex>>> lists_;
	// The contents shown when an entry is selected in a tab
	std::map<std::string, std::unique_ptr<UI::MultilineTextarea>> contents_;
};

#endif  // end of include guard: WL_WUI_ENCYCLOPEDIA_WINDOW_H
