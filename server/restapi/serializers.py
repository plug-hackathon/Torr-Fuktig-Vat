
from rest_framework import serializers

from .models import SensorData

class SensorDataSerializer(serializers.ModelSerializer):

    class Meta:
        model = SensorData
        fields = ('temp_air', 'temp_water', 'humidity', 'light', 'created')