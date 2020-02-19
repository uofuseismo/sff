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

if __name__ == "__main__":
    test_time()
    test_sac()
    test_silixa_segy()
