from django.contrib import admin

from .models import SensorData

class SensorDataAdmin(admin.ModelAdmin):
    model = SensorData
    list_display = ('moised', 'temp_air', 'temp_water', 'light', 'created')
    search_fields = ['moised', 'temp_air', 'temp_water', 'light', 'created']

admin.site.register(SensorData, SensorDataAdmin)
