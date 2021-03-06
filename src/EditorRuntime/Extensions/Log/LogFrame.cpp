/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Editor/API.h"
#include "LogFrame.h"
#include "Editor.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

LogFrame::LogFrame( wxWindow* parent )
	: wxListCtrl( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_REPORT)
{
	wxListItem level;
	level.SetText("Level");
	InsertColumn(0, level);

	wxListItem message;
	message.SetText("Message");
	message.SetWidth(300);
	InsertColumn(1, message);

	Log* log = LogGetDefault();
	log->handlers.Connect( this, &LogFrame::Process );

	Bind(wxEVT_IDLE, &LogFrame::OnIdle, this);
}

//-----------------------------------//

LogFrame::~LogFrame()
{

}

//-----------------------------------//

void LogFrame::Process(LogEntry* entry)
{
	// We cannot insert the entries right away, since it might not be thread-safe.
	entries.push_back(*entry);
}

//-----------------------------------//

void LogFrame::OnIdle(wxIdleEvent& event)
{
	LogEntry entry;

	while( entries.try_pop_front(entry) )
	{
		int id = InsertItem(GetItemCount(), wxEmptyString);

		SetItem(id, 0, wxEmptyString);
		SetItem(id, 1, entry.message);
	}
}

//-----------------------------------//

NAMESPACE_EDITOR_END