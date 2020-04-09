/*
    _   ___ ___  _   _ ___ _  _  ___  _    ___   ___
   /_\ | _ \   \| | | |_ _| \| |/ _ \| |  / _ \ / __|
  / _ \|   / |) | |_| || || .` | (_) | |_| (_) | (_ |
 /_/ \_\_|_\___/ \___/|___|_|\_|\___/|____\___/ \___|

  Log library for Arduino
  version 1.0.3
  https://github.com/thijse/Arduino-Log

Licensed under the MIT License <http://opensource.org/licenses/MIT>.

*/

#include "Log.h"

void Logging::begin(int level, Print* logOutput, bool showLevel)
{
#ifndef DISABLE_LOGGING
	setLevel(level);
	setShowLevel(showLevel);
	_logOutput = logOutput;
#endif
}

void Logging::setLevel(int level)
{
#ifndef DISABLE_LOGGING
	_level = constrain(level, LOG_LEVEL_SILENT, LOG_LEVEL_VERBOSE);
#endif
}

int Logging::getLevel() const
{
#ifndef DISABLE_LOGGING
	return _level;
#else
	return 0;
#endif
}

void Logging::setShowLevel(bool showLevel)
{
#ifndef DISABLE_LOGGING
	_showLevel = showLevel;
#endif
}

bool Logging::getShowLevel() const
{
#ifndef DISABLE_LOGGING
	return _showLevel;
#else
	return false;
#endif
}

void Logging::setPrefix(printfunction f)
{
#ifndef DISABLE_LOGGING
	_prefix = f;
#endif
}

void Logging::setSuffix(printfunction f)
{
#ifndef DISABLE_LOGGING
	_suffix = f;
#endif
}

void Logging::print(const __FlashStringHelper *format, va_list args)
{
#ifndef DISABLE_LOGGING	  	
	PGM_P p = reinterpret_cast<PGM_P>(format);
	char c = pgm_read_byte(p++);
	for(;c != 0; c = pgm_read_byte(p++))
	{
		if (c == '%')
		{
			c = pgm_read_byte(p++);
			printFormat(c, &args);
		}
		else
		{
			_logOutput->print(c);
		}
	}
#endif
}

void Logging::print(const char *format, va_list args) {
#ifndef DISABLE_LOGGING	  	
	for (; *format != 0; ++format)
	{
		if (*format == '%')
		{
			++format;
			printFormat(*format, &args);
		}
		else
		{
			_logOutput->print(*format);
		}
	}
#endif
}

void Logging::printFormat(const char format, va_list *args) {
#ifndef DISABLE_LOGGING
	if (format == '%')
	{
		_logOutput->print(format);
	}
	else if (format == 's')
	{
		register char *s = (char *)va_arg(*args, int);
		_logOutput->print(s);
	}
	else if (format == 'S')
	{
		register __FlashStringHelper *s = (__FlashStringHelper *)va_arg(*args, int);
		_logOutput->print(s);
	}
	else if (format == 'd' || format == 'i')
	{
		_logOutput->print(va_arg(*args, int), DEC);
	}
	else if (format == 'D' || format == 'F')
	{
		_logOutput->print(va_arg(*args, double));
	}
	else if (format == 'x')
	{
		_logOutput->print(va_arg(*args, int), HEX);
	}
	else if (format == 'X')
	{
		_logOutput->print("0x");
		_logOutput->print(va_arg(*args, int), HEX);
	}
	else if (format == 'b')
	{
		_logOutput->print(va_arg(*args, int), BIN);
	}
	else if (format == 'B')
	{
		_logOutput->print("0b");
		_logOutput->print(va_arg(*args, int), BIN);
	}
	else if (format == 'l')
	{
		_logOutput->print(va_arg(*args, long), DEC);
	}
	else if (format == 'c')
	{
		_logOutput->print((char) va_arg(*args, int));
	}
	else if(format == 't')
	{
		if (va_arg(*args, int) == 1)
		{
			_logOutput->print("T");
		}
		else
		{
			_logOutput->print("F");
		}
	}
	else if (format == 'T')
	{
		if (va_arg(*args, int) == 1)
		{
			_logOutput->print(F("true"));
		}
		else
		{
			_logOutput->print(F("false"));
		}
	}
#endif
}
 
Logging Log = Logging();
