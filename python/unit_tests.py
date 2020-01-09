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

if __name__ == "__main__":
    test_time()
