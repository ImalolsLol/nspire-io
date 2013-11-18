#include "ios_base.hpp"

using namespace nio;

template<class T>
typename ios_base<T>::fmtflags ios_base<T>::flags() const
{
	return f;
}

template<class T>
typename ios_base<T>::fmtflags ios_base<T>::flags(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = fmtfl;
	return tmp;
}

template<class T>
typename ios_base<T>::fmtflags ios_base<T>::setf(fmtflags fmtfl)
{
	fmtflags tmp = f;
	f = (fmtflags)(f | fmtfl);
	return tmp;
}

template<class T>
typename ios_base<T>::fmtflags ios_base<T>::setf(fmtflags fmtfl, fmtflags mask)
{
	fmtflags tmp = f;
	f = (fmtflags)( (fmtfl & mask) | ( f & ~mask ) );
	return tmp;
}

template<class T>
void ios_base<T>::unsetf(fmtflags mask)
{
	f = (fmtflags)(f & ~mask);
}

template<class T>
streamsize ios_base<T>::precision() const
{
	return p;
}

template<class T>
streamsize ios_base<T>::precision(streamsize prec)
{
	streamsize tmp = p;
	p = prec;
	return tmp;
}

template<class T>
streamsize ios_base<T>::width() const
{
	return w;
}

template<class T>
streamsize ios_base<T>::width(streamsize wide)
{
	streamsize tmp = w;
	w = wide;
	return tmp;
}

template<class T>
bool ios_base<T>::good() const
{
	return s == ios_base<T>::goodbit;
}

template<class T>
bool ios_base<T>::eof() const
{
	return s == ios_base<T>::eofbit;
}

template<class T>
bool ios_base<T>::fail() const
{
	return s == ios_base<T>::failbit || s == ios_base<T>::badbit;
}

template<class T>
bool ios_base<T>::bad() const
{
	return s == ios_base<T>::badbit;
}

template<class T>
bool ios_base<T>::operator!() const
{
	return fail();
}

template<class T>
typename ios_base<T>::iostate ios_base<T>::rdstate() const
{
	return s;
}

template<class T>
void ios_base<T>::setstate(iostate state)
{
	s = (iostate)(s | state);
}

template<class T>
void ios_base<T>::clear(iostate state)
{
	s = state;
}

template<class T>
T& ios_base<T>::operator<<(const char* val)
{
	write(val,strlen(val));
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator<<(const int val)
{
	char buf[50] = {0};
	char fmt[20] = {0};
	
	if(f & showbase && !(f & dec))
	{
		if(f & hex)
			strcat(fmt,"0x");
		else
			strcat(fmt,"0");
	}
	strcat(fmt,"%");
	
	if(f & left)
		strcat(fmt,"-");
	
	if(w)
		strcat(fmt,"*");
	
	if(f & hex)
		strcat(fmt,(f & uppercase) ? "X" : "x");
	else if(f & oct)
		strcat(fmt,"o");
	else
		strcat(fmt,"d");
	
	int num;
	if(w)
		num = sprintf(buf,fmt,w,val);
	else
		num = sprintf(buf,fmt,val);

	write(buf,num);
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator<<(const bool val)
{
	if(f & boolalpha)
	{
		if(val)
			write("true",4);
		else
			write("false",5);
	}
	else
	{
		if(val)
			write("1",1);
		else
			write("0",1);
	}
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator<<(ios_base& (*pf)(ios_base&))
{
	return static_cast<T&>(pf(*this));
}

template<class T>
T& ios_base<T>::operator>>(char* val)
{
	getline(val,50);
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator>>(int& val)
{
	char buf[50] = {0};
	
	getline(buf,50);
	if(buf[0] == 0)
	{
		clear(eofbit);
		return static_cast<T&>(*this);
	}

	val = strtol(buf,NULL,0);
	
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator>>(bool& val)
{
	char buf[50] = {0};
	
	getline(buf,50);
	if(strcmp(buf,"1") == 0 || strcmp(buf,"true") == 0 || strcmp(buf,"yes") == 0)
		val = true;
	else
		val = false;
	
	return static_cast<T&>(*this);
}

template<class T>
T& ios_base<T>::operator>>(ios_base& (*pf)(ios_base&))
{
	return static_cast<T&>(pf(*this));
}
