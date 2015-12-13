
from rest_framework import serializers

from .models import SensorData

class SensorDataSerializer(serializers.ModelSerializer):

    class Meta:
        model = SensorData
        fields = ('moised', 'temp_air', 'temp_water', 'light', 'created')
