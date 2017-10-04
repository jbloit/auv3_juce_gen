#include "C74_GENPLUGIN.h"

namespace C74_GENPLUGIN {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_44;
	Delay m_delay_24;
	Delay m_delay_25;
	Delay m_delay_27;
	Delay m_delay_23;
	Delay m_delay_43;
	Delay m_delay_22;
	Delay m_delay_19;
	Delay m_delay_17;
	Delay m_delay_29;
	Delay m_delay_33;
	Delay m_delay_41;
	Delay m_delay_42;
	Delay m_delay_31;
	Delay m_delay_39;
	Delay m_delay_35;
	Delay m_delay_37;
	Delay m_delay_15;
	Delay m_delay_21;
	Delay m_delay_9;
	Delay m_delay_5;
	Delay m_delay_13;
	Delay m_delay_7;
	Delay m_delay_11;
	int __exception;
	int vectorsize;
	t_sample m_history_36;
	t_sample m_fb_3;
	t_sample m_history_34;
	t_sample m_history_40;
	t_sample m_damp_1;
	t_sample m_history_38;
	t_sample m_spread_2;
	t_sample samplerate;
	t_sample m_fb_4;
	t_sample m_history_30;
	t_sample m_history_16;
	t_sample m_history_12;
	t_sample m_history_20;
	t_sample m_history_18;
	t_sample m_history_32;
	t_sample m_history_10;
	t_sample m_history_26;
	t_sample m_history_8;
	t_sample m_history_6;
	t_sample m_history_28;
	t_sample m_history_14;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_damp_1 = ((t_sample)0.5);
		m_spread_2 = ((int)0);
		m_fb_3 = ((t_sample)0.5);
		m_fb_4 = ((t_sample)0.9);
		m_delay_5.reset("m_delay_5", ((int)2000));
		m_history_6 = ((int)0);
		m_delay_7.reset("m_delay_7", ((int)2000));
		m_history_8 = ((int)0);
		m_delay_9.reset("m_delay_9", ((int)2000));
		m_history_10 = ((int)0);
		m_delay_11.reset("m_delay_11", ((int)2000));
		m_history_12 = ((int)0);
		m_delay_13.reset("m_delay_13", ((int)2000));
		m_history_14 = ((int)0);
		m_delay_15.reset("m_delay_15", ((int)2000));
		m_history_16 = ((int)0);
		m_delay_17.reset("m_delay_17", ((int)2000));
		m_history_18 = ((int)0);
		m_delay_19.reset("m_delay_19", ((int)2000));
		m_history_20 = ((int)0);
		m_delay_21.reset("m_delay_21", ((int)2000));
		m_delay_22.reset("m_delay_22", ((int)2000));
		m_delay_23.reset("m_delay_23", ((int)2000));
		m_delay_24.reset("m_delay_24", ((int)2000));
		m_delay_25.reset("m_delay_25", ((int)2000));
		m_history_26 = ((int)0);
		m_delay_27.reset("m_delay_27", ((int)2000));
		m_history_28 = ((int)0);
		m_delay_29.reset("m_delay_29", ((int)2000));
		m_history_30 = ((int)0);
		m_delay_31.reset("m_delay_31", ((int)2000));
		m_history_32 = ((int)0);
		m_delay_33.reset("m_delay_33", ((int)2000));
		m_history_34 = ((int)0);
		m_delay_35.reset("m_delay_35", ((int)2000));
		m_history_36 = ((int)0);
		m_delay_37.reset("m_delay_37", ((int)2000));
		m_history_38 = ((int)0);
		m_delay_39.reset("m_delay_39", ((int)2000));
		m_history_40 = ((int)0);
		m_delay_41.reset("m_delay_41", ((int)2000));
		m_delay_42.reset("m_delay_42", ((int)2000));
		m_delay_43.reset("m_delay_43", ((int)2000));
		m_delay_44.reset("m_delay_44", ((int)2000));
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_643 = (m_fb_3 * ((t_sample)0.5));
		t_sample mul_586 = (m_fb_3 * ((t_sample)0.5));
		t_sample add_629 = (((int)225) + m_spread_2);
		t_sample add_572 = (((int)225) + m_spread_2);
		t_sample add_631 = (((int)341) + m_spread_2);
		t_sample add_574 = (((int)341) + m_spread_2);
		t_sample add_641 = (((int)441) + m_spread_2);
		t_sample add_584 = (((int)441) + m_spread_2);
		t_sample add_627 = (((int)556) + m_spread_2);
		t_sample add_570 = (((int)556) + m_spread_2);
		t_sample damp_618 = m_damp_1;
		t_sample damp_612 = damp_618;
		t_sample damp_611 = damp_618;
		t_sample damp_613 = damp_618;
		t_sample damp_614 = damp_618;
		t_sample damp_615 = damp_618;
		t_sample damp_616 = damp_618;
		t_sample damp_617 = damp_618;
		t_sample damp_539 = damp_618;
		t_sample damp_546 = damp_618;
		t_sample damp_545 = damp_618;
		t_sample damp_544 = damp_618;
		t_sample damp_543 = damp_618;
		t_sample damp_542 = damp_618;
		t_sample damp_541 = damp_618;
		t_sample damp_540 = damp_618;
		t_sample add_634 = (((int)1557) + m_spread_2);
		t_sample rsub_547 = (((int)1) - damp_612);
		t_sample add_633 = (((int)1617) + m_spread_2);
		t_sample rsub_655 = (((int)1) - damp_611);
		t_sample add_635 = (((int)1491) + m_spread_2);
		t_sample rsub_667 = (((int)1) - damp_613);
		t_sample add_636 = (((int)1422) + m_spread_2);
		t_sample rsub_679 = (((int)1) - damp_614);
		t_sample add_637 = (((int)1356) + m_spread_2);
		t_sample rsub_691 = (((int)1) - damp_615);
		t_sample add_638 = (((int)1277) + m_spread_2);
		t_sample rsub_703 = (((int)1) - damp_616);
		t_sample add_639 = (((int)1188) + m_spread_2);
		t_sample rsub_710 = (((int)1) - damp_617);
		t_sample add_640 = (((int)1116) + m_spread_2);
		t_sample rsub_722 = (((int)1) - damp_618);
		t_sample add_576 = (((int)1617) + m_spread_2);
		t_sample rsub_752 = (((int)1) - damp_539);
		t_sample add_583 = (((int)1116) + m_spread_2);
		t_sample rsub_764 = (((int)1) - damp_546);
		t_sample add_582 = (((int)1188) + m_spread_2);
		t_sample rsub_776 = (((int)1) - damp_545);
		t_sample add_581 = (((int)1277) + m_spread_2);
		t_sample rsub_788 = (((int)1) - damp_544);
		t_sample add_580 = (((int)1356) + m_spread_2);
		t_sample rsub_800 = (((int)1) - damp_543);
		t_sample add_579 = (((int)1422) + m_spread_2);
		t_sample rsub_812 = (((int)1) - damp_542);
		t_sample add_578 = (((int)1491) + m_spread_2);
		t_sample rsub_828 = (((int)1) - damp_541);
		t_sample add_577 = (((int)1557) + m_spread_2);
		t_sample rsub_834 = (((int)1) - damp_540);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_645 = (in1 * ((t_sample)0.015));
			t_sample tap_554 = m_delay_5.read_linear(add_634);
			t_sample gen_625 = tap_554;
			t_sample mul_552 = (tap_554 * damp_612);
			t_sample mul_550 = (m_history_6 * rsub_547);
			t_sample add_551 = (mul_552 + mul_550);
			t_sample mul_548 = (add_551 * m_fb_4);
			t_sample add_555 = (mul_645 + mul_548);
			t_sample history_549_next_556 = fixdenorm(add_551);
			t_sample tap_654 = m_delay_7.read_linear(add_633);
			t_sample gen_644 = tap_654;
			t_sample mul_650 = (tap_654 * damp_611);
			t_sample mul_647 = (m_history_8 * rsub_655);
			t_sample add_653 = (mul_650 + mul_647);
			t_sample mul_646 = (add_653 * m_fb_4);
			t_sample add_652 = (mul_645 + mul_646);
			t_sample history_549_next_651 = fixdenorm(add_653);
			t_sample tap_665 = m_delay_9.read_linear(add_635);
			t_sample gen_624 = tap_665;
			t_sample mul_662 = (tap_665 * damp_613);
			t_sample mul_659 = (m_history_10 * rsub_667);
			t_sample add_666 = (mul_662 + mul_659);
			t_sample mul_658 = (add_666 * m_fb_4);
			t_sample add_664 = (mul_645 + mul_658);
			t_sample history_549_next_663 = fixdenorm(add_666);
			t_sample tap_678 = m_delay_11.read_linear(add_636);
			t_sample gen_623 = tap_678;
			t_sample mul_674 = (tap_678 * damp_614);
			t_sample mul_671 = (m_history_12 * rsub_679);
			t_sample add_677 = (mul_674 + mul_671);
			t_sample mul_670 = (add_677 * m_fb_4);
			t_sample add_676 = (mul_645 + mul_670);
			t_sample history_549_next_675 = fixdenorm(add_677);
			t_sample tap_690 = m_delay_13.read_linear(add_637);
			t_sample gen_622 = tap_690;
			t_sample mul_686 = (tap_690 * damp_615);
			t_sample mul_683 = (m_history_14 * rsub_691);
			t_sample add_689 = (mul_686 + mul_683);
			t_sample mul_682 = (add_689 * m_fb_4);
			t_sample add_687 = (mul_645 + mul_682);
			t_sample history_549_next_688 = fixdenorm(add_689);
			t_sample tap_702 = m_delay_15.read_linear(add_638);
			t_sample gen_621 = tap_702;
			t_sample mul_698 = (tap_702 * damp_616);
			t_sample mul_695 = (m_history_16 * rsub_703);
			t_sample add_701 = (mul_698 + mul_695);
			t_sample mul_694 = (add_701 * m_fb_4);
			t_sample add_699 = (mul_645 + mul_694);
			t_sample history_549_next_700 = fixdenorm(add_701);
			t_sample tap_707 = m_delay_17.read_linear(add_639);
			t_sample gen_620 = tap_707;
			t_sample mul_713 = (tap_707 * damp_617);
			t_sample mul_714 = (m_history_18 * rsub_710);
			t_sample add_711 = (mul_713 + mul_714);
			t_sample mul_706 = (add_711 * m_fb_4);
			t_sample add_709 = (mul_645 + mul_706);
			t_sample history_549_next_712 = fixdenorm(add_711);
			t_sample tap_719 = m_delay_19.read_linear(add_640);
			t_sample gen_619 = tap_719;
			t_sample mul_725 = (tap_719 * damp_618);
			t_sample mul_726 = (m_history_20 * rsub_722);
			t_sample add_723 = (mul_725 + mul_726);
			t_sample mul_718 = (add_723 * m_fb_4);
			t_sample add_721 = (mul_645 + mul_718);
			t_sample history_549_next_724 = fixdenorm(add_723);
			t_sample add_642 = ((((((((gen_619 + gen_620) + gen_621) + gen_622) + gen_623) + gen_624) + gen_644) + gen_625) + ((int)0));
			t_sample tap_568 = m_delay_21.read_linear(add_627);
			t_sample sub_564 = (add_642 - tap_568);
			t_sample mul_566 = (tap_568 * mul_643);
			t_sample add_565 = (add_642 + mul_566);
			t_sample tap_730 = m_delay_22.read_linear(add_641);
			t_sample sub_734 = (sub_564 - tap_730);
			t_sample mul_733 = (tap_730 * mul_643);
			t_sample add_731 = (sub_564 + mul_733);
			t_sample tap_736 = m_delay_23.read_linear(add_631);
			t_sample sub_740 = (sub_734 - tap_736);
			t_sample mul_739 = (tap_736 * mul_643);
			t_sample add_737 = (sub_734 + mul_739);
			t_sample tap_742 = m_delay_24.read_linear(add_629);
			t_sample sub_746 = (sub_740 - tap_742);
			t_sample mul_745 = (tap_742 * mul_643);
			t_sample add_743 = (sub_740 + mul_745);
			t_sample out1 = sub_746;
			t_sample mul_588 = (in2 * ((t_sample)0.015));
			t_sample tap_749 = m_delay_25.read_linear(add_576);
			t_sample gen_587 = tap_749;
			t_sample mul_755 = (tap_749 * damp_539);
			t_sample mul_756 = (m_history_26 * rsub_752);
			t_sample add_753 = (mul_755 + mul_756);
			t_sample mul_748 = (add_753 * m_fb_4);
			t_sample add_751 = (mul_588 + mul_748);
			t_sample history_549_next_754 = fixdenorm(add_753);
			t_sample tap_761 = m_delay_27.read_linear(add_583);
			t_sample gen_557 = tap_761;
			t_sample mul_767 = (tap_761 * damp_546);
			t_sample mul_768 = (m_history_28 * rsub_764);
			t_sample add_765 = (mul_767 + mul_768);
			t_sample mul_760 = (add_765 * m_fb_4);
			t_sample add_763 = (mul_588 + mul_760);
			t_sample history_549_next_766 = fixdenorm(add_765);
			t_sample tap_773 = m_delay_29.read_linear(add_582);
			t_sample gen_558 = tap_773;
			t_sample mul_779 = (tap_773 * damp_545);
			t_sample mul_780 = (m_history_30 * rsub_776);
			t_sample add_777 = (mul_779 + mul_780);
			t_sample mul_772 = (add_777 * m_fb_4);
			t_sample add_775 = (mul_588 + mul_772);
			t_sample history_549_next_778 = fixdenorm(add_777);
			t_sample tap_785 = m_delay_31.read_linear(add_581);
			t_sample gen_559 = tap_785;
			t_sample mul_791 = (tap_785 * damp_544);
			t_sample mul_792 = (m_history_32 * rsub_788);
			t_sample add_789 = (mul_791 + mul_792);
			t_sample mul_784 = (add_789 * m_fb_4);
			t_sample add_787 = (mul_588 + mul_784);
			t_sample history_549_next_790 = fixdenorm(add_789);
			t_sample tap_797 = m_delay_33.read_linear(add_580);
			t_sample gen_560 = tap_797;
			t_sample mul_804 = (tap_797 * damp_543);
			t_sample mul_801 = (m_history_34 * rsub_800);
			t_sample add_802 = (mul_804 + mul_801);
			t_sample mul_796 = (add_802 * m_fb_4);
			t_sample add_799 = (mul_588 + mul_796);
			t_sample history_549_next_803 = fixdenorm(add_802);
			t_sample tap_809 = m_delay_35.read_linear(add_579);
			t_sample gen_561 = tap_809;
			t_sample mul_816 = (tap_809 * damp_542);
			t_sample mul_813 = (m_history_36 * rsub_812);
			t_sample add_814 = (mul_816 + mul_813);
			t_sample mul_808 = (add_814 * m_fb_4);
			t_sample add_811 = (mul_588 + mul_808);
			t_sample history_549_next_815 = fixdenorm(add_814);
			t_sample tap_825 = m_delay_37.read_linear(add_578);
			t_sample gen_562 = tap_825;
			t_sample mul_824 = (tap_825 * damp_541);
			t_sample mul_829 = (m_history_38 * rsub_828);
			t_sample add_822 = (mul_824 + mul_829);
			t_sample mul_827 = (add_822 * m_fb_4);
			t_sample add_826 = (mul_588 + mul_827);
			t_sample history_549_next_823 = fixdenorm(add_822);
			t_sample tap_838 = m_delay_39.read_linear(add_577);
			t_sample gen_563 = tap_838;
			t_sample mul_837 = (tap_838 * damp_540);
			t_sample mul_841 = (m_history_40 * rsub_834);
			t_sample add_835 = (mul_837 + mul_841);
			t_sample mul_840 = (add_835 * m_fb_4);
			t_sample add_839 = (mul_588 + mul_840);
			t_sample history_549_next_836 = fixdenorm(add_835);
			t_sample add_585 = ((((((((gen_563 + gen_562) + gen_561) + gen_560) + gen_559) + gen_558) + gen_557) + gen_587) + ((int)0));
			t_sample tap_845 = m_delay_41.read_linear(add_570);
			t_sample sub_844 = (add_585 - tap_845);
			t_sample mul_846 = (tap_845 * mul_586);
			t_sample add_847 = (add_585 + mul_846);
			t_sample tap_851 = m_delay_42.read_linear(add_584);
			t_sample sub_850 = (sub_844 - tap_851);
			t_sample mul_852 = (tap_851 * mul_586);
			t_sample add_853 = (sub_844 + mul_852);
			t_sample tap_857 = m_delay_43.read_linear(add_574);
			t_sample sub_856 = (sub_850 - tap_857);
			t_sample mul_858 = (tap_857 * mul_586);
			t_sample add_859 = (sub_850 + mul_858);
			t_sample tap_863 = m_delay_44.read_linear(add_572);
			t_sample sub_862 = (sub_856 - tap_863);
			t_sample mul_864 = (tap_863 * mul_586);
			t_sample add_865 = (sub_856 + mul_864);
			t_sample out2 = sub_862;
			m_delay_5.write(add_555);
			m_delay_44.write(add_865);
			m_delay_43.write(add_859);
			m_delay_42.write(add_853);
			m_delay_41.write(add_847);
			m_history_40 = history_549_next_836;
			m_delay_39.write(add_839);
			m_history_38 = history_549_next_823;
			m_delay_37.write(add_826);
			m_history_36 = history_549_next_815;
			m_delay_35.write(add_811);
			m_history_34 = history_549_next_803;
			m_delay_33.write(add_799);
			m_history_32 = history_549_next_790;
			m_delay_31.write(add_787);
			m_history_30 = history_549_next_778;
			m_delay_29.write(add_775);
			m_history_28 = history_549_next_766;
			m_delay_27.write(add_763);
			m_history_26 = history_549_next_754;
			m_delay_25.write(add_751);
			m_delay_24.write(add_743);
			m_delay_23.write(add_737);
			m_delay_22.write(add_731);
			m_delay_21.write(add_565);
			m_history_20 = history_549_next_724;
			m_delay_19.write(add_721);
			m_history_18 = history_549_next_712;
			m_delay_17.write(add_709);
			m_history_16 = history_549_next_700;
			m_delay_15.write(add_699);
			m_history_14 = history_549_next_688;
			m_delay_13.write(add_687);
			m_history_12 = history_549_next_675;
			m_delay_11.write(add_676);
			m_history_10 = history_549_next_663;
			m_delay_9.write(add_664);
			m_history_8 = history_549_next_651;
			m_delay_7.write(add_652);
			m_history_6 = history_549_next_556;
			m_delay_5.step();
			m_delay_7.step();
			m_delay_9.step();
			m_delay_11.step();
			m_delay_13.step();
			m_delay_15.step();
			m_delay_17.step();
			m_delay_19.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			m_delay_25.step();
			m_delay_27.step();
			m_delay_29.step();
			m_delay_31.step();
			m_delay_33.step();
			m_delay_35.step();
			m_delay_37.step();
			m_delay_39.step();
			m_delay_41.step();
			m_delay_42.step();
			m_delay_43.step();
			m_delay_44.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_damp(t_param _value) {
		m_damp_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(t_param _value) {
		m_spread_2 = (_value < 0 ? 0 : (_value > 400 ? 400 : _value));
	};
	inline void set_fb2(t_param _value) {
		m_fb_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_fb1(t_param _value) {
		m_fb_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_damp(value); break;
		case 1: self->set_fb1(value); break;
		case 2: self->set_fb2(value); break;
		case 3: self->set_spread(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damp_1; break;
		case 1: *value = self->m_fb_4; break;
		case 2: *value = self->m_fb_3; break;
		case 3: *value = self->m_spread_2; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_damp_1")
	pi = self->__commonstate.params + 0;
	pi->name = "damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damp_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_fb_4")
	pi = self->__commonstate.params + 1;
	pi->name = "fb1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_fb_3")
	pi = self->__commonstate.params + 2;
	pi->name = "fb2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_spread_2")
	pi = self->__commonstate.params + 3;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 400;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // C74_GENPLUGIN::
