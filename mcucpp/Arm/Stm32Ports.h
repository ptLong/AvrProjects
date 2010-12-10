#pragma once

#ifndef IOPORTS_HPP
#error "Do not include this file directly. Use ioports.h instead."
#endif

#ifndef STM32_PORTS_H
#define STM32_PORTS_H

namespace IO
{
	inline unsigned Unpack32(unsigned value)
	{
		value = (value & 0xf0) << 12 | (value & 0x0f);
		value = (value & 0x000C000C) << 6 | (value & 0x00030003);
		value = (value & 0x02020202) << 3 | (value & 0x01010101);
		return value;
	}

	inline unsigned Pack32(unsigned value)
	{
		value = (value & 0x10101010) >> 3 | (value & 0x01010101);
		value = (value & 0x03000300) >> 6 | (value & 0x00030003);
		value = (value & 0x000f0000) >> 12 | (value & 0x0f);
		return value;
	}

#define MAKE_PORT(CRL, CRH, IDR, ODR, BSRR, BRR, LCKR, className, ID) \
	class className{\
	public:\
		typedef uint16_t DataT;\
	public:\
		static void Write(DataT value)\
		{\
			ODR = value;\
		}\
		static void ClearAndSet(DataT clearMask, DataT value)\
		{\
			BSRR = value | (uint32_t)clearMask << 16;\
		}\
		static void DirClearAndSet(DataT clearMask, DataT value)\
		{\
			DirWrite(DirRead() & clearMask | value);\
		}\
		static DataT Read()\
		{\
			return ODR;\
		}\
		static void DirWrite(DataT value)\
		{\
			CRL = Unpack32(value);\
			CRH = Unpack32(value>>8);\
		}\
		static DataT DirRead()\
		{\
			DataT tmp = Pack32(CRH) << 8;\
			return Pack32(CRL) | tmp;\
		}\
		static void Set(DataT value)\
		{\
			BSRR = value;\
		}\
		static void Clear(DataT value)\
		{\
			BSRR = (uint32_t)value << 16;\
		}\
		static void Togle(DataT value)\
		{\
			ODR ^= value;\
		}\
		static void DirSet(DataT value)\
		{\
			unsigned tmpl = Unpack32(value);\
			unsigned tmph = Unpack32(value >> 8);\
			CRL |= tmpl;\
			CRH |= tmph;\
		}\
		static void DirClear(DataT value)\
		{\
			unsigned tmpl = Unpack32(value);\
			unsigned tmph = Unpack32(value >> 8);\
			CRL &= ~tmpl;\
			CRH &= ~tmph;\
		}\
		static DataT PinRead()\
		{\
			return IDR;\
		}\
		static void DirTogle(DataT value)\
		{\
			unsigned tmpl = Unpack32(value);\
			unsigned tmph = Unpack32(value >> 8);\
			CRL ^= tmpl;\
			CRH ^= tmph;\
		}\
		enum{Id = ID};\
		enum{Width=16};\
	};

//==================================================================================================
#if defined(__ICCARM__)

#ifdef USE_PORTA
MAKE_PORT(GPIOA_CRL, GPIOA_CRH, GPIOA_IDR, GPIOA_ODR, GPIOA_BSRR, GPIOA_BRR, GPIOA_LCKR, Porta, 'A')
#endif

#ifdef USE_PORTB
MAKE_PORT(GPIOB_CRL, GPIOB_CRH, GPIOB_IDR, GPIOB_ODR, GPIOB_BSRR, GPIOB_BRR, GPIOB_LCKR, Portb, 'B')
#endif

#ifdef USE_PORTC
MAKE_PORT(GPIOC_CRL, GPIOC_CRH, GPIOC_IDR, GPIOC_ODR, GPIOC_BSRR, GPIOC_BRR, GPIOC_LCKR, Portc, 'C')
#endif

#ifdef USE_PORTD
MAKE_PORT(GPIOD_CRL, GPIOD_CRH, GPIOD_IDR, GPIOD_ODR, GPIOD_BSRR, GPIOD_BRR, GPIOD_LCKR, Portd, 'D')
#endif

#ifdef USE_PORTE
MAKE_PORT(GPIOE_CRL, GPIOE_CRH, GPIOE_IDR, GPIOE_ODR, GPIOE_BSRR, GPIOE_BRR, GPIOE_LCKR, Porte, 'E')
#endif

#ifdef USE_PORTF
MAKE_PORT(GPIOF_CRL, GPIOF_CRH, GPIOF_IDR, GPIOF_ODR, GPIOF_BSRR, GPIOF_BRR, GPIOF_LCKR, Portf, 'F')
#endif

#ifdef USE_PORTG
MAKE_PORT(GPIOG_CRL, GPIOG_CRH, GPIOG_IDR, GPIOG_ODR, GPIOG_BSRR, GPIOG_BRR, GPIOG_LCKR, Portg, 'G')
#endif

#ifdef USE_PORTH
MAKE_PORT(GPIOH_CRL, GPIOH_CRH, GPIOH_IDR, GPIOH_ODR, GPIOH_BSRR, GPIOH_BRR, GPIOH_LCKR, Porth, 'H')
#endif

#ifdef USE_PORTJ
MAKE_PORT(GPIOJ_CRL, GPIOJ_CRH, GPIOJ_IDR, GPIOJ_ODR, GPIOJ_BSRR, GPIOJ_BRR, GPIOJ_LCKR, Portj, 'J')
#endif

#ifdef USE_PORTK
MAKE_PORT(GPIOK_CRL, GPIOK_CRH, GPIOK_IDR, GPIOK_ODR, GPIOK_BSRR, GPIOK_BRR, GPIOK_LCKR, Portk, 'K')
#endif
//==================================================================================================
#elif defined(__CC_ARM)

#ifdef USE_PORTA
MAKE_PORT(GPIOA->CRL, GPIOA->CRH, GPIOA->IDR, GPIOA->ODR, GPIOA->BSRR, GPIOA->BRR, GPIOA->LCKR, Porta, 'A')
#endif

#ifdef USE_PORTB
MAKE_PORT(GPIOB->CRL, GPIOB->CRH, GPIOB->IDR, GPIOB->ODR, GPIOB->BSRR, GPIOB->BRR, GPIOB->LCKR, Portb, 'B')
#endif

#ifdef USE_PORTC
MAKE_PORT(GPIOC->CRL, GPIOC->CRH, GPIOC->IDR, GPIOC->ODR, GPIOC->BSRR, GPIOC->BRR, GPIOC->LCKR, Portc, 'C')
#endif

#ifdef USE_PORTD
MAKE_PORT(GPIOD->CRL, GPIOD->CRH, GPIOD->IDR, GPIOD->ODR, GPIOD->BSRR, GPIOD->BRR, GPIOD->LCKR, Portd, 'D')
#endif

#ifdef USE_PORTE
MAKE_PORT(GPIOE->CRL, GPIOE->CRH, GPIOE->IDR, GPIOE->ODR, GPIOE->BSRR, GPIOE->BRR, GPIOE->LCKR, Porte, 'E')
#endif

#ifdef USE_PORTF
MAKE_PORT(GPIOF->CRL, GPIOF->CRH, GPIOF->IDR, GPIOF->ODR, GPIOF->BSRR, GPIOF->BRR, GPIOF->LCKR, Portf, 'F')
#endif

#ifdef USE_PORTG
MAKE_PORT(GPIOG->CRL, GPIOG->CRH, GPIOG->IDR, GPIOG->ODR, GPIOG->BSRR, GPIOG->BRR, GPIOG->LCKR, Portg, 'G')
#endif

#ifdef USE_PORTH
MAKE_PORT(GPIOH->CRL, GPIOH->CRH, GPIOH->IDR, GPIOH->ODR, GPIOH->BSRR, GPIOH->BRR, GPIOH->LCKR, Porth, 'H')
#endif

#ifdef USE_PORTJ
MAKE_PORT(GPIOJ->CRL, GPIOJ->CRH, GPIOJ->IDR, GPIOJ->ODR, GPIOJ->BSRR, GPIOJ->BRR, GPIOJ->LCKR, Portj, 'J')
#endif

#ifdef USE_PORTK
MAKE_PORT(GPIOK->CRL, GPIOK->CRH, GPIOK->IDR, GPIOK->ODR, GPIOK->BSRR, GPIOK->BRR, GPIOK->LCKR, Portk, 'K')
#endif
//==================================================================================================
#else
#error Not supported compiler
#endif

}//namespace IO

#endif