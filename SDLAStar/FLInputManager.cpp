#include "stdafx.h"
#include "FLInputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
	if (inputManagerInstance == nullptr)
	{
		inputManagerInstance = new InputManager();
	}
	return inputManagerInstance;
}

void InputManager::AddListener(EventListener::Event evt, EventListener *listener)
{
	if (listeners.find(evt) == listeners.end())
	{
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}

void InputManager::Dispatch(EventListener::Type type, EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		for (auto const &listener : *listeners[evt])
		{
			listener->onEvent(evt);
		}
	}

	CheckPrevious(type, evt);
}

void InputManager::SetPrevious(EventListener::Event evt, bool isHeld)
{
	previouslyHeld[evt] = isHeld;
}

void InputManager::CheckPrevious(EventListener::Type type, EventListener::Event evt)
{
	if (type == EventListener::Type::Release)
	{
		SetPrevious(evt, false);
	}
	
	if (previouslyHeld[evt])
	{
		type = EventListener::Type::Hold;
	}

	std::cout << previouslyHeld[evt] << std::endl;

	Execute(type, evt);
}

void InputManager::AddCommand(EventListener::Event evt, Command *command)
{
	if (commands.find(evt) == commands.end())
	{
		commands[evt] = new std::vector<Command*>();
	}

	commands[evt]->push_back(command);
}

void InputManager::Execute(EventListener::Type type, EventListener::Event evt)
{
	if (commands.find(evt) != commands.end())
	{
		for (auto const &command : *commands[evt])
		{
			if (type == EventListener::Type::Press) { command->executePress(); }
			else if (type == EventListener::Type::Release) { command->executeRelease(); }
			else if (type == EventListener::Type::Hold) { command->executeHold(); }
			else { command->execute(); }
		}
	}

	if (type == EventListener::Type::Press)
	{
		SetPrevious(evt, true);
	}
}

void InputManager::AddKey(EventListener::Event evt, Command* command, EventListener *listener)
{
	AddListener(evt, listener);

	Command*& toBind = bindCommand(evt);
	toBind = command;

	AddCommand(evt, toBind);
}

Command*& InputManager::bindCommand(EventListener::Event evt)
{
	switch (evt)
	{
	case SDLK_UNKNOWN:		return  Key_UNKNOWN;		break;
	case SDLK_RETURN:		return	Key_RETURN;			break;
	case SDLK_ESCAPE:		return	Key_ESCAPE;			break;
	case SDLK_BACKSPACE:	return	Key_BACKSPACE;		break;
	case SDLK_TAB:			return	Key_TAB;			break;
	case SDLK_SPACE:		return	Key_SPACE;			break;
	case SDLK_EXCLAIM:		return	Key_EXCLAIM;		break;
	case SDLK_QUOTEDBL:		return	Key_QUOTEDBL;		break;
	case SDLK_HASH:			return	Key_HASH;			break;
	case SDLK_PERCENT:		return	Key_PERCENT;		break;
	case SDLK_DOLLAR:		return	Key_DOLLAR;			break;
	case SDLK_AMPERSAND:	return	Key_AMPERSAND;		break;
	case SDLK_QUOTE:		return	Key_QUOTE;			break;
	case SDLK_LEFTPAREN:	return	Key_LEFTPAREN;		break;
	case SDLK_RIGHTPAREN:	return	Key_RIGHTPAREN;		break;
	case SDLK_ASTERISK:		return	Key_ASTERISK;		break;
	case SDLK_PLUS:			return	Key_PLUS;			break;
	case SDLK_COMMA:		return	Key_COMMA;			break;
	case SDLK_MINUS:		return	Key_MINUS;			break;
	case SDLK_PERIOD:		return	Key_PERIOD;			break;
	case SDLK_SLASH:		return	Key_SLASH;			break;
	case SDLK_0:			return	Key_NUM_0;			break;
	case SDLK_1:			return	Key_NUM_1;			break;
	case SDLK_2:			return	Key_NUM_2;			break;
	case SDLK_3:			return	Key_NUM_3;			break;
	case SDLK_4:			return	Key_NUM_4;			break;
	case SDLK_5:			return	Key_NUM_5;			break;
	case SDLK_6:			return	Key_NUM_6;			break;
	case SDLK_7:			return	Key_NUM_7;			break;
	case SDLK_8:			return	Key_NUM_8;			break;
	case SDLK_9:			return	Key_NUM_9;			break;
	case SDLK_COLON:		return	Key_COLON;			break;
	case SDLK_SEMICOLON:	return	Key_SEMICOLON;		break;
	case SDLK_LESS:			return	Key_LESS;			break;
	case SDLK_EQUALS:		return	Key_EQUALS;			break;
	case SDLK_GREATER:		return	Key_GREATER;		break;
	case SDLK_QUESTION:		return	Key_QUESTION;		break;
	case SDLK_AT:			return	Key_AT;				break;
	case SDLK_LEFTBRACKET:	return	Key_LEFTBRACKET;	break;
	case SDLK_BACKSLASH:	return	Key_BACKSLASH;		break;
	case SDLK_RIGHTBRACKET: return	Key_RIGHTBRACKET;	break;
	case SDLK_CARET:		return	Key_CARET;			break;
	case SDLK_UNDERSCORE:	return	Key_UNDERSCORE;		break;
	case SDLK_BACKQUOTE:	return	Key_BACKQUOTE;		break;
	case SDLK_a:			return	Key_a;				break;
	case SDLK_b:			return	Key_b;				break;
	case SDLK_c:			return	Key_c;				break;
	case SDLK_d:			return	Key_d;				break;
	case SDLK_e:			return	Key_e;				break;
	case SDLK_f:			return	Key_f;				break;
	case SDLK_g:			return	Key_g;				break;
	case SDLK_h:			return	Key_h;				break;
	case SDLK_i:			return	Key_i;				break;
	case SDLK_j:			return	Key_j;				break;
	case SDLK_k:			return	Key_k;				break;
	case SDLK_l:			return	Key_l;				break;
	case SDLK_m:			return	Key_m;				break;
	case SDLK_n:			return	Key_n;				break;
	case SDLK_o:			return	Key_o;				break;
	case SDLK_p:			return	Key_p;				break;
	case SDLK_q:			return	Key_q;				break;
	case SDLK_r:			return	Key_r;				break;
	case SDLK_s:			return	Key_s;				break;
	case SDLK_t:			return	Key_t;				break;
	case SDLK_u:			return	Key_u;				break;
	case SDLK_v:			return	Key_v;				break;
	case SDLK_w:			return	Key_w;				break;
	case SDLK_x:			return	Key_x;				break;
	case SDLK_y:			return	Key_y;				break;
	case SDLK_z:			return	Key_z;				break;

	default: break;
	}
}

void InputManager::ProcessInput()
{
	SDL_Event evn;
	EventListener::Type type;


	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&evn) != 0)
	{
		// Print Key Press
		if (evn.type == SDL_KEYDOWN) { std::cout << evn.key.keysym.sym << std::endl; }

		// Event Types
		switch (evn.type)
		{
		case SDL_KEYDOWN: type = EventListener::Type::Press;	break;
		case SDL_KEYUP: type = EventListener::Type::Release;	break;

		default: type = EventListener::Type::None;				break;
		}

		// Key
		switch (evn.key.keysym.sym)
		{
		//case SDLK_UNKNOWN:		Dispatch(type, EventListener::Event::UNKNOWN);			break;
		case SDLK_RETURN:		Dispatch(type, EventListener::Event::RETURN);			break;
		case SDLK_ESCAPE:		Dispatch(type, EventListener::Event::ESCAPE);			break;
		case SDLK_BACKSPACE:	Dispatch(type, EventListener::Event::BACKSPACE);		break;
		case SDLK_TAB:			Dispatch(type, EventListener::Event::TAB);				break;
		case SDLK_SPACE:		Dispatch(type, EventListener::Event::SPACE);			break;
		case SDLK_EXCLAIM:		Dispatch(type, EventListener::Event::EXCLAIM);			break;
		case SDLK_QUOTEDBL:		Dispatch(type, EventListener::Event::QUOTEDBL);			break;
		case SDLK_HASH:			Dispatch(type, EventListener::Event::HASH);				break;
		case SDLK_PERCENT:		Dispatch(type, EventListener::Event::PERCENT);			break;
		case SDLK_DOLLAR:		Dispatch(type, EventListener::Event::DOLLAR);			break;
		case SDLK_AMPERSAND:	Dispatch(type, EventListener::Event::AMPERSAND);		break;
		case SDLK_QUOTE:		Dispatch(type, EventListener::Event::QUOTE);			break;
		case SDLK_LEFTPAREN:	Dispatch(type, EventListener::Event::LEFTPAREN);		break;
		case SDLK_RIGHTPAREN:	Dispatch(type, EventListener::Event::RIGHTPAREN);		break;
		case SDLK_ASTERISK:		Dispatch(type, EventListener::Event::ASTERISK);			break;
		case SDLK_PLUS:			Dispatch(type, EventListener::Event::PLUS);				break;
		case SDLK_COMMA:		Dispatch(type, EventListener::Event::COMMA);			break;
		case SDLK_MINUS:		Dispatch(type, EventListener::Event::MINUS);			break;
		case SDLK_PERIOD:		Dispatch(type, EventListener::Event::PERIOD);			break;
		case SDLK_SLASH:		Dispatch(type, EventListener::Event::SLASH);			break;
		case SDLK_0:			Dispatch(type, EventListener::Event::NUM_0);			break;
		case SDLK_1:			Dispatch(type, EventListener::Event::NUM_1);			break;
		case SDLK_2:			Dispatch(type, EventListener::Event::NUM_2);			break;
		case SDLK_3:			Dispatch(type, EventListener::Event::NUM_3);			break;
		case SDLK_4:			Dispatch(type, EventListener::Event::NUM_4);			break;
		case SDLK_5:			Dispatch(type, EventListener::Event::NUM_5);			break;
		case SDLK_6:			Dispatch(type, EventListener::Event::NUM_6);			break;
		case SDLK_7:			Dispatch(type, EventListener::Event::NUM_7);			break;
		case SDLK_8:			Dispatch(type, EventListener::Event::NUM_8);			break;
		case SDLK_9:			Dispatch(type, EventListener::Event::NUM_9);			break;
		case SDLK_COLON:		Dispatch(type, EventListener::Event::COLON);			break;
		case SDLK_SEMICOLON:	Dispatch(type, EventListener::Event::SEMICOLON);		break;
		case SDLK_LESS:			Dispatch(type, EventListener::Event::LESS);				break;
		case SDLK_EQUALS:		Dispatch(type, EventListener::Event::EQUALS);			break;
		case SDLK_GREATER:		Dispatch(type, EventListener::Event::GREATER);			break;
		case SDLK_QUESTION:		Dispatch(type, EventListener::Event::QUESTION);			break;
		case SDLK_AT:			Dispatch(type, EventListener::Event::AT);				break;
		case SDLK_LEFTBRACKET:	Dispatch(type, EventListener::Event::LEFTBRACKET);		break;
		case SDLK_BACKSLASH:	Dispatch(type, EventListener::Event::BACKSLASH);		break;
		case SDLK_RIGHTBRACKET: Dispatch(type, EventListener::Event::RIGHTBRACKET);		break;
		case SDLK_CARET:		Dispatch(type, EventListener::Event::CARET);			break;
		case SDLK_UNDERSCORE:	Dispatch(type, EventListener::Event::UNDERSCORE);		break;
		case SDLK_BACKQUOTE:	Dispatch(type, EventListener::Event::BACKQUOTE);		break;
		case SDLK_a:			Dispatch(type, EventListener::Event::a);				break;
		case SDLK_b:			Dispatch(type, EventListener::Event::b);				break;
		case SDLK_c:			Dispatch(type, EventListener::Event::c);				break;
		case SDLK_d:			Dispatch(type, EventListener::Event::d);				break;
		case SDLK_e:			Dispatch(type, EventListener::Event::e);				break;
		case SDLK_f:			Dispatch(type, EventListener::Event::f);				break;
		case SDLK_g:			Dispatch(type, EventListener::Event::g);				break;
		case SDLK_h:			Dispatch(type, EventListener::Event::h);				break;
		case SDLK_i:			Dispatch(type, EventListener::Event::i);				break;
		case SDLK_j:			Dispatch(type, EventListener::Event::j);				break;
		case SDLK_k:			Dispatch(type, EventListener::Event::k);				break;
		case SDLK_l:			Dispatch(type, EventListener::Event::l);				break;
		case SDLK_m:			Dispatch(type, EventListener::Event::m);				break;
		case SDLK_n:			Dispatch(type, EventListener::Event::n);				break;
		case SDLK_o:			Dispatch(type, EventListener::Event::o);				break;
		case SDLK_p:			Dispatch(type, EventListener::Event::p);				break;
		case SDLK_q:			Dispatch(type, EventListener::Event::q);				break;
		case SDLK_r:			Dispatch(type, EventListener::Event::r);				break;
		case SDLK_s:			Dispatch(type, EventListener::Event::s);				break;
		case SDLK_t:			Dispatch(type, EventListener::Event::t);				break;
		case SDLK_u:			Dispatch(type, EventListener::Event::u);				break;
		case SDLK_v:			Dispatch(type, EventListener::Event::v);				break;
		case SDLK_w:			Dispatch(type, EventListener::Event::w);				break;
		case SDLK_x:			Dispatch(type, EventListener::Event::x);				break;
		case SDLK_y:			Dispatch(type, EventListener::Event::y);				break;
		case SDLK_z:			Dispatch(type, EventListener::Event::z);				break;

		default: break;
		}
		break;
	}
}