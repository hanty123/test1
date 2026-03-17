/*
 * (C) Copyright 2011, Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * (C) Copyright 2011, Julius Baxter <julius@opencores.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "spr_defs.h"
#include "../Src/dev.h"

#define		CONFIG_DCACHE_ENABLE

// cache를 먼저 enable한 후에 reset,ispm_text,data,bss를 복사하기 위해서는 cache제어 함수를 ISPM으로 설정하면 안됨!!!
void mtspr0(UINT anSpr, UINT anVal)		// ISPM으로 설정하면 안됨!!!
{
	asm volatile ("l.mtspr\t\t%0,%1,0": : "r" (anSpr), "r" (anVal));
}

UINT mfspr0(UINT anSpr)					// ISPM으로 설정하면 안됨!!!
{
	UINT anVal;
	asm volatile ("l.mfspr\t\t%0,%1,0" : "=r" (anVal) : "r" (anSpr));
	return anVal;
}

typedef unsigned long	u32;
int icache_status(void);
void icache_enable(void);
void icache_disable(void);

void flush_dcache_range(unsigned long addr, unsigned long stop)
{
#ifdef CONFIG_DCACHE_ENABLE
	u32 block_size = (mfspr0(SPR_DCCFGR) & SPR_DCCFGR_CBS) ? 32 : 16;
	while (addr < stop) {
		mtspr0(SPR_DCBFR, addr);
		addr += block_size;
	}
#else
	UNUSED_ARG(addr);
	UNUSED_ARG(stop);
#endif
}

void invalidate_dcache_range(unsigned long addr, unsigned long stop)
{
#ifdef CONFIG_DCACHE_ENABLE
	u32 block_size = (mfspr0(SPR_DCCFGR) & SPR_DCCFGR_CBS) ? 32 : 16;
	while (addr < stop) {
		mtspr0(SPR_DCBIR, addr);
		addr += block_size;
	}
#else
	UNUSED_ARG(addr);
	UNUSED_ARG(stop);
#endif
}

void invalidate_icache_range(unsigned long addr, unsigned long stop)
{
	u32 block_size = (mfspr0(SPR_ICCFGR) & SPR_ICCFGR_CBS) ? 32 : 16;
	u32 ie = icache_status();

	icache_disable();
	while (addr < stop) {
		mtspr0(SPR_ICBIR, addr);
		addr += block_size;
	}
	if (ie)
		icache_enable();
}

void flush_cache(unsigned long addr, unsigned long size)
{
	flush_dcache_range(addr, addr + size);
#ifdef CONFIG_DCACHE_ENABLE
	invalidate_icache_range(addr, addr + size);
#endif
}

int icache_status(void)
{
	return mfspr0(SPR_SR) & SPR_SR_ICE;
}

int checkicache(void)
{
	unsigned long iccfgr;
	unsigned long cache_set_size;
	unsigned long cache_ways;
	unsigned long cache_block_size;

	iccfgr = mfspr0(SPR_ICCFGR);
	cache_ways = 1 << (iccfgr & SPR_ICCFGR_NCW);
	cache_set_size = 1 << ((iccfgr & SPR_ICCFGR_NCS) >> 3);
	cache_block_size = (iccfgr & SPR_ICCFGR_CBS) ? 32 : 16;

	return cache_set_size * cache_ways * cache_block_size;
}

int dcache_status(void)
{
	return mfspr0(SPR_SR) & SPR_SR_DCE;
}

int checkdcache(void)
{
	unsigned long dccfgr;
	unsigned long cache_set_size;
	unsigned long cache_ways;
	unsigned long cache_block_size;

	dccfgr = mfspr0(SPR_DCCFGR);
	cache_ways = 1 << (dccfgr & SPR_DCCFGR_NCW);
	cache_set_size = 1 << ((dccfgr & SPR_DCCFGR_NCS) >> 3);
	cache_block_size = (dccfgr & SPR_DCCFGR_CBS) ? 32 : 16;

	return cache_set_size * cache_ways * cache_block_size;
}

void dcache_enable(void)
{
	mtspr0(SPR_SR, mfspr0(SPR_SR) | SPR_SR_DCE);
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
}

void dcache_disable(void)
{
	mtspr0(SPR_SR, mfspr0(SPR_SR) & ~SPR_SR_DCE);
}

void icache_enable(void)
{
	mtspr0(SPR_SR, mfspr0(SPR_SR) | SPR_SR_ICE);
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
	asm volatile("l.nop");
}

void icache_disable(void)
{
	mtspr0(SPR_SR, mfspr0(SPR_SR) & ~SPR_SR_ICE);
}

int cache_init(void)
{
	if (mfspr0(SPR_UPR) & SPR_UPR_ICP) {
		icache_disable();
		invalidate_icache_range(0, checkicache());
		icache_enable();
//			icache_disable();
	}
#ifdef CONFIG_DCACHE_ENABLE
	if (mfspr0(SPR_UPR) & SPR_UPR_DCP) {
		dcache_disable();
		invalidate_dcache_range(0, checkdcache());
		dcache_enable();
//			dcache_disable();
		//printf("%s %d \n",__func__,__LINE__);
	}
#endif
	return 0;
}

void cache_invalidate_all(void)
{
    invalidate_icache_range(0, checkicache());
    invalidate_dcache_range(0, checkdcache());
}

