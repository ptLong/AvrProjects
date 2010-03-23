#pragma once

#ifndef PORTS_HPP
#define PORTS_HPP
#include <avr/io.h>
#include "static_assert.h"
#include "Typelist.h"

#define MAKE_PORT(portName, ddrName, pinName, className, ID) \
	struct className{\
		static volatile uint8_t &data()\
		{\
			return portName;\
		}\
		static volatile uint8_t &dir()\
		{\
			return ddrName;\
		}\
		static volatile uint8_t &pin()\
		{\
			return pinName;\
		}\
		static void Write(uint8_t value)\
		{\
			data() = value;\
		}\
		static uint8_t Read()\
		{\
			return data();\
		}\
		enum{Id = ID};\
		enum{Width=8};\
	};

#ifdef PORTA
MAKE_PORT(PORTA, DDRA, PINA, Porta, 'A')
#endif


#ifdef PORTB
MAKE_PORT(PORTB, DDRB, PINB, Portb, 'B')
#endif


#ifdef PORTC
MAKE_PORT(PORTC, DDRC, PINC, Portc, 'C')
#endif


#ifdef PORTD
MAKE_PORT(PORTD, DDRD, PIND, Portd, 'D')
#endif


#ifdef PORTE
MAKE_PORT(PORTE, DDRE, PINE, Porte, 'E')
#endif


#ifdef PORTF
MAKE_PORT(PORTF, DDRF, PINF, Portf, 'F')
#endif

#ifdef PORTG
MAKE_PORT(PORTG, DDRG, PING, Portg, 'G')
#endif


class Pin
{
public:
	Pin(volatile unsigned char &port, uint8_t pin)
	:_port(port)
	{
		_pin = pin; 
	}

	void Set()const
	{
		_port |= (1 << _pin);
	}

	void Set(uint8_t val)const
	{
		if(val)
			Set();
		else Clear();
	}

	void Clear()const
	{
		_port &= (uint8_t)~(1 << _pin);
	}

	void Togle()const
	{
		_port ^= (1 << _pin);
	}

	void SetDirWrite()const
	{
		*(&_port - 1) |= (1 << _pin);
	}

	void SetDirRead()const
	{
		*(&_port - 1) &= (uint8_t)~(1 << _pin);
	}

	uint8_t IsSet()const
	{
		return (*(&_port - 2)) & (uint8_t)(1 << _pin);
	}

private:
	volatile unsigned char &_port; 
	uint8_t _pin;
}; 



template<class PORT, uint8_t PIN>
class TPin
{
	BOOST_STATIC_ASSERT(PIN < PORT::Width);
public:
	typedef PORT Port;
	enum{Number = PIN};

	static void Set()
	{
		PORT::data() |= (1 << PIN);
	}

	static void Set(uint8_t val)
	{
		if(val)
			Set();
		else Clear();
	}

	static void Clear()
	{
		PORT::data() &= (uint8_t)~(1 << PIN);
	}

	static void Togle()
	{
		PORT::data() ^= (1 << PIN);
	}

	static void SetDirRead()
	{
		PORT::dir() &= (uint8_t)~(1 << PIN);
	}

	static void SetDirWrite()
	{
		PORT::dir() |= (1 << PIN);
	}

	static uint8_t IsSet()
	{
		return PORT::pin() & (uint8_t)(1 << PIN);
	}	
	

	static void WaiteForSet()
	{
		while(IsSet()==0){}
	}

	static void WaiteForClear()
	{
		while(IsSet()){}
	}
}; 

#ifdef PORTA
typedef TPin<Porta, 0> Pa0;
typedef TPin<Porta, 1> Pa1;
typedef TPin<Porta, 2> Pa2;
typedef TPin<Porta, 3> Pa3;
typedef TPin<Porta, 4> Pa4;
typedef TPin<Porta, 5> Pa5;
typedef TPin<Porta, 6> Pa6;
typedef TPin<Porta, 7> Pa7;
#endif

#ifdef PORTB
typedef TPin<Portb, 0> Pb0;
typedef TPin<Portb, 1> Pb1;
typedef TPin<Portb, 2> Pb2;
typedef TPin<Portb, 3> Pb3;
typedef TPin<Portb, 4> Pb4;
typedef TPin<Portb, 5> Pb5;
typedef TPin<Portb, 6> Pb6;
typedef TPin<Portb, 7> Pb7;
#endif

#ifdef PORTC
typedef TPin<Portc, 0> Pc0;
typedef TPin<Portc, 1> Pc1;
typedef TPin<Portc, 2> Pc2;
typedef TPin<Portc, 3> Pc3;
typedef TPin<Portc, 4> Pc4;
typedef TPin<Portc, 5> Pc5;
typedef TPin<Portc, 6> Pc6;
typedef TPin<Portc, 7> Pc7;
#endif

#ifdef PORTD
typedef TPin<Portd, 0> Pd0;
typedef TPin<Portd, 1> Pd1;
typedef TPin<Portd, 2> Pd2;
typedef TPin<Portd, 3> Pd3;
typedef TPin<Portd, 4> Pd4;
typedef TPin<Portd, 5> Pd5;
typedef TPin<Portd, 6> Pd6;
typedef TPin<Portd, 7> Pd7;
#endif

#ifdef PORTE
typedef TPin<Porte, 0> Pe0;
typedef TPin<Porte, 1> Pe1;
typedef TPin<Porte, 2> Pe2;
typedef TPin<Porte, 3> Pe3;
typedef TPin<Porte, 4> Pe4;
typedef TPin<Porte, 5> Pe5;
typedef TPin<Porte, 6> Pe6;
typedef TPin<Porte, 7> Pe7;
#endif

#ifdef PORTF
typedef TPin<Portf, 0> Pf0;
typedef TPin<Portf, 1> Pf1;
typedef TPin<Portf, 2> Pf2;
typedef TPin<Portf, 3> Pf3;
typedef TPin<Portf, 4> Pf4;
typedef TPin<Portf, 5> Pf5;
typedef TPin<Portf, 6> Pf6;
typedef TPin<Portf, 7> Pf7;
#endif

#ifdef PORTG
typedef TPin<Portg, 0> Pg0;
typedef TPin<Portg, 1> Pg1;
typedef TPin<Portg, 2> Pg2;
typedef TPin<Portg, 3> Pg3;
typedef TPin<Portg, 4> Pg4;
typedef TPin<Portg, 5> Pg5;
typedef TPin<Portg, 6> Pg6;
typedef TPin<Portg, 7> Pg7;
#endif


using namespace Loki;
using namespace Loki::TL;

template<class TPIN, uint8_t POSITION>
struct PW	//Pin wrapper
{
	typedef TPIN Pin;
	enum{Position = POSITION};
};


 		template <class TList> struct GetPorts;
        
        template <> struct GetPorts<NullType>
        {
            typedef NullType Result;
        };

        template <class Head, class Tail>
        struct GetPorts< Typelist<Head, Tail> >
        {
        private:
			typedef typename Head::Pin::Port Port;
            typedef typename GetPorts<Tail>::Result L1;
        public:
            typedef Typelist<Port, L1> Result;
        };



 		template <class TList, class T> struct GetPinsWithPort;

        template <class T>
        struct GetPinsWithPort<NullType, T>
        {
            typedef NullType Result;
        };

        template <class T, class Tail, uint8_t N, uint8_t M>
        struct GetPinsWithPort<Typelist<PW<TPin<T, N>, M>, Tail>, T>
        {
            // Go all the way down the list removing the type
           typedef Typelist<PW<TPin<T, N>, M>, 
                    typename GetPinsWithPort<Tail, T>::Result>
                Result;
        };

        template <class Head, class Tail, class T>
        struct GetPinsWithPort<Typelist<Head, Tail>, T>
        {
            // Go all the way down the list removing the type
			 typedef typename GetPinsWithPort<Tail, T>::Result Result;
        };


		template <class TList> struct GetMask;
        template <> struct GetMask<NullType>
        {
            enum{value = 0};
        };
        template <class Head, class Tail>
        struct GetMask< Typelist<Head, Tail> >
        {
			enum{value = (1 << Head::Pin::Number) | GetMask<Tail>::value};
        };
		
	

		template <class TList> struct PinWriteIterator;
        template <> struct PinWriteIterator<NullType>
        {
           static void UppendValue(uint8_t value, uint8_t &result)
		   {   }
        };
        template <class Head, class Tail>
        struct PinWriteIterator< Typelist<Head, Tail> >
        {
			static inline void UppendValue(uint8_t value, uint8_t &result)
			{
				if(value & (1 << Head::Position))
					result |= (1 << Head::Pin::Number);
				PinWriteIterator<Tail>::UppendValue(value, result);
			}
        };


		template <class PortList, class PinList> struct PortWriteIterator;
        template <class PinList> struct PortWriteIterator<NullType, PinList>
        {
           static void Write(uint8_t value)
		   {   }
        };

        template <class Head, class Tail, class PinList>
        struct PortWriteIterator< Typelist<Head, Tail>, PinList>
        {
			typedef typename GetPinsWithPort<PinList, Head>::Result Pins;
			enum{Mask = GetMask<Pins>::value};

			static void Write(uint8_t value)
			{   
				if(Length<Pins>::value == 1)
					Pins::Head::Pin::Set(value & Pins::Head::Position);

				uint8_t result=0;
				PinWriteIterator<Pins>::UppendValue(value, result);
				Head::data() =  (Head::data() & ~Mask) | result ;
				PortWriteIterator<Tail, PinList>::Write(value);
			}
        };

	

template<class PINS>
struct PinList
{
	typedef typename GetPorts<PINS>::Result PinsToPorts;
	typedef typename NoDuplicates<PinsToPorts>::Result Ports; 
	static void Write(uint8_t value)
	{
		PortWriteIterator<Ports, PINS>::Write(value);
	}
};

template<class HI, class LOW>
class PowerDriver
{
public:
	PowerDriver()
	{
		hi.SetDirWrite();
		low.SetDirWrite();
	}
	void SetHight()
	{
		hi.Set();
		low.Set();
	}

	void SetLow()
	{
		low.Clear();
		hi.Clear();
	}

	void Free()
	{
		low.Clear();
		hi.Set();
	}
HI hi;
LOW low;
};


#endif
