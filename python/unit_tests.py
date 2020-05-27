#!/usr/bin/env python3
import pytest
import pysff
import numpy as np

def test_time():
    """
    Tests the time module.
    """
    # Try out the setters
    tf = pysff.Time()
    tf.set_year(2020)
    tf.set_month(1)
    tf.set_day_of_month(9)
    tf.set_hour(0)
    tf.set_minute(12)
    tf.set_second(8)
    tf.set_microsecond(800000)
    assert tf.get_epoch() == 1578528728.8, 'get epoch failed'
    tf2 = tf
    tf2.set_julian_day(9)
    assert tf2.get_epoch() == 1578528728.8, 'get epoch failed'
    # Do it the other way
    t = pysff.Time()
    t.set_epoch(1578528728.8)
    assert t.get_year() == 2020, 'get year failed'
    assert t.get_month() == 1, 'get month failed'
    assert t.get_day_of_month() == 9, 'get day of month failed'
    assert t.get_julian_day() == 9, 'get julian day failed'
    assert t.get_hour() == 0, 'get hour failed'
    assert t.get_minute() == 12, 'get minute failed'
    assert t.get_second() == 8, 'get second failed'
    assert t.get_microsecond() == 800000, 'get micro_second failed'
    # Add an hour
    tday = pysff.Time()
    tday.set_epoch(86400.1)
    tnew = t + tday 
    assert tnew.get_year() == 2020, 'get year failed'
    assert tnew.get_month() == 1, 'get month failed'
    assert tnew.get_day_of_month() == 10, 'get day of month failed'
    assert tnew.get_julian_day() == 10, 'get julian day failed'
    assert tnew.get_hour() == 0, 'get hour failed'
    assert tnew.get_minute() == 12, 'get minute failed'
    assert tnew.get_second() == 8, 'get second failed'
    assert tnew.get_microsecond() == 900000, 'get micro_second failed'

    tnew = t + 86400.1 
    assert tnew.get_year() == 2020, 'get year failed - add double'
    assert tnew.get_month() == 1, 'get month failed - add double'
    assert tnew.get_day_of_month() == 10, 'get day of month failed - add double'
    assert tnew.get_julian_day() == 10, 'get julian day failed - add double'
    assert tnew.get_hour() == 0, 'get hour failed - add double'
    assert tnew.get_minute() == 12, 'get minute failed - add double'
    assert tnew.get_second() == 8, 'get second failed - add double'
    assert tnew.get_microsecond() == 900000, 'get micro_second failed - add double'

    # Subtract half a day
    thalf = pysff.Time()
    thalf.set_epoch(43200)
    tsub = tnew - thalf
    assert tsub.get_year() == 2020, 'get year failed'
    assert tsub.get_month() == 1, 'get month failed'
    assert tsub.get_day_of_month() == 9, 'get day of month failed'
    assert tsub.get_julian_day() == 9, 'get julian day failed'
    assert tsub.get_hour() == 12, 'get hour failed'
    assert tsub.get_minute() == 12, 'get minute failed'
    assert tsub.get_second() == 8, 'get second failed'
    assert tsub.get_microsecond() == 900000, 'get micro_second failed'

    tsub = tnew - 43200
    assert tsub.get_year() == 2020, 'get year failed - sub double'
    assert tsub.get_month() == 1, 'get month failed - sub double'
    assert tsub.get_day_of_month() == 9, 'get day of month failed - sub double'
    assert tsub.get_julian_day() == 9, 'get julian day failed - sub double'
    assert tsub.get_hour() == 12, 'get hour failed - sub double'
    assert tsub.get_minute() == 12, 'get minute failed - sub double'
    assert tsub.get_second() == 8, 'get second failed - sub double'
    assert tsub.get_microsecond() == 900000, 'get micro_second failed - sub double'

def test_sac():
    sac = pysff.SAC()
    sac.read('data/debug.sac')
    assert sac.get_number_of_samples() == sac.get_integer_header(sac.Integer.npts), 'npts failed'
    assert sac.get_integer_header(sac.Integer.nvhdr) == 6, 'nvhdr failed'
    assert sac.get_number_of_samples() == 100, 'npts is wrong'
    assert (sac.get_sampling_period() - 0.005) < 1.e-7, 'sampling period is wrong'
    assert sac.get_sampling_period() == sac.get_float_header(sac.Float.delta), 'delta failed'
    assert sac.get_character_header(sac.Character.knetwk) == 'FK', 'knetwk is wrong'
    assert sac.get_character_header(sac.Character.kstnm) == 'NEW', 'kstnm is wrong'
    assert sac.get_character_header(sac.Character.kcmpnm) == 'HHZ', 'kcmpnm is wrong'
    assert sac.get_character_header(sac.Character.khole) == '10', 'khole is wrong'
    ref = np.arange(1, 101, 1) 
    data = sac.get_data()
    assert np.max(ref - data) < 1.e-7, 'couldnt recover data'

def test_silixa_segy():
    tg = pysff.SilixaSEGY.TraceGroup()
    tg.read("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy")
    assert tg.get_number_of_traces() == 1280, 'number of traces is wrong'
    trace = tg.get_trace(0)
    ts = trace.get_data()
    assert trace.get_sampling_rate() == 2000, 'sampling rate is wrong'
    assert len(ts) == 30000, 'number of samples is wrong'

def test_hypoinverse2000():
    sta = pysff.HypoInverse2000.StationArchiveLine()
    p_string = "RBU  UU  EHZ IPU0202003181320 2596 -14198        0                   0     218110 0      84 85227    300     D 02"
    s_string = "NOQ  UU  HHN    4202003181320             2689ES 2 -15   1424 0 24       0 1341210  14     199   251       0J L01"
    sta.unpack_string(p_string)
    assert sta.get_network_name() == "UU", 'network name failed'
    assert sta.get_station_name() == "RBU", 'station name failed'
    assert sta.get_channel_name() == "EHZ", 'channel name failed'
    assert sta.get_location_code() == "02",  'location code failed'

    assert sta.get_p_remark() == "IP", 'p remark failed';
    assert sta.get_first_motion() == 'U', 'first motion failed'
    assert sta.get_p_weight_code() ==  0, 'p weight code failed'
    pick_time = sta.get_p_pick_time()
    assert abs(pick_time.get_epoch() - 1584537625.96) < 1.e-2, 'p pick time failed'
    assert abs(sta.get_p_residual() - -0.14) < 1.e-2, 'p residual failed'
    assert abs(sta.get_p_weight_used() - 1.98) < 1.e-2, 'p weight failed'
    assert sta.get_p_delay_time() == 0, 'p delay time failed'
    assert abs(sta.get_epicentral_distance() - 21.8) < 1.e-1, 'epicentral distance failed'
    assert abs(sta.get_takeoff_angle() - 110) < 1.e-1, 'take off angle failed'
    assert abs(sta.get_p_importance() - 0.3) < 1.e-1, 'p importance failed'
    assert abs(sta.get_duration_magnitude() - 2.27) <  1.e-2, 'duration mag failed'
    assert not sta.have_amplitude_magnitude(), 'have amp mag failed'
    assert sta.get_duration_magnitude_label() == 'D', 'dur mag label failed'
    assert not sta.have_data_source_code(), 'have data source code failed'
    assert sta.get_duration_magnitude_weight_code() == 0, 'dur mag weight code failed'
    assert not sta.have_amplitude_magnitude_weight_code(), 'amp mag weight code failed'
    assert not sta.have_amplitude(), 'have amplitude failed'
    assert not sta.have_amplitude_units(), 'have amp units failed'
    assert abs(sta.get_azimuth() - 85) < 1.e-1, 'azimuth failed'
    assert not sta.have_period_of_amplitude_measurement(), 'have period failed'
    assert abs(sta.get_coda_duration() - 84) < 1.e-1
    assert sta.pack_string() == p_string, 'pack string failed'
    sta.clear()

    sta.unpack_string(s_string)
    assert sta.get_network_name() == "UU", 'network name failed'
    assert sta.get_station_name() == "NOQ", 'station name failed'
    assert sta.get_channel_name() == "HHN", 'channel name failed'
    assert sta.get_location_code() == "01",  'location code failed'
    assert sta.get_s_remark() == "ES", 's remark failed'
    assert not sta.have_first_motion(), 's not have first motion failed'
    pick_time = sta.get_s_pick_time()
    assert abs(pick_time.get_epoch() - 1584537626.89) < 1.e-1, 's pick time failed'
    assert abs(sta.get_s_residual() - -0.15) < 1.e-2, 's residual time failed'
    assert abs(sta.get_s_weight_used() - 0.24) < 1.e-2, 's weight used failed'
    assert sta.get_s_delay_time() == 0, 's delay time failed'
    assert abs(sta.get_epicentral_distance() - 13.4) < 1.e-1, 's epi distance failed'
    assert abs(sta.get_takeoff_angle()- 121) < 1.e-1, 's takeoff failed'
    assert sta.get_s_importance() ==  0, 's importance failed'
    assert abs(sta.get_amplitude_magnitude() - 2.51) < 1.e-2, 's amp mag failed'
    assert not sta.have_duration_magnitude(), 's have dur mag failed'
    assert sta.get_amplitude_magnitude_label() ==  'L', 'amp mag label failed'
    assert sta.get_data_source_code() == 'J', 'data source code failed'
    assert sta.get_amplitude_magnitude_weight_code() == 0, 's amp mag weight code failed'
    assert not sta.have_duration_magnitude_weight_code(), 's have dur mag weight code failed'
    assert abs(sta.get_amplitude() - 14.24) < 1.e-2, 'amplitude failed'
    assert sta.get_amplitude_units() == sta.AmplitudeUnits.peak_to_peak, 'amplitude units failed'
    assert abs(sta.get_azimuth() - 199) < 1.e-1, 's az failed'
    assert abs(sta.get_period_of_amplitude_measurement() - 0.14) < 1.e-2, 'period failed'
    assert not sta.have_coda_duration(), 's have coda duration failed'
    assert sta.pack_string() == s_string, 's pack string failed'

    ev_line = "202003181320217640 4594112  399  771    24 83  4  1633184  88154 5  44298     33    1  44  87  4     100    47       D 24 L237 20         60363637L237  20        5FUUP1"
    evl =  pysff.HypoInverse2000.EventSummaryLine()
    evl.unpack_string(ev_line)
    ot = evl.get_origin_time()
    assert abs(ot.get_epoch() - 1584537621.76) < 1.e-2, 'ot failed'
    assert abs(evl.get_latitude() - 40.7657) < 1.e-4, 'ev lat failed'
    lon = evl.get_longitude();
    if (lon > 180):
        lon = lon - 360
    assert abs(lon - -112.066) < 1.e-3, 'ev lon failed'
    assert abs(evl.get_depth() - 7.71 ) < 1.e-2
    assert evl.get_number_of_weighted_residuals() ==  24, 'nweighted resid failed'
    assert abs(evl.get_distance_to_closest_station() - 4) < 1.e-1, 'dmin failed'
    assert abs(evl.get_azimuthal_gap() - 83) < 1.e-1, 'azgap failed'
    assert abs(evl.get_residual_traveltime_rms() - 0.16) < 1.e-2, 'rms failed'
    assert abs(evl.get_preferred_magnitude() - 2.37) < 1.e-2, 'prefmag failed'
    assert evl.get_preferred_magnitude_label() == 'L', 'label failed'
    assert evl.get_number_of_s_weighted_residuals() == 1, 'nweighted s failed'
    assert evl.get_number_of_first_motions() == 4, 'nfm failed'
    assert evl.get_event_identifier() == 60363637, 'evid failed'
    line_out = evl.pack_string();
    print(line_out)
    print(ev_line)


if __name__ == "__main__":
    test_time()
    print("Passed time")
    test_sac()
    print("Passed SAC")
    test_silixa_segy()
    print("Passed Silixa SEGY")
    test_hypoinverse2000()
    print("Passed hypoinverse")
