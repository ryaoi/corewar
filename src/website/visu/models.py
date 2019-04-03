from django.db import models

class logs(models.Model):
    log1 = models.TextField(max_length=100, default="", null=True)
    log2 = models.TextField(max_length=100, default="", null=True)
    log3 = models.TextField(max_length=100, default="", null=True)
    log4 = models.TextField(max_length=100, default="", null=True)
    log5 = models.TextField(max_length=100, default="", null=True)
    log6 = models.TextField(max_length=100, default="", null=True)
    log7 = models.TextField(max_length=100, default="", null=True) 

class memory(models.Model):
    screen = models.TextField(max_length=4500, default="", null=True)


