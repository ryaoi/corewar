from django.urls import path
from . import views

urlpatterns = [
        path('', views.index, name='index'),
        path('<int:cycle>/play/', views.play_cycle, name='play_cycle'),
        path('play/', views.play, name='play'),
        ]
