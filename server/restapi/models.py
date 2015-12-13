from __future__ import unicode_literals

from django.db import models

import datetime

class SensorData(models.Model):
    moised = models.IntegerField(default=0.0)
    temp_air = models.FloatField(default=0)
    temp_water = models.FloatField(default=0.0)
    light = models.FloatField(default=0.0)
    created = models.DateTimeField(auto_now_add=True)

