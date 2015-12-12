from django.contrib import admin

from .models import SensorData

class SensorDataAdmin(admin.ModelAdmin):
    model = SensorData
    list_display = ('temp_air', 'temp_water', 'humidity', 'light', 'created')
    search_fields = ['temp_air', 'temp_water', 'humidity', 'light', 'created']


admin.site.register(SensorData, SensorDataAdmin)