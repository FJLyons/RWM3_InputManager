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

void InputManager::Dispatch(EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		for (auto const &listener : *listeners[evt])
		{
			listener->onEvent(evt);
		}
	}

	Execute(evt);
}

void InputManager::AddCommand(EventListener::Event evt, Command *command)
{
	if (commands.find(evt) == commands.end())
	{
		commands[evt] = new std::vector<Command*>();
	}

	commands[evt]->push_back(command);
}

void InputManager::Execute(EventListener::Event evt)
{
	if (commands.find(evt) != commands.end())
	{
		for (auto const &command : *commands[evt])
		{
			command->execute();
		}
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
	while (SDL_PollEvent(&evn) != 0)
	{
		// Print Key Press
		if (evn.type == SDL_KEYDOWN) { std::cout << evn.key.keysym.sym << std::endl; }

		// Key
		switch (evn.key.keysym.sym)
		{
		case SDLK_UNKNOWN:		Dispatch(EventListener::Event::UNKNOWN);		break;
		case SDLK_RETURN:		Dispatch(EventListener::Event::RETURN);			break;
		case SDLK_ESCAPE:		Dispatch(EventListener::Event::ESCAPE);			break;
		case SDLK_BACKSPACE:	Dispatch(EventListener::Event::BACKSPACE);		break;
		case SDLK_TAB:			Dispatch(EventListener::Event::TAB);			break;
		case SDLK_SPACE:		Dispatch(EventListener::Event::SPACE);			break;
		case SDLK_EXCLAIM:		Dispatch(EventListener::Event::EXCLAIM);		break;
		case SDLK_QUOTEDBL:		Dispatch(EventListener::Event::QUOTEDBL);		break;
		case SDLK_HASH:			Dispatch(EventListener::Event::HASH);			break;
		case SDLK_PERCENT:		Dispatch(EventListener::Event::PERCENT);		break;
		case SDLK_DOLLAR:		Dispatch(EventListener::Event::DOLLAR);			break;
		case SDLK_AMPERSAND:	Dispatch(EventListener::Event::AMPERSAND);		break;
		case SDLK_QUOTE:		Dispatch(EventListener::Event::QUOTE);			break;
		case SDLK_LEFTPAREN:	Dispatch(EventListener::Event::LEFTPAREN);		break;
		case SDLK_RIGHTPAREN:	Dispatch(EventListener::Event::RIGHTPAREN);		break;
		case SDLK_ASTERISK:		Dispatch(EventListener::Event::ASTERISK);		break;
		case SDLK_PLUS:			Dispatch(EventListener::Event::PLUS);			break;
		case SDLK_COMMA:		Dispatch(EventListener::Event::COMMA);			break;
		case SDLK_MINUS:		Dispatch(EventListener::Event::MINUS);			break;
		case SDLK_PERIOD:		Dispatch(EventListener::Event::PERIOD);			break;
		case SDLK_SLASH:		Dispatch(EventListener::Event::SLASH);			break;
		case SDLK_0:			Dispatch(EventListener::Event::NUM_0);			break;
		case SDLK_1:			Dispatch(EventListener::Event::NUM_1);			break;
		case SDLK_2:			Dispatch(EventListener::Event::NUM_2);			break;
		case SDLK_3:			Dispatch(EventListener::Event::NUM_3);			break;
		case SDLK_4:			Dispatch(EventListener::Event::NUM_4);			break;
		case SDLK_5:			Dispatch(EventListener::Event::NUM_5);			break;
		case SDLK_6:			Dispatch(EventListener::Event::NUM_6);			break;
		case SDLK_7:			Dispatch(EventListener::Event::NUM_7);			break;
		case SDLK_8:			Dispatch(EventListener::Event::NUM_8);			break;
		case SDLK_9:			Dispatch(EventListener::Event::NUM_9);			break;
		case SDLK_COLON:		Dispatch(EventListener::Event::COLON);			break;
		case SDLK_SEMICOLON:	Dispatch(EventListener::Event::SEMICOLON);		break;
		case SDLK_LESS:			Dispatch(EventListener::Event::LESS);			break;
		case SDLK_EQUALS:		Dispatch(EventListener::Event::EQUALS);			break;
		case SDLK_GREATER:		Dispatch(EventListener::Event::GREATER);		break;
		case SDLK_QUESTION:		Dispatch(EventListener::Event::QUESTION);		break;
		case SDLK_AT:			Dispatch(EventListener::Event::AT);				break;
		case SDLK_LEFTBRACKET:	Dispatch(EventListener::Event::LEFTBRACKET);	break;
		case SDLK_BACKSLASH:	Dispatch(EventListener::Event::BACKSLASH);		break;
		case SDLK_RIGHTBRACKET: Dispatch(EventListener::Event::RIGHTBRACKET);	break;
		case SDLK_CARET:		Dispatch(EventListener::Event::CARET);			break;
		case SDLK_UNDERSCORE:	Dispatch(EventListener::Event::UNDERSCORE);		break;
		case SDLK_BACKQUOTE:	Dispatch(EventListener::Event::BACKQUOTE);		break;
		case SDLK_a:			Dispatch(EventListener::Event::a);				break;
		case SDLK_b:			Dispatch(EventListener::Event::b);				break;
		case SDLK_c:			Dispatch(EventListener::Event::c);				break;
		case SDLK_d:			Dispatch(EventListener::Event::d);				break;
		case SDLK_e:			Dispatch(EventListener::Event::e);				break;
		case SDLK_f:			Dispatch(EventListener::Event::f);				break;
		case SDLK_g:			Dispatch(EventListener::Event::g);				break;
		case SDLK_h:			Dispatch(EventListener::Event::h);				break;
		case SDLK_i:			Dispatch(EventListener::Event::i);				break;
		case SDLK_j:			Dispatch(EventListener::Event::j);				break;
		case SDLK_k:			Dispatch(EventListener::Event::k);				break;
		case SDLK_l:			Dispatch(EventListener::Event::l);				break;
		case SDLK_m:			Dispatch(EventListener::Event::m);				break;
		case SDLK_n:			Dispatch(EventListener::Event::n);				break;
		case SDLK_o:			Dispatch(EventListener::Event::o);				break;
		case SDLK_p:			Dispatch(EventListener::Event::p);				break;
		case SDLK_q:			Dispatch(EventListener::Event::q);				break;
		case SDLK_r:			Dispatch(EventListener::Event::r);				break;
		case SDLK_s:			Dispatch(EventListener::Event::s);				break;
		case SDLK_t:			Dispatch(EventListener::Event::t);				break;
		case SDLK_u:			Dispatch(EventListener::Event::u);				break;
		case SDLK_v:			Dispatch(EventListener::Event::v);				break;
		case SDLK_w:			Dispatch(EventListener::Event::w);				break;
		case SDLK_x:			Dispatch(EventListener::Event::x);				break;
		case SDLK_y:			Dispatch(EventListener::Event::y);				break;
		case SDLK_z:			Dispatch(EventListener::Event::z);				break;

		default: break;
		}
		break;

		// Event Types
		switch (evn.type)
		{
		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			break;

		default: break;
		}
	}
}