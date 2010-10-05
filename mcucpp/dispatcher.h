
//*****************************************************************************
//
// Title		: C++ simple task dispatcher
// Author		: Konstantin Chizhov
// Date			: 2010
// Target MCU	: Atmel mega AVR, TINY avr AND Xmega Series
//
//       This code is distributed under the GNU Public License
//       which can be found at http://www.gnu.org/licenses/gpl.txt
//
// As a special exception, you may use this file as part of a free software
// library without restriction. Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License. This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.
//*****************************************************************************

#include "containers.h"
#include "util.h"

typedef void (*task_t)();

typedef struct
{
	task_t task;
	uint16_t period;
} timer_t;

template<uint8_t TasksLenght, uint8_t TimersLenght>
class Dispatcher
{
public:

	static void Init()
	{	
		_tasks.Clear();
		for(uint8_t i=0; i<_timers.Size(); i++)
		{
			_timers[i].task = 0;
			_timers[i].period = 0;
		}
	}

	static void SetTask(task_t task)
	{
		ATOMIC{	_tasks.Write(task);}
	}

	static void SetTimer(task_t task, uint16_t period) __attribute__ ((noinline))
	{
		uint8_t i_idle=0;
		ATOMIC
		{
			for(uint8_t i=0; i<_timers.Size(); i++)
			{
				if(_timers[i].task == 0)
				{
					i_idle = i;
				}
				if(_timers[i].task == task)
				{
					_timers[i].period = period;
					return;
				}
			}
			_timers[i_idle].task = task;
			_timers[i_idle].period = period;
		}
	}

	static void StopTimer(task_t task)
	{
		ATOMIC
		{
			for(uint8_t i=0; i<_timers.Size(); i++)
			{
				if(_timers[i].task == task)
				{
					_timers[i].task = 0;
					return;
				}
			}
		}
	}

	static void Poll()
	{
		task_t task;
		//NOTE: no beed to block task Queue here. This is the only place the Queue read.
		//cli();
		if(_tasks.Read(task))
		{
		//	sei();
			task();
		}
		//sei();
	}

	static void TimerHandler()
	{
		for(uint8_t i=0; i<_timers.Size(); i++)
		{
			if(_timers[i].task != 0 && --_timers[i].period == 0)
			{
				_tasks.Write(_timers[i].task); 
				_timers[i].task = 0;
			}
		}
	}

private:
	static Queue<TasksLenght, task_t> _tasks;
	static Array<TimersLenght, timer_t> _timers;
};

template<uint8_t TasksLenght, uint8_t TimersLenght>
Array<TimersLenght, timer_t> Dispatcher<TasksLenght, TimersLenght>::_timers;

template<uint8_t TasksLenght, uint8_t TimersLenght>
Queue<TasksLenght, task_t> Dispatcher<TasksLenght, TimersLenght>::_tasks;



