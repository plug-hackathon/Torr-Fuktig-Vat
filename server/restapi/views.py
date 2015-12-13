from rest_framework import viewsets

from .models import SensorData
from .serializers import SensorDataSerializer

# Decorators
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
import json
from django.views import generic
from django.http import HttpResponse
from pprint import pprint

class SensorDataViewsets(viewsets.ModelViewSet):
    queryset = SensorData.objects.all()
    serializer_class = SensorDataSerializer

class PostTest(generic.View):
    @method_decorator(csrf_exempt)
    def dispatch(self, request, *args, **kwargs):
        return super(PostTest, self).dispatch(request, *args, **kwargs)
      

    def post(self, request, *args, **kwargs):
        req = request.__dict__['environ']['HTTP_USER_AGENT'].split(',')
        save_me = SensorData(
            temp_air=float(req[0]),
            temp_water=float(req[1]),
            humidity=float(req[2]),
            light=float(req[3])
        )
        save_me.save()
        pprint(save_me.__dict__)
        print('Now saved')

        return HttpResponse("OK")
