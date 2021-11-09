# -*- coding: UTF-8 -*-
"""
Urls for testResultApp
"""

from django.urls import path
from .views import TestResultView


app_name = 'testResultApp'
urlpatterns = [
    path('dummyInsert', TestResultView.as_view()),
    path('<givenTestId>', TestResultView.as_view()),
]
