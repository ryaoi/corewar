from django.urls import path
from . import views

urlpatterns = [
        path('', views.index, name='index'),
        path('play/', views.play, name='play'),
        path('<int:cycle>/show/', views.show_cycle, name='show_cycle'),
        path('prepare/', views.prepare, name='prepare'),
        path('play/update/', views.update, name='update'),
        ]
