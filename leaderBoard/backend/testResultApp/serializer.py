# -*- coding: UTF-8 -*-

"""
Here defines model serializers.
"""

from rest_framework import serializers
from .models import TestResultRecord


class TestResultRecordSerializer(serializers.ModelSerializer):
    """
    Serializer that serializes/deserializes UserInfo object
    """
    model = TestResultRecord

    class Meta:
        """
        Meta Information
        """
        model = TestResultRecord
        fields = (
            'studentName',
            'result',
            'testId',
        )
