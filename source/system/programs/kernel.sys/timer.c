// Copyright 2007-2022 Jeremiah Griffin
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

// Includes
#include <kernel.lib/screen.h>
#include <kernel.sys/irq.h>
#include <kernel.sys/timer.h>

// Variables
int volatile timerTicks;

/**
 * ~ Wait
 * ! Waits for the specified amount of ticks.
 * @ ticks Number of ticks to wait for.
 * #
 */
void Wait(int ticks)
{
  int ticks2;

  ticks2 = timerTicks + ticks;
  while (timerTicks < ticks2);
}

/**
 * ~ SystemUptime
 * ! Gets the approximate system uptime, in seconds.
 * @
 * # timerTicks / 18
 */
int SystemUptime()
{
	return timerTicks / 18;
}

/**
 * ~ SystemTicks
 * ! Gets the number of system ticks.
 * @
 * # timerTicks
 */
int SystemTicks()
{
	return timerTicks;
}

/**
 * ~ TimerHandler
 * ! Updates the tick count.
 * @ registers Register data at the time of the interrupt.
 * #
 */
void TimerHandler(struct TRegisters *registers)
{
	// Get rid of those nasty "unused parameter" warnings
	if (registers->intNumber == 0) { }

	timerTicks++;
}

/**
 * ~ TimerInitialize
 * ! Initializes the timer.
 * @
 * #
 */
void TimerInitialize()
{
	timerTicks = 0;

	IRQInstall(0, TimerHandler);
}
