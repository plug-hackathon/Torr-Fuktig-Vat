from rest_framework import viewsets

from .models import SensorData
from .serializers import SensorDataSerializer

from django.core.mail import send_mail

# Decorators
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator

from django.views import generic
from django.http import HttpResponse
from pprint import pprint

# Signals
from django.dispatch import receiver
from django.db.models.signals import pre_save

class SensorDataViewsets(viewsets.ModelViewSet):
    queryset = SensorData.objects.all()
    serializer_class = SensorDataSerializer

class PostTest(generic.View):
    @method_decorator(csrf_exempt)
    @csrf_exempt
    def dispatch(self, request, *args, **kwargs):
        print("In 'PostTest > dispatch'")
        return super(PostTest, self).dispatch(request, *args, **kwargs)

    @csrf_exempt
    def post(self, request, *args, **kwargs):
        req = request.__dict__['environ']['HTTP_USER_AGENT'].split(',')
        save_me = SensorData(
            moised=float(req[0]),
            temp_air=float(req[1])
        )
        save_me.save()
        pprint(save_me.__dict__)
        print('Now saved')

        return HttpResponse("OK")

@receiver(pre_save, sender=SensorData)
def pre_save_test(sender, instance, **kwargs):
    if instance.__dict__['temp_air'] > 40:
        print("TEMP: ", instance.__dict__['temp_air'])
        # send_mail("test subject", "test body", "from@test.com", ["to@test.com"], fail_silently=False)
