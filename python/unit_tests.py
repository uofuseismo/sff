#!/usr/bin/env python3
import pytest
import pysff
import numpy as np

def test_time():
    """
    Tests the time module.
    """
    t = pysff.Time()
    t.epoch = 1578528728.8
    assert t.year == 2020, 'get year failed'
    assert t.month == 1, 'get month failed'
    assert t.day_of_month == 9, 'get day of month failed'
    assert t.julian_day == 9, 'get julian day failed'
    assert t.hour == 0, 'get hour failed'
    assert t.minute == 12, 'get minute failed'
    assert t.second == 8, 'get second failed'
    assert t.micro_second == 800000, 'get micro_second failed'
    # Add an hour
    tday = pysff.Time()
    tday.epoch = 86400.1
    tnew = t + tday 
    assert tnew.year == 2020, 'get year failed'
    assert tnew.month == 1, 'get month failed'
    assert tnew.day_of_month == 10, 'get day of month failed'
    assert tnew.julian_day == 10, 'get julian day failed'
    assert tnew.hour == 0, 'get hour failed'
    assert tnew.minute == 12, 'get minute failed'
    assert tnew.second == 8, 'get second failed'
    assert tnew.micro_second == 900000, 'get micro_second failed'

    tnew = t + 86400.1 
    assert tnew.year == 2020, 'get year failed - add double'
    assert tnew.month == 1, 'get month failed - add double'
    assert tnew.day_of_month == 10, 'get day of month failed - add double'
    assert tnew.julian_day == 10, 'get julian day failed - add double'
    assert tnew.hour == 0, 'get hour failed - add double'
    assert tnew.minute == 12, 'get minute failed - add double'
    assert tnew.second == 8, 'get second failed - add double'
    assert tnew.micro_second == 900000, 'get micro_second failed - add double'

    # Subtract half a day
    thalf = pysff.Time()
    thalf.epoch = 43200
    tsub = tnew - thalf
    assert tsub.year == 2020, 'get year failed'
    assert tsub.month == 1, 'get month failed'
    assert tsub.day_of_month == 9, 'get day of month failed'
    assert tsub.julian_day == 9, 'get julian day failed'
    assert tsub.hour == 12, 'get hour failed'
    assert tsub.minute == 12, 'get minute failed'
    assert tsub.second == 8, 'get second failed'
    assert tsub.micro_second == 900000, 'get micro_second failed'

    tsub = tnew - 43200
    assert tsub.year == 2020, 'get year failed - sub double'
    assert tsub.month == 1, 'get month failed - sub double'
    assert tsub.day_of_month == 9, 'get day of month failed - sub double'
    assert tsub.julian_day == 9, 'get julian day failed - sub double'
    assert tsub.hour == 12, 'get hour failed - sub double'
    assert tsub.minute == 12, 'get minute failed - sub double'
    assert tsub.second == 8, 'get second failed - sub double'
    assert tsub.micro_second == 900000, 'get micro_second failed - sub double'

def test_sac():
    sac = pysff.SAC()
    sac.read('data/debug.sac')
    assert sac.number_of_samples == sac.get_integer_header(sac.Integer.npts), 'npts failed'
    assert sac.get_integer_header(sac.Integer.nvhdr) == 6, 'nvhdr failed'
    assert sac.number_of_samples == 100, 'npts is wrong'
    assert (sac.sampling_period - 0.005) < 1.e-7, 'sampling period is wrong'
    assert sac.sampling_period == sac.get_float_header(sac.Float.delta), 'delta failed'
    assert sac.get_character_header(sac.Character.knetwk) == 'FK', 'knetwk is wrong'
    assert sac.get_character_header(sac.Character.kstnm) == 'NEW', 'kstnm is wrong'
    assert sac.get_character_header(sac.Character.kcmpnm) == 'HHZ', 'kcmpnm is wrong'
    assert sac.get_character_header(sac.Character.khole) == '10', 'khole is wrong'
    ref = np.arange(1, 101, 1) 
    data = sac.data
    assert np.max(ref - data) < 1.e-7, 'couldnt recover data'

if __name__ == "__main__":
    test_time()
    test_sac()
