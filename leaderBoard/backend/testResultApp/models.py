from django.db import models

# Create your models here.
# Create your models here.
class TestResultRecord(models.Model):
	studentName = models.TextField()
	result = models.FloatField()
	testId = models.IntegerField()