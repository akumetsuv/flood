/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class ConsoleTextCtrl : public wxTextCtrl
{
public:

	ConsoleTextCtrl( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxString& name = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,	
		const wxSize& size = wxDefaultSize, 
		long style = wxBORDER_NONE | wxTE_MULTILINE | wxTE_NOHIDESEL | wxTE_RICH2 );

	virtual ~ConsoleTextCtrl();

	// Appends a line of text with a given text attribute.
	void AppendTextColor( const wxString& text, const wxTextAttr& attr );

	// Writes a new prompt line on the console.
	void NewPromptLine();

#ifdef ENABLE_SCRIPTING_LUA
	// Overrides the Lua 'print' function.
	int luaPrint(lua_State* L);
#endif

protected:

	// Initializes the control.
	void InitControl();

	// Event handlers.
	void OnEnter();
	void OnKeyDown(wxKeyEvent& event);
	void OnSetFocus(wxFocusEvent& event);

	// Holds an instance of the scripting state.
	ScriptState* luaState;

	// Holds an instance to the vaporEngine.
	Engine* engine;
};

//-----------------------------------//

NAMESPACE_EDITOR_END