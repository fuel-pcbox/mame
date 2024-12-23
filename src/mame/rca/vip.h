// license:BSD-3-Clause
// copyright-holders:Curt Coder
#pragma once

#ifndef MAME_RCA_VIP_H
#define MAME_RCA_VIP_H

#include "bus/vip/byteio.h"
#include "bus/vip/exp.h"
#include "cpu/cosmac/cosmac.h"
#include "imagedev/cassette.h"
#include "imagedev/snapquik.h"
#include "machine/ram.h"
#include "sound/discrete.h"
#include "video/cdp1861.h"

#define SCREEN_TAG      "screen"
#define CDP1802_TAG     "u1"
#define CDP1861_TAG     "u2"
#define DISCRETE_TAG    "discrete"


class vip_state : public driver_device
{
public:
	vip_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, CDP1802_TAG)
		, m_vdc(*this, CDP1861_TAG)
		, m_cassette(*this, "cassette")
		, m_beeper(*this, DISCRETE_TAG)
		, m_byteio(*this, VIP_BYTEIO_PORT_TAG)
		, m_exp(*this, "exp")
		, m_ram(*this, RAM_TAG)
		, m_rom(*this, CDP1802_TAG)
		, m_chip8(*this, "chip8")
		, m_chip8x(*this, "chip8x")
		, m_run(*this, "RUN")
		, m_keypad(*this, "KEYPAD")
		, m_io_beeper(*this, "BEEPER")
		, m_8000(1)
		, m_vdc_int(CLEAR_LINE)
		, m_vdc_dma_out(CLEAR_LINE)
		, m_vdc_ef1(CLEAR_LINE)
		, m_exp_int(CLEAR_LINE)
		, m_exp_dma_out(CLEAR_LINE)
		, m_exp_dma_in(CLEAR_LINE)
		, m_byteio_ef3(CLEAR_LINE)
		, m_byteio_ef4(CLEAR_LINE)
		, m_exp_ef1(CLEAR_LINE)
		, m_exp_ef3(CLEAR_LINE)
		, m_exp_ef4(CLEAR_LINE)
		, m_leds(*this, "led%u", 0U)
	{ }

	void vp111(machine_config &config);
	void vip(machine_config &config);

	DECLARE_INPUT_CHANGED_MEMBER(reset_w);
	DECLARE_INPUT_CHANGED_MEMBER(beeper_w);

private:
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	void update_interrupts();

	uint8_t read(offs_t offset);
	void write(offs_t offset, uint8_t data);
	uint8_t io_r(offs_t offset);
	void io_w(offs_t offset, uint8_t data);

	int clear_r();
	int ef1_r();
	int ef2_r();
	int ef3_r();
	int ef4_r();
	void q_w(int state);

	void vdc_int_w(int state);
	void vdc_dma_out_w(int state);
	void vdc_ef1_w(int state);

	void byteio_inst_w(int state);

	void exp_int_w(int state);
	void exp_dma_out_w(int state);
	void exp_dma_in_w(int state);

	DECLARE_QUICKLOAD_LOAD_MEMBER(quickload_cb);

	void vip_io(address_map &map) ATTR_COLD;
	void vip_mem(address_map &map) ATTR_COLD;

	virtual void machine_start() override ATTR_COLD;
	virtual void machine_reset() override ATTR_COLD;

	required_device<cosmac_device> m_maincpu;
	required_device<cdp1861_device> m_vdc;
	required_device<cassette_image_device> m_cassette;
	required_device<discrete_sound_device> m_beeper;
	required_device<vip_byteio_port_device> m_byteio;
	required_device<vip_expansion_slot_device> m_exp;
	required_device<ram_device> m_ram;
	required_memory_region m_rom;
	required_memory_region m_chip8;
	required_memory_region m_chip8x;
	required_ioport m_run;
	required_ioport m_keypad;
	required_ioport m_io_beeper;

	// memory state
	int m_8000;

	// interrupt state
	int m_vdc_int;
	int m_vdc_dma_out;
	int m_vdc_ef1;
	int m_exp_int;
	int m_exp_dma_out;
	int m_exp_dma_in;
	int m_byteio_ef3;
	int m_byteio_ef4;
	int m_exp_ef1;
	int m_exp_ef3;
	int m_exp_ef4;

	// keyboard state
	int m_keylatch = 0;

	// expansion state
	uint8_t m_byteio_data = 0;
	output_finder<3> m_leds;
};

#endif // MAME_RCA_VIP_H
