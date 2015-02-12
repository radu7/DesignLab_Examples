-- file: papilio_clocks.vhd
-- 
-- (c) Copyright 2008 - 2011 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
------------------------------------------------------------------------------
-- User entered comments
------------------------------------------------------------------------------
-- None
--
------------------------------------------------------------------------------
-- "Output    Output      Phase     Duty      Pk-to-Pk        Phase"
-- "Clock    Freq (MHz) (degrees) Cycle (%) Jitter (ps)  Error (ps)"
------------------------------------------------------------------------------
-- CLK_OUT1___100.000______0.000______50.0______247.415____196.077
-- CLK_OUT2____50.000______0.000______50.0______303.266____196.077
-- CLK_OUT3____32.000______0.000______50.0______345.456____196.077
-- CLK_OUT4____25.000______0.000______50.0______364.543____196.077
-- CLK_OUT5____10.000______0.000______50.0______439.530____196.077
-- CLK_OUT6_____8.000______0.000______50.0______458.791____196.077
--
------------------------------------------------------------------------------
-- "Input Clock   Freq (MHz)    Input Jitter (UI)"
------------------------------------------------------------------------------
-- __primary__________32.000____________0.010

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
use ieee.numeric_std.all;

library unisim;
use unisim.vcomponents.all;

entity papilio_clocks is
port
 (-- Clock in ports
  CLK_32Mhz_in           : in     std_logic;
  -- Clock out ports
  CLK_100Mhz          : out    std_logic;
  CLK_50Mhz          : out    std_logic;
  CLK_32Mhz          : out    std_logic;
  CLK_25Mhz          : out    std_logic;
  CLK_10Mhz          : out    std_logic;
  CLK_8Mhz          : out    std_logic
 );
end papilio_clocks;

architecture xilinx of papilio_clocks is
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of xilinx : architecture is "papilio_clocks,clk_wiz_v3_6,{component_name=papilio_clocks,use_phase_alignment=true,use_min_o_jitter=false,use_max_i_jitter=false,use_dyn_phase_shift=false,use_inclk_switchover=false,use_dyn_reconfig=false,feedback_source=FDBK_AUTO,primtype_sel=PLL_BASE,num_out_clk=6,clkin1_period=31.250,clkin2_period=31.250,use_power_down=false,use_reset=false,use_locked=false,use_inclk_stopped=false,use_status=false,use_freeze=false,use_clk_valid=false,feedback_type=SINGLE,clock_mgr_type=AUTO,manual_override=false}";
  -- Input clock buffering / unused connectors
  signal clkin1      : std_logic;
  -- Output clock buffering / unused connectors
  signal clkfbout         : std_logic;
  signal clkfbout_buf     : std_logic;
  signal clkout0          : std_logic;
  signal clkout1          : std_logic;
  signal clkout2          : std_logic;
  signal clkout3          : std_logic;
  signal clkout4          : std_logic;
  signal clkout5          : std_logic;
  -- Unused status signals
  signal locked_unused    : std_logic;

begin


  -- Input buffering
  --------------------------------------
  clkin1_buf : IBUFG
  port map
   (O => clkin1,
    I => CLK_32Mhz_in);


  -- Clocking primitive
  --------------------------------------
  -- Instantiation of the PLL primitive
  --    * Unused inputs are tied off
  --    * Unused outputs are labeled unused

  pll_base_inst : PLL_BASE
  generic map
   (BANDWIDTH            => "OPTIMIZED",
    CLK_FEEDBACK         => "CLKFBOUT",
    COMPENSATION         => "SYSTEM_SYNCHRONOUS",
    DIVCLK_DIVIDE        => 1,
    CLKFBOUT_MULT        => 25,
    CLKFBOUT_PHASE       => 0.000,
    CLKOUT0_DIVIDE       => 8,
    CLKOUT0_PHASE        => 0.000,
    CLKOUT0_DUTY_CYCLE   => 0.500,
    CLKOUT1_DIVIDE       => 16,
    CLKOUT1_PHASE        => 0.000,
    CLKOUT1_DUTY_CYCLE   => 0.500,
    CLKOUT2_DIVIDE       => 25,
    CLKOUT2_PHASE        => 0.000,
    CLKOUT2_DUTY_CYCLE   => 0.500,
    CLKOUT3_DIVIDE       => 32,
    CLKOUT3_PHASE        => 0.000,
    CLKOUT3_DUTY_CYCLE   => 0.500,
    CLKOUT4_DIVIDE       => 80,
    CLKOUT4_PHASE        => 0.000,
    CLKOUT4_DUTY_CYCLE   => 0.500,
    CLKOUT5_DIVIDE       => 100,
    CLKOUT5_PHASE        => 0.000,
    CLKOUT5_DUTY_CYCLE   => 0.500,
    CLKIN_PERIOD         => 31.250,
    REF_JITTER           => 0.010)
  port map
    -- Output clocks
   (CLKFBOUT            => clkfbout,
    CLKOUT0             => clkout0,
    CLKOUT1             => clkout1,
    CLKOUT2             => clkout2,
    CLKOUT3             => clkout3,
    CLKOUT4             => clkout4,
    CLKOUT5             => clkout5,
    LOCKED              => locked_unused,
    RST                 => '0',
    -- Input clock control
    CLKFBIN             => clkfbout_buf,
    CLKIN               => clkin1);

  -- Output buffering
  -------------------------------------
  clkf_buf : BUFG
  port map
   (O => clkfbout_buf,
    I => clkfbout);


  clkout1_buf : BUFG
  port map
   (O   => CLK_100Mhz,
    I   => clkout0);



  clkout2_buf : BUFG
  port map
   (O   => CLK_50Mhz,
    I   => clkout1);
--CLK_50Mhz <= clkin1;

  clkout3_buf : BUFG
  port map
   (O   => CLK_32Mhz,
    I   => clkout2);
--CLK_32Mhz <= clkin1;

  clkout4_buf : BUFG
  port map
   (O   => CLK_25Mhz,
    I   => clkout3);

  clkout5_buf : BUFG
  port map
   (O   => CLK_10Mhz,
    I   => clkout4);

  clkout6_buf : BUFG
  port map
   (O   => CLK_8Mhz,
    I   => clkout5);

end xilinx;
