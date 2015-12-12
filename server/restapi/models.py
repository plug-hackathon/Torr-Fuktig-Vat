from __future__ import unicode_literals

from django.db import models

import datetime

class SensorData(models.Model):
    temp_air = models.IntegerField(default=0)
    temp_water = models.IntegerField(default=0)
    humidity = models.IntegerField(default=0)
    light = models.IntegerField(default=0)
    created = models.DateField(auto_now_add=True)

